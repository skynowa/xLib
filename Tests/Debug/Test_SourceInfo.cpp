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
        std::csize_t    var1 {100};
        std::csize_t    var2 {200};
        std::ctstring_t op = xT("<");

        cSourceInfoData sourceInfoData
        {
            xFILE, xLINE, xFUNCTION, xCOUNTER,
            xLEX_TO_STR(var1), xLEX_TO_STR(var2), std::to_string(var1), std::to_string(var2), op
        };

        SourceInfo _sourceInfo(sourceInfoData);
        xTEST(!_sourceInfo.data().filePath.empty());
        xTEST_GR(_sourceInfo.data().lineNum, 0UL);
        xTEST(!_sourceInfo.data().funcName.empty());
        xTEST_GR(_sourceInfo.data().counter, 0UL);
        xTEST(!_sourceInfo.format().empty());
        xTEST(!_sourceInfo.at().empty());
        xTEST_EQ(_sourceInfo.expr(), Format::str(xT("{} {} {}"),
             xLEX_TO_STR(var1), op, xLEX_TO_STR(var2)));
        xTEST_EQ(_sourceInfo.exprValues(), Format::str(xT("{} {} {}"),
             std::to_string(var1), op, std::to_string(var2)));

		if (0) {
			Trace() << xTRACE_VAR(_sourceInfo.format());
			Trace() << xTRACE_VAR(_sourceInfo.at());
			Trace() << xTRACE_VAR(_sourceInfo.expr());
			Trace() << xTRACE_VAR(_sourceInfo.exprValues());
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
