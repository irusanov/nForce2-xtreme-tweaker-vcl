// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NForce2XTForm.h"
#include "ValidationBot.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TValidationBotDialog *ValidationBotDialog;
HWND hWndCpuz;

// ---------------------------------------------------------------------------
__fastcall TValidationBotDialog::TValidationBotDialog(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------

HWND __fastcall TValidationBotDialog::FindCpuzWindow() {
    for (HWND hwnd = GetTopWindow(NULL); hwnd != NULL; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT)) {
        if (!IsWindowVisible(hwnd))
            continue;

        int length = GetWindowTextLength(hwnd);
        if (length == 0)
            continue;

        char* title = new char[length + 1];
        GetWindowTextA(hwnd, title, length + 1);

        if (strncmp(title, "CPU-Z", 5) == 0) {
            return hwnd;
        }
    }

    return NULL;
}

void __fastcall TValidationBotDialog::ButtonBotRunClick(TObject *Sender) {
    int interval = 6;
    TryStrToInt(EditBotSleep->Text, interval);

    hWndCpuz = FindCpuzWindow();

    if (TimerBot->Enabled) {
        TimerBot->Enabled = false;
        StatusBarBot->SimpleText = "Bot stopped.";
        ButtonBotRun->Caption = "Run";
    }
    else {
        if (hWndCpuz == NULL) {
            String path = EditCpuzPath->Text;

            if (path.Length() == 0) {
                StatusBarBot->SimpleText = "CPU-Z path not selected and no CPU-Z running.";
                return;
            }

            ButtonBotRun->Enabled = false;
            StatusBarBot->SimpleText = "Launching CPU-Z";

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

            if (!ShellExecuteEx(&ShExecInfo)) {
                StatusBarBot->SimpleText = "CPU-Z not found, please check path to cpu_z.exe";
                ButtonBotRun->Enabled = true;
                ButtonBotRun->Caption = "Run";

                return;
            }

            HANDLE hThread;
            DWORD dwRet;
            do {
                dwRet = ::WaitForSingleObject(&hThread, INFINITE);

                if (dwRet != WAIT_OBJECT_0) {
                    MSG msg;
                    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                }
            }
            while ((dwRet != WAIT_OBJECT_0) && (dwRet != WAIT_FAILED));

            CloseHandle(ShExecInfo.hProcess);

            do {
                hWndCpuz = FindCpuzWindow();
            }
            while (hWndCpuz == NULL);
        }

        // SendMessage(hWndCpuz, WM_CLOSE, 0, 0);

        ButtonBotRun->Enabled = true;
        ButtonBotRun->Caption = "Stop";

        TimerBot->Interval = interval * 1000;
        TimerBot->Enabled = true;
        StatusBarBot->SimpleText = "Running";
    }
}

// ---------------------------------------------------------------------------
void __fastcall TValidationBotDialog::TimerBotTimer(TObject *Sender) {
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

    // Activate CPU-Z window
    if (hWndCpuz != NULL && !SetForegroundWindow(hWndCpuz)) {
        TimerBot->Enabled = false;
        StatusBarBot->SimpleText = "CPU-Z window lost. Bot stopped.";
        ButtonBotRun->Caption = "Run";
        return;
    }

    // Send input to validate
    SendInput(1, &ip, sizeof(INPUT));

    int step = 0;
    TryStrToInt(EditFsbStep->Text, step);

    MainForm->targetFsb += step;

    if (CheckBoxUltra->Checked) {
        pair<double, int>nextPll = MainForm->pll.GetNextPll(MainForm->targetFsb);
        double fsb = nextPll.first;
        int pll = nextPll.second;

        if (fsb > 0) {
            MainForm->targetFsb = fsb;
            MainForm->targetPll = pll;
        }
    }
    else {
        MainForm->ButtonNextPllClick(this);
    }

    if (MainForm->targetPll != 0) {
        MainForm->pll.nforce2_set_fsb_pll(MainForm->targetFsb, MainForm->targetPll);
    }

    if (CheckBoxUltra->Checked) {
        EditCoreFrequency->Caption = "N/A";
    }
    else {
        MainForm->RefreshCpuSpeed();

        EditCoreFrequency->Caption = Format("%.2f MHz", ARRAYOFCONST(((long double)MainForm->cpu_info.frequency)));
    }

    PanelCurrentFsb->Caption = Format("%.2f MHz", ARRAYOFCONST(((long double)MainForm->targetFsb)));
}

// ---------------------------------------------------------------------------
void __fastcall TValidationBotDialog::ButtonBrowseCpuzClick(TObject *Sender) {
    if (OpenDialogBot->Execute()) {
        EditCpuzPath->Text = OpenDialogBot->FileName;
    }

    OpenDialogBot->Free();
}
// ---------------------------------------------------------------------------

void __fastcall TValidationBotDialog::FormShow(TObject *Sender) {
    // Load Bot settings
    EditCpuzPath->Text = MainForm->settings.CpuzPath;
    EditBotSleep->Text = MainForm->settings.Sleep;
    EditFsbStep->Text = MainForm->settings.Step;
    CheckBoxUltra->Checked = MainForm->settings.Ultra;

    PanelCurrentFsb->Caption = Format("%.2f MHz", ARRAYOFCONST(((long double)MainForm->cpu_info.fsb)));
    EditCoreFrequency->Caption = Format("%.2f MHz", ARRAYOFCONST(((long double)MainForm->cpu_info.frequency)));

    ButtonSaveBotSettings->Enabled = false;
}
// ---------------------------------------------------------------------------

void __fastcall TValidationBotDialog::ButtonSaveBotSettingsClick(TObject *Sender) {
    // Save Bot settings
    MainForm->settings.CpuzPath = EditCpuzPath->Text;
    TryStrToInt(EditBotSleep->Text, MainForm->settings.Sleep);
    TryStrToInt(EditFsbStep->Text, MainForm->settings.Step);
    MainForm->settings.Ultra = CheckBoxUltra->Checked;
    ButtonSaveBotSettings->Enabled = false;
    StatusBarBot->SimpleText = "Bot settings saved.";
}
// ---------------------------------------------------------------------------

void __fastcall TValidationBotDialog::BotControlChange(TObject *Sender) {
    ButtonSaveBotSettings->Enabled = true;
}
// ---------------------------------------------------------------------------

void __fastcall TValidationBotDialog::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift) {
    // For some unknown reason the dialog doesn't close on ESC, handling it manually
    if (Key == 27) {
        Close();
    }
}
// ---------------------------------------------------------------------------
