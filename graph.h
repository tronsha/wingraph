//---------------------------------------------------------------------------

#ifndef graphH
#define graphH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <ComCtrls.hpp>

#include "funktion.h"
#include <ImgList.hpp>
#include <ScktComp.hpp>
#include <Sockets.hpp>
//---------------------------------------------------------------------------
class TFormGraph : public TForm
{
__published:	// IDE-managed Components
        TButton *ZeichneButton;
        TEdit *Edit8;
        TMainMenu *MainMenu;
        TMenuItem *MenuDatei;
        TMenuItem *MenuBeenden;
        TImage *Image1;
        TImage *Image2;
        TMenuItem *MenuFunktion;
        TMenuItem *MenuAchsen;
        TMenuItem *MenuBeispiele;
        TMenuItem *Beispiel1x3x025x075;
        TMenuItem *Beispiel2x3x4;
        TMenuItem *MenuHilfe;
        TMenuItem *MenuHomepage;
        TMenuItem *Beispielxx4;
        TMenuItem *Beispielx;
        TMenuItem *Beispiel1x;
        TMenuItem *MenuZeichne;
        TMenuItem *NLinie1;
        TMenuItem *MenuInfo;
        TPanel *PanelGraph;
        TTimer *TimerStart;
        TImage *PaintBox;
        TMenuItem *MenuSpeichern;
        TMenuItem *NLinie2;
        TMenuItem *MenuZeichneNeu;
        TMenuItem *MenuExtraAusgabefenster;
        TMenuItem *MenuNein;
        TMenuItem *MenuJa;
        TMenuItem *NLinie3;
        TMenuItem *MenuSonder;
        TLabel *LabelSonder;
        TMenuItem *FourierSynthese1;
        TLabel *Label_nharm;
        TEdit *fVonXEdit;
        TMenuItem *MenuNormal;
        TPanel *PanelOutGroesse;
        TLabel *LabelOutGroesse;
        TEdit *EditOutGroesse;
        TButton *ButtonOutGroesse;
        TMenuItem *MenuOutGroesse;
        TLabel *Label_y;
        TMenuItem *MenuEinstellungen;
        TMenuItem *MenuxAchse;
        TMenuItem *MenuyAchse;
        TMenuItem *MenuyAchseWert;
        TMenuItem *MenuyAchseX;
        TMenuItem *MenuxAchseWert;
        TPanel *Panel_xAchse;
        TLabel *Label_xAches;
        TEdit *Edit_xAchse;
        TButton *Button_xAches;
        TPanel *Panel_yAchse;
        TLabel *Label_yAchse;
        TEdit *Edit_yAchse;
        TButton *Button_yAchse;
        TMenuItem *MenuDrucken;
        TImage *ImageGDI;
        TMenuItem *Beispielsinx;
        TColorDialog *ColorDialog;
        TMenuItem *MenuColor;
        TSaveDialog *SaveDialog1;
	TTcpServer *ss;
        void __fastcall ZeichneButtonClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall EditKeyPress(TObject *Sender, char &Key);
        void __fastcall MenuBeendenClick(TObject *Sender);
        void __fastcall MenuHomepageClick(TObject *Sender);
        void __fastcall Beispiel1x3x025x075Click(TObject *Sender);
        void __fastcall Beispiel2x3x4Click(TObject *Sender);
        void __fastcall Beispielxx4Click(TObject *Sender);
        void __fastcall BeispielxClick(TObject *Sender);
        void __fastcall Beispiel1xClick(TObject *Sender);
        void __fastcall BeispielsinxClick(TObject *Sender);
        void __fastcall MenuZeichneClick(TObject *Sender);
        void __fastcall MenuInfoClick(TObject *Sender);
        void __fastcall TimerStartTimer(TObject *Sender);
        void __fastcall MenuSpeichernClick(TObject *Sender);
        void __fastcall MenuZeichneNeuClick(TObject *Sender);
        void __fastcall MenuNeinClick(TObject *Sender);
        void __fastcall MenuJaClick(TObject *Sender);
        void __fastcall ButtonOutGroesseClick(TObject *Sender);
        void __fastcall MenuOutGroesseClick(TObject *Sender);
        void __fastcall EditOutGroesseKeyPress(TObject *Sender, char &Key);
        void __fastcall MenuNormalClick(TObject *Sender);
        void __fastcall FourierSynthese1Click(TObject *Sender);
        void __fastcall MenuxAchseWertClick(TObject *Sender);
        void __fastcall Button_xAchesClick(TObject *Sender);
        void __fastcall Edit_xAchseKeyPress(TObject *Sender, char &Key);
        void __fastcall MenuyAchseXClick(TObject *Sender);
        void __fastcall Button_yAchseClick(TObject *Sender);
        void __fastcall MenuyAchseWertClick(TObject *Sender);
        void __fastcall Edit_yAchseKeyPress(TObject *Sender, char &Key);
        void __fastcall MenuDruckenClick(TObject *Sender);
        void __fastcall MenuColorClick(TObject *Sender);
        double __fastcall y(double x);
        void __fastcall zeichne();
        void __fastcall zeichne2();
        void __fastcall aender_fenster();
private:	// User declarations
        Funktion funk;
        Funktion::eOptimiere opt;
        bool isFunkReady;
public:		// User declarations
        __fastcall TFormGraph(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormGraph *FormGraph;
//---------------------------------------------------------------------------
        int max_x();
        int max_y();
        void axis(float, float);
        float scale_x(float);
        float scale_y(float);
        void curve(float, float, float);
        AnsiString AddUnsichtbareMalzeichen(AnsiString);
//---------------------------------------------------------------------------
#endif
