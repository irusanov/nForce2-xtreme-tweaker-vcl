#define PCI_VENDOR_ID_NVIDIA					0x10de
#define PCI_DEVICE_ID_NVIDIA_NFORCE2			0x01e0
#define NFORCE2_XTAL							25
#define NFORCE2_BOOTFSB							0x48
#define NFORCE2_PLLENABLE						0xa8
#define NFORCE2_PLLREG							0xa4
#define NFORCE2_PLLADR							0xa0
#define NFORCE2_PLL(mul, div) (0x100000 | (mul << 8) | div)
#define NFORCE2_MIN_FSB							50
#define NFORCE2_SAFE_DISTANCE					50

/* Delay in ms between FSB changes */
// #define NFORCE2_DELAY 10

class Nforce2Pll
{
private:
//	static unsigned int nforce2_dev;

public:
	Nforce2Pll(void);
	virtual ~Nforce2Pll(void);

	void init();
    static void GenerateFsbTable();
	static double nforce2_calc_fsb(int pll);
	static int nforce2_calc_pll(unsigned int fsb);
	static void nforce2_write_pll(int pll);
	static unsigned int nforce2_fsb_read(int bootfsb);
	static int nforce2_set_fsb(unsigned int fsb);
};

