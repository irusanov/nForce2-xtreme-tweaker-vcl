//---------------------------------------------------------------------------

#ifndef AboutFormH
#define AboutFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TAboutDialog : public TForm
{
__published:	// IDE-managed Components
private:  // User declarations
public:   // User declarations
  __fastcall TAboutDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutDialog *AboutDialog;
//---------------------------------------------------------------------------
#endif
