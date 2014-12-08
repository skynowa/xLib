/**
 * \file   SourceInfo.cpp
 * \brief  [CLASS_COMMENTS]
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "SourceInfo.h"
#endif


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
SourceInfo::SourceInfo(
    std::ctstring_t &a_filePath,
    culong_t        &a_lineNum,
    std::ctstring_t &a_funcName,
    culong_t        &a_counter
) :
    _filePath(a_filePath),
    _lineNum (a_lineNum),
    _funcName(a_funcName),
    _counter (a_counter)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
SourceInfo::filePath() const
{
    return _filePath;
}
//-------------------------------------------------------------------------------------------------
xINLINE culong_t &
SourceInfo::lineNum() const
{
    return _lineNum;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
SourceInfo::funcName() const
{
    return _funcName;
}
//-------------------------------------------------------------------------------------------------
xINLINE culong_t &
SourceInfo::counter() const
{
    return _counter;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
