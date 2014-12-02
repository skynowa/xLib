/**
 * \file   Test_SourceInfo.cpp
 * \brief  test SourceInfo
 */


#include <Test/Debug/Test_SourceInfo.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_SourceInfo::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("all", a_caseLoops)
    {
        SourceInfo info(xFILE, xLINE, xFUNCTION);
        Trace() << xTRACE_VAR(info.filePath());
        Trace() << xTRACE_VAR(info.lineNum());
        Trace() << xTRACE_VAR(info.funcName());

        xTEST_EQ(info.filePath().empty(), false);
        xTEST_EQ(info.lineNum(), 19UL);
        xTEST_EQ(info.funcName().empty(), false);
    }
}
//-------------------------------------------------------------------------------------------------
