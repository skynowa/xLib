/****************************************************************************
* Class name:  TfrmLogon
* Description: диалог входа в программу
* File name:   TfrmLogon.cpp
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   VCL, WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     20.07.2010 16:02:35
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <vcl.h>
#pragma hdrstop

#include "uLogon.h"
#include "uDM.h"
#include "uMain.h"
#include "GlobalVars.h"
//---------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------
//TODO: TfrmLogon
__fastcall TfrmLogon::TfrmLogon(TComponent* AOwner) :
	TForm         (AOwner),
	_m_bRes       (FALSE)
{
	//-------------------------------------
	//Gui
	Caption    = xS2D(CxAppSettings::m_sAppTitle) + xT(" - безопасность");
	KeyPreview = TRUE;
}
//---------------------------------------------------------------------------
//DONE: btnOkClick (коннектимся к уже запароленной базе)
void __fastcall TfrmLogon::btnOkClick(TObject *Sender) {
	ModalResult = mrNone;

	//-------------------------------------
	//если БД не существует - создание
	if (FALSE == CxFile::bIsExists(CxAppSettings::m_sDbFilePath)) {
		CxFile flEmptyDB;
		_m_bRes = flEmptyDB.bCreate(CxAppSettings::m_sDbFilePath + xT(".tmp"), CxFile::grWrite, CxFile::smDenyAll, CxFile::cfCreateAlways, CxFileAttribute::faNormal);
		/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);

		_m_bRes = flEmptyDB.bWrite(&CxAppSettings::m_ucDbEmpty[0], CxAppSettings::m_ulDbEmptySize);
		/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);

		_m_bRes = flEmptyDB.bClose();
		/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);

		_m_bRes = CxZCompression::bDecompress(xS2D(CxAppSettings::m_sDbFilePath) + xT(".tmp"), xS2D(CxAppSettings::m_sDbFilePath), TRUE);
		/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);

		//задание TEdit-у дефолтного пароля (в TfrmPassChange проверка данного флага)
		g_bIsFirstLaunch = TRUE;

		ModalResult = mrRetry;

		iMsgBox(Handle, xT("Создана новая БД."), CxAppSettings::m_sAppTitle, MB_ICONWARNING);

		return;
	} 

	//-------------------------------------
	//проверка валидности пароля
	try {
		conPassCheck->Close();
		conPassCheck->ConnectionString = xS2D( CxConnectionString::sMSJetOleDb40(CxAppSettings::m_sDbFilePath, xT(""), xT(""), xD2S(edtPass->Text)) );
		conPassCheck->Open();
		conPassCheck->Close();

		ModalResult = mrOk;
	}
	catch (Exception &E) {
		iMsgBox(Handle, E.Message.c_str(), CxAppSettings::m_sAppTitle, MB_ICONSTOP);

		edtPass->SetFocus();
		edtPass->SelectAll();
	}
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Навороты
*
*****************************************************************************/

//-----------------------------------------------------------------------
//DONE: FormKeyDown (обработка нажатий кнопок)
void __fastcall TfrmLogon::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {
	xCHECK_DO(VK_ESCAPE == Key, Close());
	xCHECK_DO(VK_RETURN == Key, FindNextControl(ActiveControl, true, true, false)->SetFocus());
}
//---------------------------------------------------------------------------


