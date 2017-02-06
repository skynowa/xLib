/**
 * \file   Test_StdError.cpp
 * \brief  test StdError
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_StdError)
xTEST_UNIT(Test_StdError)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_StdError::unit()
{
    cint_t ciMaxErrors = 132;  /*0...132*/;

    xTEST_CASE("isSuccess")
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

    xTEST_CASE("get")
    {
        m_iRv = StdError::get();
        xUNUSED(m_iRv);
        xTEST_EQ(0, StdError::get());
    }

    xTEST_CASE("format")
    {
        std::tstring_t sError = StdError::format();
        xTEST_EQ(false, sError.empty());
    }

    xTEST_CASE("set")
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

    xTEST_CASE("reset")
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

    xTEST_CASE("format")
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

    return true;
}
//-------------------------------------------------------------------------------------------------
