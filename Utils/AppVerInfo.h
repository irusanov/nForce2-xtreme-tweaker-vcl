//---------------------------------------------------------------------------
#ifndef AppVerInfoH
#define AppVerInfoH

#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
//---------------------------------------------------------------------------
class TAppVerInfo
{
public:
    TAppVerInfo(const wchar_t* pModPath);
    virtual ~TAppVerInfo(void);

    __property System::String LanguagesCodePage                         = {read = GetCodePage};
    __property System::String Comments[System::String LanId]            = {read = GetComments};
    __property System::String InternalName[System::String LanId]        = {read = GetInternalName};
    __property System::String ProductName[System::String LanId]         = {read = GetProductName};
    __property System::String CompanyName[System::String LanId]         = {read = GetCompanyName};
    __property System::String LegalCopyright[System::String LanId]      = {read = GetLegalCopyright};
    __property System::String ProductVersion[System::String LanId]      = {read = GetProductVersion};
    __property System::String FileDescription[System::String LanId]     = {read = GetFileDescription};
    __property System::String LegalTrademarks[System::String LanId]     = {read = GetLegalTrademarks};
    __property System::String PrivateBuild[System::String LanId]        = {read = GetPrivateBuild};
    __property System::String FileVersion[System::String LanId]         = {read = GetFileVersion};
    __property System::String OriginalFilename[System::String LanId]    = {read = GetOriginalFilename};
    __property System::String SpecialBuild[System::String LanId]        = {read = GetSpecialBuild};

protected:
    void *VerInfo;

    System::String __fastcall GetCodePage(void);
    System::String __fastcall GetComments(System::String LanId);
    System::String __fastcall GetInternalName(System::String LanId);
    System::String __fastcall GetProductName(System::String LanId);
    System::String __fastcall GetCompanyName(System::String LanId);
    System::String __fastcall GetLegalCopyright(System::String LanId);
    System::String __fastcall GetProductVersion(System::String LanId);
    System::String __fastcall GetFileDescription(System::String LanId);
    System::String __fastcall GetLegalTrademarks(System::String LanId);
    System::String __fastcall GetPrivateBuild(System::String LanId);
    System::String __fastcall GetFileVersion(System::String LanId);
    System::String __fastcall GetOriginalFilename(System::String LanId);
    System::String __fastcall GetSpecialBuild(System::String LanId);
    System::String __fastcall GetValue(const System::String& LanId, const wchar_t* pName);
};
#endif
