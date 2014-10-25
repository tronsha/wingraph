//---------------------------------------------------------------------------

#ifndef graph_outH
#define graph_outH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormGraphOut : public TForm
{
__published:	// IDE-managed Components
        TImage *PaintBox;
        void __fastcall PaintBoxMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall PaintBoxMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
        __fastcall TFormGraphOut(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormGraphOut *FormGraphOut;
//---------------------------------------------------------------------------
#endif
