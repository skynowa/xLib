/**
 * \file   CxTest_CxStdError.cpp
 * \brief  test CxStdError
 */


#include <Test/Debug/CxTest_CxStdError.h>


//---------------------------------------------------------------------------
CxTest_CxStdError::CxTest_CxStdError() {

}
//---------------------------------------------------------------------------
CxTest_CxStdError::~CxTest_CxStdError() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxStdError::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //iGet
    xTEST_BLOCK(cullBlockLoops)
    {
        const int ciMaxErrors = 200;  /*0...132*/;

        for (int i = 0; i < ciMaxErrors; ++ i) {
            int iCode = CxStdError::iGet();
            xTEST_EQ(0, CxStdError::iGet());
            xTEST_LESS_EQ(0, iCode);
        }
    }

    //-------------------------------------
    //iGet
    xTEST_BLOCK(cullBlockLoops)
    {
        const int ciMaxErrors = 200;    /*0...132*/

        for (int i = 0; i < ciMaxErrors; ++ i) {
            std::tstring sError = CxStdError::sGet();
            xTEST_EQ(false, sError.empty());
        }
    }

    //-------------------------------------
    //bSet
    xTEST_BLOCK(cullBlockLoops)
    {
        const int ciMaxErrors = 200;    /*0...132*/

        for (int i = 0; i < ciMaxErrors; ++ i) {
            m_bRes = CxStdError::bSet(i);
            xTEST_DIFF(false, m_bRes);
        }
    }

    //-------------------------------------
    //bReset
    xTEST_BLOCK(cullBlockLoops)
    {
        const int ciMaxErrors = 200;    /*0...132*/

        for (int i = 0; i < ciMaxErrors; ++ i) {
            m_bRes = CxStdError::bSet(i);
            xTEST_DIFF(false, m_bRes);

            m_bRes = CxStdError::bReset();
            xTEST_DIFF(false, m_bRes);

            xTEST_EQ(0, CxStdError::iGet());
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
            m_sRes = CxStdError::sFormat(i);
            xTEST_EQ(false, m_sRes.empty());

            //xTRACEV(xT("\CxStdError::sFormat(%lu) = %s (size = %lu)"), i, m_sRes.c_str(), m_sRes.size() - 4);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
