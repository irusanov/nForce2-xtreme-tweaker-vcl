#ifndef AppSettingsH
#define AppSettingsH

#include <vcl.h>
#include <IniFiles.hpp>

#define FILENAME "settings.ini"

class AppSettings {
private:

public:
    // General options
    bool MinimizeToTray;
    bool MinimizeHintShown;
    bool SaveWindowPosition;
    int WindowTop;
    int WindowLeft;

    // Auto-validation Bot options
    AnsiString CpuzPath;
    int Sleep;
    int Step;
    bool Ultra;

    // Load settings.ini
    void load() {
        // Settings INI file
        AnsiString Path = ExtractFilePath(Application->ExeName);
        TIniFile *Settings = new TIniFile(Path + FILENAME);

        MinimizeToTray = Settings->ReadBool("Options", "MinimizeToTray", false);
        MinimizeHintShown = Settings->ReadBool("Options", "MinimizeHintShown", false);
        SaveWindowPosition = Settings->ReadBool("Options", "SaveWindowPosition", false);

        WindowTop = Settings->ReadInteger("Options", "WindowTop", 0);
        WindowLeft = Settings->ReadInteger("Options", "WindowLeft", 0);

        CpuzPath = Settings->ReadString("Bot", "CpuzPath", "");
        Sleep = Settings->ReadInteger("Bot", "Sleep", 6);
        Step = Settings->ReadInteger("Bot", "Step", 0);
        Ultra = Settings->ReadBool("Bot", "Ultra", false);

        //Settings->Free();

        delete Settings;
    }

    // Save settings.ini
    void save() {
        // Settings INI file
        AnsiString Path = ExtractFilePath(Application->ExeName);
        TIniFile *Settings = new TIniFile(Path + FILENAME);

        Settings->WriteBool("Options", "MinimizeToTray", MinimizeToTray);
        Settings->WriteBool("Options", "MinimizeHintShown", MinimizeHintShown);
        Settings->WriteBool("Options", "SaveWindowPosition", SaveWindowPosition);

        if (Application->MainForm->WindowState == wsNormal) {
            Settings->WriteInteger("Options", "WindowTop",
                    SaveWindowPosition ? Application->MainForm->Top : 0);
            Settings->WriteInteger("Options", "WindowLeft",
                    SaveWindowPosition ? Application->MainForm->Left : 0);
        }

        Settings->WriteString("Bot", "CpuzPath", CpuzPath);
        Settings->WriteInteger("Bot", "Sleep", Sleep);
        Settings->WriteInteger("Bot", "Step", Step);
        Settings->WriteBool("Bot", "Ultra", Ultra);

        delete Settings;
    }

    void reset() {
        DeleteFile(FILENAME);
        load();
    }
};

#endif
