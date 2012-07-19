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
    const ulonglong_t cullCaseLoops
)
{
    const int ciMaxErrors = 132;  /*0...132*/;

    //-------------------------------------
    //iGet
    xTEST_CASE(cullCaseLoops)
    {
        (int)CxStdError::iGet();
        xTEST_EQ(0, CxStdError::iGet());
    }

    //-------------------------------------
    //iGet
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sError = CxStdError::sGet();
        xTEST_EQ(false, sError.empty());
    }

    //-------------------------------------
    //bSet
    xTEST_CASE(cullCaseLoops)
    {
        const int caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int i = 0; i < (int)xARRAY_SIZE(caiData); ++ i) {
            const int ciLastError = caiData[i];

            m_bRes = CxStdError::bSet(ciLastError);
            xTEST_EQ(true, m_bRes);
            xTEST_EQ(ciLastError, CxStdError::iGet());
            xTEST_EQ(0, CxStdError::iGet());
        }
    }

    //-------------------------------------
    //bReset
    xTEST_CASE(cullCaseLoops)
    {
        const int caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int i = 0; i < (int)xARRAY_SIZE(caiData); ++ i) {
            const int ciLastError = caiData[i];

            m_bRes = CxStdError::bSet(ciLastError);
            xTEST_EQ(true, m_bRes);

            m_bRes = CxStdError::bReset();
            xTEST_EQ(true, m_bRes);
            xTEST_EQ(0, CxStdError::iGet());
        }
    }

    //-------------------------------------
    //sFormat
    xTEST_CASE(cullCaseLoops)
    {
        const int caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int i = 0; i < (int)xARRAY_SIZE(caiData); ++ i) {
            const int ciLastError = caiData[i];

            m_sRes = CxStdError::sFormat(ciLastError);
            xTEST_EQ(false, m_sRes.empty());

            //xTRACEV(xT("\CxStdError::sFormat(%lu) = %s (size = %lu)"), i, m_sRes.c_str(), m_sRes.size() - 4);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
