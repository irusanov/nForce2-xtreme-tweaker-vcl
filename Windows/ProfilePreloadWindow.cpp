// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "../NForce2XTForm.h"
#include "ProfilePreloadWindow.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProfilePreloadForm *ProfilePreloadForm;

// ---------------------------------------------------------------------------
__fastcall TProfilePreloadForm::TProfilePreloadForm(TComponent* Owner)
    : TForm(Owner) {
}
// ---------------------------------------------------------------------------

void __fastcall TProfilePreloadForm::SetApplyButtonState() {
    ButtonLoadProfile->Enabled = CheckBoxTimings->Checked ||
        CheckBoxDSSR->Checked || CheckBoxAdvanced->Checked ||
        CheckBoxRomsip->Checked;
}
// ---------------------------------------------------------------------------

void __fastcall TProfilePreloadForm::ButtonLoadProfileClick(TObject *Sender) {
    ProfilesManager::profile_options_t Options = {};
    Options.timings = CheckBoxTimings->Checked;
    Options.dssr = CheckBoxDSSR->Checked;
    Options.advanced = CheckBoxAdvanced->Checked;
    Options.romsip = CheckBoxRomsip->Checked;

    MainForm->profiles.load(MainForm->profiles.previewMetadata.path, Options);

    Close();
}
// ---------------------------------------------------------------------------

void __fastcall TProfilePreloadForm::FormShow(TObject *Sender) {
    ProfilesManager::profile_metadata_t data =
        MainForm->profiles.previewMetadata;

    CheckBoxTimings->Checked = data.options.timings;
    CheckBoxDSSR->Checked = data.options.dssr;
    CheckBoxAdvanced->Checked = data.options.advanced;
    CheckBoxRomsip->Checked = data.options.romsip;

    CheckBoxTimings->Enabled = data.options.timings;
    CheckBoxDSSR->Enabled = data.options.dssr;
    CheckBoxAdvanced->Enabled = data.options.advanced;
    CheckBoxRomsip->Enabled = data.options.romsip;

    PanelName->Text = data.options.name;
    PanelAuthor->Text = data.options.author;
    PanelComment->Text = data.options.comment;
}
// ---------------------------------------------------------------------------

void __fastcall TProfilePreloadForm::SectionCheckBoxClick(TObject *Sender) {
    SetApplyButtonState();
}
// ---------------------------------------------------------------------------
