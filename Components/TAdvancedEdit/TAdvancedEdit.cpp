// ---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop
#include "TAdvancedEdit.h"
#pragma package(smart_init)
// ---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TAdvancedEdit *) {
    new TAdvancedEdit(NULL);
}

// ---------------------------------------------------------------------------
__fastcall TAdvancedEdit::TAdvancedEdit(TComponent* Owner) : TEdit(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TAdvancedEdit::CreateWnd() {
    // this->Style = csOwnerDrawFixed;
    this->Color = clWindow;
    this->Width = 26;
    this->Height = 22;
    this->AutoSize = false;
    this->CharCase = ecUpperCase;
    this->MaxLength = 2;
    this->Alignment = taCenter;
    this->OnKeyPress = KeyPress;
    this->OnChange = Change;
    this->OnExit = Exit;
    this->OnClick = Click;
    // this->OnDblClick = DblClick;
    this->AutoSelect = true;

    TEdit::CreateWnd();
}

// ---------------------------------------------------------------------------
void __fastcall TAdvancedEdit::Click(TObject *Sender) {
    this->SelectAll();
}

// ---------------------------------------------------------------------------
void __fastcall TAdvancedEdit::DblClick(TObject *Sender) {
    // AdvancedEditForm->Show();
}

// ---------------------------------------------------------------------------
void __fastcall TAdvancedEdit::Change(TObject *Sender) {
    tChanged = tValue != this->Text;
    this->Color = tChanged ? clInfoBk : clWindow;
}

// ---------------------------------------------------------------------------
__fastcall void TAdvancedEdit::setValue(UnicodeString value) {
    if (value.Length() > 0) {
        tValue = value;
        tChanged = false;
        this->Color = clWindow;
    }
}

// ---------------------------------------------------------------------------
void __fastcall TAdvancedEdit::KeyPress(TObject *Sender, System::WideChar &Key)
{
    // Allowed key codes "abcdefABCDEF0123456789" and BACKSPACE
    if ((Key >= 48 && Key <= 57) || (Key >= 65 && Key <= 70) ||
        (Key >= 97 && Key <= 102) || Key == 8) {
        return;
    }
    else {
        Key = 0;
    }
}

// ---------------------------------------------------------------------------
void __fastcall TAdvancedEdit::Exit(TObject *Sender) {
    this->SelLength = 0;
}

// ---------------------------------------------------------------------------
namespace Tadvancededit {
    void __fastcall PACKAGE Register() {
        TComponentClass classes[1] = {__classid(TAdvancedEdit)};
        RegisterComponents(L"NForce2XT", classes, 0);
    }
}
// ---------------------------------------------------------------------------
