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
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <stddef.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
//-------------------------------------------------------------------------------------------------
#define xSTD_TRACE_VAR(v) \
    #v ": " << (v)
    ///< variable for tracing

#define xSTD_TRACE_POINT \
    { \
        std::printf("\t::::: #%d in %s:%d, func: %s, error: %s :::::\n", \
            __COUNTER__, __FILE__, __LINE__, __FUNCTION__, std::strerror(errno)); \
    }
    ///< trace point

#define xSTD_VERIFY(expr) \
    { \
        if ( !(expr) ) { \
            std::printf( \
                "\n--------------------------------- xSTD_VERIFY ----------------------------------\n" \
                " Expression: %s\n" \
                " File:       %s\n" \
                " Function:   %s\n" \
                " Line:       %d\n" \
                " Last error: %s\n" \
                " Date time:  %s\n" \
                "--------------------------------------------------------------------------------\n", \
                #expr, \
                __FILE__, \
                __FUNCTION__, \
                __LINE__, \
                std::strerror(errno), \
                ::currentDateTime().c_str()); \
            \
            (void)::exit(EXIT_FAILURE); \
        } \
    }
    ///< check expression (work in debug and release modes)

#define xSTD_TEST_DO(expr, do_expr) \
    { \
        if ( !(expr) ) { \
            std::fprintf(stdout, \
                    "\n------------------ xSTD_TEST --------------------\n" \
                    " Expression: %s\n" \
                    " File:       %s\n" \
                    " Function:   %s\n" \
                    " Line:       %d\n" \
                    " Last error: %s\n" \
                    " Date time:  %s\n" \
                    "--------------------------------------------------\n", \
                    #expr, \
                    __FILE__, \
                    __FUNCTION__, \
                    __LINE__, \
                    std::strerror(errno), \
                    ::currentDateTime().c_str()); \
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
