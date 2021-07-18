//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AboutForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutDialog *AboutDialog;
//---------------------------------------------------------------------------
__fastcall TAboutDialog::TAboutDialog(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
