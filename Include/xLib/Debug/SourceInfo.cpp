/**
 * \file   SourceInfo.cpp
 * \brief  Source info
 */


#include "SourceInfo.h"

#include <xLib/Core/Format.h>


xNAMESPACE_BEGIN2(xl, debug)

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

xNAMESPACE_END2(xl, debug)
