//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include <XVCL/Classes/Ole/CxExcel.h>
//---------------------------------------------------------------------------
class TForm1 : public TForm {
	__published:
		TButton *Button1;
		void __fastcall Button1Click(TObject *Sender);

	private:

	public:
		BOOL    m_bRes;
		Variant m_varRes;
		LONG    m_liRes;
		String  m_sRes;
		CxExcel m_exlExcel;

		__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
