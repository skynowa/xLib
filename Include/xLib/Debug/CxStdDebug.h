/**
 * \file   CxStdDebug.h
 * \brief  debug by using C library and STL
 */


#pragma once

#ifndef xLib_CxStdDebugH
#define xLib_CxStdDebugH
//-------------------------------------------------------------------------------------------------
// POSIX
#include <sys/types.h>  // must be at the top (it's portable)
#include <fcntl.h>
#include <sys/stat.h>

// C library
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstdarg>
#include <cstddef>
#include <cmath>
#include <climits>
#include <cassert>
//-------------------------------------------------------------------------------------------------
///@name check condition
///@{
#define _xCHECK_RET(expr, return_expr) \
    { if ((expr)) { return (return_expr); } }
    ///< check expression and return value
#define _xCHECK_DO(expr, do_expr) \
    { if ((expr)) { do_expr; } }
    ///< check expression and do instructions
#define _xCHECK_MSG(expr, comment) \
    { if ((expr)) { std::cout << (comment) << std::endl; } }
    ///< check expression and show message with comment
#define _xCHECK_MSG_RET(expr, comment, return_expr) \
    { if ((expr)) { std::cout << (comment) << std::endl; return (return_expr); } }
    ///< check expression, show message with comment and return value
#define _xCHECK_MSG_DO(expr, comment, do_expr) \
    { if ((expr)) { std::cout << (comment) << std::endl; do_expr; } }
    ///< check expression, show message with comment and do instructions
#define _xCHECK_NA(var) \
    ;
    ///< at this point check code for variable is not applicable
#define _xCHECKS_NA \
    ;
    ///< at this point check code for variables is not applicable
///@}
//-------------------------------------------------------------------------------------------------
///@name Trace variables (variable with value)
///@{
#define _xTRACE_VAR(v1) \
    #v1 ": " << (v1)
#define _xTRACE_VAR2(v1, v2) \
    _xTRACE_VAR(v1) << ", " << _xTRACE_VAR(v2)
#define _xTRACE_VAR3(v1, v2, v3) \
    _xTRACE_VAR2(v1, v2) << ", " << _xTRACE_VAR(v3)
#define _xTRACE_VAR4(v1, v2, v3, v4) \
    _xTRACE_VAR3(v1, v2, v3) << ", " << _xTRACE_VAR(v4)
#define _xTRACE_VAR5(v1, v2, v3, v4, v5) \
    _xTRACE_VAR4(v1, v2, v3, v4) << ", " << _xTRACE_VAR(v5)
#define _xTRACE_VAR6(v1, v2, v3, v4, v5, v6) \
    _xTRACE_VAR5(v1, v2, v3, v4, v5) << ", " << _xTRACE_VAR(v6)
#define _xTRACE_VAR7(v1, v2, v3, v4, v5, v6, v7) \
    _xTRACE_VAR6(v1, v2, v3, v4, v5, v6) << ", " << _xTRACE_VAR(v7)
#define _xTRACE_VAR8(v1, v2, v3, v4, v5, v6, v7, v8) \
    _xTRACE_VAR7(v1, v2, v3, v4, v5, v6, v7) << ", " << _xTRACE_VAR(v8)
#define _xTRACE_VAR9(v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    _xTRACE_VAR8(v1, v2, v3, v4, v5, v6, v7, v8) << ", " << _xTRACE_VAR(v9)
///@}
//-------------------------------------------------------------------------------------------------
#define _xTRACE_POINT \
    { \
        std::cout \
            << "\t::::: #" << __COUNTER__ \
            << " in "      << __FILE__ \
            << ":"         << __LINE__ \
            << ", func: "  << __FUNCTION__ \
            << ", error: " << std::strerror(errno) \
            << " :::::"    << std::endl; \
    }
    ///< trace point
#define _xNOT_IMPLEMENTED \
    { _xTEST_MSG_FAIL(xT("Not implemented")); }
    ///< show not implemented message and return value
//-------------------------------------------------------------------------------------------------
#define _xVERIFY(expr) \
    { \
        if ( !(expr) ) { \
            std::cout \
                << "\n" \
                << "------------------ _xVERIFY -------------------" << "\n" \
                << " Expression: " << #expr                             << "\n" \
                << " File:       " << __FILE__                          << "\n" \
                << " Function:   " << __FUNCTION__                      << "\n" \
                << " Line:       " << __LINE__                          << "\n" \
                << " Last error: " << std::strerror(errno)              << "\n" \
                << " Date time:  " << ::currentDateTime()               << "\n" \
                << "--------------------------------------------------" << "\n" \
                << std::flush; \
            \
            (void)::exit(EXIT_FAILURE); \
        } \
    }
    ///< check expression (work in debug and release modes)
#define _xTEST_DO(expr, do_expr) \
    { \
        if ( !(expr) ) { \
            std::cout \
                << "\n" \
                << "------------------- _xTEST --------------------" << "\n" \
                << " Expression: " << #expr                             << "\n" \
                << " File:       " << __FILE__                          << "\n" \
                << " Function:   " << __FUNCTION__                      << "\n" \
                << " Line:       " << __LINE__                          << "\n" \
                << " Last error: " << std::strerror(errno)              << "\n" \
                << " Date time:  " << ::currentDateTime()               << "\n" \
                << "--------------------------------------------------" << "\n" \
                << std::flush; \
            { \
                do_expr; \
            } \
        } \
    }
    ///< test macros
#define _xTEST(expr) \
    _xTEST_DO(expr, {})
    ///< test macros
#define _xTEST_RET(expr, ret_expr) \
    _xTEST_DO(expr, return ret_expr)
    ///< test macros
#define _xTEST_NA(expr) \
    ;
    ///< test macros
//-------------------------------------------------------------------------------------------------
/**
 * current date/time, format is YYYY-MM-DD.HH:mm:ss
 */
inline std::string
currentDateTime()
{
    std::string sRv;
    char        buff[80 + 1] = {};
    time_t      timeNow      = std::time(NULL);
    std::tm    *timeLocal    = NULL;

    timeLocal = std::localtime(&timeNow);
    if (timeLocal == NULL) {
        return std::string();
    }

    size_t uiRv = std::strftime(buff, sizeof(buff) - 1, "%Y-%m-%d.%X", timeLocal);
    if (uiRv == 0) {
        return std::string();
    }

    sRv.assign(&buff[0], uiRv);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxStdDebugH
