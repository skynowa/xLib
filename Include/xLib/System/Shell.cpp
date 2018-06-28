/**
 * \file  Shell.inl
 * \brief shell
 */


#include "Shell.h"

#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Win/Com.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/Shell_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Shell_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/Shell_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/Shell_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/Shell_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xl, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Shell::isAvailable() const
{
    xTEST_NA;

    return _isAvailable_impl();
}
//-------------------------------------------------------------------------------------------------
int_t
Shell::execute(
    std::ctstring_t &a_filePath ///< file path to binary file
) const
{
    return execute(a_filePath, std::tstring_t());
}
//-------------------------------------------------------------------------------------------------
int_t
Shell::execute(
    std::ctstring_t &a_filePath,   ///< file path to binary file
    std::ctstring_t &a_params      ///< command line params for binary file
) const
{
    xTEST_NA(a_filePath);
    xTEST_NA(a_params);

    xCHECK_RET(a_filePath.empty(), -1);
    xCHECK_RET(!isAvailable(),     -1);

    // REVIEW: security bug - xT("%s \"%s\"") or xT("\"%s\" \"%s\"") ??
    std::ctstring_t cmd = a_params.empty() ?
        a_filePath : Format::str(xT("{} \"{}\""), a_filePath, a_params);

    int_t iRv = xTSYSTEM(cmd.c_str());
    xTEST_DIFF(iRv, -1);

    return iRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
