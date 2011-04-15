/****************************************************************************
* Class name:  CxTest_CxChar
* Description: test CxChar
* File name:   CxTest_CxChar.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxCharH
#define CxTest_CxCharH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxChar.h>
//---------------------------------------------------------------------------
class CxTest_CxChar : public CxTest {
	public:
		CxTest_CxChar();
	   ~CxTest_CxChar();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxChar (constructor)
CxTest_CxChar::CxTest_CxChar() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxChar (destructor)
CxTest_CxChar::~CxTest_CxChar() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxChar::bUnit() {
//    //--------------------------------------------------
//    //bIsAlphaNum
//    {
//        m_bRes = CxChar::bIsAlphaNum(INT iChar);
//        xASSERT(FALSE != m_bRes);
//    }
//
//    //--------------------------------------------------
//    //bIsAlpha
//    {
//        m_bRes = CxChar::bIsAlpha(INT iChar);
//        xASSERT(FALSE != m_bRes);
//    }
//
//    //--------------------------------------------------
//    //bIsControl
//    {
//        m_bRes = CxChar::bIsControl(INT iChar);
//        xASSERT(FALSE != m_bRes);
//    }
//
//    //--------------------------------------------------
//    //bIsDigitDec
//    {
//        m_bRes = CxChar::bIsDigitDec(INT iChar);
//        xASSERT(FALSE != m_bRes);
//    }
//
//    //--------------------------------------------------
//    //bIsDigitHex
//    {
//        m_bRes = CxChar::bIsDigitHex(INT iChar);
//        xASSERT(FALSE != m_bRes);
//    }
//
//    //--------------------------------------------------
//    //bIsGraph
//    {
//        m_bRes = CxChar::bIsGraph(INT iChar);
//        xASSERT(FALSE != m_bRes);
//    }
//
//    //--------------------------------------------------
//    //bIsPrint
//    {
//        m_bRes = CxChar::bIsPrint(INT iChar);
//        xASSERT(FALSE != m_bRes);
//    }
//
//    //--------------------------------------------------
//    //bIsPunct
//    {
//        m_bRes = CxChar::bIsPunct(INT iChar);
//        xASSERT(FALSE != m_bRes);
//    }
//
//    //--------------------------------------------------
//    //bIsSpace
//    {
//        m_bRes = CxChar::bIsSpace(INT iChar);
//        xASSERT(FALSE != m_bRes);
//    }
//
//    //--------------------------------------------------
//    //bIsLower
//    {
//        m_bRes = CxChar::bIsLower(INT iChar);
//        xASSERT(FALSE != m_bRes);
//    }
//
//    //--------------------------------------------------
//    //bIsUpper
//    {
//        m_bRes = CxChar::bIsUpper(INT iChar);
//        xASSERT(FALSE != m_bRes);
//    }
//
//    //--------------------------------------------------
//    //chToLower
//    {
//        m_chRes = CxChar::chToLower(INT iChar);
//    }
//
//    //--------------------------------------------------
//    //chToUpper
//    {
//        m_chRes = CxChar::chToUpper(INT iChar);
//    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxCharH
