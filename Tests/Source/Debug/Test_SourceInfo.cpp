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
Test_SourceInfo::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("all", a_caseLoops)
    {
        SourceInfo info(xFILE, xLINE, xFUNCTION, xCOUNTER);

        xTEST_EQ(info.filePath().empty(), false);
        xTEST_EQ(info.lineNum(), 19UL);
        xTEST_EQ(info.funcName().empty(), false);
        xTEST_EQ(info.counter(), 0UL);
        xTEST_EQ(info.format().empty(), false);

        // Trace() << xSOURCE_INFO.format();
    }
}
//-------------------------------------------------------------------------------------------------
