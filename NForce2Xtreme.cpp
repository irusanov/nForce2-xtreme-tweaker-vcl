// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
// ---------------------------------------------------------------------------
USEFORM("Windows\ProfilePreloadWindow.cpp", ProfilePreloadForm);
USEFORM("Windows\AboutWindow.cpp", AboutDialog);
USEFORM("Windows\ProfileSaveWindow.cpp", ProfileSaveForm);
USEFORM("Windows\ValidationBot.cpp", ValidationBotDialog);
USEFORM("Windows\SettingsWindow.cpp", SettingsForm);
USEFORM("NForce2XTForm.cpp", MainForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
    try {
        Application->Initialize();
        Application->MainFormOnTaskBar = true;
        Application->Title = "nForce2XT";
        Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->CreateForm(__classid(TAboutDialog), &AboutDialog);
         Application->CreateForm(__classid(TProfilePreloadForm), &ProfilePreloadForm);
         Application->CreateForm(__classid(TProfileSaveForm), &ProfileSaveForm);
         Application->CreateForm(__classid(TSettingsForm), &SettingsForm);
         Application->CreateForm(__classid(TValidationBotDialog), &ValidationBotDialog);
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
