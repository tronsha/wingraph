//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
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
__published:    // IDE-managed Components
        TButton *DrawButton;
        TEdit *Edit8;
        TMainMenu *MainMenu;
        TMenuItem *MenuFile;
        TMenuItem *MenuClose;
        TImage *Image1;
        TImage *Image2;
        TMenuItem *MenuFunction;
        TMenuItem *MenuAxes;
        TMenuItem *MenuExamples;
        TMenuItem *Example_1x3x025x075;
        TMenuItem *Example_2x3x4;
        TMenuItem *Example_xx4;
        TMenuItem *Example_x;
        TMenuItem *Example_1x;
        TMenuItem *Example_sin_x;
        TMenuItem *MenuHelp;
        TMenuItem *MenuHomepage;
        TMenuItem *MenuDraw;
        TMenuItem *NLine1;
        TMenuItem *MenuInfo;
        TPanel *PanelGraph;
        TTimer *TimerStart;
        TImage *PaintBox;
        TMenuItem *MenuSave;
        TMenuItem *NLine2;
        TMenuItem *MenuAddedToDraw;
        TMenuItem *MenuSpecial;
        TLabel *LabelSpecial;
        TMenuItem *MenuFourierSynthesis;
        TLabel *Label_nharm;
        TEdit *fVonXEdit;
        TMenuItem *MenuNormal;
        TLabel *Label_y;
        TMenuItem *MenuSettings;
        TMenuItem *Menu_xAxis;
        TMenuItem *Menu_yAxis;
        TMenuItem *Menu_yAxisValue;
        TMenuItem *Menu_yAxisX;
        TMenuItem *Menu_xAxisValue;
        TPanel *Panel_xAxis;
        TLabel *Label_xAches;
        TEdit *Edit_xAxis;
        TButton *Button_xAches;
        TPanel *Panel_yAxis;
        TLabel *Label_yAxis;
        TEdit *Edit_yAxis;
        TButton *Button_yAxis;
        TImage *ImageGDI;
        TColorDialog *ColorDialog;
        TMenuItem *MenuColor;
        TSaveDialog *SaveDialog1;
        void __fastcall DrawButtonClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall EditKeyPress(TObject *Sender, char &Key);
        void __fastcall MenuCloseClick(TObject *Sender);
        void __fastcall MenuHomepageClick(TObject *Sender);
        void __fastcall Example_1x3x025x075Click(TObject *Sender);
        void __fastcall Example_2x3x4Click(TObject *Sender);
        void __fastcall Example_xx4Click(TObject *Sender);
        void __fastcall Example_xClick(TObject *Sender);
        void __fastcall Example_1xClick(TObject *Sender);
        void __fastcall Example_sin_xClick(TObject *Sender);
        void __fastcall MenuDrawClick(TObject *Sender);
        void __fastcall MenuAddedToDrawClick(TObject *Sender);
        void __fastcall MenuInfoClick(TObject *Sender);
        void __fastcall TimerStartTimer(TObject *Sender);
        void __fastcall MenuSaveClick(TObject *Sender);
        void __fastcall MenuNormalClick(TObject *Sender);
        void __fastcall MenuFourierSynthesisClick(TObject *Sender);
        void __fastcall Menu_xAxisValueClick(TObject *Sender);
        void __fastcall Menu_yAxisValueClick(TObject *Sender);
        void __fastcall Button_xAchesClick(TObject *Sender);
        void __fastcall Button_yAxisClick(TObject *Sender);
        void __fastcall Edit_xAxisKeyPress(TObject *Sender, char &Key);
        void __fastcall Edit_yAxisKeyPress(TObject *Sender, char &Key);
        void __fastcall Menu_yAxisXClick(TObject *Sender);
        void __fastcall MenuColorClick(TObject *Sender);
		double __fastcall y(double x);
        void __fastcall render(bool reset);
//        void __fastcall render2();
        void __fastcall changeWindow();
private:        // User declarations
        Funktion funk;
        Funktion::eOptimiere opt;
        bool isFunkReady;
public:        // User declarations
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
        AnsiString prepareFunctionString(AnsiString);
//---------------------------------------------------------------------------
#endif
