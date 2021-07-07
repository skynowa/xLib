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
        culong_t val1 {10};
        culong_t val2 {20};

        ulong_t          nativeError    { NativeError::get() };
        SourceInfoData   sourceInfoData {xFILE, xLINE, xFUNCTION, xCOUNTER,
            xLEX_TO_STR(val1), xLEX_TO_STR(val), std::to_string(val1), std::to_string(val2), xT("==")};
        SourceInfo       sourceInfo(sourceInfoData);
        std::ctstring_t &stackTrace     = StackTrace().str();

        ErrorReport eport(ErrorReport::Type::Msgbox, nativeError, sourceInfo, stackTrace, xT(""));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
