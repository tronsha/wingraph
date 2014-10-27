//---------------------------------------------------------------------------
#define STRICT
#define INITGUID
#include <vcl.h>
#undef INITGUID
#pragma hdrstop
#include "SaveForm.h"
#include "MainForm.h"
using namespace Gdiplus;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSave *FormSave;
//---------------------------------------------------------------------------
void save();
//---------------------------------------------------------------------------
__fastcall TFormSave::TFormSave(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSave::ButtonSaveClick(TObject *Sender)
{
    save();
}
//---------------------------------------------------------------------------
void __fastcall TFormSave::ButtonCancelClick(TObject *Sender)
{
    Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormSave::EditSaveKeyPress(TObject *Sender, char &Key)
{
    if (Key == '\x0D')
    {
        save();
        Key = '\0';
    }
    else
    {
        if (((Key >= 'a')&&(Key <= 'z'))||((Key >= 'A')&&(Key <= 'Z'))||((Key >= '0')&&(Key <= '9'))||(Key == '\x08')||(Key == '_')||(Key == '-')||(Key == ':')||(Key == '.')||(Key == '\\')||(Key == 'Ä')||(Key == 'Ö')||(Key == 'Ü')||(Key == 'ä')||(Key == 'ö')||(Key == 'ü')||(Key == 'ß'))
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
void save()
{
    FILE * pFile;
    int returnValue = 0;
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
        GdiplusStartupInput gdiplusStartupInput;
        ULONG_PTR gdiplusToken;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

        CLSID    encoderClsid;
        Image*   image;
        WCHAR    filename[1024];

        FormGraph->PaintBox->Picture->SaveToFile("graph.tmp");

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
void __fastcall TFormSave::MenuSaveBMPClick(TObject *Sender)
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
