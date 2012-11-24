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
/* virtual */
void
CxTest_CxStdError::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const int ciMaxErrors = 132;  /*0...132*/;

    xTEST_CASE("CxStdError::iGet", cullCaseLoops)
    {
        (int)CxStdError::iGet();
        xTEST_EQ(0, CxStdError::iGet());
    }

   
    xTEST_CASE("CxStdError::sGet", cullCaseLoops)
    {
        std::tstring_t sError = CxStdError::sGet();
        xTEST_EQ(false, sError.empty());
    }

    xTEST_CASE("CxStdError::vSet", cullCaseLoops)
    {
        const int caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int i = 0; i < (int)xARRAY_SIZE(caiData); ++ i) {
            const int ciLastError = caiData[i];

            CxStdError::vSet(ciLastError);
            xTEST_EQ(ciLastError, CxStdError::iGet());
            xTEST_EQ(0, CxStdError::iGet());
        }
    }

    xTEST_CASE("CxStdError::vReset", cullCaseLoops)
    {
        const int caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int i = 0; i < (int)xARRAY_SIZE(caiData); ++ i) {
            const int ciLastError = caiData[i];

            CxStdError::vSet(ciLastError);
            CxStdError::vReset();
            xTEST_EQ(0, CxStdError::iGet());
        }
    }

    xTEST_CASE("CxStdError::sFormat", cullCaseLoops)
    {
        const int caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int i = 0; i < (int)xARRAY_SIZE(caiData); ++ i) {
            const int ciLastError = caiData[i];

            m_sRv = CxStdError::sFormat(ciLastError);
            xTEST_EQ(false, m_sRv.empty());

            //xTRACEV(xT("\CxStdError::sFormat(%lu) = %s (size = %lu)"), i, m_sRv.c_str(), m_sRv.size() - 4);
        }
    }
}
//---------------------------------------------------------------------------
