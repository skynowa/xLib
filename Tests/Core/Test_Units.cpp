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
            xTEST_EQ(xBYTES(1 * i), Byte * i);
            xTEST_EQ(xKB(1 * i),    Kb * i);
            xTEST_EQ(xMB(1 * i),    Mb * i);
            xTEST_EQ(xGB(1 * i),    Gb * i);
            xTEST_EQ(xTB(1 * i),    Tb * i);
            xTEST_EQ(xPB(1 * i),    Pb * i);
            xTEST_EQ(xEB(1 * i),    Eb * i);
        }
    }

    xTEST_CASE("Datetime")
    {
        // TEST: Datetime
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
