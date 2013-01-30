/**
 * \file  xDebug.h
 * \brief code debugging
 */


#ifndef xLib_Debug_xDebugH
#define xLib_Debug_xDebugH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTracer.h>
//---------------------------------------------------------------------------
#define _xTEST_MSG_EQ(report_type, val1, val2, msg)      { if ( !((val1) == (val2)) ) { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#val1),   xT(#val2), (val1),        (val2),         xT("=="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_DIFF(report_type, val1, val2, msg)    { if ( !((val1) != (val2)) ) { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#val1),   xT(#val2), (val1),        (val2),         xT("!="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_LESS(report_type, val1, val2, msg)    { if ( !((val1) <  (val2)) ) { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#val1),   xT(#val2), (val1),        (val2),         xT("<"),  ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_GR(report_type, val1, val2, msg)      { if ( !((val1) >  (val2)) ) { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#val1),   xT(#val2), (val1),        (val2),         xT(">"),  ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_LESS_EQ(report_type, val1, val2, msg) { if ( !((val1) <= (val2)) ) { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#val1),   xT(#val2), (val1),        (val2),         xT("<="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_GR_EQ(report_type, val1, val2, msg)   { if ( !((val1) >= (val2)) ) { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#val1),   xT(#val2), (val1),        (val2),         xT(">="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_PTR(report_type, ptr, msg)            { if ( NULL     == (ptr)   ) { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT("NULL"),  xT(#ptr),  (intptr_t)ptr, (intptr_t)NULL, xT("!="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_PTR_FAIL(report_type, ptr, msg)       { if ( NULL     != (ptr)   ) { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT("NULL"),  xT(#ptr),  (intptr_t)ptr, (intptr_t)NULL, xT("=="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_FAIL(report_type, msg)                { if ( true                ) { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT("false"), xT(""),    xT(""),        xT(""),         xT(""),   ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().reportMake(rpReport); } }

#if xDEBUG_MODE_STDOUT_PLAIN
    #define xTEST_EQ(val1, val2)                         _xTEST_MSG_EQ      (CxErrorReport::rtStdoutPlain, val1, val2, xT(""))
    #define xTEST_DIFF(val1, val2)                       _xTEST_MSG_DIFF    (CxErrorReport::rtStdoutPlain, val1, val2, xT(""))
    #define xTEST_LESS(val1, val2)                       _xTEST_MSG_LESS    (CxErrorReport::rtStdoutPlain, val1, val2, xT(""))
    #define xTEST_GR(val1, val2)                         _xTEST_MSG_GR      (CxErrorReport::rtStdoutPlain, val1, val2, xT(""))
    #define xTEST_LESS_EQ(val1, val2)                    _xTEST_MSG_LESS_EQ (CxErrorReport::rtStdoutPlain, val1, val2, xT(""))
    #define xTEST_GR_EQ(val1, val2)                      _xTEST_MSG_GR_EQ   (CxErrorReport::rtStdoutPlain, val1, val2, xT(""))
    #define xTEST_PTR(ptr)                               _xTEST_MSG_PTR     (CxErrorReport::rtStdoutPlain, ptr, xT(""))
    #define xTEST_PTR_FAIL(ptr)                          _xTEST_MSG_PTR_FAIL(CxErrorReport::rtStdoutPlain, ptr, xT(""))
    #define xTEST_FAIL                                   _xTEST_MSG_FAIL    (CxErrorReport::rtStdoutPlain, xT(""))
    #define xTEST(expr)                                  _xTEST_MSG_EQ      (CxErrorReport::rtStdoutPlain, true, expr, xT(""))

    #define xTEST_MSG_EQ(val1, val2, msg)                _xTEST_MSG_EQ      (CxErrorReport::rtStdoutPlain, val1, val2, msg)
    #define xTEST_MSG_DIFF(val1, val2, msg)              _xTEST_MSG_DIFF    (CxErrorReport::rtStdoutPlain, val1, val2, msg)
    #define xTEST_MSG_LESS(val1, val2, msg)              _xTEST_MSG_LESS    (CxErrorReport::rtStdoutPlain, val1, val2, msg)
    #define xTEST_MSG_GR(val1, val2, msg)                _xTEST_MSG_GR      (CxErrorReport::rtStdoutPlain, val1, val2, msg)
    #define xTEST_MSG_LESS_EQ(val1, val2, msg)           _xTEST_MSG_LESS_EQ (CxErrorReport::rtStdoutPlain, val1, val2, msg)
    #define xTEST_MSG_GR_EQ(val1, val2, msg)             _xTEST_MSG_GR_EQ   (CxErrorReport::rtStdoutPlain, val1, val2, msg)
    #define xTEST_MSG_PTR(ptr, msg)                      _xTEST_MSG_PTR     (CxErrorReport::rtStdoutPlain, ptr, msg)
    #define xTEST_MSG_PTR_FAIL(ptr, msg)                 _xTEST_MSG_PTR_FAIL(CxErrorReport::rtStdoutPlain, ptr, msg)
    #define xTEST_MSG_FAIL(msg)                          _xTEST_MSG_FAIL    (CxErrorReport::rtStdoutPlain, msg)
    #define xTEST_MSG(expr, msg)                         _xTEST_MSG_EQ      (CxErrorReport::rtStdoutPlain, true, expr, msg)
#elif xDEBUG_MODE_MSGBOX_PLAIN
    #define xTEST_EQ(val1, val2)                         _xTEST_MSG_EQ      (CxErrorReport::rtMsgboxPlain, val1, val2, xT(""))
    #define xTEST_DIFF(val1, val2)                       _xTEST_MSG_DIFF    (CxErrorReport::rtMsgboxPlain, val1, val2, xT(""))
    #define xTEST_LESS(val1, val2)                       _xTEST_MSG_LESS    (CxErrorReport::rtMsgboxPlain, val1, val2, xT(""))
    #define xTEST_GR(val1, val2)                         _xTEST_MSG_GR      (CxErrorReport::rtMsgboxPlain, val1, val2, xT(""))
    #define xTEST_LESS_EQ(val1, val2)                    _xTEST_MSG_LESS_EQ (CxErrorReport::rtMsgboxPlain, val1, val2, xT(""))
    #define xTEST_GR_EQ(val1, val2)                      _xTEST_MSG_GR_EQ   (CxErrorReport::rtMsgboxPlain, val1, val2, xT(""))
    #define xTEST_PTR(ptr)                               _xTEST_MSG_PTR     (CxErrorReport::rtMsgboxPlain, ptr, xT(""))
    #define xTEST_PTR_FAIL(ptr)                          _xTEST_MSG_PTR_FAIL(CxErrorReport::rtMsgboxPlain, ptr, xT(""))
    #define xTEST_FAIL                                   _xTEST_MSG_FAIL    (CxErrorReport::rtMsgboxPlain, xT(""))
    #define xTEST(expr)                                  _xTEST_MSG_EQ      (CxErrorReport::rtMsgboxPlain, true, expr, xT(""))

    #define xTEST_MSG_EQ(val1, val2, msg)                _xTEST_MSG_EQ      (CxErrorReport::rtMsgboxPlain, val1, val2, msg)
    #define xTEST_MSG_DIFF(val1, val2, msg)              _xTEST_MSG_DIFF    (CxErrorReport::rtMsgboxPlain, val1, val2, msg)
    #define xTEST_MSG_LESS(val1, val2, msg)              _xTEST_MSG_LESS    (CxErrorReport::rtMsgboxPlain, val1, val2, msg)
    #define xTEST_MSG_GR(val1, val2, msg)                _xTEST_MSG_GR      (CxErrorReport::rtMsgboxPlain, val1, val2, msg)
    #define xTEST_MSG_LESS_EQ(val1, val2, msg)           _xTEST_MSG_LESS_EQ (CxErrorReport::rtMsgboxPlain, val1, val2, msg)
    #define xTEST_MSG_GR_EQ(val1, val2, msg)             _xTEST_MSG_GR_EQ   (CxErrorReport::rtMsgboxPlain, val1, val2, msg)
    #define xTEST_MSG_PTR(ptr, msg)                      _xTEST_MSG_PTR     (CxErrorReport::rtMsgboxPlain, ptr, msg)
    #define xTEST_MSG_PTR_FAIL(ptr, msg)                 _xTEST_MSG_PTR_FAIL(CxErrorReport::rtMsgboxPlain, ptr, msg)
    #define xTEST_MSG_FAIL(msg)                          _xTEST_MSG_FAIL    (CxErrorReport::rtMsgboxPlain, msg)
    #define xTEST_MSG(expr, msg)                         _xTEST_MSG_EQ      (CxErrorReport::rtMsgboxPlain, true, expr, msg)
#else
    #define xTEST_EQ(val1, val2)                         { xNA }
    #define xTEST_DIFF(val1, val2)                       { xNA }
    #define xTEST_LESS(val1, val2)                       { xNA }
    #define xTEST_GR(val1, val2)                         { xNA }
    #define xTEST_LESS_EQ(val1, val2)                    { xNA }
    #define xTEST_GR_EQ(val1, val2)                      { xNA }
    #define xTEST_PTR(ptr)                               { xNA }
    #define xTEST_PTR_FAIL(ptr)                          { xNA }
    #define xTEST_FAIL                                   { xNA }
    #define xTEST(expr)                                  { xNA }

    #define xTEST_MSG_EQ(val1, val2, msg)                { xNA }
    #define xTEST_MSG_DIFF(val1, val2, msg)              { xNA }
    #define xTEST_MSG_LESS(val1, val2, msg)              { xNA }
    #define xTEST_MSG_GR(val1, val2, msg)                { xNA }
    #define xTEST_MSG_LESS_EQ(val1, val2, msg)           { xNA }
    #define xTEST_MSG_GR_EQ(val1, val2, msg)             { xNA }
    #define xTEST_MSG_PTR(ptr, msg)                      { xNA }
    #define xTEST_MSG_PTR_FAIL(ptr, msg)                 { xNA }
    #define xTEST_MSG_FAIL(msg)                          { xNA }
    #define xTEST_MSG(expr, msg)                         { xNA }
#endif

#define xTEST_NA(var)                                    ;
    ///< at this point debug code for variable is not applicable
#define xTESTS_NA                                        ;
    ///< at this point debug code for variables is not applicable
//-------------------------------------------------------------------------
#define xSTD_VERIFY(expr)                                { \
                                                            if ( !(expr) )  { \
                                                                const std::tstring_t csLastError = CxLastError::sGet(); \
                                                                CxTracer::vWrite(xT("\n--------------------------------- xSTD_VERIFY ----------------------------------\n") \
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
                                                                                 csLastError.c_str());  \
                                                                (void)::exit(EXIT_FAILURE); \
                                                            } \
                                                         }
    ///< check expression (work in debug and release modes)

#define xCHECK_RET(expr, return_expr)                    { if ((expr)) { return (return_expr);                          } }
    ///< check expression and return value
#define xCHECK_DO(expr, do_expr)                         { if ((expr)) { do_expr;                                       } }
    ///< check expression and do instructions
#define xCHECK_MSG(expr, comment)                        { if ((expr)) { CxTracer() << (comment);                       } }
    ///< check expression and show message with comment
#define xCHECK_MSG_RET(expr, comment, return_expr)       { if ((expr)) { CxTracer() << (comment); return (return_expr); } }
    ///< check expression, show message with comment and return value
#define xCHECK_MSG_DO(expr, comment, do_expr)            { if ((expr)) { CxTracer() << (comment); do_expr;              } }
    ///< check expression, show message with comment and do instructions
#define xCHECK_NA(var)                                   ;
    ///< at this point check code for variable is not applicable
#define xCHECKS_NA                                       ;
    ///< at this point check code for variables is not applicable

#define xTEST_STATIC(expr)                               { switch (0) {case 0: case (expr):;} }
    ///< static assert
#define xNOT_IMPLEMENTED                                 { xTEST_MSG_FAIL(xT("Not implemented")); }
    ///< show not implemented message and return value

#if xTEST_BLOCK_WITH_TRACE_POINT
    #define xTEST_CASE(case_name, cuiLoops)              xTRACE_POINT; \
                                                         for (size_t _uiCaseLoops = 0U; _uiCaseLoops < (cuiLoops); ++ _uiCaseLoops)
        ///< test block with trace point
#else
    #define xTEST_CASE(case_name, cuiLoops)              /* CxTracer() << xT("\tCase name: ") << case_name; */ \
                                                         for (size_t _uiCaseLoops = 0U; _uiCaseLoops < (cuiLoops); ++ _uiCaseLoops)
        ///< test block without trace point
#endif
//-------------------------------------------------------------------------
#define xTRACE(msg)                                      { CxTracer() << (msg); }
    ///< tracing
#define xTRACE_VAR(v)                                    ( std::tstring_t() \
                                                                .append( xT(#v) xT(": ")          ) \
                                                                .append( CxString::cast(v) ) \
                                                                .append( xT(" ")                  ) \
                                                         )
    ///< trace variable, trace variable and value
#define xTRACEV(...)                                     { CxTracer::vWrite(__VA_ARGS__); }
    ///< tracing
#define xTRACE_POINT                                     { CxTracer::vWrite(xT("Point: %lu (file: %s, function: %s, last error: %s, line: %lu)"), \
                                                                            xCOUNTER, xFILE, xFUNCTION, CxLastError::sGet().c_str(), xLINE); }
    ///< trace point (use CxTracer)
//---------------------------------------------------------------------------
#endif // xLib_Debug_xDebugH
