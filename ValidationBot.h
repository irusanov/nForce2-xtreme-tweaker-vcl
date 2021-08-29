//---------------------------------------------------------------------------

#ifndef ValidationBotH
#define ValidationBotH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <shellapi.h>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TValidationBotDialog : public TForm
{
__published:	// IDE-managed Components
    TButton *ButtonBotRun;
    TLabel *Label1;
    TEdit *EditCpuzPath;
    TLabel *Label2;
    TEdit *EditCpuzWait;
    TEdit *EditBotSleep;
    TLabel *Label3;
    TStatusBar *StatusBarBot;
    TTimer *TimerBot;
    TOpenDialog *OpenDialogBot;
    TButton *ButtonBrowseCpuz;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TPanel *PanelCurrentFsb;
    TPanel *EditCoreFrequency;
    TLabel *Label7;
    TCheckBox *CheckBoxUltra;
    TLabel *Label8;
    TEdit *EditFsbStep;
    TLabel *Label9;
    void __fastcall ButtonBotRunClick(TObject *Sender);
    void __fastcall TimerBotTimer(TObject *Sender);
    void __fastcall ButtonBrowseCpuzClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TValidationBotDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TValidationBotDialog *ValidationBotDialog;
//---------------------------------------------------------------------------
#endif
