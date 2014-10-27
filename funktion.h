// function.h
// W. Boeck, 00-09-16
// "Uebersetzung" eines PASCAL Programms
// aus ct8912250 (ct 12/89 S. 250 ff)
#ifndef FUNCTION_H
#define FUNCTION_H
#define STEINZEIT_C 0
//#include <math.h> // brauchen wir bestimmt
#include <stdlib.h>
#include <string.h>
#include <strstrea.h>
#include <iostream.h>
#include <iomanip.h>
#include "mathlib.h"

#if STEINZEIT_C
enum bool {false, true}; // w.g Datentyp bool in modernerem C
#endif


//typedef double *tDoublePtr;
struct tKnoten
{
    char operat;
    double operand;
    tKnoten *lChild, *rChild;
    tKnoten();
    /* ersetzen durch Konstruktor
    PROCEDURE NeueWurzel(VAR Wurzel : tFunktion; VAR F : STRING);
    (* alte Wurzel wird linker Sohn *)
    */
    tKnoten(tKnoten *wurzel, char operat);
    ~tKnoten(); // Destruktor, eruebrigt rekursive Prozedur DeleteTree()
}; // struct tKnoten

typedef tKnoten* tKnotenPtr;

//-- und das ist das Teil aus Parser und Evaluierer

// 
/* 
Implementaton-Variablen der PASCAL-UNIT
sollten private Variablen der Klasse sein
VAR success,fehler   : BOOLEAN;
    aktPos,FehlerArt : INTEGER;
             aktChar : CHAR;
*/
const int STR_SIZE = 256;
class Funktion
{
public:
    const static char fehlerMeldung[] [30];
  enum eOptimiere {nichts = 0, teilBaum = 1, konstanten = 2};
private:
    double x; // wegen geschachtelter Funktion f() in PASCAL-Funktion berechne();
    bool success, fehler;
    int aktPos, fehlerArt;
    int fehlerPos, fehlerNr;
    char aktChar;
  eOptimiere optimiere;
    char FStr[STR_SIZE];
    tKnoten *F1; // die Wurzel des Funktionsbaums
    ostream *errStream;
    void vereinfache (tKnotenPtr &p);
    void getNumber(char *F, unsigned int &posi, char *fHelp);
    void nextChar(int start, char *F);
    bool Pos(const char *w, const char *F, unsigned int s, int l);
    bool unaereFunktion(char *F, char &token);
    tKnoten *faktor(char *F);
    tKnoten *summe(char *F);
    tKnoten *produkt(char *F);
    tKnoten *potenz(char *F);
    tKnoten *vorzFaktor(char *F);
    tKnoten *baueBaum(char *fKlein);
    double f(tKnotenPtr &p);
    double berechne(tKnotenPtr &p, double x);
    void myDelete(tKnotenPtr &p);
    void inorderPrint(tKnoten *p, int tiefe, ostream &os) const;
    const char *unFunktName(char token) const;
    friend ostream &operator<<(ostream &os, const Funktion &d);
public:
    void zeigeFehler(ostream &os) const;
    Funktion(); // standardKonstruktor, setzt alles auf 0
    ~Funktion();
    bool initBaum
    (
      const char *F, // das ist der FunktionsString
      ostream *errStr = NULL, // Fehlermeldung bzw. "Funktion OK"
      eOptimiere opt = teilBaum // voreingestellt ist Teilboum
    );
    double berechne(double x);
}; //
//extern Funktion funk;
#endif // Funktion_H