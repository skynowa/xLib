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
#define xSTD_CHECK_RET(expr, return_expr) \
    { if ((expr)) { return (return_expr); } }
    ///< check expression and return value
#define xSTD_CHECK_DO(expr, do_expr) \
    { if ((expr)) { do_expr; } }
    ///< check expression and do instructions
#define xSTD_CHECK_MSG(expr, comment) \
    { if ((expr)) { std::cout << (comment) << std::endl; } }
    ///< check expression and show message with comment
#define xSTD_CHECK_MSG_RET(expr, comment, return_expr) \
    { if ((expr)) { std::cout << (comment) << std::endl; return (return_expr); } }
    ///< check expression, show message with comment and return value
#define xSTD_CHECK_MSG_DO(expr, comment, do_expr) \
    { if ((expr)) { std::cout << (comment) << std::endl; do_expr; } }
    ///< check expression, show message with comment and do instructions
#define xSTD_CHECK_NA(var) \
    ;
    ///< at this point check code for variable is not applicable
#define xSTD_CHECKS_NA \
    ;
    ///< at this point check code for variables is not applicable
///@}
//-------------------------------------------------------------------------------------------------
///@name Trace variables (variable with value)
///@{
#define xSTD_TRACE_VAR(v1) \
    #v1 ": " << (v1)
#define xSTD_TRACE_VAR2(v1, v2) \
    xSTD_TRACE_VAR(v1) << ", " << xSTD_TRACE_VAR(v2)
#define xSTD_TRACE_VAR3(v1, v2, v3) \
    xSTD_TRACE_VAR2(v1, v2) << ", " << xSTD_TRACE_VAR(v3)
#define xSTD_TRACE_VAR4(v1, v2, v3, v4) \
    xSTD_TRACE_VAR3(v1, v2, v3) << ", " << xSTD_TRACE_VAR(v4)
#define xSTD_TRACE_VAR5(v1, v2, v3, v4, v5) \
    xSTD_TRACE_VAR4(v1, v2, v3, v4) << ", " << xSTD_TRACE_VAR(v5)
#define xSTD_TRACE_VAR6(v1, v2, v3, v4, v5, v6) \
    xSTD_TRACE_VAR5(v1, v2, v3, v4, v5) << ", " << xSTD_TRACE_VAR(v6)
#define xSTD_TRACE_VAR7(v1, v2, v3, v4, v5, v6, v7) \
    xSTD_TRACE_VAR6(v1, v2, v3, v4, v5, v6) << ", " << xSTD_TRACE_VAR(v7)
#define xSTD_TRACE_VAR8(v1, v2, v3, v4, v5, v6, v7, v8) \
    xSTD_TRACE_VAR7(v1, v2, v3, v4, v5, v6, v7) << ", " << xSTD_TRACE_VAR(v8)
#define xSTD_TRACE_VAR9(v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    xSTD_TRACE_VAR8(v1, v2, v3, v4, v5, v6, v7, v8) << ", " << xSTD_TRACE_VAR(v9)
///@}
//-------------------------------------------------------------------------------------------------
#define xSTD_TRACE_POINT \
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
#define xSTD_NOT_IMPLEMENTED \
    { xSTD_TEST_MSG_FAIL(xT("Not implemented")); }
    ///< show not implemented message and return value
//-------------------------------------------------------------------------------------------------
#define xSTD_VERIFY(expr) \
    { \
        if ( !(expr) ) { \
            std::cout \
                << "\n" \
                << "------------------ xSTD_VERIFY -------------------" << "\n" \
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
#define xSTD_TEST_DO(expr, do_expr) \
    { \
        if ( !(expr) ) { \
            std::cout \
                << "\n" \
                << "------------------- xSTD_TEST --------------------" << "\n" \
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
#define xSTD_TEST(expr) \
    xSTD_TEST_DO(expr, {})
    ///< test macros
#define xSTD_TEST_RET(expr, ret_expr) \
    xSTD_TEST_DO(expr, return ret_expr)
    ///< test macros
#define xSTD_TEST_NA(expr) \
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
