/**
 * \file   Test_NativeError.cpp
 * \brief
 */


#include "Test_NativeError.h"

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_NativeError)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_NativeError::unit()
{
    #if   xENV_WIN
        culong_t cuiMaxErrors = 15999;  /*0...15999*/;
    #elif xENV_UNIX
        culong_t cuiMaxErrors = 132;    /*0...132*/
    #endif

    xTEST_CASE("isSuccess")
    {
        NativeError::reset();
        m_bRv = NativeError::isSuccess();
        xTEST_EQ(m_bRv, true);

        NativeError::set(10UL);
        m_bRv = NativeError::isSuccess();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("get")
    {
        m_ulRv = NativeError::get();
        xUNUSED(m_ulRv);
        xTEST_EQ(0UL, NativeError::get());
    }

    xTEST_CASE("format")
    {
        m_sRv = NativeError::format();
        xTEST_EQ(0UL,   NativeError::get());
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("set")
    {
        culong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            culong_t culLasError = caulData[i];

            NativeError::set(culLasError);
            xTEST_EQ(culLasError, NativeError::get());
        }
    }

    xTEST_CASE("reset")
    {
        culong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            culong_t culLasError = caulData[i];

            NativeError::set(culLasError);
            NativeError::reset();
            xTEST_EQ(0UL, NativeError::get());
        }
    }

    xTEST_CASE("format")
    {
        culong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            culong_t culLasError = caulData[i];

            m_sRv = NativeError::format(culLasError);
            xTEST_EQ(false, m_sRv.empty());
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
