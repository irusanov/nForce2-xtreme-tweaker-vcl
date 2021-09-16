// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NForce2XTForm.h"
#include "ProfileSaveWindow.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProfileSaveForm *ProfileSaveForm;

// ---------------------------------------------------------------------------
__fastcall TProfileSaveForm::TProfileSaveForm(TComponent* Owner) : TForm(Owner)
{
}

// ---------------------------------------------------------------------------
void __fastcall TProfileSaveForm::SetApplyButtonState() {
    ButtonSaveProfile->Enabled = CheckBoxTimings->Checked ||
        CheckBoxDSSR->Checked || CheckBoxAdvanced->Checked ||
        CheckBoxRomsip->Checked;
}

// ---------------------------------------------------------------------------
void __fastcall TProfileSaveForm::ButtonSaveProfileClick(TObject *Sender) {
    ProfilesManager::profile_options_t Options = {};
    Options.author = PanelAuthor->Text;
    Options.comment = PanelComment->Text;
    Options.timings = CheckBoxTimings->Checked;
    Options.dssr = CheckBoxDSSR->Checked;
    Options.advanced = CheckBoxAdvanced->Checked;
    Options.romsip = CheckBoxRomsip->Checked;

    SaveTextFileDialog1->InitialDir = MainForm->profiles.GetDefaultPath();

    if (SaveTextFileDialog1->Execute()) {
        if (MainForm->profiles.save(SaveTextFileDialog1->FileName, Options)) {
            Close();
        }
    }
}
// ---------------------------------------------------------------------------
void __fastcall TProfileSaveForm::SectionCheckBoxClick(TObject *Sender)
{
    SetApplyButtonState();
}
//---------------------------------------------------------------------------

