/****************************************************************************
* Class name:  CxTest_CxMacros
* Description: testing CxMacros
* File name:   CxTest_CxMacros.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/CxTest_CxMacros.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxMacros
CxTest_CxMacros::CxTest_CxMacros() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxMacros
CxTest_CxMacros::~CxTest_CxMacros() {

}
//---------------------------------------------------------------------------
//TODO: DONE (unit test)
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
        TCHAR szBuff[255 + 1];

        xBUFF_ZERO(szBuff);

        for (size_t i = 0; i < xARRAY_SIZE(szBuff); ++ i) {
            xASSERT_EQUAL(xT('\0'), szBuff[i]);
        }
    }

    //-------------------------------------
    //xARRAY_SIZE
    {
        {
            TCHAR szBuff[256] = {0};
            m_uiRes = xARRAY_SIZE(szBuff);
            xASSERT_EQUAL(256U, m_uiRes);

            INT aiBuff[256] = {0};
            m_uiRes = xARRAY_SIZE(aiBuff);
            xASSERT_EQUAL(256U, m_uiRes);

            tString asBuff[256];
            m_uiRes = xARRAY_SIZE(asBuff);
            xASSERT_EQUAL(256U, m_uiRes);
        }

        //must compile-error
        {
            ////TCHAR *pszBuff = NULL;
            ////m_uiRes = xARRAY_SIZE(pszBuff);
        }
    }

    //-------------------------------------
    //xMAX
    {
        m_uiRes = xMAX(0, 1);
        xASSERT_EQUAL(1U, m_uiRes);
    }

    //-------------------------------------
    //xMIN
    {
        m_uiRes = xMIN(5, 8);
        xASSERT_EQUAL(5U, m_uiRes);
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
    //xAsTString
    {
        //1
        {
            const TCHAR *pcszBuff = xT("xxxxx");

            m_sRes = CxMacros::sAsTString(pcszBuff);
            xASSERT_EQUAL(tString(pcszBuff), m_sRes);
        }

        //2
        {
            const TCHAR *pcszBuff = xT("1236cnqwieru872692*qwer8lkl;l<l;hoihljkhlwcruqw");

            m_sRes = CxMacros::sAsTString(pcszBuff);
            xASSERT_EQUAL(tString(pcszBuff), m_sRes);
        }

        //3
        {
            const TCHAR *pcszBuff = xT("/n/n/n/n/n/n/n/t/t/t/t/t/t");

            m_sRes = CxMacros::sAsTString(pcszBuff);
            xASSERT_EQUAL(tString(pcszBuff), m_sRes);
        }

        //4
        {
            const TCHAR *pcszBuff = xT("");

            m_sRes = CxMacros::sAsTString(pcszBuff);
            xASSERT_EQUAL(tString(pcszBuff), m_sRes);
        }

        //5
        {
            const TCHAR *pcszBuff = NULL;

            m_sRes = CxMacros::sAsTString(pcszBuff);
            xASSERT_EQUAL(tString(), m_sRes);
        }

        //7
        {
            const TCHAR cszBuff[] = xT("sdjkrtfwo34892vnm3,9rfx12j304y81-34m8905-");

            m_sRes = CxMacros::sAsTString(cszBuff);
            xASSERT_EQUAL(tString(cszBuff), m_sRes);
        }

        //8
        {
            const TCHAR cszBuff[] = {0};

            m_sRes = CxMacros::sAsTString(cszBuff);
            xASSERT_EQUAL(tString(cszBuff), m_sRes);
        }
    }

    //-------------------------------------
    //qualifiers
    {
        //xPR_SIZET
        {
	        const size_t cuiValue = 2356567;

	        m_sRes = CxString::sFormat(xT("%")xPR_SIZET, cuiValue);
	        xASSERT_EQUAL(CxString::lexical_cast(cuiValue), m_sRes);
        }

        //xPR_I64d
        {
	        const LONGLONG cllValue = 36745723;

	        m_sRes = CxString::sFormat(xT("%")xPR_I64d, cllValue);
	        xASSERT_EQUAL(CxString::lexical_cast(cllValue), m_sRes);
        }

        //xPR_I64u
        {
	        const ULONGLONG cullValue = 4767834;

	        m_sRes = CxString::sFormat(xT("%")xPR_I64u, cullValue);
	        xASSERT_EQUAL(CxString::lexical_cast(cullValue), m_sRes);
        }

        //xPR_I64x
        {
        	const LONGLONG cllValue = 57830;

	        m_sRes = CxString::sFormat(xT("%")xPR_I64x, cllValue);
	        xASSERT_EQUAL(CxString::sToLowerCase( CxString::lexical_cast(cllValue, 16) ), m_sRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
