//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "TTimingComboBox.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TTimingComboBox *)
{
	new TTimingComboBox(NULL);
}
//---------------------------------------------------------------------------
__fastcall TTimingComboBox::TTimingComboBox(TComponent* Owner)
	: TComboBox(Owner)
{
	this->Style = csDropDownList;
	this->Width = 52;
	this->OnChange = OptionChange;
	this->OnDropDown = DropDown;
	this->OnCloseUp = CloseUp;
}
//---------------------------------------------------------------------------
void __fastcall TTimingComboBox::CreateWnd()
{
	this->Style = csOwnerDrawFixed;
	this->Color = clWindow;
	this->DoubleBuffered = false;

	TComboBox::CreateWnd();

	if (initItems && !tCustomItems) {
		initItems = false;
		Items->BeginUpdate();

		for (int i = tMin; i <= tMax; i++) {
			Items->Add(IntToStr(i));
		}

		//this->ItemIndex = 0;
		Items->EndUpdate();
	}
}
//---------------------------------------------------------------------------
void __fastcall TTimingComboBox::DropDown(TObject *Sender) {
	this->Color = clWindow;
}
//---------------------------------------------------------------------------
void __fastcall TTimingComboBox::CloseUp(TObject *Sender) {
	if (tChanged) {
		this->Color = clInfoBk;
	}
	this->Style = csOwnerDrawFixed;
}
//---------------------------------------------------------------------------
//void __fastcall TTimingComboBox::DrawItem(TWinControl *Control, int Index, TRect &Rect,
//		  TOwnerDrawState State) {
//	this->Canvas->Brush->Color = clYellow;
//	this->Canvas->FillRect(Rect);
//}//---------------------------------------------------------------------------
void __fastcall TTimingComboBox::OptionChange(TObject *Sender)
{
	tChanged = tIndex != this->ItemIndex;
	this->Color = tChanged ? clInfoBk : clWindow;
}
//---------------------------------------------------------------------------
__fastcall void TTimingComboBox::setValue(int value) {

	if (value >= 0) {
		this->ItemIndex = value - tMin;

		tValue = value;
        tIndex = this->ItemIndex;
		tChanged = false;

		this->Color = clWindow;
	}
}
//---------------------------------------------------------------------------
__fastcall void TTimingComboBox::setItemValue(int value) {

	if (!tCustomValue) {
		return;
	}

	if (value >= 0) {
		int index = this->Items->IndexOf(IntToStr(value));

		if (index > -1) {
			this->ItemIndex = index;
            tIndex = index;
		} else {
			index = 0;
			for (int i = 0; i < this->Items->Count; i++) {
				if (value > StrToInt(this->Items->Strings[i])) {
					index++;
				}
			}

			this->Items->Insert(index, IntToStr(value));
			this->ItemIndex = index;
        }

		tValue = value;
		tChanged = false;

		this->Color = clWindow;
	}
}
//---------------------------------------------------------------------------
namespace Ttimingcombobox
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TTimingComboBox)};
		RegisterComponents(L"NForce2XT", classes, 0);
	}
}
//---------------------------------------------------------------------------
