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
    std::ctstring_t &a_file,
    culong_t        &a_line,
    std::ctstring_t &a_func
) :
    _file(a_file),
    _line(a_line),
    _func(a_func)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
SourceInfo::file() const
{
    return _file;
}
//-------------------------------------------------------------------------------------------------
xINLINE culong_t &
SourceInfo::line() const
{
    return _line;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
SourceInfo::func() const
{
    return _func;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
