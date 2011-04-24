/****************************************************************************
* Class name:  TfrmPassChange
* Description: смена пароля к БД
* File name:   TfrmPassChange.cpp
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   VCL, WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     20.07.2010 16:04:21
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <vcl.h>
#pragma hdrstop

#include "uPassChange.h"
#include "uDM.h"
#include "uMain.h"
#include "GlobalVars.h"
//---------------------------------------------------------------------------
#pragma package(smart_init) 
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
//DONE: TfrmPassChange
__fastcall TfrmPassChange::TfrmPassChange(TComponent* Owner) :
	TForm         (Owner),
	_m_bRes       (FALSE)
{
	//-------------------------------------
	//Gui
	Caption    = xS2D(CxAppSettings::m_sAppTitle) + xT(" - cмена пароля");
	KeyPreview = TRUE;
}
//---------------------------------------------------------------------------
//DONE: FormShow
void __fastcall TfrmPassChange::FormShow(TObject *Sender) {
	//если первый запуск приложения - в поле пишем дефолтный пароль в TEdit на БД
	if (TRUE == g_bIsFirstLaunch) {
		edtOldPass->Enabled = false;
		edtOldPass->Text    = xS2D(CxAppSettings::m_sPassDefault);
		g_bIsFirstLaunch    = FALSE;
		
		edtNewPass->SetFocus();
		edtNewPass->SelectAll();
	}
}
//---------------------------------------------------------------------------
//DONE: btnOkClick
void __fastcall TfrmPassChange::btnOkClick(TObject *Sender) {
	ModalResult = mrNone;

	//-------------------------------------
	//check
	if (edtRepeatNewPass->Text != edtNewPass->Text) {
		iMsgBox(Handle, xT("Пароли не совпадают"), CxAppSettings::m_sAppTitle, MB_ICONSTOP);

		edtNewPass->SetFocus();
		edtNewPass->SelectAll();

		return;
	}

	//-------------------------------------
	//change Password
	try {
		conMain->Close();
		conMain->ConnectionString = xT("Provider=Microsoft.Jet.OLEDB.4.0;")
									xT("Data Source=") + xS2D(CxAppSettings::m_sDbFilePath) + xT(";")
									xT("Jet OLEDB:Database Password=") + edtOldPass->Text   + xT(";")
									xT("Mode=Share Deny Read|Share Deny Write;")	/*DB must be opened in exclusive mode!*/
									xT("Persist Security Info=false");
		conMain->Open();

		//if the old password does not exist, so the second option == NULL!!!
		cmdMain->CommandText = xT("ALTER DATABASE PASSWORD ") +
							   edtNewPass->Text + xT(" ")     +
							   ( (true == edtOldPass->Text.IsEmpty()) ? String(xT("NULL")) : edtOldPass->Text ) + xT(";");
		cmdMain->Execute();
	}
	catch (Exception &E) {
		iMsgBox(Handle, E.Message.c_str(), CxAppSettings::m_sAppTitle, MB_ICONSTOP);

		return;
	}
	catch (...) {
		iMsgBox(Handle, xT("Неизвестная ошибка"), CxAppSettings::m_sAppTitle, MB_ICONSTOP);

		return;
	}

	ModalResult = mrOk;
}
//---------------------------------------------------------------------------



/****************************************************************************
*    Навороты
*
*****************************************************************************/

//-----------------------------------------------------------------------
//DONE: обработка нажатий кнопок
void __fastcall TfrmPassChange::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {
	xCHECK_DO(VK_ESCAPE == Key, Close());
	xCHECK_DO(VK_RETURN == Key, FindNextControl(ActiveControl, true, true, false)->SetFocus());
}
//---------------------------------------------------------------------------

