#ifndef ProfilesManagerH
#define ProfilesManagerH

#define VERSION_MAJOR 1
#define VERSION_MINOR 0

#include <vcl.h>
#include <IniFiles.hpp>
#include "Components\TAdvancedEdit\TAdvancedEdit.h"
#include "Components\TTimingComboBox\TTimingComboBox.h"

const String timings[14] = {
    "TRCDR", "TRCDW", "TRP", "TRAS", "TRC", "TRFC", "TDOE", "TRRD", "TWTP",
    "TWTR", "TREXT", "TRTP", "TRTW", "TREF"};

const String advanced[5] = {
    "AutoPrecharge", "SuperBypass", "DataScavengedRate", "DriveStrengthMode",
    "BurstMode"};

const String dssr[9] = {
    "DIMM0DrvStrA", "DIMM0DrvStrB", "DIMM0SlewRate",
    "DIMM1DrvStrA", "DIMM1DrvStrB", "DIMM1SlewRate",
    "DIMM2DrvStrA", "DIMM2DrvStrB", "DIMM2SlewRate"};

const String romsip[10] = {
    "Romsip65", "Romsip66", "Romsip67", "Romsip68", "Romsip69", "Romsip6A",
    "Romsip6B", "Romsip6C", "Romsip6D", "Romsip6F"};

class ProfilesManager {
private:
    UnicodeString DefaultPath = ExtractFilePath(Application->ExeName) +
        "profiles";

    void CreateDirIfNotPresent(UnicodeString DirPath) {
        if (!DirectoryExists(DirPath, false)) {
            CreateDir(DirPath);
        }
    }

    void SaveTimings(TIniFile* ini, String section, const String *names,
        int size) {
        int i, value;
        TTimingComboBox* combo;

        for (i = 0; i < size; i++) {
            combo = static_cast<TTimingComboBox*>
                (Application->FindComponent("MainForm")->FindComponent
                (names[i]));

            if (combo != NULL) {
                if (combo->CustomValue) {
                    value = (unsigned int) combo->ItemValue;
                }
                else {
                    value = (unsigned int) combo->Value;
                }

                ini->WriteInteger(section, names[i], value);
            }
        }
    }

    void LoadTimings(TIniFile* ini, String section, const String *names,
        int size) {
        int i, value, currentValue;
        TTimingComboBox* combo;

        for (i = 0; i < size; i++) {
            value = ini->ReadInteger(section, names[i], -1);

            if (value == -1)
                continue;

            combo = static_cast<TTimingComboBox*>
                (Application->FindComponent("MainForm")->FindComponent
                (names[i]));

            if (combo != NULL) {
                if (combo->CustomValue)
                    currentValue = combo->ItemValue;
                else
                    currentValue = combo->Value;

                if (currentValue != value) {
                    if (combo->CustomValue)
                        combo->ItemValue = value;
                    else
                        combo->Value = value;

                    combo->setChanged();
                }
            }
        }
    }

    void SaveRomsipValues(TIniFile* ini, String section, const String *names,
        int size) {
        int i;
        TAdvancedEdit* box;

        for (i = 0; i < size; i++) {
            box = static_cast<TAdvancedEdit*>
                (Application->FindComponent("MainForm")->FindComponent
                (names[i]));

            if (box != NULL) {
                ini->WriteString(section, StringReplace(names[i], "Romsip", "", TReplaceFlags()), box->Text);
            }
        }
    }

    void LoadRomsipValues(TIniFile* ini, String section, const String *names,
        int size) {
        int i;
        String value;
        TAdvancedEdit* box; ;

        for (i = 0; i < size; i++) {
            value = ini->ReadString(section, StringReplace(names[i], "Romsip", "", TReplaceFlags()), "");

            if (value == "")
                continue;

            box = static_cast<TAdvancedEdit*>
                (Application->FindComponent("MainForm")->FindComponent
                (names[i]));

            if (box != NULL) {
                box->Text = value;
            }
        }
    }

    void WriteVersion(TIniFile* ini) {
        ini->WriteString("PMVersion", "Major", VERSION_MAJOR);
        ini->WriteString("PMVersion", "Minor", VERSION_MINOR);
    }

public:
    typedef struct {
        bool timings;
        bool dssr;
        bool advanced;
        bool romsip;
    } profile_options_t;

    UnicodeString GetDefaultPath() {
        return DefaultPath;
    }

    void load(UnicodeString FilePath) {
        CreateDirIfNotPresent(DefaultPath);

        TIniFile *iniFile = new TIniFile(FilePath);

        LoadTimings(iniFile, "Timings", timings, COUNT_OF(timings));
        LoadTimings(iniFile, "DSSR", dssr, COUNT_OF(dssr));
        LoadTimings(iniFile, "Advanced", advanced, COUNT_OF(advanced));
        LoadRomsipValues(iniFile, "ROMSIP", romsip, COUNT_OF(romsip));

        delete iniFile;
    }

    void save(UnicodeString FilePath, profile_options_t Opts) {
        CreateDirIfNotPresent(DefaultPath);

        if (FileExists(FilePath)) {
            // TODO: Add confirmation dialog
            DeleteFile(FilePath);
        }

        TIniFile *iniFile = new TIniFile(FilePath);

        WriteVersion(iniFile);

        if (Opts.timings) {
            SaveTimings(iniFile, "Timings", timings, COUNT_OF(timings));
        }

        if (Opts.dssr) {
            SaveTimings(iniFile, "DSSR", dssr, COUNT_OF(dssr));
        }

        if (Opts.advanced) {
            SaveTimings(iniFile, "Advanced", advanced, COUNT_OF(advanced));
        }

        if (Opts.romsip) {
            SaveRomsipValues(iniFile, "ROMSIP", romsip, COUNT_OF(romsip));
        }

        delete iniFile;
    }
};
#endif
