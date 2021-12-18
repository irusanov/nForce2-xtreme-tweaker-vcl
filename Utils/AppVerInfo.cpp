//---------------------------------------------------------------------------

#pragma hdrstop

#include <memory>
#include "AppVerInfo.h"

using namespace std;

//---------------------------------------------------------------------------
#pragma package(smart_init)

typedef auto_ptr<TStringList> TAutoStringList;

__fastcall TAppVerInfo::TAppVerInfo(const wchar_t* pModPath)
{
    DWORD dwUnused;
    DWORD VerInfoSize = GetFileVersionInfoSize(pModPath, &dwUnused);

    VerInfo = malloc(VerInfoSize);
    if(VerInfo)
    {
        if(0 == GetFileVersionInfo(pModPath, 0, VerInfoSize, VerInfo))
        {
            free(VerInfo);
            VerInfo = NULL;
            throw Exception(SysErrorMessage(GetLastError()));
        }
    } //040904E4
}
//---------------------------------------------------------------------------
__fastcall TAppVerInfo::~TAppVerInfo(void)
{
    if(VerInfo)
        free(VerInfo);
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetCodePage(void)
{
    System::String retVal;

    if(VerInfo)
    {
        struct LANGANDCODEPAGE
        {
            WORD wLanguage;
            WORD wCodePage;
        } *lpTranslate;
        UINT cbTranslate;
        TAutoStringList tStr(new TStringList);
        UINT i;

        VerQueryValue(VerInfo,L"\\VarFileInfo\\Translation", (LPVOID*)&lpTranslate, &cbTranslate);
        for(i = 0; i < (cbTranslate/sizeof(LANGANDCODEPAGE)); i++)
            tStr->Add(System::String().sprintf(L"%04x%04x", lpTranslate[i].wLanguage, lpTranslate[i].wCodePage));
        retVal = tStr->CommaText;
    }
    return retVal;
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetComments(System::String LanId)
{
    return GetValue(LanId, L"Comments");
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetInternalName(System::String LanId)
{
    return GetValue(LanId, L"InternalName");
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetProductName(System::String LanId)
{
    return GetValue(LanId, L"ProductName");
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetCompanyName(System::String LanId)
{
    return GetValue(LanId, L"CompanyName");
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetLegalCopyright(System::String LanId)
{
    return GetValue(LanId, L"LegalCopyright");
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetProductVersion(System::String LanId)
{
    return GetValue(LanId, L"ProductVersion");
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetFileDescription(System::String LanId)
{
    return GetValue(LanId, L"FileDescription");
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetLegalTrademarks(System::String LanId)
{
    return GetValue(LanId, L"LegalTrademarks");
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetPrivateBuild(System::String LanId)
{
    return GetValue(LanId, L"PrivateBuild");
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetFileVersion(System::String LanId)
{
    return GetValue(LanId, L"FileVersion");
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetOriginalFilename(System::String LanId)
{
    return GetValue(LanId, L"OriginalFilename");
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetSpecialBuild(System::String LanId)
{
    return GetValue(LanId, L"SpecialBuild");
}
//---------------------------------------------------------------------------
System::String __fastcall TAppVerInfo::GetValue(const System::String& LanId, const wchar_t* pName)
{
    System::String retVal;

    if(VerInfo)
    {
        System::String aPath(System::String().sprintf(L"\\StringFileInfo\\%s\\%s", LanId.c_str(), pName));
        wchar_t *pBuf;
        UINT uLen;

        if (VerQueryValue(VerInfo, aPath.c_str(), (void**)&pBuf, &uLen))
            retVal = System::String(pBuf);
    }
    return retVal;
}
