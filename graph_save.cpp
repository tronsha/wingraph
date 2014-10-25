//---------------------------------------------------------------------------

#define STRICT
#define INITGUID
#include <vcl.h>
#undef INITGUID
#include <windows.h>
#include <initguid.h>
#include <gdiplus.h>
#include <stdio.h>
#pragma hdrstop

#include "graph_save.h"
#include "graph.h"
#include "graph_out.h"

using namespace Gdiplus;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSave *FormSave;
//---------------------------------------------------------------------------
void speicher();
//---------------------------------------------------------------------------
__fastcall TFormSave::TFormSave(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSave::ButtonSaveClick(TObject *Sender)
{
    speicher();
}
//---------------------------------------------------------------------------
void __fastcall TFormSave::ButtonAbbrechenClick(TObject *Sender)
{
    Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormSave::EditSaveKeyPress(TObject *Sender, char &Key)
{
    if (Key == '\x0D')
    {
        speicher();
        Key = '\0';
    }
    else
    {
        if (((Key >= 'a')&&(Key <= 'z'))||((Key >= 'A')&&(Key <= 'Z'))||((Key >= '0')&&(Key <= '9'))||(Key == '\x08')||(Key == '_')||(Key == '-')||(Key == ':')||(Key == '.')||(Key == '\\')||(Key == '�')||(Key == '�')||(Key == '�')||(Key == '�')||(Key == '�')||(Key == '�'))
            Key = Key;
        else
            Key = '\0';
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormSave::FormDeactivate(TObject *Sender)
{
    Visible = false;
}
//---------------------------------------------------------------------------

void speicher()
{
	FILE * pDatei;
    int rueckwert = 0;
    AnsiString FileName;
    int FilterIndex = 0;
    AnsiString MSG;

    FileName = ChangeFileExt(FormSave->EditSave->Text, FormSave->LabelSave->Caption);

    if(FormSave->LabelSave->Caption == ".png")
        FilterIndex = 1;
	if(FormSave->LabelSave->Caption == ".bmp")
		FilterIndex = 2;
	if(FormSave->LabelSave->Caption == ".gif")
		FilterIndex = 3;
	if(FormSave->LabelSave->Caption == ".tif")
		FilterIndex = 4;
	if(FormSave->LabelSave->Caption == ".jpg")
		FilterIndex = 5;
    pDatei = fopen(FileName.c_str(), "r");
    if(pDatei == NULL)
    {
        rueckwert = 6;
    }
    else
    {
        fclose(pDatei);
        MSG = FileName + " existiert bereits.\nM�chten Sie die Datei ersetzen?";
        rueckwert = MessageBox(NULL, MSG.c_str(), "Datei speichern", MB_YESNO | MB_ICONEXCLAMATION);
    }
    if(rueckwert == 6)
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
			GetEncoderClsid(L"image/bmp", &encoderClsid);
		}
		if(FilterIndex == 3)
		{
			GetEncoderClsid(L"image/gif", &encoderClsid);
		}
		if(FilterIndex == 4)
		{
			GetEncoderClsid(L"image/tiff", &encoderClsid);
		}
		if(FilterIndex == 5)
		{
			GetEncoderClsid(L"image/jpeg", &encoderClsid);
		}

		image->Save((FileName.WideChar(filename, 1024)), &encoderClsid, NULL);

		delete image;
		GdiplusShutdown(gdiplusToken);
		remove("graph.tmp");
	}

    FormSave->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormSave::MenuSaveJPEGClick(TObject *Sender)
{
    LabelSave->Caption = ".jpg";
}
//---------------------------------------------------------------------------

void __fastcall TFormSave::MenuSaveBitmapsClick(TObject *Sender)
{
    LabelSave->Caption = ".bmp";
}
//---------------------------------------------------------------------------

void __fastcall TFormSave::MenuSavePNGClick(TObject *Sender)
{
	LabelSave->Caption = ".png";
}
//---------------------------------------------------------------------------


void __fastcall TFormSave::MenuSaveTIFFClick(TObject *Sender)
{
	LabelSave->Caption = ".tif";
}
//---------------------------------------------------------------------------

void __fastcall TFormSave::MenuSaveGIFClick(TObject *Sender)
{
	LabelSave->Caption = ".gif";
}
//---------------------------------------------------------------------------

