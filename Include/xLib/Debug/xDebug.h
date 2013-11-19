/**
 * \file  xDebug.h
 * \brief code debugging
 */


#pragma once

#ifndef xLib_xDebugH
#define xLib_xDebugH
//-------------------------------------------------------------------------------------------------
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
        CxTracer() \
            << "\t::: #" << xCOUNTER  << " " \
            << "in "     << xFILE     << ":" << xLINE << ", " \
            << "func: "  << xFUNCTION << ", " \
            << "error: " << CxLastError::format() << " :::"; \
    }
    ///< trace point (use CxTracer)
//-------------------------------------------------------------------------------------------------
#endif // xLib_xDebugH
