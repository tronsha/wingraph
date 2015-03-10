//---------------------------------------------------------------------------
#ifndef InfoFormH
#define InfoFormH
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
    __published: // IDE-managed Components
        TButton *ButtonOK;
        TLabel *LabelInfoName;
        TLabel *LabelInfoCopyright;
        TLabel *LabelInfoVersion;
        TLabel *LabelInfoHomepage;
        TLabel *LabelInfoSource;
        TLabel *LabelInfoCopyrightText;
        TLabel *LabelInfoVersionText;
        TLabel *LabelInfoHomepageText;
        TLabel *LabelInfoSourceText;
        void __fastcall LabelInfoHomepageTextClick(TObject *Sender);
        void __fastcall ButtonOKClick(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall LabelInfoSourceTextClick(TObject *Sender);
    private: // User declarations
    public:  // User declarations
        __fastcall TFormInfo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInfo *FormInfo;
//---------------------------------------------------------------------------
#endif
