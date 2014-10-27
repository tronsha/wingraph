//---------------------------------------------------------------------------
#ifndef SaveFormH
#define SaveFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormSave : public TForm
{
__published:    // IDE-managed Components
        TButton *ButtonSave;
        TEdit *EditSave;
        TLabel *LabelSave;
        TButton *ButtonCancel;
        TMainMenu *MainMenuSave;
        TMenuItem *MenuSaveJPEG;
        TMenuItem *MenuSaveBMP;
        TMenuItem *MenuSavePNG;
        TMenuItem *MenuSaveTIFF;
        TMenuItem *MenuSaveGIF;
        void __fastcall ButtonSaveClick(TObject *Sender);
        void __fastcall ButtonCancelClick(TObject *Sender);
        void __fastcall EditSaveKeyPress(TObject *Sender, char &Key);
        void __fastcall FormDeactivate(TObject *Sender);
        void __fastcall MenuSaveJPEGClick(TObject *Sender);
        void __fastcall MenuSaveBMPClick(TObject *Sender);
        void __fastcall MenuSavePNGClick(TObject *Sender);
        void __fastcall MenuSaveTIFFClick(TObject *Sender);
        void __fastcall MenuSaveGIFClick(TObject *Sender);
private:    // User declarations
public:     // User declarations
        __fastcall TFormSave(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSave *FormSave;
//---------------------------------------------------------------------------
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

   Gdiplus::GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}
//---------------------------------------------------------------------------
#endif