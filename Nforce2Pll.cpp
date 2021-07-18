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

#include "OlsApi.h"
#include "Nforce2Pll.h"

unsigned int Nforce2Pll::nforce2_dev;

Nforce2Pll::Nforce2Pll(void)
{
	// Detect the southbridge, which contains PLL logic
	nforce2_dev = FindPciDeviceById(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE2, 0);

	if (nforce2_dev == 0xFFFFFFFF)
	{
		//MessageBox(NULL, L"Not a NForce2 chipset!", L"Error", MB_ICONERROR | MB_OK);
		//return -1;
	}

    //GenerateFsbTable();
}

/**
 * nforce2_calc_fsb - calculate FSB
 * @pll: PLL value
 *
 *   Calculates FSB from PLL value
 */
int Nforce2Pll::nforce2_calc_fsb(int pll)
{
	unsigned char mul, div;
	mul = (pll >> 8) & 0xff;
	div = pll & 0xff;
	if (div > 0)
		return NFORCE2_XTAL * mul / div;
	return 0;
}

/**
 * nforce2_calc_pll - calculate PLL value
 * @fsb: FSB
 *
 *   Calculate PLL value for given FSB
 */
int Nforce2Pll::nforce2_calc_pll(unsigned int fsb)
{
	unsigned char xmul, xdiv;
	unsigned char mul = 0, div = 0;
	int tried = 0;
	/* Try to calculate multiplier and divider up to 4 times */
	while (((mul == 0) || (div == 0)) && (tried <= 3)) {
		for (xdiv = 2; xdiv <= 0x80; xdiv++)
			for (xmul = 1; xmul <= 0xfe; xmul++)
				if (nforce2_calc_fsb(NFORCE2_PLL(xmul, xdiv)) ==
				    fsb + tried) {
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
void Nforce2Pll::nforce2_write_pll(int pll)
{
	int temp;
	/* Set the pll addr. to 0x00 */
	WritePciConfigDwordEx(nforce2_dev, NFORCE2_PLLADR, 0);
	/* Now write the value in all 64 registers */
	for (temp = 0; temp <= 0x3f; temp++)
		WritePciConfigDwordEx(nforce2_dev, NFORCE2_PLLREG, pll);
	return;
}

/**
 * nforce2_fsb_read - Read FSB
 *
 *   Read FSB from chipset
 *   If bootfsb != 0, return FSB at boot-time
 */
unsigned int Nforce2Pll::nforce2_fsb_read(int bootfsb)
{
	DWORD nforce2_sub5;
	DWORD fsb = 0;
	DWORD temp = 0;
	/* Get chipset boot FSB from subdevice 5 (FSB at boot-time) */
	nforce2_sub5 = FindPciDeviceById(PCI_VENDOR_ID_NVIDIA, 0x01EF, 0);
	if (!nforce2_sub5)
		return 0;
	ReadPciConfigDwordEx(nforce2_sub5, NFORCE2_BOOTFSB, &fsb);
	fsb /= 1000000;
	/* Check if PLL register is already set */
	ReadPciConfigByteEx(nforce2_dev, NFORCE2_PLLENABLE, (BYTE *)&temp);
	if (bootfsb || !temp)
		return fsb;
	/* Use PLL register FSB value */
	ReadPciConfigDwordEx(nforce2_dev, NFORCE2_PLLREG, &temp);
	fsb = nforce2_calc_fsb(temp);
	return fsb;
}

/**
 * nforce2_set_fsb - set new FSB
 * @fsb: New FSB
 *
 *   Sets new FSB
 */
int Nforce2Pll::nforce2_set_fsb(unsigned int fsb)
{
	unsigned int temp = 0;
	unsigned int tfsb;
	int diff;
	int pll = 0;
	/*if ((fsb > max_fsb) || (fsb < NFORCE2_MIN_FSB)) {
		printk(KERN_ERR PFX "FSB %d is out of range!\n", fsb);
		return -EINVAL;
	}*/
	tfsb = nforce2_fsb_read(0);
	if (!tfsb) {
		//MessageBox(NULL, L"Error while reading the FSB!", L"Error", MB_ICONERROR | MB_OK);
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
	WritePciConfigByteEx(nforce2_dev, NFORCE2_PLLENABLE, (char)temp);
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
	WritePciConfigByteEx(nforce2_dev, NFORCE2_PLLADR, (char)temp);
	return 0;
}


Nforce2Pll::~Nforce2Pll(void)
{
	nforce2_dev = NULL;
}
