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
#include "mpcx_wingraph.h"
#include "graph.h"
#include "graph_info.h"
#include "graph_save.h"
#include "graph_out.h" 

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
int FunktionColor = 0;
//---------------------------------------------------------------------------

AnsiString AddUnsichtbareMalzeichen(AnsiString in)
{
    int laenge = in.Length();
    int i, j;
    char funk_alt[STR_SIZE];
    char funk_neu[STR_SIZE*2];
    AnsiString out;

    funk_neu[0] = '\0';

    strncpy(funk_alt, in.c_str(), STR_SIZE);

    for(i = 0, j = 0; i < laenge; i++, j++)
    {
        funk_neu[j] = funk_alt[i];
        if(funk_alt[i] >= '0' && funk_alt[i] <= '9' && (funk_alt[i+1] == 'x' || funk_alt[i+1] == '('))
        {
            j++;
            funk_neu[j] = '*';
        }
        funk_neu[j+1] = '\0';
    }
    funk_neu[j] = '\0';
    out = funk_neu;
    return out;
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


    // Graph Out Start
    FormGraphOut->PaintBox->Canvas->Pen->Color = clWhite;
    FormGraphOut->PaintBox->Canvas->Pen->Width = 1500;
    FormGraphOut->PaintBox->Canvas->MoveTo(0, WY/2);
    FormGraphOut->PaintBox->Canvas->LineTo(WX, WY/2);

    FormGraphOut->PaintBox->Canvas->Pen->Color=clBlack;
    FormGraphOut->PaintBox->Canvas->Pen->Width=1;

    FormGraphOut->PaintBox->Canvas->MoveTo(0, WY/2);
    FormGraphOut->PaintBox->Canvas->LineTo(WX, WY/2);
    FormGraphOut->PaintBox->Canvas->MoveTo(WX/2,0);
    FormGraphOut->PaintBox->Canvas->LineTo(WX/2,WY);

    for (i = -x+1; i <= x-1; i++)
    {
        FormGraphOut->PaintBox->Canvas->MoveTo(WX/2-WX/2*i/x,WY/2-2);
        FormGraphOut->PaintBox->Canvas->LineTo(WX/2-WX/2*i/x,WY/2+3);
    }
    for (i = -y+1; i <= y-1; i++)
    {
        FormGraphOut->PaintBox->Canvas->MoveTo(WX/2-2,WY/2-WY/2*i/y);
        FormGraphOut->PaintBox->Canvas->LineTo(WX/2+3,WY/2-WY/2*i/y);
    }

    FormGraphOut->PaintBox->Canvas->MoveTo(WX,WY/2);
    FormGraphOut->PaintBox->Canvas->LineTo(WX-9,WY/2+3);
    FormGraphOut->PaintBox->Canvas->MoveTo(WX,WY/2);
    FormGraphOut->PaintBox->Canvas->LineTo(WX-9,WY/2-3);
    FormGraphOut->PaintBox->Canvas->MoveTo(WX/2,0);
    FormGraphOut->PaintBox->Canvas->LineTo(WX/2-3,9);
    FormGraphOut->PaintBox->Canvas->MoveTo(WX/2,0);
    FormGraphOut->PaintBox->Canvas->LineTo(WX/2+3,9);

    FormGraphOut->PaintBox->Canvas->TextOut(WX-12,WY/2+4,"X");
    FormGraphOut->PaintBox->Canvas->TextOut(WX/2-14,2,"Y");
    // Graph Out Ende
}
//---------------------------------------------------------------------------

float scale_x(float xMax)
{
    float erg;
    erg = (WX/2) / xMax;
    return erg;
}
//---------------------------------------------------------------------------

float scale_y(float yMax)
{
    float erg;
    erg = (WY/2) / yMax;
    return erg;
}
//---------------------------------------------------------------------------

void curve(float xMax, float yMax, float STEP)
{
    float x, scale_x2,scale_y2;
    int pos_y,pos_x;

    FormGraph->PaintBox->Canvas->Pen->Color = FunktionColor;
    FormGraph->PaintBox->Canvas->Pen->Width = 1;

    scale_x2=scale_x(xMax);
    scale_y2=scale_y(yMax);

    pos_x=-xMax*scale_x2;
    pos_y=FormGraph->y(-xMax)*scale_y2;

    FormGraph->PaintBox->Canvas->MoveTo(WX/2 + pos_x, WY/2 - pos_y);

    for(x=-xMax;x<=xMax;x=x+STEP)
    {
        pos_y = (FormGraph->y(x) * scale_y2);
        pos_x = (x * scale_x2);

        if (((WY/2 - pos_y) >= -2*WY) && ((WY/2 - pos_y) <= WY+2*WY))
            FormGraph->PaintBox->Canvas->LineTo(WX/2 + pos_x, WY/2 - pos_y);
        else
            FormGraph->PaintBox->Canvas->MoveTo(WX/2 + pos_x, WY/2 - pos_y);
    }

	FormGraphOut->PaintBox->Canvas->Pen->Color = FunktionColor;
    FormGraphOut->PaintBox->Canvas->Pen->Width = 1;

    scale_x2=scale_x(xMax);
    scale_y2=scale_y(yMax);

    pos_x=-xMax*scale_x2;
    pos_y=FormGraph->y(-xMax)*scale_y2;

    FormGraphOut->PaintBox->Canvas->MoveTo(WX/2 + pos_x, WY/2 - pos_y);

    for(x=-xMax;x<xMax;x=x+STEP)
    {
        pos_y = (FormGraph->y(x) * scale_y2);
        pos_x = (x * scale_x2);

        if(((WY/2 - pos_y) >= -2*WY) && ((WY/2 - pos_y) <= WY+2*WY))
            FormGraphOut->PaintBox->Canvas->LineTo(WX/2 + pos_x, WY/2 - pos_y);
        else
            FormGraphOut->PaintBox->Canvas->MoveTo(WX/2 + pos_x, WY/2 - pos_y);
    }
}
//---------------------------------------------------------------------------

//float y(x)
double __fastcall TFormGraph::y(double x)
{
    double erg;

    double a0nx;
    if(FormGraph->Edit8->Text != "")
        a0nx = FormGraph->Edit8->Text.ToDouble();
    else
        a0nx = 0;

    if(FormGraph->FourierSynthese1->Checked == true)
    {
        int z;
        float Ergebnis;

        Ergebnis = 0;

        for(z = 1; z < (2*a0nx); z = z + 2)
        {
            Ergebnis = Ergebnis + (sin(z*x)/z);
        }
        Ergebnis = (Ergebnis*4)/M_PI;
        erg = Ergebnis;
    }
    else
        erg = funk.berechne(x);

    return erg; // Ergebnisübergabe
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::ZeichneButtonClick(TObject *Sender)
{
    zeichne();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::MenuZeichneClick(TObject *Sender)
{
    zeichne();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::MenuZeichneNeuClick(TObject *Sender)
{
    zeichne2();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::zeichne()
{
    char fString[STR_SIZE];
    bool fehler;

    strncpy(fString, AddUnsichtbareMalzeichen(fVonXEdit->Text).c_str(), STR_SIZE - 1);
    strcat(fString, "  ");
    funk.initBaum(fString, NULL, opt);

    float xMax = max_x();

    float yMax = max_y();

    if(FormGraph->FourierSynthese1->Checked == true)
        yMax = 2;

    float STEP;

    if(((xMax+yMax)/2) <= 30)
        STEP = 0.01/((xMax+yMax)/4);
    else
        STEP = 0.01/(16);

    axis(xMax, yMax);
    curve(xMax, yMax, STEP);
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::zeichne2()
{
    char fString[STR_SIZE];
    bool fehler;
    strncpy(fString, AddUnsichtbareMalzeichen(fVonXEdit->Text).c_str(), STR_SIZE - 1);
    strcat(fString, "  ");
    funk.initBaum(fString, NULL, opt);

    float xMax = max_x();

    float yMax = max_y();

    float STEP;

    if(((xMax+yMax)/2) <= 30)
        STEP = 0.01/((xMax+yMax)/4);
    else
        STEP = 0.01/(16);

    curve(xMax, yMax, STEP);
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::FormCreate(TObject *Sender)
{
    FormGraph->ClientHeight = 417;
    FormGraph->PanelGraph->Top = 37;
	FunktionColor = clBlack;
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::TimerStartTimer(TObject *Sender)
{
    float xMax = max_x();
  
    float yMax = max_y();

    if(FormGraph->FourierSynthese1->Checked == true)
        yMax = 2;

    axis(xMax, yMax);
    TimerStart->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TFormGraph::EditKeyPress(TObject *Sender, char &Key)
{
    if(FormGraph->FourierSynthese1->Checked == false)
    {
        if(Key == '\r')
        {
            zeichne();
            Key = '\0';
        }
        if(Key == '.')
            Key = ',';
    }
    else
    {
        if(Key == '\r')
        {
            zeichne();
            Key = '\0';
        }
        else if(((Key >= '0')&&(Key <= '9'))||(Key == '\x08'))
            Key = Key;
        else
            Key = '\0';
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::MenuBeendenClick(TObject *Sender)
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
    //Application->Initialize();
    //Application->CreateForm(__classid(TFormInfo), &FormInfo);
    //Application->Run();
    //ShellAbout(Handle, "WinGraph","Version 1.0.0.0 \nDiese Anwendung darf frei kopiert werden!", Application->Icon->Handle);
}
//---------------------------------------------------------------------------

int max_x()
{
    int xMax;
    xMax = FormGraph->Edit_xAchse->Text.ToDouble();
    return (xMax);
}
//---------------------------------------------------------------------------

int max_y()
{
    int yMax;
    yMax = FormGraph->Edit_yAchse->Text.ToDouble();
    return (yMax);
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::Beispiel1x3x025x075Click(TObject *Sender)
{
    fVonXEdit->Text = "x^3-3x^2-0,25x+0,75";
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::Beispiel2x3x4Click(TObject *Sender)
{
    fVonXEdit->Text = "2x^2/(3x^2-4)";
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::Beispielxx4Click(TObject *Sender)
{
    fVonXEdit->Text = "x/(x^2-4)";
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::BeispielxClick(TObject *Sender)
{
    fVonXEdit->Text = "x^2";
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::Beispiel1xClick(TObject *Sender)
{
    fVonXEdit->Text = "1/x";
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::BeispielsinxClick(TObject *Sender)
{
    fVonXEdit->Text = "sin(x)";
}
//---------------------------------------------------------------------------
void __fastcall TFormGraph::MenuSpeichernClick(TObject *Sender)
{
    bool x = false;
    
    if(x)
    {
        FILE * pDatei;
        int rueckwert = 0;
        AnsiString FileName;
        int FilterIndex = 0;
        AnsiString MSG;

        if(SaveDialog1->Execute())
        {
            FileName = SaveDialog1->FileName;
            FilterIndex = SaveDialog1->FilterIndex;
            pDatei = fopen(FileName.c_str(), "r");
            if(pDatei == NULL)
            {
                rueckwert = 6;
            }
            else
            {
                fclose(pDatei);
                MSG = FileName + " existiert bereits.\nMöchten Sie die Datei ersetzen?";
				rueckwert = MessageBox(NULL, MSG.c_str(), "Datei speichern", MB_YESNO | MB_ICONEXCLAMATION);
			}
			if(rueckwert == 6)
			{
				if(FilterIndex == 1 || FilterIndex == 2 || FilterIndex == 4 || FilterIndex == 5)
				{
					GdiplusStartupInput gdiplusStartupInput;
					ULONG_PTR gdiplusToken;
					GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

					CLSID    encoderClsid;
					Image*   image;
					WCHAR    filename[1024];

					if(FormGraph->MenuNein->Checked == true)
					{
						FormGraph->PaintBox->Picture->SaveToFile("graph.tmp");
					}
					else
					{
						FormGraphOut->PaintBox->Picture->SaveToFile("graph.tmp");
					}

					image = new Image(L"graph.tmp");

					if(FilterIndex == 1)
					{
						GetEncoderClsid(L"image/png", &encoderClsid);
					}
					if(FilterIndex == 2)
					{
						GetEncoderClsid(L"image/jpeg", &encoderClsid);
					}
					if(FilterIndex == 4)
					{
						GetEncoderClsid(L"image/tiff", &encoderClsid);
					}
					if(FilterIndex == 5)
					{
						GetEncoderClsid(L"image/gif", &encoderClsid);
					}

					image->Save((FileName.WideChar(filename, 1024)), &encoderClsid, NULL);

					delete image;
					GdiplusShutdown(gdiplusToken);

				}

				if(FilterIndex == 3)
				{
					if(FormGraph->MenuNein->Checked == true)
					{
						FormGraph->PaintBox->Picture->SaveToFile(FileName);
					}
					else
					{
						FormGraphOut->PaintBox->Picture->SaveToFile(FileName);
					}
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

void __fastcall TFormGraph::MenuNeinClick(TObject *Sender)
{
    //FormGraph->MenuNein->Checked = true;
    //FormGraph->MenuJa->Checked = false;

    FormGraphOut->Visible = false;

    WX = 375;
    WY = 375;

    FormGraph->MenuOutGroesse->Visible = false;
    FormGraph->NLinie3->Visible = false;

    FormGraph->MenuSpeichern->Enabled = true;

    FormGraph->MenuDrucken->Enabled = false;

    if(FormGraph->MenuNormal->Checked == true)
    {
        FormGraph->ClientHeight = 417;
    }
    if(FormGraph->MenuSonder->Checked == true)
    {
        FormGraph->ClientHeight = 449;
    }

    aender_fenster();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::MenuJaClick(TObject *Sender)
{
    //FormGraph->MenuNein->Checked = false;
    //FormGraph->MenuJa->Checked = true;
    FormGraphOut->PaintBox->Height = EditOutGroesse->Text.ToDouble();
    FormGraphOut->PaintBox->Width = EditOutGroesse->Text.ToDouble();
    FormGraphOut->Visible = true;
    FormGraphOut->Left = 0;
    FormGraphOut->Top = 0;
    FormGraphOut->ClientHeight = EditOutGroesse->Text.ToDouble();
    FormGraphOut->ClientWidth = EditOutGroesse->Text.ToDouble();
    WX = EditOutGroesse->Text.ToDouble();
    WY = EditOutGroesse->Text.ToDouble();
/*
    FormGraph->MenuOutGroesse->Visible = true;
    FormGraph->NLinie3->Visible = true;
*/
    if(EditOutGroesse->Text.ToDouble() == 600)
        FormGraph->MenuSpeichern->Enabled = true;
    else
        FormGraph->MenuSpeichern->Enabled = false;

    FormGraph->MenuDrucken->Enabled = true;

    if(FormGraph->MenuNormal->Checked == true)
    {
        FormGraph->ClientHeight = 36;
    }
    if(FormGraph->MenuSonder->Checked == true)
    {
        FormGraph->ClientHeight = 68;
    }

    aender_fenster();

    if(FormGraph->fVonXEdit->Visible == true)
        FormGraph->fVonXEdit->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::aender_fenster()
{
    if(FormGraph->MenuSonder->Checked == true)
    {
        if((FormGraph->FourierSynthese1->Checked == false)||(FormGraph->Edit8->Text != ""))
        {
            FormGraph->zeichne();
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
    if(FormGraph->MenuSonder->Checked == true)
    {
        TimerStart->Enabled = true;
    }

    FormGraph->fVonXEdit->Visible = true;
    FormGraph->Label_y->Visible = true;

    FormGraph->MenuSonder->Checked = false;
    FormGraph->MenuNormal->Checked = true;
    FormGraph->FourierSynthese1->Checked = false;

    FormGraph->Edit8->Visible = false;
    FormGraph->Edit8->Text = "";

    if (FormGraph->MenuNein->Checked == true)
    {
        FormGraph->ClientHeight = 417;
    }
    else
    {
        FormGraph->ClientHeight = 36;
    }
    FormGraph->ZeichneButton->Top = 6;
    FormGraph->PanelGraph->Top = 37;

    FormGraph->MenuZeichne->Enabled = true;
    FormGraph->ZeichneButton->Visible = true;

    FormGraph->LabelSonder->Visible = false;
    FormGraph->LabelSonder->Caption = "";
    FormGraph->ImageGDI->Visible = false;
    FormGraph->Label_nharm->Visible = false;

    FormGraph->MenuyAchse->Enabled = true;
    FormGraph->MenuBeispiele->Visible = true;
    FormGraph->MenuZeichneNeu->Enabled = true;
    FormGraph->MenuZeichne->Enabled = true;
    FormGraph->ZeichneButton->Visible = true;

    TimerStart->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::FourierSynthese1Click(TObject *Sender)
{
    FormGraph->MenuSonder->Checked = true;
    FormGraph->FourierSynthese1->Checked = true;

    FormGraph->fVonXEdit->Visible = false;
    FormGraph->Label_y->Visible = false;
    FormGraph->MenuNormal->Checked = false;

    FormGraph->Edit8->Visible = true;
    FormGraph->Edit8->Text = "";

    if(FormGraph->MenuNein->Checked == true)
    {
        FormGraph->ClientHeight = 449;
    }
    else
    {
        FormGraph->ClientHeight = 68;
    }
    FormGraph->ZeichneButton->Top = 38;
    FormGraph->PanelGraph->Top = 69;

    FormGraph->LabelSonder->Caption = "Fourier-Synthese";
    FormGraph->LabelSonder->Left = (FormGraph->ClientWidth - FormGraph->LabelSonder->Width)/2;
    FormGraph->LabelSonder->Visible = false;
    FormGraph->ImageGDI->Visible = true;
    FormGraph->Label_nharm->Visible = true;

    FormGraph->MenuyAchse->Enabled = false;
    FormGraph->MenuBeispiele->Visible = false;
    FormGraph->MenuZeichneNeu->Enabled = false;
    FormGraph->MenuZeichne->Enabled = true;
    FormGraph->ZeichneButton->Visible = true;

    TimerStart->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::ButtonOutGroesseClick(TObject *Sender)
{
    if(EditOutGroesse->Text.ToDouble() >= 600)
        EditOutGroesse->Text = 600;
    if(EditOutGroesse->Text.ToDouble() <= 200)
        EditOutGroesse->Text = 200;

    if(EditOutGroesse->Text.ToDouble() == 600)
        FormGraph->MenuSpeichern->Enabled = true;
    else
        FormGraph->MenuSpeichern->Enabled = false;

    FormGraphOut->PaintBox->Height = EditOutGroesse->Text.ToDouble();
    FormGraphOut->PaintBox->Width = EditOutGroesse->Text.ToDouble();
    FormGraphOut->ClientHeight = EditOutGroesse->Text.ToDouble();
    FormGraphOut->ClientWidth = EditOutGroesse->Text.ToDouble();
    WX = EditOutGroesse->Text.ToDouble();
    WY = EditOutGroesse->Text.ToDouble();

    FormGraph->PanelOutGroesse->Visible = false;

    aender_fenster();

    if(FormGraph->fVonXEdit->Visible == true)
        FormGraph->fVonXEdit->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::MenuOutGroesseClick(TObject *Sender)
{
    FormGraph->PanelOutGroesse->Visible = true;
    FormGraph->EditOutGroesse->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::EditOutGroesseKeyPress(TObject *Sender, char &Key)
{
    if(Key == '\r')
    {
        ButtonOutGroesseClick(NULL);
        Key = '\0';
    }
    else if(((Key >= '0')&&(Key <= '9'))||(Key == '\x08'))
        Key = Key;
    else
        Key = '\0';
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::MenuxAchseWertClick(TObject *Sender)
{
    FormGraph->Panel_xAchse->Visible = true;
    FormGraph->Edit_xAchse->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::Button_xAchesClick(TObject *Sender)
{
    if(Edit_xAchse->Text.ToDouble() >= 50) Edit_xAchse->Text = 50;
    if(Edit_xAchse->Text.ToDouble() <= 1) Edit_xAchse->Text = 1;

    if(MenuyAchseX->Checked == true)
    {
        Edit_yAchse->Text = Edit_xAchse->Text;
    }

    FormGraph->Panel_xAchse->Visible = false;

    aender_fenster();

    if(FormGraph->fVonXEdit->Visible == true)
        FormGraph->fVonXEdit->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::Edit_xAchseKeyPress(TObject *Sender, char &Key)
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

void __fastcall TFormGraph::MenuyAchseXClick(TObject *Sender)
{
    if(MenuyAchseX->Checked == true)
    {
        MenuyAchseX->Checked = false;
        MenuyAchseWert->Enabled = true;
    }
    else // (MenuyAchseX->Checked == false)
    {
        MenuyAchseX->Checked = true;
        MenuyAchseWert->Enabled = false;
        Edit_yAchse->Text = Edit_xAchse->Text;
        aender_fenster();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::MenuyAchseWertClick(TObject *Sender)
{
    FormGraph->Panel_yAchse->Visible = true;
    FormGraph->Edit_yAchse->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::Button_yAchseClick(TObject *Sender)
{
    if(Edit_yAchse->Text.ToDouble() >= 50)
        Edit_yAchse->Text = 50;
    if(Edit_yAchse->Text.ToDouble() <= 1)
        Edit_yAchse->Text = 1;

    FormGraph->Panel_yAchse->Visible = false;

    aender_fenster();

    if(FormGraph->fVonXEdit->Visible == true)
        FormGraph->fVonXEdit->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::Edit_yAchseKeyPress(TObject *Sender, char &Key)
{
    if(Key == '\r')
    {
        Button_yAchseClick(NULL);
        Key = '\0';
    }
    else if(((Key >= '0')&&(Key <= '9'))||(Key == '\x08'))
        Key = Key;
    else
        Key = '\0';
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::MenuDruckenClick(TObject *Sender)
{
    FormGraphOut->Print();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::MenuColorClick(TObject *Sender)
{
    if(ColorDialog->Execute())
        FunktionColor = ColorDialog->Color;
}
//---------------------------------------------------------------------------


