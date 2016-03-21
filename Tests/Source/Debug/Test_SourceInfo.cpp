/**
 * \file   Test_SourceInfo.cpp
 * \brief  test SourceInfo
 */


#include <Test/Debug/Test_SourceInfo.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_SourceInfo)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_SourceInfo::unit()
{
    xTEST_CASE("all")
    {
        SourceInfo info(xFILE, xLINE, xFUNCTION, xCOUNTER);

        xTEST_EQ(info.filePath().empty(), false);
        xTEST_GR(info.lineNum(), 0UL);
        xTEST_EQ(info.funcName().empty(), false);
        xTEST_GR(info.counter(), 0UL);
        xTEST_EQ(info.format().empty(), false);

        // Trace() << xSOURCE_INFO.format();
    }
}
//-------------------------------------------------------------------------------------------------
