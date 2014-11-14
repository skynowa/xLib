/**
 * \file  FileType.inl
 * \brief file type
 */


#if !xOPTION_HEADER_ONLY
    #include "FileType.h"
#endif

#include <xLib/Core/Utils.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/FileType_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/FileType_unix.inl"

    #if   xENV_LINUX

    #elif xENV_BSD

    #elif xENV_APPLE

    #endif
#endif


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
FileType::FileType(
    std::ctstring_t &a_filePath
) :
    _filePath(a_filePath)
{
    xTEST_EQ(a_filePath.empty(), false);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
FileType::filePath() const
{
    xTEST_EQ(_filePath.empty(), false);

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
FileType::isExists(
    cExType &a_value
) const
{
    xTEST_EQ(filePath().empty(), false);
    xTEST_NA(a_value);

    xCHECK_RET(a_value == (get() & a_value), true);

    return false;
}
//-------------------------------------------------------------------------------------------------
xINLINE FileType::types_t
FileType::get() const
{
    xTEST_EQ(filePath().empty(), false);

    return _get_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
FileType::set(
    ctypes_t &a_values
) const
{
    xTEST_EQ(filePath().empty(), false);
    xTEST_NA(a_values);

    _set_impl(a_values);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
FileType::add(
    cExType &a_value
) const
{
    xTEST_EQ(filePath().empty(), false);
    xTEST_NA(a_value);

    modify(static_cast<ExType>( 0 ), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
FileType::remove(
    cExType &a_value
) const
{
    xTEST_EQ(filePath().empty(), false);
    xTEST_NA(a_value);

    modify(a_value, static_cast<ExType>( 0 ));
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
FileType::modify(
    cExType &a_valueRemove,
    cExType &a_valueAdd
) const
{
    xTEST_EQ(filePath().empty(), false);
    xTEST_NA(a_valueRemove);
    xTEST_NA(a_valueAdd);

    // get current attributes
    const types_t valueRemove = static_cast<types_t>( a_valueRemove );
    const types_t valueAdd    = static_cast<types_t>( a_valueAdd );
    types_t       values      = get();

    // change bits
    values &= ~valueRemove;
    values |= valueAdd;

    // change the attributes
    set(values);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
FileType::clear() const
{
    xTEST_EQ(filePath().empty(), false);

    _clear_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
