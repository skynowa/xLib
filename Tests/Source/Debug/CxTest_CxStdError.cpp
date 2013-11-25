/**
 * \file   CxTest_CxStdError.cpp
 * \brief  test CxStdError
 */


#include <Test/Debug/CxTest_CxStdError.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxStdError::unit(
    culonglong_t &a_caseLoops
)
{
    cint_t ciMaxErrors = 132;  /*0...132*/;

    xTEST_CASE("CxStdError::isSuccess", a_caseLoops)
    {
        CxStdError::reset();
        m_bRv = CxStdError::isSuccess();
        xTEST_EQ(true, m_bRv);

        m_bRv = CxStdError::isSuccess();
        xTEST_EQ(true, m_bRv);

        CxStdError::set(10);
        m_bRv = CxStdError::isSuccess();
        xTEST_EQ(false, m_bRv);

        m_bRv = CxStdError::isSuccess();
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxStdError::get", a_caseLoops)
    {
        m_iRv = CxStdError::get();
        xUNUSED(m_iRv);
        xTEST_EQ(0, CxStdError::get());
    }

    xTEST_CASE("CxStdError::format", a_caseLoops)
    {
        std::tstring_t sError = CxStdError::format();
        xTEST_EQ(false, sError.empty());
    }

    xTEST_CASE("CxStdError::set", a_caseLoops)
    {
        cint_t caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int_t i = 0; i < (int_t)xARRAY_SIZE(caiData); ++ i) {
            cint_t ciLastError = caiData[i];

            CxStdError::set(ciLastError);
            xTEST_EQ(ciLastError, CxStdError::get());
            xTEST_EQ(0, CxStdError::get());
        }
    }

    xTEST_CASE("CxStdError::reset", a_caseLoops)
    {
        cint_t caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int_t i = 0; i < (int_t)xARRAY_SIZE(caiData); ++ i) {
            cint_t ciLastError = caiData[i];

            CxStdError::set(ciLastError);
            CxStdError::reset();
            xTEST_EQ(0, CxStdError::get());
        }
    }

    xTEST_CASE("CxStdError::format", a_caseLoops)
    {
        cint_t caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int_t i = 0; i < (int_t)xARRAY_SIZE(caiData); ++ i) {
            cint_t ciLastError = caiData[i];

            m_sRv = CxStdError::format(ciLastError);
            xTEST_EQ(false, m_sRv.empty());

            //xTRACEV(xT("\CxStdError::format(%lu) = %s (size = %lu)"), i, m_sRv.c_str(), m_sRv.size() - 4);
        }
    }
}
//------------------------------------------------------------------------------
