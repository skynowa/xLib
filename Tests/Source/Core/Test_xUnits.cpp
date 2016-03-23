/**
 * \file   Test_Units.cpp
 * \brief  test Units
 */


#include <Test/Core/Test_Units.h>

#include <xLib/Core/Format.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Units)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Units::unit()
{
    xTEST_CASE("Bytes")
    {
        culonglong_t BYTE = 1ULL;
        culonglong_t KB   = 1024ULL;
        culonglong_t MB   = 1024ULL * 1024;
        culonglong_t GB   = 1024ULL * 1024 * 1024;
        culonglong_t TB   = 1024ULL * 1024 * 1024 * 1024;
        culonglong_t PB   = 1024ULL * 1024 * 1024 * 1024 * 1024;
        culonglong_t EB   = 1024ULL * 1024 * 1024 * 1024 * 1024 * 1024;

        for (size_t i = 0; i < 20; ++ i) {
            xTEST_EQ(xBYTES(1 * i), BYTE * i);
            xTEST_EQ(xKB(1 * i),    KB * i);
            xTEST_EQ(xMB(1 * i),    MB * i);
            xTEST_EQ(xGB(1 * i),    GB * i);
            xTEST_EQ(xTB(1 * i),    TB * i);
            xTEST_EQ(xPB(1 * i),    PB * i);
            xTEST_EQ(xEB(1 * i),    EB * i);
        }
    }

    xTEST_CASE("Datetime")
    {
        // TEST: Datetime
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
