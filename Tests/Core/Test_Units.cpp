/**
 * \file   Test_Units.cpp
 * \brief  test Units
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Units)
xTEST_UNIT(Test_Units)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Units::unit()
{
    xTEST_CASE("Bytes")
    {
        culonglong_t Byte = 1ULL;
        culonglong_t Kb   = 1024ULL;
        culonglong_t Mb   = 1024ULL * 1024;
        culonglong_t Gb   = 1024ULL * 1024 * 1024;
        culonglong_t Tb   = 1024ULL * 1024 * 1024 * 1024;
        culonglong_t Pb   = 1024ULL * 1024 * 1024 * 1024 * 1024;
        culonglong_t Eb   = 1024ULL * 1024 * 1024 * 1024 * 1024 * 1024;

        for (size_t i = 0; i < 20; ++ i) {
            xTEST_EQ(xBYTES(i), Byte * i);
            xTEST_EQ(xKB(i),    Kb * i);
            xTEST_EQ(xMB(i),    Mb * i);
            xTEST_EQ(xGB(i),    Gb * i);
            xTEST_EQ(xTB(i),    Tb * i);
            xTEST_EQ(xPB(i),    Pb * i);
            xTEST_EQ(xEB(i),    Eb * i);
        }
    }

    xTEST_CASE("Datetime")
    {
        // TEST: Datetime
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
