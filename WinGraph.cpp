//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USEFORM("MainForm.cpp", FormGraph);
USEFORM("InfoForm.cpp", FormInfo);
USEFORM("SaveForm.cpp", FormSave);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                Application->Initialize();
                Application->Title = "WinGraph";
                Application->CreateForm(__classid(TFormGraph), &FormGraph);
                Application->CreateForm(__classid(TFormInfo), &FormInfo);
                Application->CreateForm(__classid(TFormSave), &FormSave);
                Application->Run();
        }
        catch (Exception &exception)
        {
                Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
