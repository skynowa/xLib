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
CxTest_CxLastError::CxTest_CxLastError() {

}
//---------------------------------------------------------------------------
CxTest_CxLastError::~CxTest_CxLastError() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxLastError::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //ulGet
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif defined(xOS_ENV_UNIX)
            const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            ULONG ulCode = CxLastError::ulGet();
            xASSERT_EQ(0UL, CxLastError::ulGet());
            xASSERT_LESS_EQ(0UL, ulCode);
        }
    }

    //-------------------------------------
    //ulGet
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif defined(xOS_ENV_UNIX)
            const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            std::tstring sError = CxLastError::sGet();
            xASSERT_EQ(false, sError.empty());
        }
    }

    //-------------------------------------
    //bSet
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif defined(xOS_ENV_UNIX)
            const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            m_bRes = CxLastError::bSet(i);
            xASSERT_DIFF(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bReset
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif defined(xOS_ENV_UNIX)
            const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            m_bRes = CxLastError::bSet(i);
			xASSERT_DIFF(FALSE, m_bRes);

			m_bRes = CxLastError::bReset();
			xASSERT_DIFF(FALSE, m_bRes);

			xASSERT_EQ(0UL, CxLastError::ulGet());
        }
    }

    //-------------------------------------
    //sFormat
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif defined(xOS_ENV_UNIX)
            const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            m_sRes = CxLastError::sFormat(i);
            xASSERT_EQ(false, m_sRes.empty());

            //xTRACEV(xT("\tCxLastError::sFormat(%li) = %s (size = %li)"), i, m_sRes.c_str(), m_sRes.size() - 4);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
