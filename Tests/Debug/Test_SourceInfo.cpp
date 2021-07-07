/**
 * \file   Test_SourceInfo.cpp
 * \brief  test SourceInfo
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_SourceInfo)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_SourceInfo::unit()
{
    xTEST_CASE("all")
    {
        std::csize_t var1 {100};
        std::csize_t var2 {200};

        cSourceInfoData _sourceInfoData
        {
            xFILE, xLINE, xFUNCTION, xCOUNTER,
            xLEX_TO_STR(var1), xLEX_TO_STR(var2), std::to_string(var1), std::to_string(var2)
        };

        SourceInfo _sourceInfo(_sourceInfoData);
        xTEST(!_sourceInfo.data().filePath.empty());
        xTEST_GR(_sourceInfo.data().lineNum, 0UL);
        xTEST(!_sourceInfo.data().funcName.empty());
        xTEST_GR(_sourceInfo.data().counter, 0UL);
        xTEST(!_sourceInfo.format().empty());

        Trace() << _sourceInfo.format();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
