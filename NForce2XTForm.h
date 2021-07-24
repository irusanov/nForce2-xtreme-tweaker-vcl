// ---------------------------------------------------------------------------

#ifndef NForce2XTFormH
#define NForce2XTFormH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "OlsApi.h"
#include "Nforce2Pll.h"
#include "Constants.h"
#include "Utils.h"
#include "QueryPerformance.h"

#include "AboutForm.h"
#include "Components\TAdvancedEdit\TAdvancedEdit.h"
#include "Components\TTimingComboBox\TTimingComboBox.h"

// ---------------------------------------------------------------------------
class TMainForm : public TForm {
__published: // IDE-managed Components
	TButton *ButtonApply;
	TButton *ButtonRefresh;
	TTabControl *TabControl1;
	TPanel *PanelDram;
	TPanel *PanelChipset;
	TPanel *PanelInfo;
	TGroupBox *GroupBoxTimings;
	TGroupBox *GroupBoxAdvanced;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TGroupBox *GroupBox1;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label9;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Help1;
	TMenuItem *Exit1;
	TMenuItem *About1;
	TLabel *Label8;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TPanel *EditFamily;
	TPanel *EditCpuName;
	TPanel *EditModel;
	TPanel *EditStepping;
	TPanel *EditExtFamily;
	TPanel *EditExtModel;
	TPanel *EditManRev;
	TPanel *EditCoreRev;
	TPanel *EditCoreName;
	TPanel *EditCoreFrequency;
	TPanel *EditCoreMulti;
	TPanel *EditFsbClock;
	TPanel *EditDramFrequency;
	TPanel *EditL1DataCache;
	TPanel *EditL1InstCache;
	TPanel *EditL1Cache;
	TPanel *EditL2Cache;
	TLabel *LabelCAS;
	TTimingComboBox *CAS;
	TTimingComboBox *TRCDR;
	TLabel *LabelTRCDR;
	TTimingComboBox *TRCDW;
	TTimingComboBox *TRP;
	TTimingComboBox *TRAS;
	TTimingComboBox *TRC;
	TTimingComboBox *TRFC;
	TTimingComboBox *CR;
	TTimingComboBox *TDOE;
	TTimingComboBox *TRRD;
	TTimingComboBox *TWTP;
	TTimingComboBox *TWTR;
	TTimingComboBox *TREXT;
	TTimingComboBox *TRTP;
	TTimingComboBox *TRTW;
	TTimingComboBox *TREF;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TLabel *Label31;
	TTimingComboBox *DIMM0DrvStrB;
	TLabel *Label32;
	TLabel *Label33;
	TLabel *Label34;
	TLabel *Label35;
	TLabel *Label36;
	TLabel *Label37;
	TLabel *Label38;
	TLabel *Label39;
	TLabel *Label40;
	TLabel *Label41;
	TLabel *Label42;
	TTimingComboBox *AutoPrecharge;
	TTimingComboBox *SuperBypass;
	TTimingComboBox *DataScavengedRate;
	TTimingComboBox *DriveStrengthMode;
	TTimingComboBox *BurstMode;
	TTimingComboBox *TimingComboBox29;
	TTimingComboBox *DIMM0DrvStrA;
	TTimingComboBox *DIMM2DrvStrB;
	TTimingComboBox *DIMM0SlewRate;
	TTimingComboBox *DIMM1DrvStrA;
	TTimingComboBox *DIMM1DrvStrB;
	TTimingComboBox *DIMM1SlewRate;
	TTimingComboBox *DIMM2DrvStrA;
	TTimingComboBox *DIMM2SlewRate;
	TLabel *Label43;
	TTimingComboBox *CPUDisconnect;
	TGroupBox *GroupBox4;
	TTimingComboBox *AGPFastWrite;
	TTimingComboBox *AGPSBA;
	TTimingComboBox *AGPControllerLatency;
	TTimingComboBox *AGPBusLatency;
	TTimingComboBox *PCILatency;
	TLabel *Label44;
	TLabel *Label45;
	TLabel *Label46;
	TLabel *Label47;
	TLabel *Label48;
	TGroupBox *GroupBox5;
	TTrackBar *TrackBarPll;
	TPanel *PanelCurrentFsb;
	TButton *ButtonNextPll;
	TButton *ButtonPrevPll;
	TAdvancedEdit *Romsip65;
	TLabel *Label49;
	TAdvancedEdit *Romsip66;
	TLabel *Label50;
	TAdvancedEdit *Romsip67;
	TAdvancedEdit *Romsip68;
	TAdvancedEdit *Romsip69;
	TLabel *Label51;
	TLabel *Label52;
	TLabel *Label53;
	TAdvancedEdit *Romsip6A;
	TAdvancedEdit *Romsip6B;
	TAdvancedEdit *Romsip6C;
	TAdvancedEdit *Romsip6D;
	TAdvancedEdit *Romsip6F;
	TLabel *Label54;
	TLabel *Label55;
	TLabel *Label56;
	TLabel *Label57;
	TLabel *Label58;
	TTrayIcon *TrayIcon;
	TLabel *Label59;
	TPanel *EditFsbDramRatio;
	TLabel *Label60;
	TLabel *Label61;
	TTimingComboBox *XCAARB_WRCOUNT;
	TTimingComboBox *XCAARB_RDCOUNT;
	TLabel *Label62;
	TLabel *Label63;
	TTimingComboBox *XCAARB_PRCOUNT;
	TLabel *Label64;
	TTimingComboBox *WRDATA_Delay;
	TLabel *Label65;
	TTimingComboBox *WRTORD_Delay;
	TTimingComboBox *RDTOWR_Delay;
	TLabel *Label66;
	TTimingComboBox *SYSDCOUT_Delay;
	TLabel *Label67;
	TTimingComboBox *SYSDCIN_Delay;
	TLabel *Label68;
	TLabel *Label69;
	TTimingComboBox *HALTDisconnect;
	TTimingComboBox *STPGNTDisconnect;
	TLabel *Label70;
	TGroupBox *GroupBox7;

	void __fastcall TabControl1Change(TObject *Sender);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
	void __fastcall ButtonRefreshClick(TObject *Sender);
	void __fastcall ButtonApplyClick(TObject *Sender);
	void __fastcall TabControl1DrawTab(TCustomTabControl *Control, int TabIndex,
		const TRect &Rect, bool Active);
	void __fastcall TrayIconDblClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ButtonNextPllClick(TObject *Sender);
	void __fastcall ButtonPrevPllClick(TObject *Sender);
	void __fastcall TrackBarPllChange(TObject *Sender);

protected:
//	virtual void __fastcall CreateParams(TCreateParams &Params);

private: // User declarations
	bool minimizeHintShown = false;
	void __fastcall OnMinimize(TObject *Sender);
	void __fastcall OnRestore(TObject *Sender);
	void __fastcall UpdatePllSlider(unsigned int position);

public: // User declarations
	__fastcall TMainForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
// ---------------------------------------------------------------------------
#endif
