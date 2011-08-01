/****************************************************************************
* Class name:  CxTest_CxLastError
* Description: test CxLastError
* File name:   CxTest_CxLastError.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Debug/CxTest_CxLastError.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxLastError
CxTest_CxLastError::CxTest_CxLastError() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxLastError
CxTest_CxLastError::~CxTest_CxLastError() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxLastError::bUnit() {
    //-------------------------------------
    //ulGet
    {
        #if defined(xOS_WIN)
        const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif defined(xOS_LINUX)
        const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            ULONG ulCode = CxLastError::ulGet();
            xASSERT_EQUAL(0UL, CxLastError::ulGet());
            xASSERT_LESS_EQUAL(0UL, ulCode);
        }
    }

    //-------------------------------------
    //ulGet
    {
        #if defined(xOS_WIN)
        const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif defined(xOS_LINUX)
        const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            tString sError = CxLastError::sGet();
            xASSERT_EQUAL(false, sError.empty());
        }
    }

    //-------------------------------------
    //bSet
    {
        #if defined(xOS_WIN)
        const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif defined(xOS_LINUX)
        const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            m_bRes = CxLastError::bSet(i);
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bReset
    {
        #if defined(xOS_WIN)
        const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif defined(xOS_LINUX)
        const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            m_bRes = CxLastError::bSet(i);
			xASSERT_NOT_EQUAL(FALSE, m_bRes);

			m_bRes = CxLastError::bReset();
			xASSERT_NOT_EQUAL(FALSE, m_bRes);

			xASSERT_EQUAL(0UL, CxLastError::ulGet());
        }
    }

    //-------------------------------------
    //sFormat
    {
        m_sRes = CxLastError::sFormat(0);
        xASSERT_EQUAL(false, m_sRes.empty());

        m_sRes = CxLastError::sFormat(1);
        xASSERT_EQUAL(false, m_sRes.empty());

        m_sRes = CxLastError::sFormat(2);
        xASSERT_EQUAL(false, m_sRes.empty());

        m_sRes = CxLastError::sFormat(3);
        xASSERT_EQUAL(false, m_sRes.empty());

        m_sRes = CxLastError::sFormat(4);
        xASSERT_EQUAL(false, m_sRes.empty());
    }

    return TRUE;
}
//---------------------------------------------------------------------------
