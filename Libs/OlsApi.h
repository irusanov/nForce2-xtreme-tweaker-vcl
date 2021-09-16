//-----------------------------------------------------------------------------
//     Author : hiyohiyo
//       Mail : hiyohiyo@crystalmark.info
//        Web : http://openlibsys.org/
//    License : The modified BSD license
//
//                     Copyright 2007-2009 OpenLibSys.org. All rights reserved.
//-----------------------------------------------------------------------------
// for WinRing0 1.3.x

#pragma once
#include <System.Types.hpp>
/******************************************************************************
**
** DLL Information
**
******************************************************************************/

//-----------------------------------------------------------------------------
// GetDllStatus
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
DWORD // DLL Status, defined OLS_DLL_****
WINAPI GetDllStatus();

//-----------------------------------------------------------------------------
// GetDllVersion
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
DWORD // DLL Version, defined OLS_VERSION
WINAPI GetDllVersion(
	PBYTE major,		// major version
	PBYTE minor,		// minor version
	PBYTE revision,		// revision
	PBYTE release		// release/build
);

//-----------------------------------------------------------------------------
// GetDriverVersion
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
DWORD // Device Driver Version, defined OLS_DRIVER_VERSION
WINAPI GetDriverVersion(
	PBYTE major,		// major version
	PBYTE minor,		// minor version
	PBYTE revision,		// revision
	PBYTE release		// release/build
);

//-----------------------------------------------------------------------------
// GetDriverType
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
DWORD // Device Driver Type, defined OLS_DRIVER_TYPE_****
WINAPI GetDriverType();

//-----------------------------------------------------------------------------
// InitializeOls
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI InitializeOls();

//-----------------------------------------------------------------------------
// DeinitializeOls
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
VOID WINAPI DeinitializeOls();

/******************************************************************************
**
** CPU
**
******************************************************************************/

//-----------------------------------------------------------------------------
// IsCpuid
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: support CPUID instruction, FALSE: not support CPUID instruction
WINAPI IsCpuid();

//-----------------------------------------------------------------------------
// IsMsr
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: support MSR(Model-Specific Register), FALSE: not support MSR
WINAPI IsMsr();

//-----------------------------------------------------------------------------
// IsTsc
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: support TSC(Time Stamp Counter), FALSE: not support TSC
WINAPI IsTsc();

//-----------------------------------------------------------------------------
// Rdmsr
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI Rdmsr(
	DWORD index,					// MSR index
	PDWORD eax,						// bit  0-31
	PDWORD edx						// bit 32-63
);

//-----------------------------------------------------------------------------
// RdmsrTx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI RdmsrTx(
	DWORD index,					// MSR index
	PDWORD eax,						// bit  0-31
	PDWORD edx,						// bit 32-63
	DWORD_PTR threadAffinityMask
);

//-----------------------------------------------------------------------------
// RdmsrPx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI RdmsrPx(
	DWORD index,					// MSR index
	PDWORD eax,						// bit  0-31
	PDWORD edx,						// bit 32-63
	DWORD_PTR processAffinityMask
);

//-----------------------------------------------------------------------------
// Wrmsr
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI Wrmsr(
	DWORD index,					// MSR index
	DWORD eax,						// bit  0-31
	DWORD edx						// bit 32-63
);

//-----------------------------------------------------------------------------
// WrmsrTx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI WrmsrTx(
	DWORD index,					// MSR index
	DWORD eax,						// bit  0-31
	DWORD edx,						// bit 32-63
	DWORD_PTR threadAffinityMask
);

//-----------------------------------------------------------------------------
// WrmsrPx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI WrmsrPx(
	DWORD index,					// MSR index
	DWORD eax,						// bit  0-31
	DWORD edx,						// bit 32-63
	DWORD_PTR processAffinityMask
);

//-----------------------------------------------------------------------------
// Rdpmc
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI Rdpmc(
	DWORD index,					// PMC index
	PDWORD eax,						// bit  0-31
	PDWORD edx						// bit 32-63
);

//-----------------------------------------------------------------------------
// RdmsrTx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI RdpmcTx(
	DWORD index,					// PMC index
	PDWORD eax,						// bit  0-31
	PDWORD edx,						// bit 32-63
	DWORD_PTR threadAffinityMask
);

//-----------------------------------------------------------------------------
// RdmsrPx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI RdpmcPx(
	DWORD index,					// PMC index
	PDWORD eax,						// bit  0-31
	PDWORD edx,						// bit 32-63
	DWORD_PTR processAffinityMask
);

//-----------------------------------------------------------------------------
// Cpuid
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI Cpuid(
	DWORD index,					// CPUID index
	PDWORD eax,
	PDWORD ebx,
	PDWORD ecx,
	PDWORD edx
);

//-----------------------------------------------------------------------------
// CpuidTx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI CpuidTx(
	DWORD index,					// CPUID index
	PDWORD eax,
	PDWORD ebx,
	PDWORD ecx,
	PDWORD edx,
	DWORD_PTR threadAffinityMask
);

//-----------------------------------------------------------------------------
// CpuidPx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI CpuidPx(
	DWORD index,					// CPUID index
	PDWORD eax,
	PDWORD ebx,
	PDWORD ecx,
	PDWORD edx,
	DWORD_PTR processAffinityMask
);

//-----------------------------------------------------------------------------
// Rdtsc
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI Rdtsc(
	PDWORD eax,						// bit  0-31
	PDWORD edx						// bit 32-63
);

//-----------------------------------------------------------------------------
// RdmsrTx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI RdtscTx(
	PDWORD eax,						// bit  0-31
	PDWORD edx,						// bit 32-63
	DWORD_PTR threadAffinityMask
);

//-----------------------------------------------------------------------------
// RdmsrPx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI RdtscPx(
	PDWORD eax,						// bit  0-31
	PDWORD edx,						// bit 32-63
	DWORD_PTR processAffinityMask
);

//-----------------------------------------------------------------------------
// Hlt
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI Hlt();

//-----------------------------------------------------------------------------
// HltTx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI HltTx(
	DWORD_PTR threadAffinityMask
);

//-----------------------------------------------------------------------------
// HltPx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI HltPx(
	DWORD_PTR processAffinityMask
);

/******************************************************************************
**
** I/O
**
******************************************************************************/

//-----------------------------------------------------------------------------
// ReadIoPortByte
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BYTE // Read Value
WINAPI ReadIoPortByte(
	WORD port			// I/O port address
);

//-----------------------------------------------------------------------------
// ReadIoPortWord
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
WORD // Read Value
WINAPI ReadIoPortWord(
	WORD port			// I/O port address
);

//-----------------------------------------------------------------------------
// ReadIoPortDword
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
DWORD // Read Value
WINAPI ReadIoPortDword(
	WORD port			// I/O port address
);

//-----------------------------------------------------------------------------
// ReadIoPortByteEx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI ReadIoPortByteEx(
	WORD port,			// I/O port address
	PBYTE value			// Read Value
);
//-----------------------------------------------------------------------------
// ReadIoPortWordEx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI ReadIoPortWordEx(
	WORD port,			// I/O port address
	PWORD value			// Read Value
);
//-----------------------------------------------------------------------------
// ReadIoPortDwordEx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI ReadIoPortDwordEx(
	WORD port,			// I/O port address
	PDWORD value		// Read Value
);

//-----------------------------------------------------------------------------
// WriteIoPortByte
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
VOID
WINAPI WriteIoPortByte(
	WORD port,			// I/O port address
	BYTE value			// Write Value
);

//-----------------------------------------------------------------------------
// WriteIoPortDword
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
VOID
WINAPI WriteIoPortDword(
	WORD port,			// I/O port address
	DWORD value			// Write Value
);


//-----------------------------------------------------------------------------
// WriteIoPortWord
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
VOID
WINAPI WriteIoPortWord(
	WORD port,			// I/O port address
	WORD value			// Write Value
);

//-----------------------------------------------------------------------------
// WriteIoPortByteEx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI WriteIoPortByteEx(
	WORD port,			// I/O port address
	BYTE value			// Write Value
);

//-----------------------------------------------------------------------------
// WriteIoPortWordEx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI WriteIoPortWordEx(
	WORD port,			// I/O port address
	WORD value			// Write Value
);


//-----------------------------------------------------------------------------
// WriteIoPortDwordEx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI WriteIoPortDwordEx(
	WORD port,			// I/O port address
	DWORD value			// Write Value
);

/******************************************************************************
**
** PCI
**
******************************************************************************/
// pciAddress
//  0- 2: Function Number
//  3- 7: Device Number
//  8-15: PCI Bus Number
// 16-31: Reserved
// 0xFFFFFFFF : Error

//-----------------------------------------------------------------------------
// SetPciMaxBusNo
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
VOID
WINAPI SetPciMaxBusIndex(
	BYTE max			// Max PCI Bus to Scan
);

//-----------------------------------------------------------------------------
// ReadPciConfigByte
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BYTE // Read Value
WINAPI ReadPciConfigByte(
	DWORD pciAddress,	// PCI Device Address
	BYTE regAddress		// Configuration Address 0-255
);

//-----------------------------------------------------------------------------
// ReadPciConfigWord
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
WORD // Read Value
WINAPI ReadPciConfigWord(
	DWORD pciAddress,	// PCI Device Address
	BYTE regAddress		// Configuration Address 0-255
);

//-----------------------------------------------------------------------------
// ReadPciConfigDword
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
DWORD // Read Value
WINAPI ReadPciConfigDword(
	DWORD pciAddress,	// PCI Device Address
	BYTE regAddress		// Configuration Address 0-255
);

//-----------------------------------------------------------------------------
// ReadPciConfigByteEx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI ReadPciConfigByteEx(
	DWORD pciAddress,	// PCI Device Address
	DWORD regAddress,	// Configuration Address 0-whatever
	PBYTE value			// Read Value
);

//-----------------------------------------------------------------------------
// ReadPciConfigWordEx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI ReadPciConfigWordEx(
	DWORD pciAddress,	// PCI Device Address
	DWORD regAddress,	// Configuration Address 0-whatever
	PWORD value			// Read Value
);

//-----------------------------------------------------------------------------
// ReadPciConfigDwordEx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI ReadPciConfigDwordEx(
	DWORD pciAddress,	// PCI Device Address
	DWORD regAddress,	// Configuration Address 0-whatever
	PDWORD value		// Read Value
);

//-----------------------------------------------------------------------------
// WritePciConfigByte
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
VOID
WINAPI WritePciConfigByte(
	DWORD pciAddress,	// PCI Device Address
	BYTE regAddress,	// Configuration Address 0-255
	BYTE value			// Write Value
);

//-----------------------------------------------------------------------------
// WritePciConfigWord
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
VOID
WINAPI WritePciConfigWord(
	DWORD pciAddress,	// PCI Device Address
	BYTE regAddress,	// Configuration Address 0-255
	WORD value			// Write Value
);

//-----------------------------------------------------------------------------
// WritePciConfigDword
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
VOID
WINAPI WritePciConfigDword(
	DWORD pciAddress,	// PCI Device Address
	BYTE regAddress,	// Configuration Address 0-255
	DWORD value			// Write Value
);

//-----------------------------------------------------------------------------
// WritePciConfigByteEx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI WritePciConfigByteEx(
	DWORD pciAddress,	// PCI Device Address
	DWORD regAddress,	// Configuration Address 0-whatever
	BYTE value			// Write Value
);

//-----------------------------------------------------------------------------
// WritePciConfigWordEx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI WritePciConfigWordEx(
	DWORD pciAddress,	// PCI Device Address
	DWORD regAddress,	// Configuration Address 0-whatever
	WORD value			// Write Value
);

//-----------------------------------------------------------------------------
// WritePciConfigDwordEx
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
BOOL // TRUE: success, FALSE: failure
WINAPI WritePciConfigDwordEx(
	DWORD pciAddress,	// PCI Device Address
	DWORD regAddress,	// Configuration Address 0-whatever
	DWORD value			// Write Value
);

//-----------------------------------------------------------------------------
// FindPciDeviceById
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
DWORD // pciAddress, 0xFFFFFFFF: failure
WINAPI FindPciDeviceById(
	WORD vendorId,		// Vendor ID
	WORD deviceId,		// Device ID
	BYTE index			// Index
);

//-----------------------------------------------------------------------------
// FindPciDeviceByClass
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
DWORD // pciAddress, 0xFFFFFFFF: failure
WINAPI FindPciDeviceByClass(
	BYTE baseClass,		// Base Class
	BYTE subClass,		// Sub Class
	BYTE programIf,		// Program Interface
	BYTE index			// Index
);

/******************************************************************************
**
** Memory (Special API)
**
******************************************************************************/

#ifdef _PHYSICAL_MEMORY_SUPPORT
//-----------------------------------------------------------------------------
// ReadDmiMemory
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
DWORD // Read size(byte), 0: failure
WINAPI ReadDmiMemory(
	PBYTE buffer,		// Buffer
	DWORD count,		// Count
	DWORD unitSize		// Unit Size (BYTE, WORD, DWORD)
);

//-----------------------------------------------------------------------------
// ReadPhysicalMemory
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
DWORD // Read size(byte), 0: failure
WINAPI ReadPhysicalMemory(
	DWORD_PTR address,	// Physical Memory Address
	PBYTE buffer,		// Buffer
	DWORD count,		// Count
	DWORD unitSize		// Unit Size (BYTE, WORD, DWORD)
);

//-----------------------------------------------------------------------------
// WritePhysicalMemory
//-----------------------------------------------------------------------------
extern "C" __declspec(dllexport)
DWORD // Write size(byte), 0: failure
WINAPI WritePhysicalMemory(
	DWORD_PTR address,	// Physical Memory Address
	PBYTE buffer,		// Buffer
	DWORD count,		// Count
	DWORD unitSize		// Unit Size (BYTE, WORD, DWORD)
);
#endif
