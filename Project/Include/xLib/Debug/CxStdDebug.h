/**
 * \file   CxStdDebug.h
 * \brief  debug by using C library and STL, header only.
 */


#pragma once

//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
#define xSTD_TRACE_POINT \
    { \
        ::printf("\t::::: #%d in %s:%d, func: %s, error: %s :::::\n", \
            __COUNTER__, __FILE__, __LINE__, __FUNCTION__, ::strerror(errno)); \
    }
    ///< trace point

#define xSTD_TRACE_VAR(v) \
    #v ": " << v
    ///< variable for tracing

#define xSTD_TEST_DO(expr, do_expr) \
    if ( !(expr) ) { \
        ::fprintf(stdout, \
                "\n-------------------- TEST ----------------------\n" \
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
                ::strerror(errno), \
                currentDateTime().c_str()); \
        { \
            do_expr; \
        } \
    }
    ///< test macros

#define xSTD_TEST(expr) \
    xSTD_TEST_DO(expr, {})
    ///< test macros

#define xSTD_TEST_RET(expr, ret_expr) \
    xSTD_TEST_DO(expr, return ret_expr)
    ///< test macros

#define xSTD_TEST_NA(expr) ;
    ///< test macros

#define xSTD_ARRAY_SIZE(a) \
    ( sizeof(a) / sizeof((a)[0]) )
    ///< get array size
//------------------------------------------------------------------------------
/**
 * current date/time, format is YYYY-MM-DD.HH:mm:ss
 */
inline std::string
currentDateTime()
{
    char       srv[80 + 1] = {};
    time_t     now         = ::time(NULL);
    struct tm *tms         = ::localtime(&now);

    size_t urv = ::strftime(srv, sizeof(srv), "%Y-%m-%d.%X", tms);
    if (urv == 0) {
        return std::string();
    }

    return srv;
}
//------------------------------------------------------------------------------
