/**
 * \file  xDebug.h
 * \brief code debugging
 */


#pragma once

#ifndef xLib_xDebugH
#define xLib_xDebugH
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
#endif // xLib_xDebugH
