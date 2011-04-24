/****************************************************************************
* Class name:  bLogon
* Description: ����� ��������������, ��������� ������
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
	//�������� ������
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

		//����� ������
		case mrRetry: {
				//-------------------------------------
				//TODO: ��������� ������
				const std::auto_ptr<TfrmPassChange> apfrmPassChange(new TfrmPassChange(Application));
				/*DEBUG*/xASSERT_RET(NULL != apfrmPassChange.get(), FALSE);

				INT iRes = apfrmPassChange->ShowModal();
				switch (iRes) {
					case mrOk: {
							*psPass = apfrmPassChange->edtNewPass->Text;

							Application->MessageBox(xT("������ ������� ������."), xT("������������"), MB_OK + MB_ICONINFORMATION);
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

		//�����
		default: {
				return FALSE;
			}
			break;
	}

	return TRUE;
}
//---------------------------------------------------------------------------