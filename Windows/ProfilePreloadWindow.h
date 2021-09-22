//---------------------------------------------------------------------------

#ifndef ProfilePreloadWindowH
#define ProfilePreloadWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>

#include "ProfilesManager.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TProfilePreloadForm : public TForm
{
__published:	// IDE-managed Components
    TCheckBox *CheckBoxTimings;
    TCheckBox *CheckBoxDSSR;
    TCheckBox *CheckBoxAdvanced;
    TCheckBox *CheckBoxRomsip;
    TButton *ButtonLoadProfile;
    TButton *ButtonCancel;
    TLabel *Label1;
    TLabel *Label2;
    TMemo *PanelComment;
    TMemo *PanelAuthor;
    TLabel *Label3;
    TLabel *Label4;
    TMemo *PanelName;
    void __fastcall ButtonLoadProfileClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall SectionCheckBoxClick(TObject *Sender);
    void __fastcall SetApplyButtonState();
private:	// User declarations
public:		// User declarations
    __fastcall TProfilePreloadForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TProfilePreloadForm *ProfilePreloadForm;
//---------------------------------------------------------------------------
#endif
