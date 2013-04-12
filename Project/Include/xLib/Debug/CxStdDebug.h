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
        printf("    ::::: #%d in %s:%d, func: %s :::::\n", \
               __COUNTER__, __FILE__, __LINE__, __FUNCTION__, ::GetLastError()); \
    }

#define xSTD_TEST(expr) \
    if ( !(expr) )  { \
        fprintf(stderr, \
                "\n------------------ xSTD_TEST --------------------\n" \
                " Expression: %s\n" \
                " File:       %s\n" \
                " Function:   %s\n" \
                " Line:       %d\n" \
                " Last error: %lu\n" \
                "--------------------------------------------------\n", \
                #expr, \
                __FILE__, \
                __FUNCTION__, \
                __LINE__, \
                ::GetLastError()); \
        exit(EXIT_FAILURE); \
    }
//------------------------------------------------------------------------------
#endif // xLib_Debug_CxStdDebugH
