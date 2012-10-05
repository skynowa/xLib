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

    //-------------------------------------
    // ulGet
    xTEST_CASE(cullCaseLoops)
    {
        (void)CxLastError::ulGet();
        xTEST_EQ(0UL, CxLastError::ulGet());
    }

    //-------------------------------------
    // sGet
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxLastError::sGet();
        xTEST_EQ(0UL,   CxLastError::ulGet());
        xTEST_EQ(false, m_sRv.empty());
    }

    //-------------------------------------
    // bSet
    xTEST_CASE(cullCaseLoops)
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

    //-------------------------------------
    // bReset
    xTEST_CASE(cullCaseLoops)
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

    //-------------------------------------
    // sFormat
    xTEST_CASE(cullCaseLoops)
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
