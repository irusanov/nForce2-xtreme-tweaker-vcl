//---------------------------------------------------------------------------

#ifndef TAdvancedEditH
#define TAdvancedEditH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TAdvancedEdit : public TEdit
{
private:
	BYTE tMin = 0x0;
	BYTE tMax = 0xFF;
	bool tChanged;
    UnicodeString tValue = "";
	void __fastcall KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Change(TObject *Sender);
	void __fastcall Click(TObject *Sender);
	void __fastcall DblClick(TObject *Sender);
	void __fastcall Exit(TObject *Sender);
protected:
	virtual void __fastcall CreateWnd();
public:
	__fastcall TAdvancedEdit(TComponent* Owner);
    __fastcall void setValue(UnicodeString value);
__published:
	__property bool Changed = {read = tChanged};
	__property UnicodeString InitialValue = {read = tValue, write = setValue};
	__property BYTE Min = {read = tMin, write = tMin};
	__property BYTE Max = {read = tMax, write = tMax};
};
//---------------------------------------------------------------------------
#endif
