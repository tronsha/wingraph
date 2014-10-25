//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "graph_out.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormGraphOut *FormGraphOut;
//---------------------------------------------------------------------------
int igOldMouseX, igOldMouseY;
//---------------------------------------------------------------------------
__fastcall TFormGraphOut::TFormGraphOut(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormGraphOut::PaintBoxMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (Button == mbLeft)
  {
    igOldMouseX = X;
    igOldMouseY = Y;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphOut::PaintBoxMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  int iDeltaX, iDeltaY;
  if (Shift.Contains(ssLeft))
  {
    iDeltaX = X - igOldMouseX;
    iDeltaY = Y - igOldMouseY;
    Top = Top + iDeltaY;
    Left = Left + iDeltaX;
  }
}
//---------------------------------------------------------------------------

