//---------------------------------------------------------------------------

#ifndef graph_infoH
#define graph_infoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormInfo : public TForm
{
__published:	// IDE-managed Components
        TButton *ButtonOK;
        TLabel *LabelInfoName;
        TLabel *LabelInfoCopy;
        TLabel *LabelInfoVersion;
        TLabel *LabelInfoHomepage;
        TLabel *LabelInfoURL;
        TLabel *LabelInfoCopyName;
        TLabel *LabelInfoVersionNummer;
        void __fastcall LabelInfoURLClick(TObject *Sender);
        void __fastcall ButtonOKClick(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormInfo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInfo *FormInfo;
//---------------------------------------------------------------------------
#endif
