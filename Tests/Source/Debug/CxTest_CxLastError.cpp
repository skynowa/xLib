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

    xTEST_CASE("CxLastError::ulGet", cullCaseLoops)
    {
        (void)CxLastError::ulGet();
        xTEST_EQ(0UL, CxLastError::ulGet());
    }

    xTEST_CASE("CxLastError::sGet", cullCaseLoops)
    {
        m_sRv = CxLastError::sGet();
        xTEST_EQ(0UL,   CxLastError::ulGet());
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxLastError::vSet", cullCaseLoops)
    {
        const ulong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            const ulong_t culLasError = caulData[i];

            CxLastError::vSet(culLasError);
            xTEST_EQ(culLasError, CxLastError::ulGet());
        }
    }

    xTEST_CASE("CxLastError::vReset", cullCaseLoops)
    {
        const ulong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            const ulong_t culLasError = caulData[i];

            CxLastError::vSet(culLasError);
            CxLastError::vReset();
            xTEST_EQ(0UL, CxLastError::ulGet());
        }
    }

    xTEST_CASE("CxLastError::sFormat", cullCaseLoops)
    {
        const ulong_t caulData[] = {
            0UL,
            cuiMaxErrors - 10UL,
            cuiMaxErrors,
            cuiMaxErrors + 10UL
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            const ulong_t culLasError = caulData[i];

            m_sRv = CxLastError::sFormat(culLasError);
            xTEST_EQ(false, m_sRv.empty());
        }
    }
}
//---------------------------------------------------------------------------
