/****************************************************************************
* Class name:  TfrmLogon
* Description: диалог входа в программу
* File name:   TfrmLogon.h
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   VCL, WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     20.07.2010 16:02:35
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef uLogonH
#define uLogonH
//----------------------------------------------------------------------------
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//----------------------------------------------------------------------------
#include <XLib\xCommon.h>
//----------------------------------------------------------------------------
class TfrmLogon : public TForm {
	__published:
		TBitBtn *btnCancel;
		TBitBtn *btnOk;
		TBitBtn *btnRetry;
		TEdit *edtPass;
		TLabel *lbl1;
		TADOConnection *conPassCheck;
 
		void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall btnOkClick(TObject *Sender);

	public:
		virtual __fastcall TfrmLogon(TComponent* AOwner);

	private:
		BOOL               _m_bRes; 
};
//----------------------------------------------------------------------------
#endif    
