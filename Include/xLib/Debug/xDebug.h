/**
 * \file  xDebug.h
 * \brief code debugging
 */


#pragma once

#ifndef xLib_xDebugH
#define xLib_xDebugH
//-------------------------------------------------------------------------------------------------
#define xSTD_VERIFY(expr) \
    if ( !(expr) ) { \
        std::ctstring_t lastError = CxLastError::format(); \
        CxTracer().write( \
            xT("\n--------------------------------- xSTD_VERIFY ----------------------------------\n") \
            xT("  Expression: %s\n") \
            xT("  File:       %s\n") \
            xT("  Function:   %s\n") \
            xT("  Line:       %lu\n") \
            xT("  Last error: %s\n") \
            xT("--------------------------------------------------------------------------------\n"), \
            xT(#expr), \
            xFILE, \
            xFUNCTION, \
            xLINE, \
            lastError.c_str()); \
        \
        (void_t)::exit(EXIT_FAILURE); \
    } \
    ///< check expression (work in debug and release modes)

#define xCHECK_RET(expr, return_expr) \
    { if (expr) { return (return_expr); } }
    ///< check expression and return value
#define xCHECK_DO(expr, do_expr) \
    { if (expr) { do_expr; } }
    ///< check expression and do instructions
#define xCHECK_MSG(expr, comment) \
    { if (expr) { CxTracer() << (comment); } }
    ///< check expression and show message with comment
#define xCHECK_MSG_RET(expr, comment, return_expr) \
    { if (expr) { CxTracer() << (comment); return (return_expr); } }
    ///< check expression, show message with comment and return value
#define xCHECK_MSG_DO(expr, comment, do_expr) \
    { if (expr) { CxTracer() << (comment); do_expr; } }
    ///< check expression, show message with comment and do instructions
#define xCHECK_NA(var) \
    ;
    ///< at this point check code for variable is not applicable
#define xCHECKS_NA \
    ;
    ///< at this point check code for variables is not applicable

#define xNOT_IMPLEMENTED \
    { xTEST_MSG_FAIL(xT("Not implemented")); }
    ///< show not implemented message and return value
//-------------------------------------------------------------------------------------------------
#define xTRACE(msg) \
    { CxTracer() << (msg); }
    ///< tracing
#define xTRACE_VAR(v) \
    ( \
        std::tstring_t() \
            .append( xT(#v) xT(": ") ) \
            .append( CxString::cast(v) ) \
            .append( xT(" ") ) \
    )
    ///< trace variable, trace variable and value
#define xTRACEV(...) \
    { CxTracer().write(__VA_ARGS__); }
    ///< tracing
#define xTRACE_POINT \
    { \
        CxTracer().write(xT("Point: %lu (file: %s, function: %s, last error: %s, line: %lu)"), \
            xCOUNTER, xFILE, xFUNCTION, CxLastError::get().c_str(), xLINE); \
    }
    ///< trace point (use CxTracer)
//-------------------------------------------------------------------------------------------------
#endif // xLib_xDebugH
