#include "OlsApi.h"
#include "Utils.h"
#include "Constants.h"

unsigned int SetBits(unsigned int val, int offset, int n, unsigned int newValue) {
	return val & ~(((1U << n) - 1) << offset) | newValue << offset;
}

unsigned int GetBits(unsigned int val, int offset, int n) {
	return (val >> offset)&~(~0U << n);
}

unsigned int MakePciAddress(int bus, int device, int function, int offset) {
	return 0x80000000 | bus << 16 | device << 11 | function << 8 | offset;
}

unsigned int ReadPciReg(unsigned int pciDev)
{
	WriteIoPortDwordEx(PCI_ADDR_PORT, pciDev);
	return ReadIoPortDword(PCI_DATA_PORT);
}

bool WritePciReg(unsigned int pciDev, unsigned int value)
{
	WriteIoPortDwordEx(PCI_ADDR_PORT, pciDev);
	return WriteIoPortDwordEx(PCI_DATA_PORT, value) == 1;
}

string GetStringPart(BYTE val) {
	if (val != 0) {
		string s(1, val);
		return s;
	}
	return "";
}

string GetCpuName() {
	string model = "";
	DWORD eax = 0, ebx = 0, ecx = 0, edx = 0;

	if (Cpuid(0x80000002, &eax, &ebx, &ecx, &edx))
		model = model + IntToStr(eax) + IntToStr(ebx) + IntToStr(ecx) +
			IntToStr(edx);

	if (Cpuid(0x80000003, &eax, &ebx, &ecx, &edx))
		model = model + IntToStr(eax) + IntToStr(ebx) + IntToStr(ecx) +
			IntToStr(edx);

	if (Cpuid(0x80000004, &eax, &ebx, &ecx, &edx))
		model = model + IntToStr(eax) + IntToStr(ebx) + IntToStr(ecx) +
			IntToStr(edx);

	trim(model);

	return model;
}

string IntToStr(DWORD val) {
	BYTE part1 = val & 0xff;
	BYTE part2 = val >> 8 & 0xff;
	BYTE part3 = val >> 16 & 0xff;
	BYTE part4 = val >> 24 & 0xff;

	return GetStringPart(part1) + GetStringPart(part2) + GetStringPart(part3) +
		GetStringPart(part4);
}

// trim from start (in place)
void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
	{return !std::isspace(ch);}));
}

// trim from end (in place)
void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
	{return !std::isspace(ch);}).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}
