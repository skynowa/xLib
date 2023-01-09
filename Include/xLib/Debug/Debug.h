/**
 * \file  Debug.h
 * \brief code debugging
 */


#pragma once

#include <xLib/Core/Defines.h>

//-------------------------------------------------------------------------------------------------
///\name compile time build info messages
///\{
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
///\}
//-------------------------------------------------------------------------------------------------
///\name check condition
///\{
#define xCHECK_RET(expr, return_expr) \
    { if (expr) { return (return_expr); } }
    ///< check expression and return value
#define xCHECK_DO(expr, do_expr) \
    { if (expr) { do_expr; } }
    ///< check expression and do instructions
#define xCHECK_MSG(expr, comment) \
    { if (expr) { xl::log::Trace() << (comment); } }
    ///< check expression and show message with comment
#define xCHECK_MSG_RET(expr, comment, return_expr) \
    { if (expr) { xl::log::Trace() << (comment); return (return_expr); } }
    ///< check expression, show message with comment and return value
#define xCHECK_MSG_DO(expr, comment, do_expr) \
    { if (expr) { xl::log::Trace() << (comment); do_expr; } }
    ///< check expression, show message with comment and do instructions
#define xCHECK_NA(var) \
    ;
    ///< at this point check code for variable is not applicable
#define xCHECKS_NA \
    ;
    ///< at this point check code for variables is not applicable
///\}
//-------------------------------------------------------------------------------------------------
///\name Trace variables (variable with value)
///\{
#define xSTD_TRACE_VAR(v1) \
	#v1 xT(": ") << (v1)
#define xSTD_TRACE_VAR_2(v1, v2) \
	xSTD_TRACE_VAR(v1) <<  xT(", ") << xSTD_TRACE_VAR(v2)
#define xSTD_TRACE_VAR_3(v1, v2, v3) \
	xSTD_TRACE_VAR_2(v1, v2) <<  xT(", ") << xSTD_TRACE_VAR(v3)
#define xSTD_TRACE_VAR_4(v1, v2, v3, v4) \
	xSTD_TRACE_VAR_3(v1, v2, v3) <<  xT(", ") << xSTD_TRACE_VAR(v4)
#define xSTD_TRACE_VAR_5(v1, v2, v3, v4, v5) \
	xSTD_TRACE_VAR_4(v1, v2, v3, v4) <<  xT(", ") << xSTD_TRACE_VAR(v5)
#define xSTD_TRACE_VAR_6(v1, v2, v3, v4, v5, v6) \
	xSTD_TRACE_VAR_5(v1, v2, v3, v4, v5) <<  xT(", ") << xSTD_TRACE_VAR(v6)
#define xSTD_TRACE_VAR_7(v1, v2, v3, v4, v5, v6, v7) \
	xSTD_TRACE_VAR_6(v1, v2, v3, v4, v5, v6) <<  xT(", ") << xSTD_TRACE_VAR(v7)
#define xSTD_TRACE_VAR_8(v1, v2, v3, v4, v5, v6, v7, v8) \
	xSTD_TRACE_VAR_7(v1, v2, v3, v4, v5, v6, v7) <<  xT(", ") << xSTD_TRACE_VAR(v8)
#define xSTD_TRACE_VAR_9(v1, v2, v3, v4, v5, v6, v7, v8, v9) \
	xSTD_TRACE_VAR_8(v1, v2, v3, v4, v5, v6, v7, v8) <<  xT(", ") << xSTD_TRACE_VAR(v9)
#define xSTD_TRACE_VAR_10(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) \
	xSTD_TRACE_VAR_9(v1, v2, v3, v4, v5, v6, v7, v8, v9) <<  xT(", ") << xSTD_TRACE_VAR(v10)
///\}

///\name Trace variables with label
///\{
#define xPRINT_VAR(v) \
	#v xT(": [") << (v) << xT("]")
#define xUNKNOWN_VAR(v) \
	xT("Unknown ") << xSTD_TRACE_VAR(v)
#define xINVALID_VAR(v) \
	xT("Invalid ") << xSTD_TRACE_VAR(v)
#define xTRACE_PTR(p) \
	#p xT(": ") << xT("{") << (p) << xT(", ") << ((p) ? *(p) : 0) << xT("}")
///\}
//-------------------------------------------------------------------------------------------------
#define xTRACE_POINT \
    { \
        xl::debug::cSourceInfoData data = {xFILE, xLINE, xFUNCTION, xCOUNTER, {}, {}, {}, {}, {}}; \
        xl::debug::SourceInfo      sourceInfo(data); \
        \
        xl::log::Trace() \
            << xT("\t::: ")  << sourceInfo.at() << xT(", ") \
            << xT("error: ") << NativeError::format() << xT(" :::"); \
    }
    ///< trace point (use Trace)
#define xTRACE_FUNC \
    { \
        xl::debug::cSourceInfoData data = {xFILE, xLINE, xFUNCTION, xCOUNTER, {}, {}, {}, {}, {}}; \
        xl::debug::SourceInfo      sourceInfo(data); \
        \
        xl::log::Trace() \
            << xT("\t::: ") << sourceInfo.data().funcName << xT(" :::"); \
    }
    ///< trace function (use Trace)
#define xTRACE_FUNC_VAR(v) \
    { \
        xl::debug::cSourceInfoData data = {xFILE, xLINE, xFUNCTION, xCOUNTER, {}, {}, {}, {}, {}}; \
        xl::debug::SourceInfo      sourceInfo(data); \
        \
        xl::log::Trace() \
            << xT("\t::: ") << sourceInfo.data().funcName << xT(": ") << xSTD_TRACE_VAR(v) << xT(" :::"); \
    }
    ///< trace function variable (use Trace)
#define xTRACE_NOT_IMPLEMENTED \
    { \
        xl::debug::cSourceInfoData data = {xFILE, xLINE, xFUNCTION, xCOUNTER, {}, {}, {}, {}, {}}; \
        xl::debug::SourceInfo      sourceInfo(data); \
        \
        xl::log::Trace() \
            << xT("\t::: ") << sourceInfo.data().funcName << xT(": Not implemented :::"); \
    }
    ///< trace not implemented message
#define xNOT_IMPLEMENTED \
    { xTEST_FAIL_MSG(xT("Not implemented")); }
    ///< show not implemented message
//-------------------------------------------------------------------------------------------------
