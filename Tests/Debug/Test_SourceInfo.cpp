/**
 * \file   Test_SourceInfo.cpp
 * \brief  test SourceInfo
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_SourceInfo)
xTEST_UNIT(Test_SourceInfo)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_SourceInfo::unit()
{
    xTEST_CASE("all")
    {
        cSourceInfoData _sourceInfoData = {xFILE, xLINE, xFUNCTION, xCOUNTER};
        SourceInfo      _sourceInfo(_sourceInfoData);

        xTEST_EQ(_sourceInfo.data().filePath.empty(), false);
        xTEST_GR(_sourceInfo.data().lineNum, 0UL);
        xTEST_EQ(_sourceInfo.data().funcName.empty(), false);
        xTEST_GR(_sourceInfo.data().counter, 0UL);
        xTEST_EQ(_sourceInfo.format().empty(), false);

        // Trace() << _sourceInfoData.format();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
