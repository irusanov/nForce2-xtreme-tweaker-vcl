#include <vcl.h>
#pragma hdrstop

#include "NForce2XTForm.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TAdvancedEdit"
#pragma link "TTimingComboBox"
#pragma resource "*.dfm"
TMainForm *MainForm;

// https://github.com/torvalds/linux/blob/master/drivers/cpufreq/powernow-k7.c#L78
// 0x0 - 0x1f. 0 - 31
const int fid_codes[32] = {
    110, 115, 120, 125, 50, 55, 60, 65,
    70, 75, 80, 85, 90, 95, 100, 105,
    30, 190, 40, 200, 130, 135, 140, 210,
    150, 225, 160, 165, 170, 180, 230, 240,
};

enum CodeName {
    Spitfire,
    Morgan,
    Applebred,
    Thunderbird,
    Palomino,
    Thoroughbred,
    Barton,
};

struct timing_def_t {
    UnicodeString name;
    unsigned int bus;
    unsigned int device;
    unsigned int function;
    unsigned int reg;
    unsigned int offset;
    unsigned int bits;
};

const struct timing_def_t timingDefs[] = {
    // name,                    b,  d,  f, reg, offset, bits
    { "CAS",                    0,  0,  1, 0xB0,  4,  3 },

    { "TRC",                    0,  0,  1, 0x90,  0,  5 },
    { "TRFC",                   0,  0,  1, 0x90,  8,  5 },
    { "TRAS",                   0,  0,  1, 0x90, 15,  4 },
    { "TRCDR",                  0,  0,  1, 0x90, 20,  4 },
    { "TRCDW",                  0,  0,  1, 0x90, 24,  4 },
    { "TRP",                    0,  0,  1, 0x90, 28,  4 },

    { "TDOE",                   0,  0,  1, 0x94, 28,  3 },
    { "TRRD",                   0,  0,  1, 0x94, 24,  3 },
    { "TWTP",                   0,  0,  1, 0x94, 20,  3 },
    { "TWTR",                   0,  0,  1, 0x94, 16,  3 },
    { "TREXT",                  0,  0,  1, 0x94, 12,  2 },
    { "TRTP",                   0,  0,  1, 0x94,  8,  3 },
    { "TRTW",                   0,  0,  1, 0x94,  4,  3 },

    { "CR",                     0,  0,  1, 0x84, 29,  1 },
    { "TREF",                   0,  0,  1, 0x60,  0, 16 },

    { "AutoPrecharge",          0,  0,  1, 0x84, 17,  1 },
    { "BurstMode",              0,  0,  1, 0xA0,  3,  1 },
    //{ "DLLEnable",            0,  0,  1, 0xA4,  0,  1 },
    { "DriveStrengthMode",      0,  0,  1, 0xA4,  1,  1 },
    { "SuperBypass",            0,  0,  1, 0xFC,  0,  1 },
    { "DataScavengedRate",      0,  0,  1, 0xF8,  2,  1 },

    { "FsbDramRatio",           0,  0,  3, 0x7C,  0,  8 },
};

const struct timing_def_t doubledTimingDefs[] = {
    { "DIMM0DrvStrA",           0,  0,  4, 0x64,  8,  4 },
    { "DIMM1DrvStrA",           0,  0,  4, 0x64, 24,  4 },
    { "DIMM2DrvStrA",           0,  0,  4, 0x7C,  8,  4 },
    { "DIMM0DrvStrB",           0,  0,  4, 0x70,  8,  4 },
    { "DIMM1DrvStrB",           0,  0,  4, 0x70, 24,  4 },
    { "DIMM2DrvStrB",           0,  0,  4, 0x80,  8,  4 },

    { "DIMM0SlewRate",          0,  0,  4, 0x64,  0,  4 },
    { "DIMM1SlewRate",          0,  0,  4, 0x64, 16,  4 },
    { "DIMM2SlewRate",          0,  0,  4, 0x7C,  0,  4 },
};

const struct timing_def_t chipsetTimingDefs[] = {
    // name,                    b,  d,  f, reg, offset, bits
    { "CPUDisconnect",          0,  0,  0, 0x6C, 28,  1 },
    { "HALTDisconnect",         0,  0,  0, 0x6C, 14,  1 },
    { "STPGNTDisconnect",       0,  0,  0, 0x6C, 31,  1 },
    { "AGPFastWrite",           0,  0,  0, 0x44,  4,  1 },
    { "AGPSBA",                 0,  0,  0, 0x48,  9,  1 },
    { "AGPControllerLatency",   0, 30,  0, 0x0C,  8,  8 },
    { "AGPBusLatency",          0, 30,  0, 0x18, 24,  8 },
    { "PCILatency",             0,  8,  0, 0x18, 24,  8 },
    { "PCIFrequency",           0,  0,  3, 0x78,  0, 16 },
    //{ "DIMM_B0_CFG",          0,  0,  2, 0x40,  0,  1 },
    //{ "DIMM_B1_CFG",          0,  0,  2, 0x44,  0,  1 },
    //{ "DIMM_A0_CFG",          0,  0,  2, 0x48,  0,  1 },

    // Thermal Throttling Ratio
    { "TTHRatio",               0,  1,  0, 0x95,  1,  3 },
    // Normal Throttling Ratio
    { "NTHRatio",               0,  1,  0, 0x95,  1,  3 },
};

const struct timing_def_t s2kTimings[] = {
    // S2K Control 1 Register
    { "SYSDCIN_Delay",          0,  0,  0, 0xE4,  0,  4 },
    { "SYSDCOUT_Delay",         0,  0,  0, 0xE4,  4,  2 },
    { "RDTOWR_Delay",           0,  0,  0, 0xE4,  7,  2 },
    { "WRTORD_Delay",           0,  0,  0, 0xE4, 10,  1 },
    { "WRDATA_Delay",           0,  0,  0, 0xE4, 12,  3 },
    { "XCAARB_PRCOUNT",         0,  0,  0, 0xE4, 16,  3 },
    { "XCAARB_RDCOUNT",         0,  0,  0, 0xE4, 19,  3 },
    { "XCAARB_WRCOUNT",         0,  0,  0, 0xE4, 22,  3 },
    { "FID",                    0,  0,  0, 0xF0, 28,  4 },
};

const struct timing_def_t romsipDefs[] = {
    // name,                    b,  d,  f, reg, offset, bits
    { "Romsip48",               0,  0,  3, 0x48,  0,  8 },
    { "Romsip4C",               0,  0,  3, 0x4C,  0,  8 },
    { "Romsip4D",               0,  0,  3, 0x4C,  8,  8 },
    { "Romsip50",               0,  0,  3, 0x50,  0,  8 },
    { "Romsip65",               0,  0,  3, 0x64,  8,  8 },
    { "Romsip66",               0,  0,  3, 0x64, 16,  8 },
    { "Romsip67",               0,  0,  3, 0x64, 24,  8 },
    { "Romsip68",               0,  0,  3, 0x68,  0,  8 },
    { "Romsip69",               0,  0,  3, 0x68,  8,  8 },
    { "Romsip6A",               0,  0,  3, 0x68, 16,  8 },
    { "Romsip6B",               0,  0,  3, 0x68, 24,  8 },
    { "Romsip6C",               0,  0,  3, 0x6C,  0,  8 },
    { "Romsip6D",               0,  0,  3, 0x6C,  8,  8 },
    //{ "Romsip6E",             0,  0,  3, 0x6C, 16,  8 },
    { "Romsip6F",               0,  0,  3, 0x6C, 24,  8 },
    { "Romsip74",               0,  0,  3, 0x74,  0,  8 },
};

const int NUMBER_OF_TABS = 3;
bool updateFromButtons = false;

// Get timing definition by component name
static timing_def_t __fastcall GetDefByName(const struct timing_def_t* table, int size, UnicodeString name) {
    for (int i = 0; i < size; i++) {
        if (table[i].name == name) {
            return table[i];
        }
    }

    return {
    };
}
// ---------------------------------------------------------------------------

static unsigned int __fastcall GetFID() {
    timing_def_t def;
    unsigned int pciAddress;
    unsigned int regValue;
    unsigned int value;

    // Get actual FID from chipset
    def = GetDefByName(s2kTimings, COUNT_OF(s2kTimings), "FID");
    pciAddress = MakePciAddress(def.bus, def.device, def.function, def.reg);
    regValue = ReadPciReg(pciAddress);
    // if value is 0011 (0x3), ratio is >= 12.5x (FID 0x3)
    value = GetBits(regValue, def.offset, def.bits);

    return value;
}
// ---------------------------------------------------------------------------

static void __fastcall WritePciFrequency(unsigned int value) {
    timing_def_t def;
    unsigned int pciAddress, regValue;

    def = GetDefByName(chipsetTimingDefs, COUNT_OF(chipsetTimingDefs), "PCIFrequency");
    pciAddress = MakePciAddress(def.bus, def.device, def.function, def.reg);
    regValue = ReadPciReg(pciAddress);

    regValue = SetBits(regValue, def.offset, def.bits, value);
    WritePciReg(pciAddress, regValue);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::RefreshPciFrequency() {
    timing_def_t def;
    unsigned int pciAddress;
    unsigned int regValue;
    unsigned int value;

    // Get current PCI bus frequency
    def = GetDefByName(chipsetTimingDefs, COUNT_OF(chipsetTimingDefs), "PCIFrequency");
    pciAddress = MakePciAddress(def.bus, def.device, def.function, def.reg);
    regValue = ReadPciReg(pciAddress);
    value = GetBits(regValue, def.offset, def.bits);

    cpu_info.pciDiv = value & 0xff;
    cpu_info.pciMul = value >> 8 & 0xff;

    // First write?
    if (cpu_info.pciDiv != 0xf) {
        unsigned int newMul = (cpu_info.pciMul * 0xf) / cpu_info.pciDiv;
        cpu_info.pciDiv = 0xf;
        cpu_info.pciMul = newMul;

        WritePciFrequency(cpu_info.pciMul << 8 | cpu_info.pciDiv);
    }
}
// ---------------------------------------------------------------------------

// Refresh frequency related parameters
void __fastcall TMainForm::RefreshCpuSpeed() {
    DWORD eax = 0, ebx = 0, ecx = 0, edx = 0;
    timing_def_t def;
    unsigned int pciAddress;
    unsigned int regValue;
    unsigned int value;

    // Read current FSB
    cpu_info.fsbFromPll = pll.nforce2_fsb_read(0);
    // Measure current CPU frequency
    cpu_info.frequency = qpc.MeasureCPUFrequency();

    // Update current FID and VID
    if (Rdmsr(MSR_K7_FID_VID_STATUS, &eax, &edx)) {
        cpu_info.currVid = GetBits(edx, 0, 6);
        cpu_info.currFid = GetBits(eax, 0, 6);
    }

    cpu_info.fid = GetFID();

    // FID from chipset is 4 bits and covers up to 12.5x
    // CurrFID from MSR_K7_FID_VID_STATUS is also unreliable
    // Calculate multiplier from CPU frequency and FSB (from PLL)
    if (cpu_info.fsbFromPll > 0) {
        cpu_info.multi = floor(((cpu_info.frequency / cpu_info.fsbFromPll) * 2) + 0.5) / 2;
    }
    else {
        cpu_info.multi = fid_codes[cpu_info.fid] / 10.0;
    }

    cpu_info.fsb = cpu_info.frequency / cpu_info.multi;
    targetFsb = cpu_info.fsb;

    // Get FSB:DRAM ratio
    def = GetDefByName(timingDefs, COUNT_OF(timingDefs), "FsbDramRatio");
    pciAddress = MakePciAddress(def.bus, def.device, def.function, def.reg);
    regValue = ReadPciReg(pciAddress);
    value = GetBits(regValue, def.offset, def.bits);

    cpu_info.fsbDiv = value & 0xf;
    cpu_info.dramDiv = value >> 4 & 0xf;

    if (cpu_info.fsbDiv > 0 && cpu_info.dramDiv > 0) {
        cpu_info.dram = cpu_info.fsb * cpu_info.dramDiv / cpu_info.fsbDiv;
    }

    RefreshPciFrequency();
}
// ---------------------------------------------------------------------------

// Read CPU and system info, invoked once
bool __fastcall TMainForm::InitSystemInfo() {
    DWORD eax = 0, ebx = 0, ecx = 0, edx = 0;

    // CPUID information
    if (Cpuid(0x00000001, &eax, &ebx, &ecx, &edx)) {
        cpu_info.cpuid = eax;
        cpu_info.stepping = eax & 0xf;
        cpu_info.family = eax >> 8 & 0xf;
        cpu_info.model = eax >> 4 & 0xf;
    }
    else {
        return false;
    }

    // Extended CPUID information
    if (Cpuid(0x80000001, &eax, &ebx, &ecx, &edx)) {
        cpu_info.extFamily = eax >> 8 & 0xf;
        cpu_info.extModel = eax >> 4 & 0xf;
        cpu_info.MP = edx >> FEATURE_K7_ECC_BIT & 1;
    }
    else {
        return false;
    }

    // L1 Data cache
    if (Cpuid(0x80000005, &eax, &ebx, &ecx, &edx)) {
        cpu_info.l1DataCache = (ecx >> 24 & 0xff);
        cpu_info.l1InstCache = (edx >> 24 & 0xff);
        cpu_info.l1Cache = cpu_info.l1DataCache + cpu_info.l1InstCache;
    }

    // L2 cache
    if (Cpuid(0x80000006, &eax, &ebx, &ecx, &edx)) {
        cpu_info.l2Cache = (ecx >> 16 & 0xffff);
    }

    if (Rdmsr(MSR_K7_MANID, &eax, &edx)) {
        cpu_info.manID.minorRev = GetBits(eax, 0, 4);
        cpu_info.manID.majorRev = GetBits(eax, 4, 4);
        cpu_info.manID.reticleSite = GetBits(eax, 8, 2);
    }

    // Read CPU FID and VID values
    if (Rdmsr(MSR_K7_FID_VID_STATUS, &eax, &edx)) {
        cpu_info.currVid = GetBits(edx, 0, 6);
        cpu_info.startVid = GetBits(edx, 8, 6);
        cpu_info.maxVid = GetBits(edx, 16, 6);

        cpu_info.currFid = GetBits(eax, 0, 6);
        cpu_info.startFid = GetBits(eax, 8, 6);
        cpu_info.maxFid = GetBits(eax, 16, 6);
    }

    cpu_info.cpuName = GetCpuName();
    decode_amd_model_string(cpu_info.cpuName);
    // decode_amd_model_string("Athlon XP-M");

    RefreshCpuSpeed();

    switch (cpu_info.cpuid) {
    default: ;
    }

    return true;
}
// ---------------------------------------------------------------------------

static int __fastcall GetCASValueIndex(unsigned int value) {
    // CAS is bits [5:4], bit 6 is Half Latency toggle
    // CAS 2.0 = 010 2
    // CAS 2.5 = 110 5
    // CAS 3.0 = 011 3
    // 001, 101 and 111 are reserved

    if (value == 2)
        return 0; // CAS 2.0
    if (value == 6)
        return 1; // CAS 2.5
    if (value == 3)
        return 2; // CAS 3.0

    return -1;
}
// ---------------------------------------------------------------------------

static void __fastcall ReadTimings(const struct timing_def_t* table, int size) {
    timing_def_t def;
    unsigned int pciAddress, regValue, value;
    TTimingComboBox* combo;
    UnicodeString name;

    for (int i = 0; i < size; i++) {
        name = table[i].name;
        def = GetDefByName(table, size, name);
        combo = static_cast<TTimingComboBox*>(Application->FindComponent("MainForm")->FindComponent(name));

        if (combo != NULL && combo != 0 && sizeof(def) > 0) {
            pciAddress = MakePciAddress(def.bus, def.device, def.function, def.reg);
            regValue = ReadPciReg(pciAddress);
            value = GetBits(regValue, def.offset, def.bits);

            if (name == "CAS") {
                combo->Value = GetCASValueIndex(value);
            }
            else if (combo->CustomValue) {
                combo->ItemValue = value;
            }
            else {
                combo->Value = value;
            }

            // MessageDlg(def.name, mtConfirmation, mbOKCancel, 0);
        }
    }
}
// ---------------------------------------------------------------------------

static void __fastcall ReadRomsipValues(const struct timing_def_t* table, int size) {
    timing_def_t def;
    unsigned int pciAddress, regValue, value;
    TAdvancedEdit* box;
    UnicodeString name;

    for (int i = 0; i < size; i++) {
        name = table[i].name;
        def = GetDefByName(table, size, name);
        box = static_cast<TAdvancedEdit*>(Application->FindComponent("MainForm")->FindComponent(name));

        if (box != NULL && box != 0 && sizeof(def) > 0) {
            pciAddress = MakePciAddress(def.bus, def.device, def.function, def.reg);
            regValue = ReadPciReg(pciAddress);
            value = GetBits(regValue, def.offset, def.bits);

            box->Text = IntToHex(Byte(value), 2);
            box->InitialValue = box->Text;
        }
    }
}
// ---------------------------------------------------------------------------

const UnicodeString timingsToSkip[6] = {
    "CAS", "CR", "HALTDisconnect", "STPGNTDisconnect", "BurstMode", "DriveStrengthMode"
};

static void __fastcall WriteTimings(const struct timing_def_t* table, int size, bool doubled) {
    timing_def_t def;
    unsigned int pciAddress, regValue, value, bits;
    TTimingComboBox* combo;
    UnicodeString name;

    for (int i = 0; i < size; i++) {
        name = table[i].name;

        // Skip if timing requires a custom write
        if (Contains(timingsToSkip, COUNT_OF(timingsToSkip), name)) {
            continue;
        }

        combo = static_cast<TTimingComboBox*>(Application->FindComponent("MainForm")->FindComponent(name));

        if (combo != NULL && combo != 0 && combo->Changed) {
            def = GetDefByName(table, size, name);
            bits = def.bits;

            if (combo->CustomValue) {
                value = (unsigned int) combo->ItemValue;
            }
            else {
                value = (unsigned int) combo->Value;
            }

            if (doubled) {
                value = (value << 4) | value;
                bits *= 2;
            }

            pciAddress = MakePciAddress(def.bus, def.device, def.function, def.reg);
            regValue = ReadPciReg(pciAddress);
            regValue = SetBits(regValue, def.offset, bits, value);
            WritePciReg(pciAddress, regValue);
        }
    }
}
// ---------------------------------------------------------------------------

static void __fastcall WriteBurstMode(const struct timing_def_t* table, int size) {
    UnicodeString name = "BurstMode";
    timing_def_t def;
    unsigned int pciAddress, regValue, value;
    TTimingComboBox* combo = static_cast<TTimingComboBox*>
        (Application->FindComponent("MainForm")->FindComponent(name));

    if (combo != NULL && combo != 0 && combo->Changed) {
        def = GetDefByName(table, size, name);
        value = (unsigned int) combo->Value;

        // Write values for DIMM_0, DIMM_B1 and DIMM_A0
        for (int i = 0; i < 3; i++) {
            pciAddress = MakePciAddress(def.bus, def.device, def.function, def.reg + i * 8);
            regValue = ReadPciReg(pciAddress) & NF2_DRAM_CFG1_ACCESS_MASK;
            regValue = SetBits(regValue, def.offset, def.bits, value);
            WritePciReg(pciAddress, regValue);
        }
    }
}
// ---------------------------------------------------------------------------

static void __fastcall WriteDriveStrengthMode(const struct timing_def_t* table, int size) {
    UnicodeString name = "DriveStrengthMode";
    timing_def_t def;
    unsigned int pciAddress, regValue, value;
    TTimingComboBox* combo = static_cast<TTimingComboBox*>
        (Application->FindComponent("MainForm")->FindComponent(name));

    if (combo != NULL && combo != 0 && combo->Changed) {
        def = GetDefByName(table, size, name);
        value = (unsigned int) combo->Value;

        // Write values for DIMM_0, DIMM_B1 and DIMM_A0
        for (int i = 0; i < 3; i++) {
            pciAddress = MakePciAddress(def.bus, def.device, def.function, def.reg + i * 8);
            regValue = (ReadPciReg(pciAddress) & NF2_DRAM_CFG2_ACCESS_MASK) | LBIT(21);
            regValue = SetBits(regValue, def.offset, def.bits, value);
            WritePciReg(pciAddress, regValue);
        }
    }
}
// ---------------------------------------------------------------------------

static void __fastcall WriteBusDisconnect() {
    bool busDisconnect;
    timing_def_t def;
    unsigned int pciAddress = MakePciAddress(0, 0, 0, 0x6C);
    unsigned int regValue, value;
    TTimingComboBox* combo;

    combo = static_cast<TTimingComboBox*>(Application->FindComponent("MainForm")->FindComponent("STPGNTDisconnect"));

    if (combo != NULL && combo != 0 && combo->Changed) {
        regValue = ReadPciReg(pciAddress);
        value = (unsigned int) combo->Value;

        regValue = SetBits(regValue, 28, 1, ~value & 0x1);
        regValue = SetBits(regValue, 31, 1, value);
        WritePciReg(pciAddress, regValue);
    }

    combo = static_cast<TTimingComboBox*>(Application->FindComponent("MainForm")->FindComponent("HALTDisconnect"));

    if (combo != NULL && combo != 0 && combo->Changed) {
        regValue = ReadPciReg(pciAddress);
        value = (unsigned int) combo->Value;

        regValue = SetBits(regValue, 14, 2, (value << 1) | value);
        WritePciReg(pciAddress, regValue);
    }
}
// ---------------------------------------------------------------------------

static void __fastcall WriteRomsipValues(const struct timing_def_t* table, int size) {
    timing_def_t def;
    unsigned int pciAddress, regValue, value;
    TAdvancedEdit* box;
    UnicodeString name;

    for (int i = 0; i < size; i++) {
        name = table[i].name;
        box = static_cast<TAdvancedEdit*>(Application->FindComponent("MainForm")->FindComponent(name));

        if (box != NULL && box != 0 && box->Changed) {
            def = GetDefByName(table, size, name);
            pciAddress = MakePciAddress(def.bus, def.device, def.function, def.reg);
            regValue = ReadPciReg(pciAddress);

            value = StrToInt("0x" + box->Text);

            regValue = SetBits(regValue, def.offset, def.bits, value);
            WritePciReg(pciAddress, regValue);
        }
    }
}
// ---------------------------------------------------------------------------

static void __fastcall RefreshTimings() {
    ReadTimings(timingDefs, COUNT_OF(timingDefs));
    ReadTimings(doubledTimingDefs, COUNT_OF(doubledTimingDefs));
    ReadTimings(chipsetTimingDefs, COUNT_OF(chipsetTimingDefs));
    ReadTimings(s2kTimings, COUNT_OF(s2kTimings));
    ReadRomsipValues(romsipDefs, COUNT_OF(romsipDefs));
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::UpdatePllSlider(double fsb, int pll) {
    targetFsb = fsb;
    targetPll = pll;

    PanelCurrentFsb->Caption = Format("%.2f MHz", ARRAYOFCONST(((long double)targetFsb)));

    bool minReached = TrackBarPll->Position <= TrackBarPll->Min;
    bool maxReached = TrackBarPll->Position >= TrackBarPll->Max;

    ButtonNextPll->Enabled = !maxReached;
    ButtonPrevPll->Enabled = !minReached;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::UpdateAgpSlider(unsigned int mul) {
    double pci = (mul / 15.0) * 6.25;
    double agp = pci * 2.0;

    PanelCurrentAgpPci->Caption = Format("%.2f / %.2f", ARRAYOFCONST(((long double)agp, (long double)pci)));

    bool minReached = TrackBarAgp->Position <= TrackBarAgp->Min;
    bool maxReached = TrackBarAgp->Position >= TrackBarAgp->Max;

    ButtonNextAgp->Enabled = !maxReached;
    ButtonPrevAgp->Enabled = !minReached;
}
// ---------------------------------------------------------------------------

// Main
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner) {
    if (!InitializeOls()) {
        MessageDlg("Error initializing OpenLibSys", mtError, mbOKCancel, 0);
        Application->Terminate();
    }

    if (GetDllStatus() != 0x0) {
        MessageDlg("Error loading WinRing.dll", mtError, mbOKCancel, 0);
        AppExit();
    }

    if (!pll.init()) {
        MessageDlg("Not a NForce2 chipset!", mtError, mbOKCancel, 0);
        Application->ShowMainForm = false;
        AppExit();
    }
    else {
        Application->OnMinimize = OnMinimize;
        Application->OnRestore = OnRestore;

        InitSystemInfo();
        RefreshTimings();

        // Populate static System data
        EditCpuName->Caption = cpu_info.cpuName.c_str();
        EditManRev->Caption = cpu_info.manID.minorRev;

        EditFamily->Caption = cpu_info.family;
        EditModel->Caption = cpu_info.model;
        EditStepping->Caption = cpu_info.stepping;

        EditExtFamily->Caption = cpu_info.extFamily;
        EditExtModel->Caption = cpu_info.extModel;

        EditL1Cache->Caption = Format("%.0d KBytes", ARRAYOFCONST((cpu_info.l1Cache)));
        EditL1DataCache->Caption = Format("%.0d KBytes", ARRAYOFCONST((cpu_info.l1DataCache)));
        EditL1InstCache->Caption = Format("%.0d KBytes", ARRAYOFCONST((cpu_info.l1InstCache)));
        EditL2Cache->Caption = Format("%.0d KBytes", ARRAYOFCONST((cpu_info.l2Cache)));
        // EditRevision->Caption = cpu_info.coreRevision;
        // EditRevision->Caption = Format("%d.%d", ARRAYOFCONST((cpu_info.manID.minorRev, cpu_info.manID.minorRev)));

    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TabControl1Change(TObject *Sender) {
    TPanel* TabPanels[NUMBER_OF_TABS] = {PanelDram, PanelChipset, PanelInfo};
    int index = TabControl1->TabIndex;

    TPanel *Panel;
    for (int i = 0; i < NUMBER_OF_TABS; i++) {
        Panel = TabPanels[i];
        Panel->Visible = (i == index);
    }

    switch (index) {
    case 2:
        RefreshCpuSpeed();

        EditCoreMulti->Caption = Format("x %.1f", ARRAYOFCONST(((long double)cpu_info.multi)));
        EditCoreFrequency->Caption = Format("%.2f MHz", ARRAYOFCONST(((long double)cpu_info.frequency)));
        EditFsbClock->Caption = Format("%.2f MHz", ARRAYOFCONST(((long double)cpu_info.fsb)));

        if (cpu_info.dram > 0) {
            EditDramFrequency->Caption = Format("%.2f MHz", ARRAYOFCONST(((long double)cpu_info.dram)));
            EditFsbDramRatio->Caption = Format("%d:%d", ARRAYOFCONST((cpu_info.fsbDiv, cpu_info.dramDiv)));
        }
        break;
    case 1:
        RefreshCpuSpeed();
        updateFromButtons = true;
        TrackBarPll->Position = cpu_info.fsb;
        TrackBarAgp->Position = cpu_info.pciMul;
        UpdatePllSlider(cpu_info.fsb, 0);
        // UpdateAgpSlider(cpu_info.pciBus);
        updateFromButtons = false;
        break;
    default: ;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonRefreshClick(TObject *Sender) {
    RefreshTimings();

    int index = TabControl1->TabIndex;

    if (index != 0) {
        RefreshCpuSpeed();
    }

    if (index == 1) {
        updateFromButtons = true;
        TrackBarPll->Position = cpu_info.fsb;
        TrackBarAgp->Position = cpu_info.pciMul;
        UpdatePllSlider(cpu_info.fsb, 0);
        // UpdateAgpSlider(cpu_info.pciBus);
        updateFromButtons = false;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonApplyClick(TObject *Sender) {
    switch (TabControl1->TabIndex) {
    case 0:
        WriteTimings(timingDefs, COUNT_OF(timingDefs), false);
        WriteTimings(doubledTimingDefs, COUNT_OF(doubledTimingDefs), true);
        WriteRomsipValues(romsipDefs, COUNT_OF(romsipDefs));
        WriteBurstMode(timingDefs, COUNT_OF(timingDefs));
        WriteDriveStrengthMode(timingDefs, COUNT_OF(timingDefs));
        RefreshTimings();
        break;
    case 1:
        WriteTimings(chipsetTimingDefs, COUNT_OF(chipsetTimingDefs), false);
        WriteTimings(s2kTimings, COUNT_OF(s2kTimings), false);
        WriteBusDisconnect();
        WritePciFrequency(TrackBarAgp->Position << 8 | 0xf);
        RefreshTimings();
        if (targetPll != 0) {
            pll.nforce2_set_fsb_pll(targetFsb, targetPll);
        }
        RefreshCpuSpeed();
        updateFromButtons = true;
        UpdatePllSlider(cpu_info.fsb, targetPll);
        UpdateAgpSlider(cpu_info.pciMul);
        updateFromButtons = false;
        break;
    default: ;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::AppExit() {
    DeinitializeOls();
    Application->Terminate();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::Exit1Click(TObject *Sender) {
    AppExit();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::About1Click(TObject *Sender) {
    AboutDialog->ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TabControl1DrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active)
{
    int left = Active ? 9 : 5;
    int top = Active ? 3 : 2;

    Control->Canvas->Brush->Color = clBtnFace;
    Control->Canvas->Font->Color = Active ? clBlue : clWindowText;
    Control->Canvas->FillRect(Rect);

    Control->Canvas->TextOut(Rect.Left + left, Rect.Top + top,
        (static_cast<TTabControl *>(Control))->Tabs->Strings[TabIndex]);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::OnMinimize(TObject *Sender) {
    // If minimize to tray enabled
    if (settings.MinimizeToTray) {
        TrayIcon->Visible = true;
        Application->MainFormOnTaskBar = false;
        Application->MainForm->Hide();
        // WindowState = wsMinimized;

        if (!settings.MinimizeHintShown) {
            TrayIcon->Animate = true;
            TrayIcon->ShowBalloonHint();
        }
    }

    TabControl1->Visible = false;
    ButtonApply->Visible = false;
    ButtonRefresh->Visible = false;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::OnRestore(TObject *Sender) {
    // If minimize to tray enabled
    if (settings.MinimizeToTray) {
        TrayIcon->Visible = false;
        Application->MainFormOnTaskBar = true;

        if (!settings.MinimizeHintShown) {
            TrayIcon->BalloonHint = NULL;
            settings.MinimizeHintShown = true;
            settings.save();
        }
    }

    TabControl1->Visible = true;
    ButtonApply->Visible = true;
    ButtonRefresh->Visible = true;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TrayIconDblClick(TObject *Sender) {
    Application->Restore();
    Application->MainForm->Show();
    // WindowState = wsNormal;
    Application->MainForm->BringToFront();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender) {
    DeinitializeOls();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonNextPllClick(TObject *Sender) {
    pair<double, int>nextPll = pll.GetNextPll(targetFsb);
    double fsb = nextPll.first;
    int pll = nextPll.second;

    if (fsb > 0) {
        updateFromButtons = true;
        TrackBarPll->Position = fsb;
        UpdatePllSlider(fsb, pll);
        updateFromButtons = false;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonPrevPllClick(TObject *Sender) {
    pair<double, int>prevPll = pll.GetPrevPll(targetFsb);
    double fsb = prevPll.first;
    int pll = prevPll.second;

    if (fsb > 0) {
        updateFromButtons = true;
        TrackBarPll->Position = fsb;
        UpdatePllSlider(fsb, pll);
        updateFromButtons = false;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TrackBarPllChange(TObject *Sender) {
    if (!updateFromButtons) {
        int position = static_cast<TTrackBar*>(Sender)->Position;
        pair<double, int>p = pll.GetPrevPll(position);
        UpdatePllSlider(p.first, p.second);
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonPrevAgpClick(TObject *Sender) {
    TrackBarAgp->Position--;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonNextAgpClick(TObject *Sender) {
    TrackBarAgp->Position++;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TrackBarAgpChange(TObject *Sender) {
    UpdateAgpSlider(TrackBarAgp->Position);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::AutoValidationBotClick(TObject *Sender) {
    ValidationBotDialog->ShowModal();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action) {
    settings.save();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender) {
    settings.load();
    profiles.init();

    if (settings.SaveWindowPosition) {
        Position = poDefault;
        MainForm->Top = settings.WindowTop;
        MainForm->Left = settings.WindowLeft;
    }
    else {
        Position = poDesktopCenter;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::SettingsMenuItemClick(TObject *Sender) {
    SettingsForm->ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::LoadProfileMenuItemClick(TObject *Sender) {
    OpenTextFileDialog1->InitialDir = profiles.GetDefaultPath();

    if (OpenTextFileDialog1->Execute()) {
        if (FileExists(OpenTextFileDialog1->FileName)) {
            profiles.readMetadata(OpenTextFileDialog1->FileName);
            ProfilePreloadForm->ShowModal();
        }
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::SaveProfileMenuItemClick(TObject *Sender) {
    ProfileSaveForm->ShowModal();
}
// ---------------------------------------------------------------------------
