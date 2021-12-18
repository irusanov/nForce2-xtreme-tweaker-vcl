// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AboutWindow.h"
#include "../Utils/AppVerInfo.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutDialog *AboutDialog;

// ---------------------------------------------------------------------------
__fastcall TAboutDialog::TAboutDialog(TComponent* Owner) : TForm(Owner) {
    TAppVerInfo VersionInfo = TAppVerInfo(Application->ExeName.c_str());
    String LanId = VersionInfo.LanguagesCodePage;

    StaticTextAppName->Caption = Application->Title;
    StaticTextAppVersion->Caption = "v" + VersionInfo.ProductVersion[LanId];
    StaticTextCopyright->Caption = VersionInfo.LegalCopyright[LanId];
    StaticTextDeveloperName->Caption = VersionInfo.CompanyName[LanId];
}
// ---------------------------------------------------------------------------
void __fastcall TAboutDialog::Button1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

