/**
 * \file  Debug.h
 * \brief code debugging
 */


#pragma once

#include <xLib/Core/Defines.h>

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
#define xBUILD_UNKNOWN(msg) xBUILD_MSG("UNKNOWN", msg)
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
    { if (expr) { Trace() << (comment); } }
    ///< check expression and show message with comment
#define xCHECK_MSG_RET(expr, comment, return_expr) \
    { if (expr) { Trace() << (comment); return (return_expr); } }
    ///< check expression, show message with comment and return value
#define xCHECK_MSG_DO(expr, comment, do_expr) \
    { if (expr) { Trace() << (comment); do_expr; } }
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
#define xTRACE_VAR(xVA_VALUES_1) \
    #xVA_VALUES_1 xT(": ") << (xVA_VALUES_1)
#define xTRACE_VAR2(xVA_VALUES_2) \
    xTRACE_VAR(xVA_VALUES_1)  << xT(", ") << xTRACE_VAR(v2)
#define xTRACE_VAR3(xVA_VALUES_3) \
    xTRACE_VAR2(xVA_VALUES_2) << xT(", ") << xTRACE_VAR(v3)
#define xTRACE_VAR4(xVA_VALUES_4) \
    xTRACE_VAR3(xVA_VALUES_3) << xT(", ") << xTRACE_VAR(v4)
#define xTRACE_VAR5(xVA_VALUES_5) \
    xTRACE_VAR4(xVA_VALUES_4) << xT(", ") << xTRACE_VAR(v5)
#define xTRACE_VAR6(xVA_VALUES_6) \
    xTRACE_VAR5(xVA_VALUES_5) << xT(", ") << xTRACE_VAR(v6)
#define xTRACE_VAR7(xVA_VALUES_7) \
    xTRACE_VAR6(xVA_VALUES_6) << xT(", ") << xTRACE_VAR(v7)
#define xTRACE_VAR8(xVA_VALUES_8) \
    xTRACE_VAR7(xVA_VALUES_7) << xT(", ") << xTRACE_VAR(v8)
#define xTRACE_VAR9(xVA_VALUES_9) \
    xTRACE_VAR8(xVA_VALUES_8) << xT(", ") << xTRACE_VAR(v9)
#define xTRACE_VAR10(xVA_VALUES_10) \
    xTRACE_VAR8(xVA_VALUES_9) << xT(", ") << xTRACE_VAR(v10)
///@}
//-------------------------------------------------------------------------------------------------
#define xTRACE_POINT \
    { \
        Trace() \
            << xT("\t::: #") << xCOUNTER  << xT(" ") \
            << xT("in ")     << xFILE     << xT(":") << xLINE << xT(", ") \
            << xT("func: ")  << xFUNCTION << xT(", ") \
            << xT("error: ") << NativeError::format() << xT(" :::"); \
    }
    ///< trace point (use Trace)
#define xNOT_IMPLEMENTED \
    { xTEST_FAIL_MSG(xT("Not implemented")); }
    ///< show not implemented message
//-------------------------------------------------------------------------------------------------
