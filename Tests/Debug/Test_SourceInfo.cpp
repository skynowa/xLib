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

        SourceInfo sourceInfo(sourceInfoData);
        xTEST(!sourceInfo.data().filePath.empty());
        xTEST_GR(sourceInfo.data().lineNum, 0UL);
        xTEST(!sourceInfo.data().funcName.empty());
        xTEST_GR(sourceInfo.data().counter, 0UL);
        xTEST(!sourceInfo.format().empty());
        xTEST(!sourceInfo.at().empty());
        xTEST_EQ(sourceInfo.expr(), Format::str(xT("{} {} {}"),
             xLEX_TO_STR(var1), op, xLEX_TO_STR(var2)));
        xTEST_EQ(sourceInfo.exprValues(), Format::str(xT("{} {} {}"),
             std::to_string(var1), op, std::to_string(var2)));

		if (0) {
			Trace() << xTRACE_VAR(sourceInfo.format());
			Trace() << xTRACE_VAR(sourceInfo.at());
			Trace() << xTRACE_VAR(sourceInfo.expr());
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
