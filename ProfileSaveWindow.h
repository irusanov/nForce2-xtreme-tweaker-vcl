//---------------------------------------------------------------------------

#ifndef ProfileSaveWindowH
#define ProfileSaveWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>

#include "ProfilesManager.h"
//---------------------------------------------------------------------------
class TProfileSaveForm : public TForm
{
__published:	// IDE-managed Components
    TCheckBox *CheckBoxTimings;
    TCheckBox *CheckBoxDSSR;
    TCheckBox *CheckBoxAdvanced;
    TCheckBox *CheckBoxRomsip;
    TButton *ButtonSaveProfile;
    TButton *ButtonCancel;
    TSaveTextFileDialog *SaveTextFileDialog1;
    void __fastcall ButtonSaveProfileClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TProfileSaveForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TProfileSaveForm *ProfileSaveForm;
//---------------------------------------------------------------------------
#endif
