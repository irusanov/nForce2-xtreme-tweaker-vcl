//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NForce2XTForm.h"
#include "SettingsWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingsForm *SettingsForm;

//---------------------------------------------------------------------------
void __fastcall TSettingsForm::LoadOptions() {
    CheckBoxMinimizeToTray->Checked = MainForm->settings.MinimizeToTray;
    CheckBoxSaveWindowPosition->Checked = MainForm->settings.SaveWindowPosition;
    ButtonApplySettings->Enabled = false;
}
//---------------------------------------------------------------------------
__fastcall TSettingsForm::TSettingsForm(TComponent* Owner)
    : TForm(Owner)
{
    LoadOptions();
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::ButtonApplySettingsClick(TObject *Sender)
{
    MainForm->settings.MinimizeToTray = CheckBoxMinimizeToTray->Checked;
    MainForm->settings.SaveWindowPosition = CheckBoxSaveWindowPosition->Checked;
    MainForm->settings.save();
    LoadOptions();
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::ButtonResetSettingsClick(TObject *Sender)
{
    UnicodeString msg = "Do you want to reset application settings?";

    if (MessageDlg(msg, mtConfirmation, mbOKCancel, 0) == mrOk) {
        MainForm->settings.reset();
        LoadOptions();
    }
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::CheckBoxMinimizeToTrayClick(TObject *Sender)
{
    ButtonApplySettings->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::CheckBoxSaveWindowPositionClick(TObject *Sender)
{
    ButtonApplySettings->Enabled = true;
}
//---------------------------------------------------------------------------
