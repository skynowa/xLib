/****************************************************************************
* Class name:  bLogon
* Description: форма аутентификации, изменения пароля
* File name:   bLogon.cpp
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     24.11.2010 12:33:34
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <XVCL\Forms\uLogon.h>
#include <XVCL\Forms\uPassChange.h>

//---------------------------------------------------------------------------
//TODO: bLogon 
BOOL bLogon(String *psPass) {
	//-------------------------------------
	//проверка пароля
	const std::auto_ptr<TfrmLogon> apfrmLogon(new TfrmLogon(Application));
	/*DEBUG*/xASSERT_RET(NULL != apfrmLogon.get(), FALSE);

	INT iRes = apfrmLogon->ShowModal();
	switch (iRes) {
		case mrOk: {
				*psPass = apfrmLogon->edtPass->Text;
			}
			break;
		case mrCancel:	{
				return FALSE;
			}
			break;

		//смена пароля
		case mrRetry: {
				//-------------------------------------
				//TODO: изменение пароля
				const std::auto_ptr<TfrmPassChange> apfrmPassChange(new TfrmPassChange(Application));
				/*DEBUG*/xASSERT_RET(NULL != apfrmPassChange.get(), FALSE);

				INT iRes = apfrmPassChange->ShowModal();
				switch (iRes) {
					case mrOk: {
							*psPass = apfrmPassChange->edtNewPass->Text;

							Application->MessageBox(xT("Пароль успешно изменён."), xT("Безопасность"), MB_OK + MB_ICONINFORMATION);
						}
						break;
					case mrCancel: {
							return FALSE;
						}
						break;
					default: {
							return FALSE;
						}
						break;
				}
			}
			break;

		//выход
		default: {
				return FALSE;
			}
			break;
	}

	return TRUE;
}
//---------------------------------------------------------------------------