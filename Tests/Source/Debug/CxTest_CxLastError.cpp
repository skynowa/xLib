/****************************************************************************
* Class name:  CxTest_CxLastError
* Description: test CxLastError
* File name:   CxTest_CxLastError.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Debug/CxTest_CxLastError.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxLastError (constructor)
CxTest_CxLastError::CxTest_CxLastError() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxLastError (destructor)
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
            xASSERT(0 == CxLastError::ulGet());
            xASSERT(0 <= ulCode);
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
            xASSERT(false == sError.empty());
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
            xASSERT(FALSE != m_bRes);
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
			xASSERT(FALSE != m_bRes);

			m_bRes = CxLastError::bReset();
			xASSERT(FALSE != m_bRes);

			xASSERT(0UL == CxLastError::ulGet());
        }
    }

    //-------------------------------------
    //sFormat
    {
        m_sRes = CxLastError::sFormat(0);
        xASSERT(false == m_sRes.empty());

        m_sRes = CxLastError::sFormat(1);
        xASSERT(false == m_sRes.empty());

        m_sRes = CxLastError::sFormat(2);
        xASSERT(false == m_sRes.empty());

        m_sRes = CxLastError::sFormat(3);
        xASSERT(false == m_sRes.empty());

        m_sRes = CxLastError::sFormat(4);
        xASSERT(false == m_sRes.empty());
    }

    return TRUE;
}
//---------------------------------------------------------------------------
