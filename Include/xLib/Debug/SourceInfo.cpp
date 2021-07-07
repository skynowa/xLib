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
    cSourceInfoData &a_data
) :
    _data(a_data)
{
}
//-------------------------------------------------------------------------------------------------
cSourceInfoData &
SourceInfo::data() const
{
    return _data;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SourceInfo::format() const
{
    return Format::str(xT("#{} in {}:{}, func: {}"), _data.counter, _data.filePath, _data.lineNum,
    	_data.funcName);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SourceInfo::at() const
{
    return Format::str(xT("{}:{}"), _data.filePath, _data.lineNum);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SourceInfo::expr() const
{
    return Format::str(xT("{} ({}) {} {} ({})"),
        _data.exprVar1, _data.exprValue1,
        _data.exprOp,
        _data.exprVar2, _data.exprValue2);
}
//-------------------------------------------------------------------------------------------------

} // namespace
