/**
 * \file   SourceInfo.cpp
 * \brief  Source info
 */


#include "SourceInfo.h"

#include <xLib/Core/Format.h>


namespace xl::debug
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
SourceInfo::SourceInfo(
    cSourceInfoOption &a_option
) :
    _option(a_option)
{
}
//-------------------------------------------------------------------------------------------------
cSourceInfoOption &
SourceInfo::option() const
{
    return _option;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SourceInfo::format() const
{
    return Format::str(xT("#{} in {}, func: {}"), _option.counter, at(), _option.funcName);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SourceInfo::at() const
{
    return Format::str(xT("{}:{}"), _option.filePath, _option.lineNum);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SourceInfo::expr() const
{
    return Format::str(xT("{} {} {}"), _option.exprVar1, _option.exprOp, _option.exprVar2);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SourceInfo::exprValues() const
{
    return Format::str(xT("{} {} {}"), _option.exprValue1, _option.exprOp, _option.exprValue2);
}
//-------------------------------------------------------------------------------------------------

} // namespace
