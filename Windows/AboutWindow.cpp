// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AboutWindow.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutDialog *AboutDialog;

// ---------------------------------------------------------------------------
__fastcall TAboutDialog::TAboutDialog(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------
void __fastcall TAboutDialog::Button1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

