/**
 * \file  CxShell.inl
 * \brief shell
 */


#include <xLib/Core/CxString.h>
#include <xLib/Core/Win/CxCom.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTrace.h>

#if   xENV_WIN
    #include "Platform/Win/CxShell_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxShell_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/CxShell_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/CxShell_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/CxShell_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxShell::isAvailable() const
{
    xTESTS_NA;

    return _isAvailable_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxShell::execute(
    std::ctstring_t &a_filePath,   ///< file path to binary file
    std::ctstring_t &a_params      ///< command line params for binary file
) const
{
    xTEST_NA(a_filePath);
    xTEST_NA(a_params);

    xCHECK_DO(a_filePath.empty(), return);
    xCHECK_DO(!isAvailable(),     return);

    // REVIEW: security bug - xT("%s \"%s\"") or xT("\"%s\" \"%s\"") ??
    std::ctstring_t cmd = CxString::format(xT("%s \"%s\""), a_filePath.c_str(), a_params.c_str());

    int_t iRv = xTSYSTEM(cmd.c_str());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
