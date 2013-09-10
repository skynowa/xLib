/**
 * \file   CxStdDebug.h
 * \brief  debug by using C library and STL, header only.
 */


#ifndef xLib_Debug_CxStdDebugH
#define xLib_Debug_CxStdDebugH
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
        printf("    ::::: #%d in %s:%d, func: %s, error: %ld :::::\n", \
               __COUNTER__, __FILE__, __LINE__, __FUNCTION__, errno); \
    }

#define xSTD_TEST_DO(expr, do_expr) \
    if ( !(expr) )  { \
        fprintf(stderr, \
                "\n------------------ xSTD_TEST --------------------\n" \
                " Expression: %s\n" \
                " File:       %s\n" \
                " Function:   %s\n" \
                " Line:       %d\n" \
                " Last error: %d\n" \
                "--------------------------------------------------\n", \
                #expr, \
                __FILE__, \
                __FUNCTION__, \
                __LINE__, \
                errno); \
        { \
            do_expr; \
        } \
    }

#define xSTD_TEST(expr) \
    xSTD_TEST_DO(expr, exit(EXIT_FAILURE))

#define xSTD_TEST_RET(expr, ret_expr) \
    xSTD_TEST_DO(expr, return (ret_expr))
//------------------------------------------------------------------------------
#endif // xLib_Debug_CxStdDebugH
