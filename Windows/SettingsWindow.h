//---------------------------------------------------------------------------

#ifndef SettingsWindowH
#define SettingsWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TSettingsForm : public TForm
{
__published:	// IDE-managed Components
    TCheckBox *CheckBoxMinimizeToTray;
    TCheckBox *CheckBoxSaveWindowPosition;
    TButton *ButtonApplySettings;
    TButton *ButtonResetSettings;
    TButton *ButtonCancel;
    void __fastcall ButtonApplySettingsClick(TObject *Sender);
    void __fastcall ButtonResetSettingsClick(TObject *Sender);
    void __fastcall CheckBoxMinimizeToTrayClick(TObject *Sender);
    void __fastcall CheckBoxSaveWindowPositionClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TSettingsForm(TComponent* Owner);
    void __fastcall LoadOptions();
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingsForm *SettingsForm;
//---------------------------------------------------------------------------
#endif
