/**
 * \file  CxFileType.inl
 * \brief file type
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTrace.h>

#if   xENV_WIN
    #include "Platform/Win/CxFileType_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxFileType_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxFileType_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxFileType_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxFileType::CxFileType(
    std::ctstring_t &a_filePath
) :
    _filePath(a_filePath)
{
    xTEST_EQ(a_filePath.empty(), false);
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxFileType::filePath() const
{
    xTEST_EQ(_filePath.empty(), false);

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxFileType::isExists(
    cExType &a_value
) const
{
    xTEST_EQ(filePath().empty(), false);
    xTEST_NA(a_value);

    xCHECK_RET(a_value == (get() & a_value), true);

    return false;
}
//-------------------------------------------------------------------------------------------------
inline CxFileType::types_t
CxFileType::get() const
{
    xTEST_EQ(filePath().empty(), false);

    return _get_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::set(
    ctypes_t &a_values
) const
{
    xTEST_EQ(filePath().empty(), false);
    xTEST_NA(a_values);

    _set_impl(a_values);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::add(
    cExType &a_value
) const
{
    xTEST_EQ(filePath().empty(), false);
    xTEST_NA(a_value);

    modify(static_cast<ExType>( 0 ), a_value);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::remove(
    cExType &a_value
) const
{
    xTEST_EQ(filePath().empty(), false);
    xTEST_NA(a_value);

    modify(a_value, static_cast<ExType>( 0 ));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::modify(
    cExType &a_valueRemove,
    cExType &a_valueAdd
) const
{
    xTEST_EQ(filePath().empty(), false);
    xTEST_NA(a_valueRemove);
    xTEST_NA(a_valueAdd);

    // get current attributes
    types_t values = get();

    // change bits
    values &= ~a_valueRemove;
    values |= a_valueAdd;

    // change the attributes
    set(values);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::clear() const
{
    xTEST_EQ(filePath().empty(), false);

    _clear_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
