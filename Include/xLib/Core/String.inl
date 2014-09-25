/**
 * \file  String.inl
 * \brief string utils
 */


#if !xOPTION_HEADER_ONLY
    #include "String.h"
#endif

#include <xLib/Core/Units.h>
#include <xLib/Core/Functors.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/Const.h>
#include <xLib/Core/Char.h>
#include <xLib/Core/Array.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>
#include <xLib/Debug/StdDebug.h>

#if   xENV_WIN
    #include "Platform/Win/String_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/String_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/String_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/String_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, core)

/*******************************************************************************
*   casting
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
inline std::tstring_t
String::cast(
    const T &a_value    ///< source value
)
{
    xTEST_NA(a_value);

    std::tstring_t sRv;

    try {
        std::tostringstream_t oss;

        oss.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        oss << a_value;

        sRv = oss.str();
    } catch (std::ctostringstream_t::failure &) {
        sRv.clear();
    } catch (...) {
        sRv.clear();
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
inline std::tstring_t
String::cast(
    const T &a_value,   ///< source value
    cint_t  &a_base     ///< valid values: 8, 10, 16
)
{
    xTEST_NA(a_value);
    xTEST_NA(a_base);

    std::tstring_t sRv;

    try {
        std::tostringstream_t oss;

        oss.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        oss << std::setbase(a_base) << std::uppercase << a_value;  // std::showbase

        sRv = oss.str();
    } catch (std::ctostringstream_t::failure &) {
        sRv.clear();
    } catch (...) {
        sRv.clear();
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
inline T
String::cast(
    std::ctstring_t &a_str  ///< source string
)
{
    xTEST_NA(a_str);

    T rvT;

    try {
        std::tistringstream_t iss(a_str);

        iss.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        iss >> rvT;
    } catch (std::ctistringstream_t::failure &) {
        return T();
    } catch (...) {
        return T();
    }

    return rvT;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
inline T
String::cast(
    std::ctstring_t &a_str, ///< source string
    cint_t          &a_base ///< valid values: 8, 10, 16
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_base);

    T rvT;

    try {
        std::tistringstream_t iss(a_str);

        iss.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        iss >> std::setbase(a_base) >> rvT;
    } catch (std::ctistringstream_t::failure &) {
        return T();
    } catch (...) {
        return T();
    }

    return rvT;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
