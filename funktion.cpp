// funktion.cpp
// W. Boeck, 00-09-16
// "Uebersetzung" eines PASCAL Programms
// aus ct8912250 (ct 12/89 S. 250 ff)
//#include <vcl/vcl.h>
#include <ctype.h>  // fuer tuupper()
#include "funktion.h"

/* PASCAL-CODE, wird erstzt durch destruktor
PROCEDURE DeleteTree(VAR p : tFunktion);
  (* loescht einen (Teil-)Baum und gibt seinen *)
  (* Speicherplatz frei                        *)
BEGIN
  IF p<>NIL THEN BEGIN
    DeleteTree(p^.LChild);
    DeleteTree(p^.RChild);
    IF (p^.Operator = #0) THEN BEGIN
      DISPOSE(p^.Operand); DISPOSE(p);
      p := NIL
    END
    ELSE BEGIN DISPOSE(p); p := NIL
    END
  END
END;
*/
//-----------struct tKnoten ------------
tKnoten::tKnoten(): operat(0), operand(0.0) , lChild(NULL), rChild(NULL)
{} //tKnoten()

/* // ersetzen durch Konstruktor
PROCEDURE NeueWurzel(VAR Wurzel : tFunktion; VAR F : STRING);
(* alte Wurzel wird linker Sohn *)
VAR hilf : tFunktion;
BEGIN
  NEW(hilf);
  hilf^.LChild := Wurzel;
  Wurzel := hilf;
  Wurzel^.RChild := NIL;
  Wurzel^.Operator := aktChar;
  Wurzel^.Operand  := NIL;
  NextChar(aktPos,F)
END;
!!! VAR F rausnehmen !!!
*/
tKnoten::tKnoten(tKnoten *wurzel, char operat): operat(operat), operand(0.0) , lChild(wurzel), rChild(NULL)
{
    wurzel = this; // neuer Knoten an wurzel des uebergebenen Baums
} //tKnoten(tKnoten &tKnoten, char *F)

tKnoten::~tKnoten() // Destruktor, eruebrigt rekursive Prozedur DeleteTree()
{
    if (lChild != NULL)
        delete lChild;
    if (rChild != NULL)
        delete rChild;
} // ~tKnoten()

//-----------class Funktion ------------

const char Funktion::fehlerMeldung[] [30] =
{
    "schliessende Klammer erwartet",
    "oeffnende Klammer erwartett",
    "Fehler beim Einlesen der Zahl",
    "unerwartetes Ende der Eingabe",
    "Zeichen hier nicht erwartet"
};

Funktion::Funktion() : x(0.0),success(false), fehler(false), aktPos(0), fehlerArt(-1), aktChar('\0'), optimiere(teilBaum), F1(NULL), errStream(NULL)
{
} //Funktion()

bool Funktion::initBaum
(
    const char *F, // das ist der FunktionsString
    ostream *errStr, // Fehlermeldung bzw. "Funktion OK"   default = NULL
    eOptimiere opt // default = teilBaum
)
{
    //strncpy(orgFStr, F, STR_SIZE - 1);

    errStream = errStr;
    optimiere = opt;
    strncpy(FStr, F, STR_SIZE - 1);
    tKnoten *baumWurzel = NULL;
    baumWurzel = baueBaum(FStr);
    if (F1 != NULL)
        delete F1;
    F1 = baumWurzel;
    return fehler;
}


void Funktion::vereinfache (tKnotenPtr &p)
{
    tKnoten *hilf;

    if (p != NULL)
    {
        vereinfache(p->lChild);
        vereinfache(p->rChild);
        if ((optimiere & teilBaum) != 0)
        {
            // aus - (-Baum) wird Baum
            if (p->operat == 's' && p->operat == p->lChild->operat == 's')
            {
                hilf = p->lChild->lChild;
                myDelete(p->lChild);
                myDelete(p);
                p = hilf;
            }
            // aus Baum1 + (-Baum2) wird Baum1 - Baum2
            if (p->operat == '+' && p->rChild->operat == 's')
            {
                hilf = p->rChild->lChild;
                myDelete(p->rChild);
                p->rChild = hilf;
                p->operat = '-';
            }
            // aus Baum1 - (-Baum2) wird Baum1 + Baum2
            if (p->operat == '-' && p->rChild->operat == 's')
            {
                hilf = p->rChild->lChild;
                myDelete(p->rChild);
                p->rChild = hilf;
                p->operat = '+';
            }
            // aus -Baum1 + Baum2 wird Baum2 - Baum1
            if (p->operat == '+' && p->lChild->operat == 's')
            {
                hilf = p->lChild->lChild;
                myDelete(p->lChild);
                p->lChild = p->rChild;
                p->rChild = hilf;
                p->operat = '-';
            }
        }  // if ((optimiere & teilBaum)!= 0)
        /*
        hier koennte man noch einen IF-Zweig einfuegen, der konstante
      Teilbaeume berechnet; aus x*3*5 sollte also x*15 werden...
        */
        if ((optimiere & konstanten) == 0)
            return; // raus, wenn kontanten nicht optimiert werden sollen
        double ergebnis;
        if (p->operat == '\1')
            return;
        // nur dann reingehen, wenn lChild und rChild auf Konstanten zeigen
        if (p->lChild == NULL || p->lChild->operat !=  '\0')
            return;
        if (p->rChild == NULL || p->rChild->operat !=  '\0')
            return;
        ergebnis = f(p);
        myDelete(p->lChild);
        //p->lChild = NULL;
        myDelete(p->rChild);
        //p->rChild = NULL;
        p->operat = '\0';
        p->operand = ergebnis;
    }// if (p != NULL)
} //vereinfache (*tKnoten p);

void Funktion::getNumber(char *F, unsigned int &posi, char *fHelp)
{
    char help[] = "x"; // strcat mit char ist in C nicht !!
    *fHelp = '\0'; // Nullstring
    while (posi < strlen(F) && F[posi] >= '0' && F[posi] <= '9')
    {
        *help = F[posi]; strcat(fHelp, help);
        posi++;
    }
    // Auch Komma alz Dezimaltrenner zulassen !!
    if(posi < strlen(F)  && (F[posi] == '.' ||F[posi] == ',') )
    {
        // *help = F[posi]; strcat(fHelp, help);
        *help = '.'; strcat(fHelp, help);
        posi++;
    }
    while (posi < strlen(F) && F[posi] >= '0' && F[posi] <= '9')
    {
        *help = F[posi]; strcat(fHelp, help);
        posi++;
    }
    if(posi < strlen(F)  && (F[posi] == 'e' || F[posi] == 'E'))
    {
        *help = F[posi]; strcat(fHelp, help);
        posi++;
        if(posi < strlen(F)  && (F[posi] == '+' || F[posi] == '-'))
        {
            *help = F[posi]; strcat(fHelp, help);
            posi++;
        } // if
        while (posi < strlen(F) && F[posi] >= '0' && F[posi] <= '9')
        {
            *help = F[posi]; strcat(fHelp, help);
            posi++;
        }
    } // if(posi < strlen(F)  && (F[posi] == 'e') || (F[posi] == 'E'))
} //getNumber(char *F, int &posi, char *fHelp

/*
PROCEDURE NextChar(start : INTEGER; VAR F : STRING);
(* ueberspringt Leerzeichen und liefert in globaler Variable   *)
(* aktChar das Zeichen an Position aktPos aus F; wird das Ende *)
(* von F erreicht, so steht #0 in aktChar                      *)
BEGIN
  IF start > Length(F) THEN aktChar := #0
  ELSE BEGIN
    REPEAT                (* Blanks in Eingabe ueberspringen       *)
      INC(start)
    UNTIL (F[start] <> ' ') OR (start >= Length(F));
    IF start <= Length(F) THEN BEGIN
      aktPos := start;    (* Zeichen gefunden *)
      aktChar := F[aktPos] END
    ELSE INC(aktPos)      (* falls Rest leer nur eins weitersetzen *)
  END                     (* ==> Fehler hinter letztem Buchstaben  *)
END;
*/
void Funktion::nextChar(int start, char *F)
{
    int len = strlen(F);
    if(start >= len)
        aktChar = '\0';
    else
    {
        do
        {
            start++;
        } while ( ! (F[start] != ' ' || start >= len - 1)); // REPEAT UNTIL Falle
        if( start <= len - 1)
        {
            aktPos = start;
            aktChar = F[aktPos];
        }
        else
            aktPos++;
    }
} //nextChar(int start, char *F)

/*
Funktion Pos(w,F : STRING; s,l : INTEGER):BOOLEAN;
(* prueft, ob w an Position s in F steht,     *)
(* l ist die Anzahl der zu pruefenden Zeichen *)
VAR index : INTEGER; bool : BOOLEAN;
BEGIN
  IF Length(F) < s+l-1 THEN (* nur loslegen, wenn      *)
    Pos := FALSE
  ELSE BEGIN                (* String notw. Laenge hat *)
    bool := TRUE;
    FOR index := s TO s+l-1 DO
      bool := bool AND (w[index-s+1] = F[index]);
    Pos := bool
  END
END;
*/
bool Funktion::Pos(const char *w, const char *F, unsigned int s, int l)
{
    if (strlen(F) < s + l - 1) //*** pruefen
        return false;
    bool ret = true;
    for (unsigned int index = s; index <= s + l - 1; index++)
        ret = ret && (toupper(w[index - s]) == toupper(F[index]));
    return ret;
} // Pos(const char *w, const char *F, int s, int l)

/*
Funktion UnaereFunktion(VAR F : STRING; VAR Token : CHAR):BOOLEAN;
BEGIN           (* Rueckgabe TRUE, falls gefunden          *)
  Token := #0;  (* enthaelt Kodierung (Token) der Funktion *)
  (* WICHTIG: bei kuerzeren Bezeichnern, die in laengeren  *)
  (* enthalten sind, muss zuerst der lange abgefragt       *)
  (* werden, dehalb sinh vor sin und arctanh vor arctan    *)

  IF Pos('ln',F,aktPos,2) THEN Token := 'a'

  ELSE IF Pos('sinh',F,aktPos,4) THEN Token := 'j'
  ELSE IF Pos('cosh',F,aktPos,4) THEN Token := 'k'
  ELSE IF Pos('tanh',F,aktPos,4) THEN Token := 'l'
  ELSE IF Pos('sqrt',F,aktPos,4) THEN Token := 'm'
  ELSE IF Pos('frac',F,aktPos,4) THEN Token := 'n'

  ELSE IF Pos('log',F,aktPos,3) THEN Token := 'b'
  ELSE IF Pos('exp',F,aktPos,3) THEN Token := 'c'
  ELSE IF Pos('sin',F,aktPos,3) THEN Token := 'd'
  ELSE IF Pos('cos',F,aktPos,3) THEN Token := 'e'
  ELSE IF Pos('tan',F,aktPos,3) THEN Token := 'f'
  ELSE IF Pos('abs',F,aktPos,3) THEN Token := 'o'
  ELSE IF Pos('cot',F,aktPos,3) THEN Token := 'p'

  ELSE IF Pos('arctanh',F,aktPos,7) THEN Token := 'r'

  ELSE IF Pos('arcsin',F,aktPos,6) THEN Token := 'g'
  ELSE IF Pos('arccos',F,aktPos,6) THEN Token := 'h'
  ELSE IF Pos('arctan',F,aktPos,6) THEN Token := 'i'
  ELSE IF Pos('arccot',F,aktPos,6) THEN Token := 'q';


  CASE Token OF
     'a'              : BEGIN INC(aktPos,1); NextChar(aktPos,F); END;
     'b'..'f','o','p' : BEGIN INC(aktPos,2); NextChar(aktPos,F); END;
     'j'..'n'         : BEGIN INC(aktPos,3); NextChar(aktPos,F); END;
     'g'..'i','q'     : BEGIN INC(aktPos,5); NextChar(aktPos,F); END;
     'r'              : BEGIN INC(aktPos,6); NextChar(aktPos,F); END
    ELSE UnaereFunktion := FALSE (* keine gefunden *)
  END;
  IF Token <> #0 THEN UnaereFunktion := TRUE
END;
*/
bool Funktion::unaereFunktion(char *F, char &token)
{
    token = '\0';
    if (Pos("ln", F, aktPos, 2)) token = 'a';
    else if (Pos("sinh", F, aktPos, 4)) token = 'j';
    else if (Pos("cosh", F, aktPos, 4)) token = 'k';
    else if (Pos("tanh", F, aktPos, 4)) token = 'l';
    else if (Pos("sqrt", F, aktPos, 4)) token = 'm';
    else if (Pos("frac", F, aktPos, 4)) token = 'n';

    else if (Pos("log", F, aktPos, 3)) token = 'b';
    else if (Pos("exp", F, aktPos, 3)) token = 'c';
    else if (Pos("sin", F, aktPos, 3)) token = 'd';
    else if (Pos("cos", F, aktPos, 3)) token = 'e';
    else if (Pos("tan", F, aktPos, 3)) token = 'f';
    else if (Pos("abs", F, aktPos, 3)) token = 'o';
    else if (Pos("cot", F, aktPos, 3)) token = 'p';

    else if (Pos("arctanh", F, aktPos, 7)) token = 'r';

    else if (Pos("arcsin", F, aktPos, 6)) token = 'g';
    else if (Pos("arccos", F, aktPos, 6)) token = 'h';
    else if (Pos("arctan", F, aktPos, 6)) token = 'i';
    else if (Pos("arccot", F, aktPos, 6)) token = 'q';

    switch (token)
    {
        case 'a':
            aktPos++;
            nextChar(aktPos, F);
            break;
        case 'b': case 'c':  case 'd': case 'e': case 'f':
        case 'o': case 'p':
            aktPos += 2;
            nextChar(aktPos, F);
            break;
        case 'j': case 'k': case 'l':  case 'm':  case 'n':
            aktPos += 3;
            nextChar(aktPos, F);
            break;
        case 'g': case 'h': case 'i':  case 'q':
            aktPos += 5;
            nextChar(aktPos, F);
            break;
        case 'r':
            aktPos += 6;
            nextChar(aktPos, F);
            break;
        default:
            return false;
    } // switch
    return (token != '\0');
} //unaereFunktion(char *F, char &token)
/*
Funktion Faktor(VAR F : STRING):tFunktion;
(* ist fuer Klammerung, unaere Funktionen, x, e, pi    *)
(* und (Real-) Zahlen zustaendig                        *)
(* zurueckgeliefert wird Teilbaum, der obiges enthaelt *)
VAR Knoten : tFunktion;
    valid  : INTEGER;
    posi   : INTEGER;
    Token  : CHAR;
    Fhelp  : STRING;
BEGIN
  Knoten := NIL;
  IF aktChar = '(' THEN (* Rekursion bei '(' *)
  BEGIN
    NextChar(aktPos,F); Knoten := Summe(F);
    IF (aktChar <> ')') AND NOT fehler THEN BEGIN
      fehler := TRUE;
      FehlerArt := 0 (* ')' erwartet *)
    END;
    IF NOT fehler THEN NextChar(aktPos,F);
    Faktor := Knoten
  END
  ELSE IF UnaereFunktion(F,Token) THEN BEGIN
    IF aktChar <> '(' THEN BEGIN
      fehler := TRUE;
      FehlerArt := 1; (* '(' erwartet *)
      Faktor := Knoten
    END
    ELSE BEGIN (* sonst *)
      NewNode(Knoten); Knoten^.Operator := Token;
      NextChar(aktPos,F); Knoten^.LChild := Summe(F)
    END;
    IF (aktChar <> ')') AND NOT fehler THEN BEGIN
      fehler := TRUE;
      FehlerArt := 0 (* ')' erwartet *)
    END;
    IF NOT fehler THEN NextChar(aktPos,F);
    Faktor := Knoten
  END
  ELSE IF (aktChar = 'x') THEN BEGIN
    NewNode(Knoten);
    Knoten^.Operator := #1;
    NextChar(aktPos,F);
    Faktor := Knoten
  END
  ELSE IF Pos('pi',F,aktPos,2) THEN BEGIN
    NewNode(Knoten); NEW(Knoten^.Operand);
    Knoten^.Operand^ := pi;
    INC(aktPos); NextChar(aktPos,F);
    Faktor := Knoten
  END
  ELSE IF aktChar = 'e' THEN BEGIN
    NewNode(Knoten); NEW(Knoten^.Operand);
    Knoten^.Operand^ := e;
    NextChar(aktPos,F);
    Faktor := Knoten
  END
  ELSE IF (aktChar >= '0') AND (aktChar <= '9')
    OR (aktChar = '.') THEN BEGIN
    NewNode(Knoten); NEW(Knoten^.Operand);
    posi := aktPos; GetNumber(F,posi,Fhelp);
    VAL(Fhelp,Knoten^.Operand^,valid);
    aktPos := posi - 1; NextChar(aktPos,F);
    fehler := valid <> 0;
    FehlerArt := 2; (* Fehler beim Einlesen der Zahl *)
    Faktor := Knoten
  END
  ELSE BEGIN
    fehler := TRUE;   (* bei vorzeitigem Ende der Eingabe oder *)
    IF (aktChar = ' ') OR (aktPos = Length(F)+1) THEN FehlerArt := 3
    ELSE FehlerArt := 4;
    Faktor := Knoten  (* unbekanntem Zeichen                   *)
  END (* Fehler *)
END;
*/

tKnoten *Funktion::faktor(char *F)
{
    tKnoten *knoten = NULL;
    unsigned int posi;
    char token;
    char fHelp[STR_SIZE] = "";

    if(aktChar == '(' && ! fehler)
    {
        nextChar(aktPos, F);
        knoten = summe(F);
        if (aktChar != ')' && ! fehler)
        {
            fehler = true;
            fehlerArt = 0; // ')' erwartet
        }
        if (! fehler)
            nextChar(aktPos, F);
        return knoten;
    } // if(aktChar == '(' && ! fehler)
    if (unaereFunktion(F, token))
    {
        if (aktChar != '(')
        {
            fehler = true;
            fehlerArt = 1; // '(' erwartet
            return knoten;
        }
        else // sonst
        {
            knoten = new tKnoten;
            knoten->operat = token;
            nextChar(aktPos, F);
            knoten->lChild = summe(F);
        }
        if (aktChar != ')' && !fehler)
        {
            fehler = true;
            fehlerArt = 0; // ')' erwartet
        }
        if (! fehler)
            nextChar(aktPos, F);
        return knoten;
    } // if (unaereFunktion(F, token)

    if(toupper(aktChar) == 'X')
    {
        knoten = new tKnoten;
        knoten->operat = '\1';
        nextChar(aktPos, F);
        return knoten;
    } // if(toupper(aktChar) == 'X')

    if(Pos("pi", F, aktPos, 2))
    {
        knoten = new tKnoten(knoten, '\0');
        knoten->operand = 2.0 * PI_HALBE;
        aktPos++;
        nextChar(aktPos, F);
        return knoten;
    } // if(Pos("pi", F, aktPos, 2))

    if(toupper(aktChar) == 'E')
    {
        knoten = new tKnoten(knoten, '\0');
        knoten->operand = E;
        nextChar(aktPos, F);
        return knoten;
    } //if(toupper(aktChar) == 'E')

    if(aktChar >= '0' && aktChar <= '9' || aktChar == '.')
    {
        knoten = new tKnoten;
        posi = aktPos;
        getNumber(F, posi, fHelp);
        double dummy;
        istrstream inString(fHelp);
        inString >> dummy;
        fehler = inString.fail();
        knoten->operand = dummy;
        if (fehler)
            fehlerArt = 2; //Fehler beim einlesen der Zahl
        aktPos = posi - 1;
        nextChar(aktPos, F);
        return knoten;
    } // if(aktChar >= '0' && aktChar <= '9' || aktChar == '.')
    fehler = true;
    if (aktChar == ' ' || (unsigned) aktPos == strlen(F))
        fehlerArt = 3;
    else
        fehlerArt = 4;
    return knoten;
} // faktor(char *F)

/*
Funktion Summe(VAR F : STRING):tFunktion;
VAR Wurzel : tFunktion;
BEGIN
  Wurzel := NIL;
  Wurzel := Produkt(F);
  WHILE ((aktChar = '+') OR (aktChar = '-')) AND NOT fehler DO
  BEGIN
    NeueWurzel(Wurzel,F);
    Wurzel^.RChild := Produkt(F)
  END;
  Summe := Wurzel
END;
*/
tKnoten *Funktion::summe(char *F)
{
    tKnoten *wurzel = produkt(F);
    while((aktChar == '+' || aktChar == '-') && ! fehler )
    {
        //neueWurzel(wurzel, aktChar);
        wurzel = new tKnoten(wurzel, aktChar);
        nextChar(aktPos,F); // aus Konstruktor rausgenommen
        wurzel->rChild = produkt(F);
    }
    return wurzel;
} // summe(char *F)
/*
Funktion Produkt(VAR F : STRING):tFunktion;
VAR Wurzel : tFunktion;
BEGIN
  Wurzel := NIL;
  Wurzel := Potenz(F);
  WHILE ((aktChar = '*') OR (aktChar = '/')) AND NOT fehler DO
  BEGIN
    NeueWurzel(Wurzel,F);
    Wurzel^.RChild := Potenz(F)
  END;
  Produkt := Wurzel
END;
*/

tKnoten *Funktion::produkt(char *F)
{
    tKnoten *wurzel = potenz(F);
    while ((aktChar == '*' || aktChar == '/')  && ! fehler)
    {
        //neueWurzel(wurzel, aktChar);
        wurzel = new tKnoten(wurzel, aktChar);
        nextChar(aktPos,F); // aus Konstruktor rausgenommen
        wurzel->rChild = potenz(F);
    }
    return wurzel;
} // produkt(char *F)
/*
Funktion Potenz(VAR F : STRING):tFunktion;
VAR Wurzel : tFunktion;
BEGIN (* Bearbeitung von Potenzen *)
  Wurzel := NIL;
  Wurzel := VorzFaktor(F);
  WHILE (aktChar = '^') AND (NOT fehler) DO
  BEGIN
    NeueWurzel(Wurzel,F);
    Wurzel^.RChild := VorzFaktor(F)
  END;
  Potenz := Wurzel
END;
*/
tKnoten *Funktion::potenz(char *F)
{
    tKnoten *wurzel = vorzFaktor(F);
    while(aktChar == '^' && ! fehler)
    {
        wurzel = new tKnoten(wurzel, aktChar);
        nextChar(aktPos, F); // aus Konstruktor rausgenommen
        wurzel->rChild = vorzFaktor(F);
    }
    return wurzel;
} //potenz(char *F);
/*
Funktion VorzFaktor( VAR F : STRING):tFunktion;
VAR Wurzel : tFunktion;
BEGIN
  Wurzel := NIL;
  IF (aktChar = '-') THEN BEGIN
    NewNode(Wurzel);
    Wurzel^.Operator := 's';
    NextChar(aktPos,F);
    Wurzel^.LChild := Faktor(F);
    VorzFaktor := Wurzel
  END
  ELSE IF aktChar = '+' THEN BEGIN
    NextChar(aktPos,F);
    Wurzel := Faktor(F);
    VorzFaktor := Wurzel
  END
  ELSE BEGIN
    Wurzel := Faktor(F);
    VorzFaktor := Wurzel
  END
END;
*/
tKnoten* Funktion::vorzFaktor(char *F)
{
    tKnoten *wurzel = NULL;
    if(aktChar == '-')
    {
        wurzel = new tKnoten;
        wurzel->operat = 's';
        nextChar(aktPos,F);
        wurzel->lChild = faktor(F);
        return wurzel; // und raus
    } // if(aktChar == '-')
    if(aktChar == '+')
    {
        nextChar(aktPos,F);
        wurzel->lChild = faktor(F);
        return wurzel; // und raus
    }
    wurzel = faktor(F);
    return wurzel;

} //vorzFaktor(char *F)

tKnoten *Funktion::baueBaum(char *fKlein)
{
    tKnoten *wurzel = NULL;
    aktPos = -1; // weil nextChar inkrementiert
    nextChar(aktPos, fKlein); // fuehrende Blanks ueberlesen
    fehler = false;
    wurzel = summe(fKlein); // eigentlicher Start
    /* Fehler falls Stringende nicht erreicht
    Leerzeichen am Ende erlaubt */
    if ((unsigned)aktPos < strlen(fKlein) && fKlein[aktPos] != ' ' && ! fehler)
    {
        fehler = true;
        fehlerArt = 4; //falsches Eingabezeichen
    }
    if (! fehler)
    {
        fehlerPos = -1;
        fehlerNr = -1;
        vereinfache(wurzel); // *** noch zu riskant
    }
    else // falls Fehler aufgetreten
    {
        //DeleteTree(Wurzel);
        delete wurzel;
        wurzel = NULL;
        fehlerPos = aktPos;
        fehlerNr= fehlerArt;
    }
    return wurzel;
} // baueBaum()

double Funktion::f(tKnotenPtr &p)
{
    if (p == NULL)
      return 0;
    switch(p->operat)
    {
        case '\0': return p->operand;
        case '\1': return x;
        case '+': return f(p->lChild) + f(p->rChild);
        case '-': return f(p->lChild) - f(p->rChild);
        case '*': return f(p->lChild) * f(p->rChild);
        case '/': return f(p->lChild) / f(p->rChild);
        case '^': return pow(f(p->lChild), f(p->rChild));
        case 'a': return log(f(p->lChild)); // log nat
        case 'b': return log10(f(p->lChild)); //log10
        case 'c': return exp(f(p->lChild));
        case 'd': return sin(f(p->lChild));
        case 'e': return cos(f(p->lChild));
        case 'f': return tan(f(p->lChild));
        case 'g': return asin(f(p->lChild));
        case 'h': return acos(f(p->lChild));
        case 'i': return atan(f(p->lChild));
        case 'j': return sinh(f(p->lChild));
        case 'k': return cosh(f(p->lChild));
        case 'l': return tanh(f(p->lChild));
        case 'm': return sqrt(f(p->lChild));
        case 'n': return frac(f(p->lChild));
        case 'o': return fabs(f(p->lChild));
        case 'p': return 1.0 / tan(f(p->lChild));
        case 'q': return arccot(f(p->lChild));
        case 'r': return arctanh(f(p->lChild));
        case 's': return -f(p->lChild);
        default:
          if (errStream != NULL)
              (*errStream) << "fehler im Baum: Operator = '" << p->operat << "'" << endl;
        return 0;
    } // switch
}
double Funktion::berechne(double x)
{
    if (fehler)
        return 0;
    tKnotenPtr knoten = F1;
    return berechne(knoten, x);
}

double Funktion::berechne(tKnotenPtr &p, double x)
{
    this->x = x;
    if (p == NULL)
        return 0.0;
    return f(p);
} //  berechne(tKnotenPtr p, double x)

/* ***********
struct tKnoten
{
    char operat;
    tDoublePtr operand;
    tKnoten *lChild, *rChild;
    tKnoten();

    tKnoten(tKnoten *wurzel, char operat);

    ~tKnoten(); // Destruktor, eruebrigt rekursive Prozedur DeleteTree()
}; // struct tKnoten
*/
const char *Funktion::unFunktName(char token) const
{
    switch (token)
    {
        case 'a': return "ln";
        case 'b': return "log";
        case 'c': return "exp";
        case 'd': return "sin";
        case 'e': return "cos";
        case 'f': return "tan";
        case 'g': return "arcsin";
        case 'h': return "arccos";
        case 'i': return "arctan";
        case 'j': return "sinh";
        case 'k': return "cosh";
        case 'l': return "tanh";
        case 'm': return "sqrt";
        case 'n': return "frac";
        case 'o': return "abs";
        case 'p': return "cot";
        case 'q': return "arccot";
        case 'r': return "arctanh";
    }
    return "unbek.";
} // unFunktName(char token)

// so ist Baum mit Wurzel nach oben
// um 90 Grd im Urzeigersinn gedreht dargestellt
void Funktion::inorderPrint(tKnoten *p, int tiefe, ostream &os) const
{
    if (p == NULL)
        return;
    // inorderPrint(p->lChild, tiefe+1, os);
    inorderPrint(p->rChild, tiefe+1, os);
    os << setw(tiefe * 2) << "";
    switch(p->operat)
    {
        case '\0':
            os << p->operand << endl; break;
        case '\1':
            os << "x" << endl; break;
        case 'a': case 'b': case 'c': case 'd':
        case 'e': case 'f': case 'g': case 'h':
        case 'i': case 'j': case 'k': case 'l':
        case 'm': case 'n': case 'o': case 'p':
        case 'q': case 'r':
            os << unFunktName(p->operat) << endl; break;
        default:
            os << p->operat << endl; break;
    } // switch()
    //inorderPrint(p->rChild, tiefe + 1, os);
    inorderPrint(p->lChild, tiefe + 1, os);
} //inorderPrint(()

void Funktion::myDelete(tKnotenPtr &p)
{
    //p->operand = NULL;
    p->lChild = NULL;
    p->rChild = NULL;
    p = NULL;
    delete p;
}

void Funktion::zeigeFehler(ostream &os)  const
{
    os << endl;
    if (fehlerPos == -1)
    {
        os << "Funktion OK" << endl;
        return;
    }
    os << FStr << endl;
    os << setw(fehlerPos) << "" << "^X" << endl;
    os << fehlerMeldung[fehlerNr] << endl;
}
//------------------------------------------------------
Funktion::~Funktion()
{
    delete F1;
} // ~Funktion()

ostream &operator<<(ostream &os, const Funktion &d)
{
// Dezimalpunkt zeigen
    int savePrec = os.precision(2); // alte praezision
#if STEINZEIT_C
    ong saveFlags = os.setf(ios::showpoint );  // Hier isses ein long
#else
    // und hier vom Typ std::os_base::fmtflags
    // Achtung : Im Builder1 ist es noch anders !!!
    /*std:: */
    ios_base::fmtflags saveFlags = os.setf(ios::showpoint);
    // int savePrec = os.precision(3);
#endif
    if (d.fehlerPos == -1)
    {
        os << "Funktion OK " << endl;
        os << "Hier der Funktionsbaum:" << endl;
        d.inorderPrint(d.F1, 0, os);
    }
    else
    {
        d.zeigeFehler(os);
    }
    os.precision(savePrec);
    os.setf(saveFlags);
    return os;
}
//Funktion funk;



