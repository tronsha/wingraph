//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USEFORM("graph.cpp", FormGraph);
USEFORM("graph_info.cpp", FormInfo);
USEFORM("graph_save.cpp", FormSave);
USEFORM("graph_out.cpp", FormGraphOut);
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
		Application->CreateForm(__classid(TFormGraphOut), &FormGraphOut);
		Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
