//---------------------------------------------------------------------------
#define STRICT
#define INITGUID
#include <vcl.h>
#undef INITGUID
#include <windows.h>
#include <initguid.h>
#include <gdiplus.h>
#include <stdio.h>
#include <math.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "info.h"
#include "MainForm.h"
#include "InfoForm.h"
#include "SaveForm.h"
using namespace Gdiplus;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TFormGraph *FormGraph;
//---------------------------------------------------------------------------
__fastcall TFormGraph::TFormGraph(TComponent* Owner) : TForm(Owner), isFunkReady(false), opt(Funktion::nichts)
{
}
//---------------------------------------------------------------------------
int WX = 375;
int WY = 375;
int drawingColor = 0;
//---------------------------------------------------------------------------
AnsiString prepareFunctionString(AnsiString in)
{
    int length = in.Length();
    int i, j;
    char oldFunctionString[STR_SIZE];
    char newFunctionString[STR_SIZE*2];
    AnsiString out;

    newFunctionString[0] = '\0';

    strncpy(oldFunctionString, in.c_str(), STR_SIZE);

    for(i = 0, j = 0; i < length; i++, j++)
    {
        newFunctionString[j] = oldFunctionString[i];
        if(oldFunctionString[i] >= '0' && oldFunctionString[i] <= '9' && (oldFunctionString[i+1] == 'x' || oldFunctionString[i+1] == '('))
        {
            j++;
            newFunctionString[j] = '*';
        }
        newFunctionString[j+1] = '\0';
    }
    newFunctionString[j] = '\0';

    return newFunctionString;
}
//---------------------------------------------------------------------------
void axis(float xMax, float yMax)
{
    int i;
    int x = xMax;
    int y = yMax;

    FormGraph->PaintBox->Canvas->Pen->Color = clWhite;
    FormGraph->PaintBox->Canvas->Pen->Width = 1000;
    FormGraph->PaintBox->Canvas->MoveTo(0, WY/2);
    FormGraph->PaintBox->Canvas->LineTo(WX, WY/2);

    FormGraph->PaintBox->Canvas->Pen->Color = clBlack;
    FormGraph->PaintBox->Canvas->Pen->Width = 1;

    FormGraph->PaintBox->Canvas->MoveTo(0, WY/2);
    FormGraph->PaintBox->Canvas->LineTo(WX, WY/2);
    FormGraph->PaintBox->Canvas->MoveTo(WX/2,0);
    FormGraph->PaintBox->Canvas->LineTo(WX/2,WY);

    for (i = -x+1; i <= x-1; i++)
    {
        FormGraph->PaintBox->Canvas->MoveTo(WX/2-WX/2*i/x,WY/2-2);
        FormGraph->PaintBox->Canvas->LineTo(WX/2-WX/2*i/x,WY/2+3);
    }
    for (i = -y+1; i <= y-1; i++)
    {
        FormGraph->PaintBox->Canvas->MoveTo(WX/2-2,WY/2-WY/2*i/y);
        FormGraph->PaintBox->Canvas->LineTo(WX/2+3,WY/2-WY/2*i/y);
    }

    FormGraph->PaintBox->Canvas->MoveTo(WX,WY/2);
    FormGraph->PaintBox->Canvas->LineTo(WX-9,WY/2+3);
    FormGraph->PaintBox->Canvas->MoveTo(WX,WY/2);
    FormGraph->PaintBox->Canvas->LineTo(WX-9,WY/2-3);
    FormGraph->PaintBox->Canvas->MoveTo(WX/2,0);
    FormGraph->PaintBox->Canvas->LineTo(WX/2-3,9);
    FormGraph->PaintBox->Canvas->MoveTo(WX/2,0);
    FormGraph->PaintBox->Canvas->LineTo(WX/2+3,9);

    FormGraph->PaintBox->Canvas->TextOut(WX-12,WY/2+4,"X");
    FormGraph->PaintBox->Canvas->TextOut(WX/2-14,2,"Y");
}
//---------------------------------------------------------------------------
float scale_x(float xMax)
{
    float result;
    result = (WX/2) / xMax;
    return result;
}
//---------------------------------------------------------------------------
float scale_y(float yMax)
{
    float result;
    result = (WY/2) / yMax;
    return result;
}
//---------------------------------------------------------------------------
void curve(float xMax, float yMax, float step)
{
    float x, scale_x2, scale_y2;
    int pos_y, pos_x;

    FormGraph->PaintBox->Canvas->Pen->Color = drawingColor;
    FormGraph->PaintBox->Canvas->Pen->Width = 1;

    scale_x2 = scale_x(xMax);
    scale_y2 = scale_y(yMax);

    pos_x = -xMax * scale_x2;
    pos_y = FormGraph->y(-xMax) * scale_y2;

    FormGraph->PaintBox->Canvas->MoveTo(WX/2 + pos_x, WY/2 - pos_y);

    for(x = -xMax; x <= xMax; x = x + step)
    {
        pos_y = (FormGraph->y(x) * scale_y2);
        pos_x = (x * scale_x2);

        if (((WY / 2 - pos_y) >= -2 * WY) && ((WY / 2 - pos_y) <= WY + 2 * WY))
            FormGraph->PaintBox->Canvas->LineTo(WX / 2 + pos_x, WY / 2 - pos_y);
        else
            FormGraph->PaintBox->Canvas->MoveTo(WX / 2 + pos_x, WY / 2 - pos_y);
    }
}
//---------------------------------------------------------------------------
//float y(x)
double __fastcall TFormGraph::y(double x)
{
    double a0nx;
    double result;

    if(FormGraph->Edit8->Text != "")
        a0nx = FormGraph->Edit8->Text.ToDouble();
    else
        a0nx = 0;

    if(FormGraph->MenuFourierSynthesis->Checked == true)
    {
        int z;
        result = 0;

        for(z = 1; z < (2 * a0nx); z = z + 2)
        {
            result = result + (sin(z * x) / z);
        }
        result = (result * 4) / M_PI;
    }
    else
        result = funk.berechne(x);

    return result;
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::DrawButtonClick(TObject *Sender)
{
	render(true);
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::MenuDrawClick(TObject *Sender)
{
	render(true);
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::MenuAddedToDrawClick(TObject *Sender)
{
    render(false);
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::render(bool reset)
{
    char fString[STR_SIZE];

    strncpy(fString, prepareFunctionString(fVonXEdit->Text).c_str(), STR_SIZE - 1);
    strcat(fString, "  ");
    funk.initBaum(fString, NULL, opt);

    float step;
    float xMax = max_x();
    float yMax = max_y();

    if(FormGraph->MenuFourierSynthesis->Checked == true)
        yMax = 2;

    if(((xMax+yMax)/2) <= 30)
        step = 0.01/((xMax+yMax)/4);
    else
        step = 0.01/(16);

    if(reset)
        axis(xMax, yMax);

    curve(xMax, yMax, step);
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::FormCreate(TObject *Sender)
{
    FormGraph->ClientHeight = 417;
    FormGraph->PanelGraph->Top = 37;
    drawingColor = clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::TimerStartTimer(TObject *Sender)
{
    float xMax = max_x();
    float yMax = max_y();

    if(FormGraph->MenuFourierSynthesis->Checked == true)
        yMax = 2;

    axis(xMax, yMax);
    TimerStart->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::EditKeyPress(TObject *Sender, char &Key)
{
    if(FormGraph->MenuFourierSynthesis->Checked == false)
    {
        if(Key == '\r')
        {
			render(true);
            Key = '\0';
        }
        if(Key == '.')
            Key = ',';
    }
    else
    {
        if(Key == '\r')
        {
			render(true);
            Key = '\0';
        }
        else if(((Key >= '0')&&(Key <= '9'))||(Key == '\x08'))
            Key = Key;
        else
            Key = '\0';
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::MenuCloseClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::MenuHomepageClick(TObject *Sender)
{
    ShellExecute(Handle, "open", "http://www.mpcx.net/", "", "", SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::MenuInfoClick(TObject *Sender)
{
    FormInfo->Position = poMainFormCenter;
    FormInfo->Visible = true;
}
//---------------------------------------------------------------------------
int max_x()
{
    int xMax;
    xMax = FormGraph->Edit_xAxis->Text.ToDouble();
    return (xMax);
}
//---------------------------------------------------------------------------
int max_y()
{
    int yMax;
    yMax = FormGraph->Edit_yAxis->Text.ToDouble();
    return (yMax);
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::Example_1x3x025x075Click(TObject *Sender)
{
    fVonXEdit->Text = "x^3-3x^2-0,25x+0,75";
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::Example_2x3x4Click(TObject *Sender)
{
    fVonXEdit->Text = "2x^2/(3x^2-4)";
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::Example_xx4Click(TObject *Sender)
{
    fVonXEdit->Text = "x/(x^2-4)";
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::Example_xClick(TObject *Sender)
{
    fVonXEdit->Text = "x^2";
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::Example_1xClick(TObject *Sender)
{
    fVonXEdit->Text = "1/x";
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::Example_sin_xClick(TObject *Sender)
{
    fVonXEdit->Text = "sin(x)";
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::MenuSaveClick(TObject *Sender)
{
    bool x = false;
    
    if(x)
    {
        FILE * pFile;
        int returnValue = 0;
        int filterIndex = 0;
        AnsiString FileName;
        AnsiString MSG;

        if(SaveDialog1->Execute())
        {
            FileName = SaveDialog1->FileName;
            filterIndex = SaveDialog1->FilterIndex;
            pFile = fopen(FileName.c_str(), "r");
            if(pFile == NULL)
            {
                returnValue = 6;
            }
            else
            {
                fclose(pFile);
                MSG = FileName + " existiert bereits.\nMöchten Sie die Datei ersetzen?";
                returnValue = MessageBox(NULL, MSG.c_str(), "Datei speichern", MB_YESNO | MB_ICONEXCLAMATION);
            }
            if(returnValue == 6)
            {
                if(filterIndex == 1 || filterIndex == 2 || filterIndex == 4 || filterIndex == 5)
                {
                    GdiplusStartupInput gdiplusStartupInput;
                    ULONG_PTR gdiplusToken;
                    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

                    CLSID    encoderClsid;
                    Image*   image;
                    WCHAR    filename[1024];

                    FormGraph->PaintBox->Picture->SaveToFile("graph.tmp");

                    image = new Image(L"graph.tmp");

                    if(filterIndex == 1)
                    {
                        GetEncoderClsid(L"image/png", &encoderClsid);
                    }
                    if(filterIndex == 2)
                    {
                        GetEncoderClsid(L"image/jpeg", &encoderClsid);
                    }
                    if(filterIndex == 4)
                    {
                        GetEncoderClsid(L"image/tiff", &encoderClsid);
                    }
                    if(filterIndex == 5)
                    {
                        GetEncoderClsid(L"image/gif", &encoderClsid);
                    }

                    image->Save((FileName.WideChar(filename, 1024)), &encoderClsid, NULL);

                    delete image;
                    GdiplusShutdown(gdiplusToken);
                }

                if(filterIndex == 3)
                {
                    FormGraph->PaintBox->Picture->SaveToFile(FileName);
                }
            }
        }
    }
    else
    {
        FormSave->Position = poMainFormCenter;
        FormSave->Visible = true;
        FormSave->EditSave->SetFocus();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::changeWindow()
{
    if(FormGraph->MenuSpecial->Checked == true)
    {
        if((FormGraph->MenuFourierSynthesis->Checked == false)||(FormGraph->Edit8->Text != ""))
        {
			FormGraph->render(true);
        }
        else
        {
            FormGraph->TimerStart->Enabled = true;
        }
    }
    else
    {
        FormGraph->TimerStart->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::MenuNormalClick(TObject *Sender)
{
    if(FormGraph->MenuSpecial->Checked == true)
    {
        TimerStart->Enabled = true;
    }

    FormGraph->fVonXEdit->Visible = true;
    FormGraph->Label_y->Visible = true;

    FormGraph->MenuSpecial->Checked = false;
    FormGraph->MenuNormal->Checked = true;
    FormGraph->MenuFourierSynthesis->Checked = false;

    FormGraph->Edit8->Visible = false;
    FormGraph->Edit8->Text = "";

    FormGraph->ClientHeight = 417;

    FormGraph->DrawButton->Top = 6;
    FormGraph->PanelGraph->Top = 37;

    FormGraph->MenuDraw->Enabled = true;
    FormGraph->DrawButton->Visible = true;

    FormGraph->LabelSpecial->Visible = false;
    FormGraph->LabelSpecial->Caption = "";
    FormGraph->ImageGDI->Visible = false;
    FormGraph->Label_nharm->Visible = false;

    FormGraph->Menu_yAxis->Enabled = true;
    FormGraph->MenuExamples->Visible = true;
    FormGraph->MenuAddedToDraw->Enabled = true;
    FormGraph->MenuDraw->Enabled = true;
    FormGraph->DrawButton->Visible = true;

    TimerStart->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::MenuFourierSynthesisClick(TObject *Sender)
{
    FormGraph->MenuSpecial->Checked = true;
    FormGraph->MenuFourierSynthesis->Checked = true;

    FormGraph->fVonXEdit->Visible = false;
    FormGraph->Label_y->Visible = false;
    FormGraph->MenuNormal->Checked = false;

    FormGraph->Edit8->Visible = true;
    FormGraph->Edit8->Text = "";

    FormGraph->ClientHeight = 449;

    FormGraph->DrawButton->Top = 38;
    FormGraph->PanelGraph->Top = 69;

    FormGraph->LabelSpecial->Caption = "Fourier-Synthese";
    FormGraph->LabelSpecial->Left = (FormGraph->ClientWidth - FormGraph->LabelSpecial->Width)/2;
    FormGraph->LabelSpecial->Visible = false;
    FormGraph->ImageGDI->Visible = true;
    FormGraph->Label_nharm->Visible = true;

    FormGraph->Menu_yAxis->Enabled = false;
    FormGraph->MenuExamples->Visible = false;
    FormGraph->MenuAddedToDraw->Enabled = false;
    FormGraph->MenuDraw->Enabled = true;
    FormGraph->DrawButton->Visible = true;

    TimerStart->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::Menu_xAxisValueClick(TObject *Sender)
{
    FormGraph->Panel_xAxis->Visible = true;
    FormGraph->Edit_xAxis->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::Button_xAchesClick(TObject *Sender)
{
    if(Edit_xAxis->Text.ToDouble() >= 50) Edit_xAxis->Text = 50;
    if(Edit_xAxis->Text.ToDouble() <= 1) Edit_xAxis->Text = 1;

    if(Menu_yAxisX->Checked == true)
    {
        Edit_yAxis->Text = Edit_xAxis->Text;
    }

    FormGraph->Panel_xAxis->Visible = false;

    changeWindow();

    if(FormGraph->fVonXEdit->Visible == true)
        FormGraph->fVonXEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::Edit_xAxisKeyPress(TObject *Sender, char &Key)
{
    if(Key == '\r')
    {
        Button_xAchesClick(NULL);
        Key = '\0';
    }
    else if(((Key >= '0')&&(Key <= '9'))||(Key == '\x08'))
        Key = Key;
    else
        Key = '\0';
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::Menu_yAxisXClick(TObject *Sender)
{
    if(Menu_yAxisX->Checked == true)
    {
        Menu_yAxisX->Checked = false;
        Menu_yAxisValue->Enabled = true;
    }
    else
    {
        Menu_yAxisX->Checked = true;
        Menu_yAxisValue->Enabled = false;
        Edit_yAxis->Text = Edit_xAxis->Text;
        changeWindow();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::Menu_yAxisValueClick(TObject *Sender)
{
    FormGraph->Panel_yAxis->Visible = true;
    FormGraph->Edit_yAxis->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::Button_yAxisClick(TObject *Sender)
{
    if(Edit_yAxis->Text.ToDouble() >= 50)
        Edit_yAxis->Text = 50;
    if(Edit_yAxis->Text.ToDouble() <= 1)
        Edit_yAxis->Text = 1;

    FormGraph->Panel_yAxis->Visible = false;

    changeWindow();

    if(FormGraph->fVonXEdit->Visible == true)
        FormGraph->fVonXEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::Edit_yAxisKeyPress(TObject *Sender, char &Key)
{
    if(Key == '\r')
    {
        Button_yAxisClick(NULL);
        Key = '\0';
    }
    else if(((Key >= '0')&&(Key <= '9'))||(Key == '\x08'))
        Key = Key;
    else
        Key = '\0';
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::MenuColorClick(TObject *Sender)
{
    if(ColorDialog->Execute())
        drawingColor = ColorDialog->Color;
}
//---------------------------------------------------------------------------


