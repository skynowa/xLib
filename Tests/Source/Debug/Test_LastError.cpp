/**
 * \file   Test_LastError.cpp
 * \brief
 */


#include <Test/Debug/Test_LastError.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_LastError::unit(
    culonglong_t &a_caseLoops
)
{
    #if   xENV_WIN
        culong_t cuiMaxErrors = 15999;  /*0...15999*/;
    #elif xENV_UNIX
        culong_t cuiMaxErrors = 132;    /*0...132*/
    #endif

    xTEST_CASE("NativeError::isSuccess", a_caseLoops)
    {
        NativeError::reset();
        m_bRv = NativeError::isSuccess();
        xTEST_EQ(m_bRv, true);

        NativeError::set(10UL);
        m_bRv = NativeError::isSuccess();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("NativeError::get", a_caseLoops)
    {
        m_ulRv = NativeError::get();
        xUNUSED(m_ulRv);
        xTEST_EQ(0UL, NativeError::get());
    }

    xTEST_CASE("NativeError::format", a_caseLoops)
    {
        m_sRv = NativeError::format();
        xTEST_EQ(0UL,   NativeError::get());
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("NativeError::set", a_caseLoops)
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

    xTEST_CASE("NativeError::reset", a_caseLoops)
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

    xTEST_CASE("NativeError::format", a_caseLoops)
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
