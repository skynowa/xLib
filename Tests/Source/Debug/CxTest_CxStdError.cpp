/**
 * \file   CxTest_CxStdError.cpp
 * \brief  test CxStdError
 */


#include <Test/Debug/CxTest_CxStdError.h>


//------------------------------------------------------------------------------
CxTest_CxStdError::CxTest_CxStdError() {

}
//------------------------------------------------------------------------------
CxTest_CxStdError::~CxTest_CxStdError() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxStdError::unit(
    const ulonglong_t &cullCaseLoops
)
{
    const int ciMaxErrors = 132;  /*0...132*/;

    xTEST_CASE("CxStdError::get", cullCaseLoops)
    {
        m_iRv = CxStdError::get();
        xUNUSED(m_iRv);
        xTEST_EQ(0, CxStdError::get());
    }

    xTEST_CASE("CxStdError::toString", cullCaseLoops)
    {
        std::tstring_t sError = CxStdError::toString();
        xTEST_EQ(false, sError.empty());
    }

    xTEST_CASE("CxStdError::set", cullCaseLoops)
    {
        const int caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int i = 0; i < (int)xARRAY_SIZE(caiData); ++ i) {
            const int ciLastError = caiData[i];

            CxStdError::set(ciLastError);
            xTEST_EQ(ciLastError, CxStdError::get());
            xTEST_EQ(0, CxStdError::get());
        }
    }

    xTEST_CASE("CxStdError::reset", cullCaseLoops)
    {
        const int caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int i = 0; i < (int)xARRAY_SIZE(caiData); ++ i) {
            const int ciLastError = caiData[i];

            CxStdError::set(ciLastError);
            CxStdError::reset();
            xTEST_EQ(0, CxStdError::get());
        }
    }

    xTEST_CASE("CxStdError::format", cullCaseLoops)
    {
        const int caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int i = 0; i < (int)xARRAY_SIZE(caiData); ++ i) {
            const int ciLastError = caiData[i];

            m_sRv = CxStdError::format(ciLastError);
            xTEST_EQ(false, m_sRv.empty());

            //xTRACEV(xT("\CxStdError::format(%lu) = %s (size = %lu)"), i, m_sRv.c_str(), m_sRv.size() - 4);
        }
    }
}
//------------------------------------------------------------------------------
