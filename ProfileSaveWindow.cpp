//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NForce2XTForm.h"
#include "ProfileSaveWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProfileSaveForm *ProfileSaveForm;
//---------------------------------------------------------------------------
__fastcall TProfileSaveForm::TProfileSaveForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TProfileSaveForm::ButtonSaveProfileClick(TObject *Sender)
{
    ProfilesManager::profile_options_t Options = {};
    Options.timings = CheckBoxTimings->Checked;
    Options.dssr = CheckBoxDSSR->Checked;
    Options.advanced = CheckBoxAdvanced->Checked;
    Options.romsip = CheckBoxRomsip->Checked;

    SaveTextFileDialog1->InitialDir = MainForm->profiles.GetDefaultPath();
    SaveTextFileDialog1->Execute();

    if (SaveTextFileDialog1->FileName.Length() > 0) {
        MainForm->profiles.save(SaveTextFileDialog1->FileName, Options);
    }

    Close();
}
//---------------------------------------------------------------------------
