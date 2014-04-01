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
#define xSTD_TRACE_VAR(v) \
    #v ": " << (v)
    ///< variable for tracing

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

#define xSTD_TEST_NA(expr)
    ;
    ///< test macros

#define xSTD_ARRAY_SIZE(a) \
    ( sizeof(a) / sizeof((a)[0]) )
    ///< get array size
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
