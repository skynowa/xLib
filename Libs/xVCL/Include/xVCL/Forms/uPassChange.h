/****************************************************************************
* Class name:  TfrmPassChange
* Description: смена пароля к БД
* File name:   TfrmPassChange.h
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   VCL, WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     20.07.2010 16:04:21
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef uPassChangeH
#define uPassChangeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//----------------------------------------------------------------------------
#include <XLib\xCommon.h>
//---------------------------------------------------------------------------
class TfrmPassChange : public TForm {
	__published:
		TEdit *edtOldPass;
		TEdit *edtNewPass;
		TEdit *edtRepeatNewPass;
		TLabel *Label1;
		TLabel *Label2;
		TLabel *Label3;
		TBitBtn *btnCancel;
		TBitBtn *btnOk;
		TADOConnection *conMain;
		TADOCommand *cmdMain;

		void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall btnOkClick(TObject *Sender);
		void __fastcall FormShow(TObject *Sender);

	public:
		__fastcall TfrmPassChange(TComponent* Owner);

	private:
		BOOL               _m_bRes;
};
//---------------------------------------------------------------------------
#endif
