#pragma once

#define VERSION_MAJOR 1
#define VERSION_MINOR 2

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
    "DIMM0DrvStrA", "DIMM0DrvStrB", "DIMM0SlewRate", "DIMM1DrvStrA",
    "DIMM1DrvStrB", "DIMM1SlewRate", "DIMM2DrvStrA", "DIMM2DrvStrB",
    "DIMM2SlewRate"};

const String romsip[15] = {
    "Romsip48", "Romsip4C", "Romsip4D", "Romsip50", "Romsip65", "Romsip66",
    "Romsip67", "Romsip68", "Romsip69", "Romsip6A", "Romsip6B", "Romsip6C",
    "Romsip6D", "Romsip6F", "Romsip74"};

class ProfilesManager {
private:
    UnicodeString DefaultPath = ExtractFilePath(Application->ExeName) +
        "profiles\\";

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
                ini->WriteString(section, StringReplace(names[i], "Romsip", "",
                    TReplaceFlags()), box->Text);
            }
        }
    }

    void LoadRomsipValues(TIniFile* ini, String section, const String *names,
        int size) {
        int i;
        String value;
        TAdvancedEdit* box; ;

        for (i = 0; i < size; i++) {
            value = ini->ReadString(section, StringReplace(names[i], "Romsip",
                "", TReplaceFlags()), "");

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

public:
    typedef struct {
        String name;
        String author;
        String comment;
        bool timings;
        bool dssr;
        bool advanced;
        bool romsip;
    } profile_options_t;

    typedef struct {
        int versionMajor;
        int versionMinor;
        String path;
        profile_options_t options;
    } profile_metadata_t;

    UnicodeString GetDefaultPath() {
        return DefaultPath;
    }

    profile_metadata_t readMetadata(UnicodeString FilePath) {
        TIniFile *iniFile = new TIniFile(FilePath);

        previewMetadata.path = FilePath;

        previewMetadata.versionMajor =
            iniFile->ReadInteger("PMVersion", "Major", 0);
        previewMetadata.versionMinor =
            iniFile->ReadInteger("PMVersion", "Minor", 0);
        previewMetadata.options.name =
            iniFile->ReadString("Metadata", "Name", "");
        previewMetadata.options.author =
            iniFile->ReadString("Metadata", "Author", "");
        previewMetadata.options.comment =
            iniFile->ReadString("Metadata", "Comment", "");

        previewMetadata.options.timings = iniFile->SectionExists("Timings");
        previewMetadata.options.dssr = iniFile->SectionExists("DSSR");
        previewMetadata.options.advanced = iniFile->SectionExists("Advanced");
        previewMetadata.options.romsip = iniFile->SectionExists("ROMSIP");

        delete iniFile;

        return previewMetadata;
    }

    void writeMetadata(TIniFile* ini, profile_options_t Opts) {
        ini->WriteString("PMVersion", "Major", VERSION_MAJOR);
        ini->WriteString("PMVersion", "Minor", VERSION_MINOR);
        ini->WriteString("Metadata", "Name", Opts.name);
        ini->WriteString("Metadata", "Author", Opts.author);
        ini->WriteString("Metadata", "Comment", Opts.comment);
    }

    void load(UnicodeString FilePath, profile_options_t Opts) {
        TIniFile *iniFile = new TIniFile(FilePath);

        if (Opts.timings) {
            LoadTimings(iniFile, "Timings", timings, COUNT_OF(timings));
        }

        if (Opts.dssr) {
            LoadTimings(iniFile, "DSSR", dssr, COUNT_OF(dssr));
        }

        if (Opts.advanced) {
            LoadTimings(iniFile, "Advanced", advanced, COUNT_OF(advanced));
        }

        if (Opts.romsip) {
            LoadRomsipValues(iniFile, "ROMSIP", romsip, COUNT_OF(romsip));
        }

        delete iniFile;
    }

    bool save(UnicodeString FilePath, profile_options_t Opts) {
        TIniFile *iniFile = new TIniFile(FilePath);

        if (FileExists(FilePath)) {
            String msg = "Profile already exists. Do you want to overwrite it?";

            if (MessageDlg(msg, mtConfirmation, mbOKCancel, 0) != mrOk) {
                delete iniFile;
                return false;
            }

            // Save existing name, author and comment
            if (Opts.name.Length() == 0) {
                Opts.name = iniFile->ReadString("Metadata", "Name", "");
            }

            if (Opts.author.Length() == 0) {
                Opts.author = iniFile->ReadString("Metadata", "Author", "");
            }

            if (Opts.comment.Length() == 0) {
                Opts.comment = iniFile->ReadString("Metadata", "Comment", "");
            }

            iniFile->EraseSection("Timings");
            iniFile->EraseSection("DSSR");
            iniFile->EraseSection("Advanced");
            iniFile->EraseSection("ROMSIP");
        }

        writeMetadata(iniFile, Opts);

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

        return true;
    }

    void init() {
        CreateDirIfNotPresent(DefaultPath);
    }

    // Preload profile data
    profile_metadata_t previewMetadata;
};
