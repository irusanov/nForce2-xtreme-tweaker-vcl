//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NForce2XTForm.h"
#include "ValidationBot.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TValidationBotDialog *ValidationBotDialog;
//---------------------------------------------------------------------------
__fastcall TValidationBotDialog::TValidationBotDialog(TComponent* Owner)
    : TForm(Owner)
{
    PanelCurrentFsb->Caption =
        Format("%.2f MHz", ARRAYOFCONST(((long double)MainForm->targetFsb)));

    EditCoreFrequency->Caption =
            Format("%.2f MHz", ARRAYOFCONST(((long double)MainForm->cpu_info.frequency)));
}
//---------------------------------------------------------------------------
void __fastcall TValidationBotDialog::ButtonBotRunClick(TObject *Sender)
{
    if (TimerBot->Enabled) {
        TimerBot->Enabled = false;
        StatusBarBot->SimpleText = "Bot stopped. Please close CPU-Z.";
        ButtonBotRun->Caption = "Run";
    } else {
        ButtonBotRun->Enabled = false;
        StatusBarBot->SimpleText = "Launching CPU-Z";

        String path = EditCpuzPath->Text;
        std::wstring path_wstr(path.begin(), path.end());

        SHELLEXECUTEINFO ShExecInfo = {0};
        ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
        ShExecInfo.hwnd = NULL;
        ShExecInfo.lpVerb = _T("open");
        ShExecInfo.lpFile = path_wstr.c_str();
        ShExecInfo.lpParameters = NULL;
        ShExecInfo.lpDirectory = NULL;
        ShExecInfo.nShow = SW_SHOW;
        ShExecInfo.hInstApp = NULL;
        ShellExecuteEx(&ShExecInfo);
        WaitForSingleObject(ShExecInfo.hProcess, StrToInt(EditCpuzWait->Text));
        CloseHandle(ShExecInfo.hProcess);

        ButtonBotRun->Enabled = true;
        ButtonBotRun->Caption = "Stop";

        TimerBot->Interval = StrToInt(EditBotSleep->Text);
        TimerBot->Enabled = true;
        StatusBarBot->SimpleText = "Running";
    }
}
//---------------------------------------------------------------------------
void __fastcall TValidationBotDialog::TimerBotTimer(TObject *Sender)
{
    // ...
    INPUT ip;
    // ...
    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    // Press the "F7" key
    ip.ki.wVk = VK_F7; // virtual-key code for the "F7" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    //StatusBarBot->SimpleText = "FSB set";
    int step = StrToInt(EditFsbStep->Text);

    if (CheckBoxUltra->Checked) {
        int targetFsb = MainForm->targetFsb + step;

        pair<double, int> nextPll = MainForm->pll.GetNextPll(targetFsb);
        double fsb = nextPll.first;
        int pll = nextPll.second;

        if (fsb > 0) {
            MainForm->targetFsb = fsb;
            MainForm->targetPll = pll;
        }
    } else {
        MainForm->targetFsb += step;
        MainForm->ButtonNextPllClick(this);
    }

    if (MainForm->targetPll != 0) {
        MainForm->pll.nforce2_set_fsb_pll(MainForm->targetFsb, MainForm->targetPll);
    }

    if (CheckBoxUltra->Checked) {
        EditCoreFrequency->Caption = "N/A";
    } else {
        MainForm->RefreshCpuSpeed();

        EditCoreFrequency->Caption =
                Format("%.2f MHz", ARRAYOFCONST(((long double)MainForm->cpu_info.frequency)));
    }

    PanelCurrentFsb->Caption =
            Format("%.2f MHz", ARRAYOFCONST(((long double)MainForm->targetFsb)));
}
//---------------------------------------------------------------------------
void __fastcall TValidationBotDialog::ButtonBrowseCpuzClick(TObject *Sender)
{
    if (OpenDialogBot->Execute()) {
        EditCpuzPath->Text = OpenDialogBot->FileName;
    }

    OpenDialogBot->Free();
}
//---------------------------------------------------------------------------

