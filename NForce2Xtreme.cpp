// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
// ---------------------------------------------------------------------------
USEFORM("ProfileSaveWindow.cpp", ProfileSaveForm);
USEFORM("ProfilePreloadWindow.cpp", ProfilePreloadForm);
USEFORM("SettingsWindow.cpp", SettingsForm);
USEFORM("ValidationBot.cpp", ValidationBotDialog);
USEFORM("AboutWindow.cpp", AboutDialog);
USEFORM("NForce2XTForm.cpp", MainForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
    try {
        Application->Initialize();
        Application->MainFormOnTaskBar = true;
        Application->Title = "nForce2XT";
        Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->CreateForm(__classid(TAboutDialog), &AboutDialog);
         Application->CreateForm(__classid(TValidationBotDialog), &ValidationBotDialog);
         Application->CreateForm(__classid(TSettingsForm), &SettingsForm);
         Application->CreateForm(__classid(TProfileSaveForm), &ProfileSaveForm);
         Application->CreateForm(__classid(TProfilePreloadForm), &ProfilePreloadForm);
         Application->Run();
    }
    catch (Exception &exception) {
        Application->ShowException(&exception);
    }
    catch (...) {
        try {
            throw Exception("");
        }
        catch (Exception &exception) {
            Application->ShowException(&exception);
        }
    }
    return 0;
}
// ---------------------------------------------------------------------------
