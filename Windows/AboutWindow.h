//---------------------------------------------------------------------------

#ifndef AboutWindowH
#define AboutWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TAboutDialog : public TForm
{
__published:	// IDE-managed Components
    TStaticText *StaticTextAppName;
    TStaticText *StaticTextAppVersion;
    TStaticText *StaticTextCopyright;
    TStaticText *StaticTextDeveloperName;
    TImage *Image1;
    TButton *Button1;
    void __fastcall Button1Click(TObject *Sender);
private:  // User declarations
public:   // User declarations
  __fastcall TAboutDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutDialog *AboutDialog;
//---------------------------------------------------------------------------
#endif
