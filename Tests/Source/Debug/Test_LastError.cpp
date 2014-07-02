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

    xTEST_CASE("LastError::isSuccess", a_caseLoops)
    {
        LastError::reset();
        m_bRv = LastError::isSuccess();
        xTEST_EQ(m_bRv, true);

        LastError::set(10UL);
        m_bRv = LastError::isSuccess();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("LastError::get", a_caseLoops)
    {
        m_ulRv = LastError::get();
        xUNUSED(m_ulRv);
        xTEST_EQ(0UL, LastError::get());
    }

    xTEST_CASE("LastError::format", a_caseLoops)
    {
        m_sRv = LastError::format();
        xTEST_EQ(0UL,   LastError::get());
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("LastError::set", a_caseLoops)
    {
        culong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            culong_t culLasError = caulData[i];

            LastError::set(culLasError);
            xTEST_EQ(culLasError, LastError::get());
        }
    }

    xTEST_CASE("LastError::reset", a_caseLoops)
    {
        culong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            culong_t culLasError = caulData[i];

            LastError::set(culLasError);
            LastError::reset();
            xTEST_EQ(0UL, LastError::get());
        }
    }

    xTEST_CASE("LastError::format", a_caseLoops)
    {
        culong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            culong_t culLasError = caulData[i];

            m_sRv = LastError::format(culLasError);
            xTEST_EQ(false, m_sRv.empty());
        }
    }
}
//-------------------------------------------------------------------------------------------------
