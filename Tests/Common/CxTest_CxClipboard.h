/****************************************************************************
* Class name:  CxTest_CxClipboard
* Description: test CxClipboard
* File name:   CxTest_CxClipboard.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxClipboardH
#define CxTest_CxClipboardH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxClipboard.h>
//---------------------------------------------------------------------------
class CxTest_CxClipboard : public CxTest {
	public:
					CxTest_CxClipboard();
				   ~CxTest_CxClipboard();

	   virtual BOOL bUnit             ();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxClipboard (comment)
CxTest_CxClipboard::CxTest_CxClipboard() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxClipboard (comment)
CxTest_CxClipboard::~CxTest_CxClipboard() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL CxTest_CxClipboard::bUnit() {
	CxClipboard cbCB;

	const tString csText = xT("Simple text");

	//-------------------------------------
	//bSetOwner
	{
		m_bRes = cbCB.bSetOwner(NULL);
		xASSERT(FALSE != m_bRes); 
	}

	//-------------------------------------
	//bOpen
	{
		////m_bRes = cbCB.bOpen();
		////xASSERT(FALSE != m_bRes); 
	}

	//-------------------------------------
	//bClear
	{
		m_bRes = cbCB.bClear();
		xASSERT(FALSE != m_bRes); 
	}

	//-------------------------------------
	//bGetData
	{
		////m_bRes = cbCB.bGetData(EFormat fmFormat);
		////xASSERT(FALSE != m_bRes); 
	}

	//-------------------------------------
	//bSetData
	{
		////m_bRes = cbCB.bSetData(EFormat fmFormat, HANDLE hData);
		////xASSERT(FALSE != m_bRes); 
	}

	//-------------------------------------
	//bSetText
	{
		m_bRes = cbCB.bSetText(csText);
		xASSERT(FALSE != m_bRes); 
	}

	//-------------------------------------
	//bIsHasFormat
	{
	#ifdef _UNICODE
		m_bRes = cbCB.bIsHasFormat(CxClipboard::fmUnicodeText);
	#else
		m_bRes = cbCB.bIsHasFormat(CxClipboard::fmText);
	#endif
		xASSERT(FALSE != m_bRes); 
	}

	//-------------------------------------
	//bGetText
	{
		m_bRes = cbCB.bGetText(&m_sRes);
		xASSERT(FALSE  != m_bRes); 
		xASSERT(csText == m_sRes); 
	}

	//-------------------------------------
	//bClose
	{
		////m_bRes = cbCB.bClose();
		////xASSERT(FALSE != m_bRes); 
	}

	return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxClipboardH
