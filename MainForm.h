//---------------------------------------------------------------------------
#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <windows.h>
#include <initguid.h>
#include <gdiplus.h>
#include <stdio.h>
#include <math.h>
#include "funktion.h"
//#-------------------------------------------------------------------------
class TFormGraph : public TForm
{
    __published: // IDE-managed Components
        TMainMenu *MainMenu;
        TMenuItem *MenuFile;
        TMenuItem *MenuDraw;
        TMenuItem *MenuAddedToDraw;
        TMenuItem *NLine1;
        TMenuItem *MenuSave;
        TMenuItem *NLine2;
        TMenuItem *MenuClose;
        TMenuItem *MenuFunction;
        TMenuItem *MenuNormal;
        TMenuItem *MenuSpecial;
        TMenuItem *MenuFourierSynthesis;
        TMenuItem *MenuSettings;
        TMenuItem *MenuColor;
        TMenuItem *MenuAxes;
        TMenuItem *Menu_xAxis;
        TMenuItem *Menu_xAxisValue;
        TMenuItem *Menu_yAxis;
        TMenuItem *Menu_yAxisValue;
        TMenuItem *Menu_yAxisX;
        TMenuItem *MenuHelp;
        TMenuItem *MenuInfo;
        TMenuItem *MenuLicense;
        TMenuItem *MenuExamples;
        TMenuItem *Example_1x3x025x075;
        TMenuItem *Example_2x3x4;
        TMenuItem *Example_xx4;
        TMenuItem *Example_x;
        TMenuItem *Example_1x;
        TMenuItem *Example_sin_x;
        TImage *ImageGDI;
        TImage *Image1;
        TImage *Image2;
        TImage *PaintBox;
        TButton *DrawButton;
        TEdit *FunctionEdit;
        TEdit *EditFourierSynthesis;
        TLabel *LabelSpecial;
        TLabel *Label_nharm;
        TPanel *PanelGraph;
        TPanel *Panel_xAxis;
        TButton *Button_xAxis;
        TEdit *Edit_xAxis;
        TLabel *Label_xAxis;
        TPanel *Panel_yAxis;
        TButton *Button_yAxis;
        TEdit *Edit_yAxis;
        TLabel *Label_yAxis;
        TLabel *Label_y;
        TTimer *TimerStart;
        TColorDialog *ColorDialog;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall MenuDrawClick(TObject *Sender);
        void __fastcall MenuAddedToDrawClick(TObject *Sender);
        void __fastcall MenuSaveClick(TObject *Sender);
        void __fastcall MenuCloseClick(TObject *Sender);
        void __fastcall MenuNormalClick(TObject *Sender);
        void __fastcall MenuFourierSynthesisClick(TObject *Sender);
        void __fastcall MenuColorClick(TObject *Sender);
        void __fastcall Menu_xAxisValueClick(TObject *Sender);
        void __fastcall Menu_yAxisValueClick(TObject *Sender);
        void __fastcall Menu_yAxisXClick(TObject *Sender);
        void __fastcall MenuInfoClick(TObject *Sender);
        void __fastcall MenuLicenseClick(TObject *Sender);
        void __fastcall Example_1x3x025x075Click(TObject *Sender);
        void __fastcall Example_2x3x4Click(TObject *Sender);
        void __fastcall Example_xx4Click(TObject *Sender);
        void __fastcall Example_xClick(TObject *Sender);
        void __fastcall Example_1xClick(TObject *Sender);
        void __fastcall Example_sin_xClick(TObject *Sender);
        void __fastcall DrawButtonClick(TObject *Sender);
        void __fastcall Button_xAxisClick(TObject *Sender);
        void __fastcall Button_yAxisClick(TObject *Sender);
        void __fastcall Edit_xAxisKeyPress(TObject *Sender, char &Key);
        void __fastcall Edit_yAxisKeyPress(TObject *Sender, char &Key);
        void __fastcall EditKeyPress(TObject *Sender, char &Key);
        void __fastcall TimerStartTimer(TObject *Sender);
        void __fastcall changeWindow();
        void __fastcall render(bool reset);
        void __fastcall about();
        double __fastcall y(double x);
    private: // User declarations
        Funktion funk;
        Funktion::eOptimiere opt;
        bool isFunkReady;
    public:  // User declarations
        __fastcall TFormGraph(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormGraph *FormGraph;
//---------------------------------------------------------------------------
int max_x();
int max_y();
float scale_x(float);
float scale_y(float);
void axis(float, float);
void curve(float, float, float);
AnsiString prepareFunctionString(AnsiString);
//---------------------------------------------------------------------------
#endif
