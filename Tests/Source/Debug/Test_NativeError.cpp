/**
 * \file   Test_NativeError.cpp
 * \brief
 */


#include <Test/Debug/Test_NativeError.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_NativeError)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_NativeError::unit(
    std::csize_t &a_caseLoops
)
{
    #if   xENV_WIN
        culong_t cuiMaxErrors = 15999;  /*0...15999*/;
    #elif xENV_UNIX
        culong_t cuiMaxErrors = 132;    /*0...132*/
    #endif

    xTEST_CASE("isSuccess", a_caseLoops)
    {
        NativeError::reset();
        m_bRv = NativeError::isSuccess();
        xTEST_EQ(m_bRv, true);

        NativeError::set(10UL);
        m_bRv = NativeError::isSuccess();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("get", a_caseLoops)
    {
        m_ulRv = NativeError::get();
        xUNUSED(m_ulRv);
        xTEST_EQ(0UL, NativeError::get());
    }

    xTEST_CASE("format", a_caseLoops)
    {
        m_sRv = NativeError::format();
        xTEST_EQ(0UL,   NativeError::get());
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("set", a_caseLoops)
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

    xTEST_CASE("reset", a_caseLoops)
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

    xTEST_CASE("format", a_caseLoops)
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
}
//-------------------------------------------------------------------------------------------------
