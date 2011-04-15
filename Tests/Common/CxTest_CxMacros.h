/****************************************************************************
* Class name:  CxTest_CxMacros
* Description: testing CxMacros
* File name:   CxTest_CxMacros.h
* Compilers:   Visual C++ 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxMacrosH
#define CxTest_CxMacrosH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxMacros.h>
//---------------------------------------------------------------------------
class CxTest_CxMacros : public CxTest {
	public:
		CxTest_CxMacros();
	   ~CxTest_CxMacros();

	   /*virtual*/ BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxMacros (constructor)
CxTest_CxMacros::CxTest_CxMacros() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxMacros (destructor)
CxTest_CxMacros::~CxTest_CxMacros() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit (unit test)
/*virtual*/
BOOL
CxTest_CxMacros::bUnit() {
	//-------------------------------------
	//xPTR_DELETE
	{
		INT *pPtr = new INT();
		xASSERT(NULL != pPtr);

		/*CxMacros::*/xPTR_DELETE(pPtr);
		xASSERT(NULL == pPtr);
	}
	//-------------------------------------
	//xARRAY_DELETE
	{
		INT *pPtr = new INT[5];
		xASSERT(NULL != pPtr);

		/*CxMacros::*/xARRAY_DELETE(pPtr);
		xASSERT(NULL == pPtr);
	}

	//-------------------------------------
	//xARRAY_ZERO_DELETE
	{
		INT *pPtr = new INT[5];
		xASSERT(NULL != pPtr);

		xARRAY_ZERO_DELETE(pPtr);
		xASSERT(NULL == pPtr);
	}

	//-------------------------------------
	//xBUFF_ZERO
	{
		TCHAR szBuff[256];

		xBUFF_ZERO(szBuff);
	}

	//-------------------------------------
	//xARRAY_SIZE
	{
		TCHAR szBuff[256] = {0};

		m_uiRes = xARRAY_SIZE(szBuff);
		xASSERT(256 == m_uiRes);
	}

	//-------------------------------------
	//xMAX
	{
		m_uiRes = xMAX(0, 1);
		/*DEBUG*/xASSERT(1 == m_uiRes);
	}

	//-------------------------------------
	//xMIN
	{
		m_uiRes = xMIN(5, 8);
		/*DEBUG*/xASSERT(5 == m_uiRes);
	}
	//-------------------------------------
	//xUNUSED
	{
		size_t uiArg = 0;

		xUNUSED(uiArg);
	}

	//-------------------------------------
	//xS2US
	{
	}

	//-------------------------------------
	//xUS2S
	{
	}

	//-------------------------------------
	//xS2TS
	{
	}

	//-------------------------------------
	//xTS2S
	{
	}

	//-------------------------------------
	//xRANDOMIZE
	{
		////xRANDOMIZE();
		// n/a
	}

	//-------------------------------------
	//xRANDOM
	{
		m_uiRes = xRANDOM(10);
		//xASSERT();
	}

	return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxMacrosH
