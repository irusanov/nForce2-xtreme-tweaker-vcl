//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NForce2XTForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TimingComboBox"
#pragma resource "*.dfm"
TMainForm *MainForm;

// MANID Register, MSR C001_001Eh
typedef struct
{
	unsigned char reticleSite; 	// [9-8]
	unsigned char majorRev; 	// [7-4]
	unsigned char minorRev; 	// [3-0]
} man_id_t;

struct CPUInfo
{
	unsigned int cpuid;
    string codeName;
	string cpuName;
	unsigned char family;
	unsigned char model;
	unsigned char extFamily;
	unsigned char extModel;
	unsigned char stepping;
	unsigned char patchLevel;
	double frequency;
    double pllValue;
	double fsb;
	unsigned int fid;
	double multi;
    man_id_t manID;
} cpu_info;

// https://github.com/torvalds/linux/blob/master/drivers/cpufreq/powernow-k7.c#L78
const int fid_codes[32] = {
    110, 115, 120, 125, 50, 55, 60, 65,
    70, 75, 80, 85, 90, 95, 100, 105,
    30, 190, 40, 200, 130, 135, 140, 210,
	150, 225, 160, 165, 170, 180, 230, 240,
};

struct timing_def_t
{
	UnicodeString name;
	unsigned int bus;
	unsigned int device;
	unsigned int function;
	unsigned int reg;
	unsigned int offset;
	unsigned int bits;
};

const struct timing_def_t timingDefs[] = {
	// name, 					b,  d,  f, reg, offset, bits
	{ "CAS",					0,  0,  1, 0xB0,  4,  3 },

	{ "TRC",    				0,  0,  1, 0x90,  0,  5 },
	{ "TRFC",   				0,  0,  1, 0x90,  8,  5 },
	{ "TRAS",   				0,  0,  1, 0x90, 15,  4 },
	{ "TRCDR",  				0,  0,  1, 0x90, 20,  4 },
	{ "TRCDW",  				0,  0,  1, 0x90, 24,  4 },
	{ "TRP",  					0,  0,  1, 0x90, 28,  4 },

	{ "TDOE",   				0,  0,  1, 0x94, 28,  3 },
	{ "TRRD",   				0,  0,  1, 0x94, 24,  3 },
	{ "TWTP",   				0,  0,  1, 0x94, 20,  3 },
	{ "TWTR",   				0,  0,  1, 0x94, 16,  3 },
	{ "TREXT",  				0,  0,  1, 0x94, 12,  2 },
	{ "TRTP",   				0,  0,  1, 0x94,  8,  3 },
	{ "TRTW",   				0,  0,  1, 0x94,  4,  3 },

	{ "CR",     				0,  0,  1, 0x84, 29,  1 },
	{ "TREF",   				0,  0,  1, 0x60,  0, 16 },

	{ "AutoPrecharge",   		0,  0,  1, 0x84, 17,  1 },
	{ "BurstMode",   			0,  0,  1, 0xA0,  3,  1 },
	{ "DLLEnable",   			0,  0,  1, 0xA4,  0,  1 },
	{ "DriveStrengthMode",   	0,  0,  1, 0xA4,  1,  1 },
	{ "SuperBypass",   			0,  0,  1, 0xFC,  0,  1 },
	{ "DataScavengedRate",   	0,  0,  1, 0xF8,  2,  1 }
};

const struct timing_def_t doubledTimingDefs[] = {
	{ "DIMM0DrvStrA",   		0,  0,  4, 0x64,  8,  4 },
	{ "DIMM1DrvStrA",   		0,  0,  4, 0x64, 24,  4 },
	{ "DIMM2DrvStrA",   		0,  0,  4, 0x7C,  8,  4 },
	{ "DIMM0DrvStrB",   		0,  0,  4, 0x70,  8,  4 },
	{ "DIMM1DrvStrB",   		0,  0,  4, 0x70, 24,  4 },
	{ "DIMM2DrvStrB",   		0,  0,  4, 0x80,  8,  4 },

	{ "DIMM0SlewRate",   		0,  0,  4, 0x64,  0,  4 },
	{ "DIMM1SlewRate",   		0,  0,  4, 0x64, 16,  4 },
	{ "DIMM2SlewRate",   		0,  0,  4, 0x7C,  0,  4 },
};

const struct timing_def_t chipsetTimingDefs[] = {
	// name, 					b, d, f, reg, offset, bits
	{ "CPUDisconnect",			0,  0,  0, 0x6C, 28,  1 },
	{ "AGPFastWrite",			0,  0,  0, 0x44,  4,  1 },
	{ "AGPSBA",					0,  0,  0, 0x48,  9,  1 },
	{ "AGPControllerLatency",	0, 30,  0, 0x0C,  8,  8 },
	{ "AGPBusLatency",			0, 30,  0, 0x18, 24,  8 },
	{ "PCILatency",				0,  8,  0, 0x18, 24,  8 },
	{ "DIMM_B0_CFG",			0,  0,  2, 0x40,  0,  1 },
	{ "DIMM_B1_CFG",			0,  0,  2, 0x44,  0,  1 },
	{ "DIMM_A0_CFG",			0,  0,  2, 0x48,  0,  1 },
};

Nforce2Pll pll;
QueryPerformance qpc;

// Read cpu and system info
static bool __fastcall InitSystemInfo() {
	DWORD eax = 0, ebx = 0, ecx = 0, edx = 0;

	if (Cpuid(0x00000001, &eax, &ebx, &ecx, &edx))
	{
		cpu_info.cpuid = eax;
        cpu_info.stepping = eax & 0xf;
        cpu_info.family = eax >> 8 & 0xf;
		cpu_info.model = eax >> 4 & 0xf;
	}
	else
	{
		return false;
	}

	if (Cpuid(0x80000001, &eax, &ebx, &ecx, &edx))
    {
        cpu_info.extFamily = eax >> 8 & 0xf;
        cpu_info.extModel = eax >> 4 & 0xf;
    }
	else
	{
		return false;
	}

	if (Rdmsr(MSR_K7_MANID, &eax, &edx))
	{
        cpu_info.manID.minorRev = GetBits(eax, 0, 4);
        cpu_info.manID.majorRev = GetBits(eax, 4, 4);
        cpu_info.manID.reticleSite = GetBits(eax, 8, 2);
	}

	cpu_info.cpuName = GetCpuName();
	cpu_info.pllValue = pll.nforce2_fsb_read(0);
	cpu_info.frequency = qpc.MeasureCPUFrequency();

	Rdmsr(MSR_K7_FID_VID_STATUS, &eax, &edx);
	unsigned int cfid = GetBits(eax, 0, 6);
	cpu_info.fid = cfid;
	cpu_info.multi = fid_codes[cfid] / 10.0;
	cpu_info.fsb = cpu_info.frequency / cpu_info.multi;

	return true;
}
//---------------------------------------------------------------------------

// Get timing definition by component name
static timing_def_t __fastcall GetDefByName(const struct timing_def_t* table,
	int size, UnicodeString name)
{
	for (int i = 0; i < size; i++) {
		if (table[i].name == name) {
			return table[i];
		}
	}

	return {};
}
//---------------------------------------------------------------------------

static int __fastcall GetCASValueIndex(unsigned int value)
{
	// CAS is bits [5:4], bit 6 is Half Latency toggle
	// CAS 2.0 = 010 2
	// CAS 2.5 = 110 5
	// CAS 3.0 = 011 3
	// 001, 101 and 111 are reserved

	if (value == 2) return 0; // CAS 2.0
	if (value == 6) return 1; // CAS 2.5
	if (value == 3) return 2; // CAS 3.0

	return -1;
}
//---------------------------------------------------------------------------

static void __fastcall ReadTimings(const struct timing_def_t* table, int size)
{
	timing_def_t def;
	unsigned int pciAddress, regValue, value;
	TTimingComboBox* combo;
	UnicodeString name;

	for (int i = 0; i < size; i++) {
		name = table[i].name;
		def = GetDefByName(table, size, name);
		combo = reinterpret_cast<TTimingComboBox *>
			(Application->FindComponent("MainForm")->FindComponent(name));

		if (combo != NULL && combo != 0 && sizeof(def) > 0) {
			pciAddress = MakePciAddress(def.bus, def.device, def.function, def.reg);
			regValue = ReadPciReg(pciAddress);
			value = GetBits(regValue, def.offset, def.bits);

			if (name == "CAS") {
				combo->Value = GetCASValueIndex(value);
			} else if (combo->CustomValue) {
                combo->ItemValue = value;
			} else {
                combo->Value = value;
            }

			//MessageDlg(def.name, mtConfirmation, mbOKCancel, 0);
		}
	}
}
//---------------------------------------------------------------------------

static void __fastcall WriteTimings(const struct timing_def_t* table, int size,
	bool doubled)
{
	timing_def_t def;
	unsigned int pciAddress, regValue, value;
	TTimingComboBox* combo;
	UnicodeString name;

	for (int i = 0; i < size; i++) {
		name = table[i].name;
		combo = reinterpret_cast<TTimingComboBox *>
			(Application->FindComponent("MainForm")->FindComponent(name));

		if (combo != NULL && combo != 0 && combo->Changed) {
			def = GetDefByName(table, size, name);
			pciAddress = MakePciAddress(def.bus, def.device, def.function, def.reg);
			regValue = ReadPciReg(pciAddress);
			if (combo->CustomValue) {
			   value = (unsigned int) combo->ItemValue;
			} else {
				value = (unsigned int) combo->Value;
            }

			if (doubled) {
				value = value << 4 | value;
			}

			if (name != "CAS" && name != "CR")
			{
				regValue = SetBits(regValue, def.offset, def.bits, value);
				WritePciReg(pciAddress, regValue);
			}
		}
	}
}
//---------------------------------------------------------------------------

static void __fastcall RefreshTimings()
{
	ReadTimings(timingDefs, COUNT_OF(timingDefs));
    ReadTimings(doubledTimingDefs, COUNT_OF(doubledTimingDefs));
	ReadTimings(chipsetTimingDefs, COUNT_OF(chipsetTimingDefs));
}
//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	if (!InitializeOls())
	{
		MessageDlg("Error initializing OpenLibSys", mtError, mbOKCancel, 0);
		Application->Terminate();
	}

	if (GetDllStatus() != 0x0)
	{
		MessageDlg("Error loading WinRing.dll", mtError, mbOKCancel, 0);
		DeinitializeOls();
        Application->Terminate();
	}

	InitSystemInfo();
	RefreshTimings();

	//UnicodeString name = GetCpuName().c_str();
	//MessageDlg(name, mtConfirmation, mbOKCancel, 0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TabControl1Change(TObject *Sender)
{
	const int NUMBER_OF_TABS = 3;
	TPanel* TabPanels[NUMBER_OF_TABS] = { PanelDram, PanelChipset, PanelInfo };
	int index = TabControl1->TabIndex;

	TPanel *Panel;
	for (int i = 0; i < NUMBER_OF_TABS; i++) {
		Panel = TabPanels[i];
		Panel->Visible = false;
	}

	Panel = TabPanels[index];
	Panel->Visible = true;

	int test;

	switch (index) {
	case 2:
        //InitSystemInfo();
		EditCpuName->Caption = cpu_info.cpuName.c_str();
		EditManRev->Caption = cpu_info.manID.minorRev;

		EditFamily->Caption = cpu_info.family;
		EditModel->Caption = cpu_info.model;
		EditStepping->Caption = cpu_info.stepping;

		EditExtFamily->Caption = cpu_info.extFamily;
		EditExtModel->Caption = cpu_info.extModel;
		//EditRevision->Caption = cpu_info.coreRevision;
		//EditRevision->Caption = Format("%d.%d", ARRAYOFCONST((cpu_info.manID.minorRev, cpu_info.manID.minorRev)));

		EditCoreMulti->Caption = Format("x %.1f", ARRAYOFCONST(((long double)cpu_info.multi)));
		EditCoreFrequency->Caption = Format("%.2f MHz", ARRAYOFCONST(((long double)cpu_info.frequency)));
		EditFsbClock->Caption = Format("%.2f MHz", ARRAYOFCONST(((long double)cpu_info.fsb)));

		//test = TimingComboBox1->Value;

		break;
	default:
		;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Exit1Click(TObject *Sender)
{
    DeinitializeOls();
    Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::About1Click(TObject *Sender)
{
	AboutDialog->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonRefreshClick(TObject *Sender)
{
	RefreshTimings();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonApplyClick(TObject *Sender)
{
	switch(TabControl1->TabIndex)
	{
		case 0:
			WriteTimings(timingDefs, COUNT_OF(timingDefs), false);
			WriteTimings(doubledTimingDefs, COUNT_OF(doubledTimingDefs), true);
            RefreshTimings();
		break;
		default:
        ;
	}
}
//---------------------------------------------------------------------------
