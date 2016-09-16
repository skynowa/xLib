/**
 * \file   Test_SourceInfo.cpp
 * \brief  test SourceInfo
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xlib;

xTEST_CLASS(Test_SourceInfo)
xTEST_UNIT(Test_SourceInfo)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_SourceInfo::unit()
{
    xTEST_CASE("all")
    {
        SourceInfo sourceInfo( {xFILE, xLINE, xFUNCTION, xCOUNTER} );

        xTEST_EQ(sourceInfo.data().filePath.empty(), false);
        xTEST_GR(sourceInfo.data().lineNum, 0UL);
        xTEST_EQ(sourceInfo.data().funcName.empty(), false);
        xTEST_GR(sourceInfo.data().counter, 0UL);
        xTEST_EQ(sourceInfo.format().empty(), false);

        // Trace() << sourceInfo.format();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
