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
BOOL
CxTest_CxStdError::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //iGet
    xTEST_BLOCK(cullBlockLoops)
    {
        const INT ciMaxErrors = 200;  /*0...132*/;

        for (INT i = 0; i < ciMaxErrors; ++ i) {
            INT iCode = CxStdError::iGet();
            xASSERT_EQ(0, CxStdError::iGet());
            xASSERT_LESS_EQ(0, iCode);
        }
    }

    //-------------------------------------
    //iGet
    xTEST_BLOCK(cullBlockLoops)
    {
        const INT ciMaxErrors = 200;    /*0...132*/

        for (INT i = 0; i < ciMaxErrors; ++ i) {
            std::tstring sError = CxStdError::sGet();
            xASSERT_EQ(false, sError.empty());
        }
    }

    //-------------------------------------
    //bSet
    xTEST_BLOCK(cullBlockLoops)
    {
        const INT ciMaxErrors = 200;    /*0...132*/

        for (INT i = 0; i < ciMaxErrors; ++ i) {
            m_bRes = CxStdError::bSet(i);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bReset
    xTEST_BLOCK(cullBlockLoops)
    {
        const INT ciMaxErrors = 200;    /*0...132*/

        for (INT i = 0; i < ciMaxErrors; ++ i) {
            m_bRes = CxStdError::bSet(i);
			xASSERT_NOT_EQ(FALSE, m_bRes);

			m_bRes = CxStdError::bReset();
			xASSERT_NOT_EQ(FALSE, m_bRes);

			xASSERT_EQ(0, CxStdError::iGet());
        }
    }

    //-------------------------------------
    //sFormat
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_WIN)
            const size_t cuiMaxErrors = 17000;  /*0...15999*/;
        #elif defined(xOS_LINUX)
            const size_t cuiMaxErrors = 200;    /*0...132*/
        #endif

        for (ULONG i = 0; i < cuiMaxErrors; ++ i) {
            m_sRes = CxStdError::sFormat(i);
            xASSERT_EQ(false, m_sRes.empty());

            //xTRACEV(xT("\CxStdError::sFormat(%li) = %s (size = %li)"), i, m_sRes.c_str(), m_sRes.size() - 4);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
