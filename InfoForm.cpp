//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "InfoForm.h"
#include "info.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormInfo *FormInfo;
//---------------------------------------------------------------------------
__fastcall TFormInfo::TFormInfo(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::LabelInfoHomepageTextClick(TObject *Sender)
{
    ShellExecute(Handle, "open", INFO_HOMEPAGE, "", "", SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::ButtonOKClick(TObject *Sender)
{
    Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::FormDeactivate(TObject *Sender)
{
    Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::FormCreate(TObject *Sender)
{
    LabelInfoName->Caption = INFO_PROGRAM;
    LabelInfoCopyrightText->Caption = INFO_COPYRIGHT;
    LabelInfoHomepageText->Caption = INFO_HOMEPAGE;
    LabelInfoVersionText->Caption = INFO_VERSION;
}
//---------------------------------------------------------------------------

