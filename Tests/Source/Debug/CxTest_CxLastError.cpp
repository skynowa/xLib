/**
 * \file   CxTest_CxLastError.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxLastError.h>


//------------------------------------------------------------------------------
CxTest_CxLastError::CxTest_CxLastError() {

}
//------------------------------------------------------------------------------
CxTest_CxLastError::~CxTest_CxLastError() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxLastError::unit(
    culonglong_t &a_cullCaseLoops
)
{
    #if   xOS_ENV_WIN
        culong_t cuiMaxErrors = 15999;  /*0...15999*/;
    #elif xOS_ENV_UNIX
        culong_t cuiMaxErrors = 132;    /*0...132*/
    #endif

    xTEST_CASE("CxLastError::isSuccess", a_cullCaseLoops)
    {
        CxLastError::reset();
        m_bRv = CxLastError::isSuccess();
        xTEST_EQ(true, m_bRv);

        CxLastError::set(10UL);
        m_bRv = CxLastError::isSuccess();
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxLastError::get", a_cullCaseLoops)
    {
        m_ulRv = CxLastError::get();
        xUNUSED(m_ulRv);
        xTEST_EQ(0UL, CxLastError::get());
    }

    xTEST_CASE("CxLastError::format", a_cullCaseLoops)
    {
        m_sRv = CxLastError::format();
        xTEST_EQ(0UL,   CxLastError::get());
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxLastError::set", a_cullCaseLoops)
    {
        culong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            culong_t culLasError = caulData[i];

            CxLastError::set(culLasError);
            xTEST_EQ(culLasError, CxLastError::get());
        }
    }

    xTEST_CASE("CxLastError::reset", a_cullCaseLoops)
    {
        culong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            culong_t culLasError = caulData[i];

            CxLastError::set(culLasError);
            CxLastError::reset();
            xTEST_EQ(0UL, CxLastError::get());
        }
    }

    xTEST_CASE("CxLastError::format", a_cullCaseLoops)
    {
        culong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            culong_t culLasError = caulData[i];

            m_sRv = CxLastError::format(culLasError);
            xTEST_EQ(false, m_sRv.empty());
        }
    }
}
//------------------------------------------------------------------------------
