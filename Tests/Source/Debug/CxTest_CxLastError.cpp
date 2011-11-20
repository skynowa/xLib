/**
 * \file   CxTest_CxLastError.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxLastError.h>


//---------------------------------------------------------------------------
CxTest_CxLastError::CxTest_CxLastError() {

}
//---------------------------------------------------------------------------
CxTest_CxLastError::~CxTest_CxLastError() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxLastError::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //ulGet
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xOS_ENV_WIN
            const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif xOS_ENV_UNIX
            const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            ULONG ulCode = CxLastError::ulGet();
            xTEST_EQ(0UL, CxLastError::ulGet());
            xTEST_LESS_EQ(0UL, ulCode);
        }
    }

    //-------------------------------------
    //ulGet
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xOS_ENV_WIN
            const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif xOS_ENV_UNIX
            const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            std::tstring sError = CxLastError::sGet();
            xTEST_EQ(false, sError.empty());
        }
    }

    //-------------------------------------
    //bSet
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xOS_ENV_WIN
            const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif xOS_ENV_UNIX
            const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            m_bRes = CxLastError::bSet(i);
            xTEST_DIFF(false, m_bRes);
        }
    }

    //-------------------------------------
    //bReset
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xOS_ENV_WIN
            const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif xOS_ENV_UNIX
            const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            m_bRes = CxLastError::bSet(i);
            xTEST_DIFF(false, m_bRes);

            m_bRes = CxLastError::bReset();
            xTEST_DIFF(false, m_bRes);

            xTEST_EQ(0UL, CxLastError::ulGet());
        }
    }

    //-------------------------------------
    //sFormat
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xOS_ENV_WIN
            const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif xOS_ENV_UNIX
            const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            m_sRes = CxLastError::sFormat(i);
            xTEST_EQ(false, m_sRes.empty());

            //xTRACEV(xT("\tCxLastError::sFormat(%lu) = %s (size = %lu)"), i, m_sRes.c_str(), m_sRes.size() - 4);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
