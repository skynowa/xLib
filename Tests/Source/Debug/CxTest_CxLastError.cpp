/**
 * \file   CxTest_CxLastError.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxLastError.h>


//---------------------------------------------------------------------------
CxTest_CxLastError::CxTest_CxLastError() {

}
//---------------------------------------------------------------------------
CxTest_CxLastError::~CxTest_CxLastError() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxLastError::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    #if   xOS_ENV_WIN
        const ulong_t cuiMaxErrors = 15999;  /*0...15999*/;
    #elif xOS_ENV_UNIX
        const ulong_t cuiMaxErrors = 132;    /*0...132*/
    #endif

    xTEST_CASE("CxLastError::get", cullCaseLoops)
    {
        (void)CxLastError::get();
        xTEST_EQ(0UL, CxLastError::get());
    }

    xTEST_CASE("CxLastError::toString", cullCaseLoops)
    {
        m_sRv = CxLastError::toString();
        xTEST_EQ(0UL,   CxLastError::get());
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxLastError::set", cullCaseLoops)
    {
        const ulong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            const ulong_t culLasError = caulData[i];

            CxLastError::set(culLasError);
            xTEST_EQ(culLasError, CxLastError::get());
        }
    }

    xTEST_CASE("CxLastError::reset", cullCaseLoops)
    {
        const ulong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            const ulong_t culLasError = caulData[i];

            CxLastError::set(culLasError);
            CxLastError::reset();
            xTEST_EQ(0UL, CxLastError::get());
        }
    }

    xTEST_CASE("CxLastError::format", cullCaseLoops)
    {
        const ulong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            const ulong_t culLasError = caulData[i];

            m_sRv = CxLastError::format(culLasError);
            xTEST_EQ(false, m_sRv.empty());
        }
    }
}
//---------------------------------------------------------------------------
