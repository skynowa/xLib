/**
 * \file  Test_ErrorReport.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_ErrorReport)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_ErrorReport::unit()
{
    xTEST_CASE("ctor")
    {
        ulong_t          nativeError    { NativeError::get() };
        SourceInfoData   sourceInfoData {xFILE, xLINE, xFUNCTION, xCOUNTER, {}, {}, {}, {}, {}};
        SourceInfo       sourceInfo(sourceInfoData);
        std::ctstring_t &stackTrace     = StackTrace().str();

        culong_t val1 {10};
        culong_t val2 {20};

        ErrorReport eport(ErrorReport::Type::Msgbox,
            xLEX_TO_STR(val1), xLEX_TO_STR(val), val1, val2,
            xT("=="), nativeError, sourceInfo, stackTrace, xT(""));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
