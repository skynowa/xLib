/**
 * \file  xDebug.h
 * \brief code debugging
 */


#pragma once

//-------------------------------------------------------------------------------------------------
///@name compile time build info messages
///@{
#define xBUILD_MESSAGE(msg) xBUILD_MSG("MESSAGE", msg)
#define xBUILD_INFO(msg)    xBUILD_MSG("INFO",    msg)
#define xBUILD_WARNING(msg) xBUILD_MSG("WARNING", msg)
#define xBUILD_ERROR(msg)   xBUILD_MSG("ERROR",   msg)
#define xBUILD_TODO(msg)    xBUILD_MSG("TODO",    msg)
#define xBUILD_IMPL(msg)    xBUILD_MSG("IMPL",    msg)
#define xBUILD_NA(msg)      xBUILD_MSG("N/A",     msg)
#define xBUILD_FIX(msg)     xBUILD_MSG("FIX",     msg)
#define xBUILD_REVIEW(msg)  xBUILD_MSG("REVIEW",  msg)
#define xBUILD_SECURE(msg)  xBUILD_MSG("SECURE",  msg)
#define xBUILD_BUG(msg)     xBUILD_MSG("BUG",     msg)
#define xBUILD_HACK(msg)    xBUILD_MSG("HACK",    msg)
#define xBUILD_CUSTOM(msg)  xBUILD_MSG("CUSTOM",  msg)
#define xBUILD_MAGIC(msg)   xBUILD_MSG("MAGIC",   msg)
///@}
//-------------------------------------------------------------------------------------------------
///@name check condition
///@{
#define xCHECK_RET(expr, return_expr) \
    { if (expr) { return (return_expr); } }
    ///< check expression and return value
#define xCHECK_DO(expr, do_expr) \
    { if (expr) { do_expr; } }
    ///< check expression and do instructions
#define xCHECK_MSG(expr, comment) \
    { if (expr) { CxTrace() << (comment); } }
    ///< check expression and show message with comment
#define xCHECK_MSG_RET(expr, comment, return_expr) \
    { if (expr) { CxTrace() << (comment); return (return_expr); } }
    ///< check expression, show message with comment and return value
#define xCHECK_MSG_DO(expr, comment, do_expr) \
    { if (expr) { CxTrace() << (comment); do_expr; } }
    ///< check expression, show message with comment and do instructions
#define xCHECK_NA(var) \
    ;
    ///< at this point check code for variable is not applicable
#define xCHECKS_NA \
    ;
    ///< at this point check code for variables is not applicable
///@}
//-------------------------------------------------------------------------------------------------
///@name Trace variables (variable with value)
///@{
#define xTRACE_VAR(v1) \
    #v1 ": " << (v1)
#define xTRACE_VAR2(v1, v2) \
    xTRACE_VAR(v1) << ", " << xTRACE_VAR(v2)
#define xTRACE_VAR3(v1, v2, v3) \
    xTRACE_VAR2(v1, v2) << ", " << xTRACE_VAR(v3)
#define xTRACE_VAR4(v1, v2, v3, v4) \
    xTRACE_VAR3(v1, v2, v3) << ", " << xTRACE_VAR(v4)
#define xTRACE_VAR5(v1, v2, v3, v4, v5) \
    xTRACE_VAR4(v1, v2, v3, v4) << ", " << xTRACE_VAR(v5)
#define xTRACE_VAR6(v1, v2, v3, v4, v5, v6) \
    xTRACE_VAR5(v1, v2, v3, v4, v5) << ", " << xTRACE_VAR(v6)
#define xTRACE_VAR7(v1, v2, v3, v4, v5, v6, v7) \
    xTRACE_VAR6(v1, v2, v3, v4, v5, v6) << ", " << xTRACE_VAR(v7)
#define xTRACE_VAR8(v1, v2, v3, v4, v5, v6, v7, v8) \
    xTRACE_VAR7(v1, v2, v3, v4, v5, v6, v7) << ", " << xTRACE_VAR(v8)
#define xTRACE_VAR9(v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    xTRACE_VAR8(v1, v2, v3, v4, v5, v6, v7, v8) << ", " << xTRACE_VAR(v9)
///@}
//-------------------------------------------------------------------------------------------------
#define xTRACE_POINT \
    { \
        CxTrace() \
            << "\t::: #" << xCOUNTER  << " " \
            << "in "     << xFILE     << ":" << xLINE << ", " \
            << "func: "  << xFUNCTION << ", " \
            << "error: " << CxLastError::format() << " :::"; \
    }
    ///< trace point (use CxTrace)
#define xNOT_IMPLEMENTED \
    { xTEST_MSG_FAIL(xT("Not implemented")); }
    ///< show not implemented message and return value
//-------------------------------------------------------------------------------------------------
