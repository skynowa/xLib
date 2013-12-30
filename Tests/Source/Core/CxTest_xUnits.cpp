/**
 * \file   CxTest_xUnits.cpp
 * \brief  test xUnits
 */


#include <Test/Core/CxTest_xUnits.h>


//---------------------------------------------------------------------------
/* virtual */
void_t
CxTest_xUnits::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("xUnits::bytes", a_caseLoops)
    {
        culonglong_t BYTE = 1ULL;
        culonglong_t KB   = 1024ULL;
        culonglong_t MB   = 1024ULL * 1024;
        culonglong_t GB   = 1024ULL * 1024 * 1024;
        culonglong_t TB   = 1024ULL * 1024 * 1024 * 1024;
        culonglong_t PB   = 1024ULL * 1024 * 1024 * 1024 * 1024;
        culonglong_t EB   = 1024ULL * 1024 * 1024 * 1024 * 1024 * 1024;

        xTEST_EQ(1ULL,   BYTE);
        xTEST_EQ(xKB(1), KB);
        xTEST_EQ(xMB(1), MB);
        xTEST_EQ(xGB(1), GB);
        xTEST_EQ(xTB(1), TB);
        xTEST_EQ(xPB(1), PB);
        xTEST_EQ(xEB(1), EB);
    }
}
//---------------------------------------------------------------------------
