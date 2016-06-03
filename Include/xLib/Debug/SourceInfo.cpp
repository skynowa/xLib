/**
 * \file   SourceInfo.cpp
 * \brief  Source info
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "SourceInfo.h"
#endif

#include <xLib/Core/Format.h>


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
SourceInfo::SourceInfo(
    cSourceInfoData &a_data
) :
    _data(a_data)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE cSourceInfoData &
SourceInfo::data() const
{
    return _data;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
SourceInfo::format() const
{
    return Format::str(xT("#{} in {}:{}, func: {}"), _data.counter, _data.filePath, _data.lineNum,
    	_data.funcName);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
SourceInfo::at() const
{
    return Format::str(xT("{}:{}"), _data.filePath, _data.lineNum);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
