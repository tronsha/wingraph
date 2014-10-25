//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "graph_info.h"
#include "mpcx_wingraph.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormInfo *FormInfo;
//---------------------------------------------------------------------------
__fastcall TFormInfo::TFormInfo(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::LabelInfoURLClick(TObject *Sender)
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
    LabelInfoName->Caption = INFO_PROGRAMM;
    LabelInfoCopyName->Caption = INFO_COPYRIGHT;
    LabelInfoURL->Caption = INFO_HOMEPAGE;
    LabelInfoVersionNummer->Caption = INFO_VERSION;
}
//---------------------------------------------------------------------------

