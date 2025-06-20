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
    xTEST_CASE("ctor")
    {
        const SourceInfo info(xFILE, xLINE, xFUNCTION, xCOUNTER);
        if (0) {
            LogCout() << xTRACE_VAR(info.option().filePath);
            LogCout() << xTRACE_VAR(info.option().lineNum);
            LogCout() << xTRACE_VAR(info.option().funcName);
            LogCout() << xTRACE_VAR(info.option().counter);
        }
        xTEST_DIFF(info.option().filePath.find(xT("Test_SourceInfo.cpp")), std::tstring_t::npos);
        xTEST_GR(info.option().lineNum, 0);
        xTEST_DIFF(info.option().funcName.find(xT("Test_SourceInfo::unit()")), std::tstring_t::npos);
        xTEST_GR(info.option().counter, 0);
        xTEST(info.option().exprVar1.empty());
        xTEST(info.option().exprVar2.empty());
        xTEST(info.option().exprValue1.empty());
        xTEST(info.option().exprValue2.empty());
        xTEST(info.option().exprOp.empty());
    }

    xTEST_CASE("all")
    {
        std::csize_t    var1 {100};
        std::csize_t    var2 {200};
        std::ctstring_t op = xT("<");

        cSourceInfoOption option
        {
            xFILE, xLINE, xFUNCTION, xCOUNTER,
            xLEX_TO_STR(var1), xLEX_TO_STR(var2), std::to_string(var1), std::to_string(var2), op
        };

        SourceInfo _sourceInfo(option);
		if (0) {
			LogCout() << xTRACE_VAR(_sourceInfo.format());
			LogCout() << xTRACE_VAR(_sourceInfo.at());
			LogCout() << xTRACE_VAR(_sourceInfo.expr());
			LogCout() << xTRACE_VAR(_sourceInfo.exprValues());
		}
        xTEST(!_sourceInfo.option().filePath.empty());
        xTEST_GR(_sourceInfo.option().lineNum, 0UL);
        xTEST(!_sourceInfo.option().funcName.empty());
        xTEST_GR(_sourceInfo.option().counter, 0UL);
        xTEST(!_sourceInfo.format().empty());
        xTEST(!_sourceInfo.at().empty());
        xTEST_EQ(_sourceInfo.expr(), Format::str(xT("{} {} {}"),
             xLEX_TO_STR(var1), op, xLEX_TO_STR(var2)));
        xTEST_EQ(_sourceInfo.exprValues(), Format::str(xT("{} {} {}"),
             std::to_string(var1), op, std::to_string(var2)));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
