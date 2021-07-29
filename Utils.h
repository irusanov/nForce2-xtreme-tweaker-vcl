#pragma once
using namespace std;

unsigned int SetBits(unsigned int val, int offset, int n,
    unsigned int newValue);

unsigned int GetBits(unsigned int val, int offset, int n);

unsigned int MakePciAddress(int bus, int device, int function, int offset);

unsigned int ReadPciReg(unsigned int pciDev);

bool WritePciReg(unsigned int pciDev, unsigned int value);

string GetCpuName();

string GetStringPart(BYTE val);

string IntToStr(DWORD val);

void ltrim(std::string &s);

// trim from end (in place)
void rtrim(std::string &s);

// trim from both ends (in place)
void trim(std::string &s);
