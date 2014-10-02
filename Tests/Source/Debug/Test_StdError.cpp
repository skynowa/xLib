/**
 * \file   Test_StdError.cpp
 * \brief  test StdError
 */


#include <Test/Debug/Test_StdError.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_StdError::unit(
    culonglong_t &a_caseLoops
)
{
    cint_t ciMaxErrors = 132;  /*0...132*/;

    xTEST_CASE("StdError::isSuccess", a_caseLoops)
    {
        StdError::reset();
        m_bRv = StdError::isSuccess();
        xTEST_EQ(m_bRv, true);

        m_bRv = StdError::isSuccess();
        xTEST_EQ(m_bRv, true);

        StdError::set(10);
        m_bRv = StdError::isSuccess();
        xTEST_EQ(m_bRv, false);

        m_bRv = StdError::isSuccess();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("StdError::get", a_caseLoops)
    {
        m_iRv = StdError::get();
        xUNUSED(m_iRv);
        xTEST_EQ(0, StdError::get());
    }

    xTEST_CASE("StdError::format", a_caseLoops)
    {
        std::tstring_t sError = StdError::format();
        xTEST_EQ(false, sError.empty());
    }

    xTEST_CASE("StdError::set", a_caseLoops)
    {
        cint_t caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int_t i = 0; i < (int_t)xARRAY_SIZE(caiData); ++ i) {
            cint_t stdError = caiData[i];

            StdError::set(stdError);
            xTEST_EQ(stdError, StdError::get());
            xTEST_EQ(0, StdError::get());
        }
    }

    xTEST_CASE("StdError::reset", a_caseLoops)
    {
        cint_t caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int_t i = 0; i < (int_t)xARRAY_SIZE(caiData); ++ i) {
            cint_t stdError = caiData[i];

            StdError::set(stdError);
            StdError::reset();
            xTEST_EQ(0, StdError::get());
        }
    }

    xTEST_CASE("StdError::format", a_caseLoops)
    {
        cint_t caiData[] = {
            0,
            ciMaxErrors - 10,
            ciMaxErrors,
            ciMaxErrors + 10
        };

        for (int_t i = 0; i < (int_t)xARRAY_SIZE(caiData); ++ i) {
            cint_t stdError = caiData[i];

            m_sRv = StdError::format(stdError);
            xTEST_EQ(false, m_sRv.empty());

            //xTRACEV(xT("\StdError::format(%lu) = %s (size = %lu)"), i, m_sRv.c_str(), m_sRv.size() - 4);
        }
    }
}
//-------------------------------------------------------------------------------------------------
