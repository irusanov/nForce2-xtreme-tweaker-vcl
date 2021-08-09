// SPDX-License-Identifier: GPL-2.0-only
/*
 * (C) 2004-2006  Sebastian Witt <se.witt@gmx.net>
 *
 *  Based upon reverse engineered information
 *
 *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*
 *
 *  2021  Ivan Rusanov <ivan.b.rusanov@gmail.com>
 *  Partial port of the nforce2 linux driver
 *  https://github.com/torvalds/linux/blob/master/drivers/cpufreq/cpufreq-nforce2.c
 */
//#define DEBUG_CONSOLE
#include <vcl.h>

#include "OlsApi.h"
#include "Utils.h"
#include "Nforce2Pll.h"

using namespace std;

unsigned long nforce2_dev;
map<double, int>possibleFsb;

#ifdef DEBUG_CONSOLE
String text = "";
static HANDLE handle;
#endif

Nforce2Pll::Nforce2Pll(void) {
    // possibleFsb = GenerateFsbTable();
#ifdef DEBUG_CONSOLE
    if (!handle) {
        AllocConsole();
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
    }
#endif
}

void Nforce2Pll::init() {
    // Detect the southbridge, which contains PLL logic
    nforce2_dev = FindPciDeviceById(PCI_VENDOR_ID_NVIDIA,
        PCI_DEVICE_ID_NVIDIA_NFORCE2, 0);

    possibleFsb = nforce2_gen_fsb_table();

#ifdef DEBUG_CONSOLE
    for (const auto &[k, v] : possibleFsb) {
        text = Format("%.2f: 0x%x", ARRAYOFCONST(((long double)k, v))) + "\n";
        WriteConsole(handle, text.c_str(), text.Length(), 0, 0);
    }
#endif

    if (nforce2_dev == 0xFFFFFFFF) {
        MessageDlg("Not a NForce2 chipset!", mtError, mbOKCancel, 0);
        return;
    }
}

/**
 * nforce2_calc_fsb - calculate FSB
 * @pll: PLL value
 *
 *   Calculates FSB from PLL value
 */
double Nforce2Pll::nforce2_calc_fsb(int pll) {
    double mul, div;

    mul = (pll >> 8) & 0xff;
    div = pll & 0xff;

    if (div > 0)
        return ceil((25.0 * mul / div) * 100.0) / 100.0;

    return 0;
}

/**
 * nforce2_calc_pll - calculate PLL value
 * @fsb: FSB
 *
 *   Calculate PLL value for given FSB
 */
int Nforce2Pll::nforce2_calc_pll(double fsb) {
    unsigned char xmul, xdiv;
    unsigned char mul = 0, div = 0;
    int tried = 0;
    int tfsb = round(fsb);

    /* Try to calculate multiplier and divider up to 4 times */
    while (((mul == 0) || (div == 0)) && (tried <= 3)) {
        for (xdiv = 2; xdiv <= 0x80; xdiv++)
            for (xmul = 0x1; xmul <= 0xfe; xmul++)
                if (nforce2_calc_fsb(NFORCE2_PLL(xmul, xdiv)) == tfsb + tried) {
                    mul = xmul;
                    div = xdiv;
                }
        tried++;
    }

    if ((mul == 0) || (div == 0))
        return -1;

    return NFORCE2_PLL(mul, div);
}

/**
 * nforce2_write_pll - write PLL value to chipset
 * @pll: PLL value
 *
 *   Writes new FSB PLL value to chipset
 */
void Nforce2Pll::nforce2_write_pll(int pll) {
    int temp;

    /* Set the pll addr. to 0x00 */
    WritePciConfigDwordEx(nforce2_dev, NFORCE2_PLLADR, 0);

    /* Now write the value in all 64 registers */
    for (temp = 0; temp <= 0x3f; temp++)
        WritePciConfigDwordEx(nforce2_dev, NFORCE2_PLLREG, pll);
}

/**
 * nforce2_fsb_read - Read FSB
 *
 *   Read FSB from chipset
 *   If bootfsb != 0, return FSB at boot-time
 */
double Nforce2Pll::nforce2_fsb_read(int bootfsb) {
    unsigned int nforce2_sub5, fsb, temp = 0;

    /* Get chipset boot FSB from subdevice 5 (FSB at boot-time) */
    nforce2_sub5 = FindPciDeviceById(PCI_VENDOR_ID_NVIDIA, 0x01EF, 0);

    if (!nforce2_sub5)
        return 0;

    ReadPciConfigDwordEx(nforce2_sub5, NFORCE2_BOOTFSB, (DWORD *) &fsb);

    fsb /= 1000000;

    /* Check if PLL register is already set */
    ReadPciConfigByteEx(nforce2_dev, NFORCE2_PLLENABLE, (BYTE *)&temp);

    if (bootfsb || !temp)
        return ceil(fsb * 100.0) / 100.0;

    /* Use PLL register FSB value */
    ReadPciConfigDwordEx(nforce2_dev, NFORCE2_PLLREG, (DWORD *) &temp);
    double cfsb = nforce2_calc_fsb(temp);

    return cfsb;
}

int Nforce2Pll::nforce2_set_fsb_pll(double tfsb, int tpll) {
    unsigned int temp = 0;
    double fsb, diff;
    int pll = -1;
    pair<double, int> p;

    /* First write? Then set actual value */
    ReadPciConfigByteEx(nforce2_dev, NFORCE2_PLLENABLE, (BYTE *)&temp);

    if (!temp) {
        fsb = nforce2_fsb_read(0);
        pll = nforce2_calc_pll(fsb);

        if (pll < 0)
            return -1;

        nforce2_write_pll(pll);
    }

    /* Enable write access */
    temp = 0x01;
    WritePciConfigByteEx(nforce2_dev, NFORCE2_PLLENABLE, temp);

    fsb = nforce2_fsb_read(0);
    diff = tfsb - fsb;

    while (pll != tpll) {
        if (diff > 0) {
            p = GetNextPll(fsb);
        } else {
            p = GetPrevPll(fsb);
        }

        fsb = p.first;
        pll = p.second;

        nforce2_write_pll(pll);
    }

    temp = 0x40;
    WritePciConfigByteEx(nforce2_dev, NFORCE2_PLLADR, temp);

    return 0;
}

/**
 * nforce2_set_fsb - set new FSB
 * @fsb: New FSB
 *
 *   Sets new FSB
 */
int Nforce2Pll::nforce2_set_fsb(double fsb) {
    unsigned int temp = 0;
    double tfsb;
    int diff;
    int pll = 0;
    /* if ((fsb > max_fsb) || (fsb < NFORCE2_MIN_FSB)) {
     printk(KERN_ERR PFX "FSB %d is out of range!\n", fsb);
     return -EINVAL;
     } */
    tfsb = nforce2_fsb_read(0);

    if (!tfsb) {
        // MessageBox(NULL, L"Error while reading the FSB!", L"Error", MB_ICONERROR | MB_OK);
        return -1;
    }

    /* First write? Then set actual value */
    ReadPciConfigByteEx(nforce2_dev, NFORCE2_PLLENABLE, (BYTE *)&temp);

    if (!temp) {
        pll = nforce2_calc_pll(tfsb);

        if (pll < 0)
            return -1;

        nforce2_write_pll(pll);
    }

    /* Enable write access */
    temp = 0x01;
    WritePciConfigByteEx(nforce2_dev, NFORCE2_PLLENABLE, temp);
    diff = tfsb - fsb;

    if (!diff)
        return 0;

    while ((tfsb != fsb) && (tfsb <= 350) && (tfsb >= 50)) {
        if (diff < 0)
            tfsb++;
        else
            tfsb--;

        /* Calculate the PLL reg. value */
        pll = nforce2_calc_pll(tfsb);

        if (pll == -1)
            return -1;

        nforce2_write_pll(pll);
#ifdef NFORCE2_DELAY
        Sleep(NFORCE2_DELAY);
#endif
    }
    temp = 0x40;
    WritePciConfigByteEx(nforce2_dev, NFORCE2_PLLADR, temp);

    return 0;
}

map<double, int> Nforce2Pll::nforce2_gen_fsb_table() {
    int xmul, xdiv;
    map<double, int>fsbMap;
    map<double, int>::iterator it;

    for (xdiv = 2; xdiv <= 0x80; xdiv++) {
        for (xmul = 0xf0; xmul <= 0xfe; xmul++) {
            int pll = NFORCE2_PLL(xmul, xdiv);
            double fsb = nforce2_calc_fsb(pll) * 1.00225;

            if (fsb >= 30.0 && fsb <= 350.0) {
                it = fsbMap.find(fsb);

                if (it == fsbMap.end()) {
                    fsbMap.insert({fsb, pll});
                }
            }
        }
    }

    return fsbMap;
}

pair<double, int> Nforce2Pll::GetPrevPll(double fsb) {
    map<double, int>::reverse_iterator it;

    for (it = possibleFsb.rbegin(); it != possibleFsb.rend(); ++it) {
        if (fsb - it->first >= 0.05) {
#ifdef DEBUG_CONSOLE
            text = Format("Prev PLL: %.2f",
                ARRAYOFCONST(((long double)it->first))) + "\n";
            WriteConsole(handle, text.c_str(), text.Length(), 0, 0);
#endif
            return {
                it->first, it->second
            };
        }
    }

    return {
        0, 0
    };
}

pair<double, int> Nforce2Pll::GetNextPll(double fsb) {
    map<double, int>::iterator it;

    for (it = possibleFsb.begin(); it != possibleFsb.end(); it++) {
        if (it->first - fsb >= 0.05) {
#ifdef DEBUG_CONSOLE
            text = Format("Next PLL: %.2f",
                ARRAYOFCONST(((long double)it->first))) + "\n";
            WriteConsole(handle, text.c_str(), text.Length(), 0, 0);
#endif
            return {
                it->first, it->second
            };
        }
    }

    return {
        0, 0
    };
}

Nforce2Pll::~Nforce2Pll(void) {
    nforce2_dev = NULL;
}
