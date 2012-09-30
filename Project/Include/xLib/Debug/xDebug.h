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
#define _xASSERT_RET(report_type, expr, return_expr)              { if ( !(expr) )                { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#expr), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger().bReportMake(rpReport); return (return_expr);} }
#define _xASSERT_DO(report_type, expr, do_expr)                   { if ( !(expr) )                { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#expr), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger().bReportMake(rpReport); do_expr;}      }
#define _xASSERT_MSG(report_type, expr, comment)                  { if ( !(expr) )                { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#expr), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger().bReportMake(rpReport);}                       }
#define _xASSERT_MSG_RET(report_type, expr, comment, return_expr) { if ( !(expr) )                { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#expr), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger().bReportMake(rpReport); return (return_expr);} }
#define _xASSERT_MSG_DO(report_type, expr, comment, do_expr)      { if ( !(expr) )                { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#expr), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger().bReportMake(rpReport); do_expr;}      }

#define _xTEST_EQ(report_type, expr1, expr2)                      { if ( !((expr1) == (expr2)) )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("=="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_DIFF(report_type, expr1, expr2)                    { if ( !((expr1) != (expr2)) )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("!="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_LESS(report_type, expr1, expr2)                    { if ( !((expr1) <  (expr2)) )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<"),  ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_GREATER(report_type, expr1, expr2)                 { if ( !((expr1) >  (expr2)) )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">"),  ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_LESS_EQ(report_type, expr1, expr2)                 { if ( !((expr1) <= (expr2)) )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_GREATER_EQ(report_type, expr1, expr2)              { if ( !((expr1) >= (expr2)) )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_PTR(report_type, ptr)                              { if ( (NULL)    == (ptr)    )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("!="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_PTR_FAIL(report_type, ptr)                         { if ( (NULL)    != (ptr)    )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("=="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_FAIL(report_type)                                  { if ( true                  )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(""),        xT(""),         xT("fail"), xT(""),     xT(""),   ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger().bReportMake(rpReport); } }


#if xDEBUG_MODE_MSGBOX_PLAIN
    #define xASSERT_RET(expr, return_expr)              _xASSERT_RET(CxErrorReport::rtMsgboxPlain, expr, return_expr)
    #define xASSERT_DO(expr, do_expr)                   _xASSERT_DO(CxErrorReport::rtMsgboxPlain, expr, do_expr)
    #define xASSERT_MSG(expr, comment)                  _xASSERT_MSG(CxErrorReport::rtMsgboxPlain, expr, comment)
    #define xASSERT_MSG_RET(expr, comment, return_expr) _xASSERT_MSG_RET(CxErrorReport::rtMsgboxPlain, expr, comment, return_expr)
    #define xASSERT_MSG_DO(expr, comment, do_expr)      _xASSERT_MSG_DO(CxErrorReport::rtMsgboxPlain, expr, comment, do_expr)

    #define xTEST_EQ(expr1, expr2)                      _xTEST_EQ(CxErrorReport::rtMsgboxPlain, expr1, expr2)
    #define xTEST_DIFF(expr1, expr2)                    _xTEST_DIFF(CxErrorReport::rtMsgboxPlain, expr1, expr2)
    #define xTEST_LESS(expr1, expr2)                    _xTEST_LESS(CxErrorReport::rtMsgboxPlain, expr1, expr2)
    #define xTEST_GREATER(expr1, expr2)                 _xTEST_GREATER(CxErrorReport::rtMsgboxPlain, expr1, expr2)
    #define xTEST_LESS_EQ(expr1, expr2)                 _xTEST_LESS_EQ(CxErrorReport::rtMsgboxPlain, expr1, expr2)
    #define xTEST_GREATER_EQ(expr1, expr2)              _xTEST_GREATER_EQ(CxErrorReport::rtMsgboxPlain, expr1, expr2)
    #define xTEST_PTR(ptr)                              _xTEST_PTR(CxErrorReport::rtMsgboxPlain, ptr)
    #define xTEST_PTR_FAIL(ptr)                         _xTEST_PTR_FAIL(CxErrorReport::rtMsgboxPlain, ptr)
    #define xTEST_FAIL                                  _xTEST_FAIL(CxErrorReport::rtMsgboxPlain)

#elif xDEBUG_MODE_MSGBOX_FORMATED
    #define xASSERT_RET(expr, return_expr)              _xASSERT_RET(CxErrorReport::rtMsgboxFormated, expr, return_expr)
    #define xASSERT_DO(expr, do_expr)                   _xASSERT_DO(CxErrorReport::rtMsgboxFormated, expr, do_expr)
    #define xASSERT_MSG(expr, comment)                  _xASSERT_MSG(CxErrorReport::rtMsgboxFormated, expr, comment)
    #define xASSERT_MSG_RET(expr, comment, return_expr) _xASSERT_MSG_RET(CxErrorReport::rtMsgboxFormated, expr, comment, return_expr)
    #define xASSERT_MSG_DO(expr, comment, do_expr)      _xASSERT_MSG_DO(CxErrorReport::rtMsgboxFormated, expr, comment, do_expr)

    #define xTEST_EQ(expr1, expr2)                      _xTEST_EQ(CxErrorReport::rtMsgboxFormated, expr1, expr2)
    #define xTEST_DIFF(expr1, expr2)                    _xTEST_DIFF(CxErrorReport::rtMsgboxFormated, expr1, expr2)
    #define xTEST_LESS(expr1, expr2)                    _xTEST_LESS(CxErrorReport::rtMsgboxFormated, expr1, expr2)
    #define xTEST_GREATER(expr1, expr2)                 _xTEST_GREATER(CxErrorReport::rtMsgboxFormated, expr1, expr2)
    #define xTEST_LESS_EQ(expr1, expr2)                 _xTEST_LESS_EQ(CxErrorReport::rtMsgboxFormated, expr1, expr2)
    #define xTEST_GREATER_EQ(expr1, expr2)              _xTEST_GREATER_EQ(CxErrorReport::rtMsgboxFormated, expr1, expr2)
    #define xTEST_PTR(ptr)                              _xTEST_PTR(CxErrorReport::rtMsgboxFormated, ptr)
    #define xTEST_PTR_FAIL(ptr)                         _xTEST_PTR_FAIL(CxErrorReport::rtMsgboxFormated, ptr)
    #define xTEST_FAIL                                  _xTEST_FAIL(CxErrorReport::rtMsgboxFormated)

#elif xDEBUG_MODE_STDOUT_PLAIN
    #define xASSERT_RET(expr, return_expr)              _xASSERT_RET(CxErrorReport::rtStdoutPlain, expr, return_expr)
    #define xASSERT_DO(expr, do_expr)                   _xASSERT_DO(CxErrorReport::rtStdoutPlain, expr, do_expr)
    #define xASSERT_MSG(expr, comment)                  _xASSERT_MSG(CxErrorReport::rtStdoutPlain, expr, comment)
    #define xASSERT_MSG_RET(expr, comment, return_expr) _xASSERT_MSG_RET(CxErrorReport::rtStdoutPlain, expr, comment, return_expr)
    #define xASSERT_MSG_DO(expr, comment, do_expr)      _xASSERT_MSG_DO(CxErrorReport::rtStdoutPlain, expr, comment, do_expr)

    #define xTEST_EQ(expr1, expr2)                      _xTEST_EQ(CxErrorReport::rtStdoutPlain, expr1, expr2)
    #define xTEST_DIFF(expr1, expr2)                    _xTEST_DIFF(CxErrorReport::rtStdoutPlain, expr1, expr2)
    #define xTEST_LESS(expr1, expr2)                    _xTEST_LESS(CxErrorReport::rtStdoutPlain, expr1, expr2)
    #define xTEST_GREATER(expr1, expr2)                 _xTEST_GREATER(CxErrorReport::rtStdoutPlain, expr1, expr2)
    #define xTEST_LESS_EQ(expr1, expr2)                 _xTEST_LESS_EQ(CxErrorReport::rtStdoutPlain, expr1, expr2)
    #define xTEST_GREATER_EQ(expr1, expr2)              _xTEST_GREATER_EQ(CxErrorReport::rtStdoutPlain, expr1, expr2)
    #define xTEST_PTR(ptr)                              _xTEST_PTR(CxErrorReport::rtStdoutPlain, ptr)
    #define xTEST_PTR_FAIL(ptr)                         _xTEST_PTR_FAIL(CxErrorReport::rtStdoutPlain, ptr)
    #define xTEST_FAIL                                  _xTEST_FAIL(CxErrorReport::rtStdoutPlain)

#elif xDEBUG_MODE_STDOUT_HTML
    #define xASSERT_RET(expr, return_expr)              _xASSERT_RET(CxErrorReport::rtStdoutHtml, expr, return_expr)
    #define xASSERT_DO(expr, do_expr)                   _xASSERT_DO(CxErrorReport::rtStdoutHtml, expr, do_expr)
    #define xASSERT_MSG(expr, comment)                  _xASSERT_MSG(CxErrorReport::rtStdoutHtml, expr, comment)
    #define xASSERT_MSG_RET(expr, comment, return_expr) _xASSERT_MSG_RET(CxErrorReport::rtStdoutHtml, expr, comment, return_expr)
    #define xASSERT_MSG_DO(expr, comment, do_expr)      _xASSERT_MSG_DO(CxErrorReport::rtStdoutHtml, expr, comment, do_expr)

    #define xTEST_EQ(expr1, expr2)                      _xTEST_EQ(CxErrorReport::rtStdoutHtml, expr1, expr2)
    #define xTEST_DIFF(expr1, expr2)                    _xTEST_DIFF(CxErrorReport::rtStdoutHtml, expr1, expr2)
    #define xTEST_LESS(expr1, expr2)                    _xTEST_LESS(CxErrorReport::rtStdoutHtml, expr1, expr2)
    #define xTEST_GREATER(expr1, expr2)                 _xTEST_GREATER(CxErrorReport::rtStdoutHtml, expr1, expr2)
    #define xTEST_LESS_EQ(expr1, expr2)                 _xTEST_LESS_EQ(CxErrorReport::rtStdoutHtml, expr1, expr2)
    #define xTEST_GREATER_EQ(expr1, expr2)              _xTEST_GREATER_EQ(CxErrorReport::rtStdoutHtml, expr1, expr2)
    #define xTEST_PTR(ptr)                              _xTEST_PTR(CxErrorReport::rtStdoutHtml, ptr)
    #define xTEST_PTR_FAIL(ptr)                         _xTEST_PTR_FAIL(CxErrorReport::rtStdoutHtml, ptr)
    #define xTEST_FAIL                                  _xTEST_FAIL(CxErrorReport::rtStdoutHtml)

#elif xDEBUG_MODE_LOGGING_PLAIN
    #define xASSERT_RET(expr, return_expr)              _xASSERT_RET(CxErrorReport::rtLoggingPlain, expr, return_expr)
    #define xASSERT_DO(expr, do_expr)                   _xASSERT_DO(CxErrorReport::rtLoggingPlain, expr, do_expr)
    #define xASSERT_MSG(expr, comment)                  _xASSERT_MSG(CxErrorReport::rtLoggingPlain, expr, comment)
    #define xASSERT_MSG_RET(expr, comment, return_expr) _xASSERT_MSG_RET(CxErrorReport::rtLoggingPlain, expr, comment, return_expr)
    #define xASSERT_MSG_DO(expr, comment, do_expr)      _xASSERT_MSG_DO(CxErrorReport::rtLoggingPlain, expr, comment, do_expr)

    #define xTEST_EQ(expr1, expr2)                      _xTEST_EQ(CxErrorReport::rtLoggingPlain, expr1, expr2)
    #define xTEST_DIFF(expr1, expr2)                    _xTEST_DIFF(CxErrorReport::rtLoggingPlain, expr1, expr2)
    #define xTEST_LESS(expr1, expr2)                    _xTEST_LESS(CxErrorReport::rtLoggingPlain, expr1, expr2)
    #define xTEST_GREATER(expr1, expr2)                 _xTEST_GREATER(CxErrorReport::rtLoggingPlain, expr1, expr2)
    #define xTEST_LESS_EQ(expr1, expr2)                 _xTEST_LESS_EQ(CxErrorReport::rtLoggingPlain, expr1, expr2)
    #define xTEST_GREATER_EQ(expr1, expr2)              _xTEST_GREATER_EQ(CxErrorReport::rtLoggingPlain, expr1, expr2)
    #define xTEST_PTR(ptr)                              _xTEST_PTR(CxErrorReport::rtLoggingPlain, ptr)
    #define xTEST_PTR_FAIL(ptr)                         _xTEST_PTR_FAIL(CxErrorReport::rtLoggingPlain, ptr)
    #define xTEST_FAIL                                  _xTEST_FAIL(CxErrorReport::rtLoggingPlain)

#elif xDEBUG_MODE_LOGGING_HTML
    #define xASSERT_RET(expr, return_expr)              _xASSERT_RET(CxErrorReport::rtLoggingHtml, expr, return_expr)
    #define xASSERT_DO(expr, do_expr)                   _xASSERT_DO(CxErrorReport::rtLoggingHtml, expr, do_expr)
    #define xASSERT_MSG(expr, comment)                  _xASSERT_MSG(CxErrorReport::rtLoggingHtml, expr, comment)
    #define xASSERT_MSG_RET(expr, comment, return_expr) _xASSERT_MSG_RET(CxErrorReport::rtLoggingHtml, expr, comment, return_expr)
    #define xASSERT_MSG_DO(expr, comment, do_expr)      _xASSERT_MSG_DO(CxErrorReport::rtLoggingHtml, expr, comment, do_expr)

    #define xTEST_EQ(expr1, expr2)                      _xTEST_EQ(CxErrorReport::rtLoggingHtml, expr1, expr2)
    #define xTEST_DIFF(expr1, expr2)                    _xTEST_DIFF(CxErrorReport::rtLoggingHtml, expr1, expr2)
    #define xTEST_LESS(expr1, expr2)                    _xTEST_LESS(CxErrorReport::rtLoggingHtml, expr1, expr2)
    #define xTEST_GREATER(expr1, expr2)                 _xTEST_GREATER(CxErrorReport::rtLoggingHtml, expr1, expr2)
    #define xTEST_LESS_EQ(expr1, expr2)                 _xTEST_LESS_EQ(CxErrorReport::rtLoggingHtml, expr1, expr2)
    #define xTEST_GREATER_EQ(expr1, expr2)              _xTEST_GREATER_EQ(CxErrorReport::rtLoggingHtml, expr1, expr2)
    #define xTEST_PTR(ptr)                              _xTEST_PTR(CxErrorReport::rtLoggingHtml, ptr)
    #define xTEST_PTR_FAIL(ptr)                         _xTEST_PTR_FAIL(CxErrorReport::rtLoggingHtml, ptr)
    #define xTEST_FAIL                                  _xTEST_FAIL(CxErrorReport::rtLoggingHtml)

#elif xDEBUG_MODE_NOLOGGING
    #define xASSERT_RET(expr, return_expr)              { if ( !(expr) ) { return (return_expr); } }
    #define xASSERT_DO(expr, do_expr)                   { if ( !(expr) ) { do_expr;              } }
    #define xASSERT_MSG(expr, comment)                  { xNA                                      }
    #define xASSERT_MSG_RET(expr, comment, return_expr) { if ( !(expr) ) { return (return_expr); } }
    #define xASSERT_MSG_DO(expr, comment, do_expr)      { if ( !(expr) ) { do_expr;              } }

    #define xTEST_EQ(expr1, expr2)                      { xNA }
    #define xTEST_DIFF(expr1, expr2)                    { xNA }
    #define xTEST_LESS(expr1, expr2)                    { xNA }
    #define xTEST_GREATER(expr1, expr2)                 { xNA }
    #define xTEST_LESS_EQ(expr1, expr2)                 { xNA }
    #define xTEST_GREATER_EQ(expr1, expr2)              { xNA }
    #define xTEST_PTR(ptr)                              { xNA }
    #define xTEST_PTR_FAIL(ptr)                         { xNA }
    #define xTEST_FAIL                                  { xNA }

#elif xDEBUG_MODE_NO
    #define xASSERT_RET(expr, return_expr)              { xNA }
    #define xASSERT_DO(expr, do_expr)                   { xNA }
    #define xASSERT_MSG(expr, comment)                  { xNA }
    #define xASSERT_MSG_RET(expr, comment, return_expr) { xNA }
    #define xASSERT_MSG_DO(expr, comment, do_expr)      { xNA }

    #define xTEST_EQ(expr1, expr2)                      { xNA }
    #define xTEST_DIFF(expr1, expr2)                    { xNA }
    #define xTEST_LESS(expr1, expr2)                    { xNA }
    #define xTEST_GREATER(expr1, expr2)                 { xNA }
    #define xTEST_LESS_EQ(expr1, expr2)                 { xNA }
    #define xTEST_GREATER_EQ(expr1, expr2)              { xNA }
    #define xTEST_PTR(ptr)                              { xNA }
    #define xTEST_PTR_FAIL(ptr)                         { xNA }
    #define xTEST_FAIL                                  { xNA }

#else
    #error xLib: incorrect debug mode
#endif
//-------------------------------------------------------------------------
#define xSTD_VERIFY(expr)                               { \
                                                            if ( !(expr) )  { \
                                                                std::tstring_t sLastError = CxLastError::sGet(); \
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
                                                                                 sLastError.c_str());  \
                                                                (void)::exit(EXIT_FAILURE); \
                                                            } \
                                                        }
    ///< check expression (work in debug and release modes)

#define xCHECK_RET(expr, return_expr)                   { if ((expr)) { return (return_expr);                          } }
    ///< check expression and return value
#define xCHECK_DO(expr, do_expr)                        { if ((expr)) { do_expr;                                       } }
    ///< check expression and do instructions
#define xCHECK_MSG(expr, comment)                       { if ((expr)) { CxTracer() << (comment);                       } }
    ///< check expression and show message with comment
#define xCHECK_MSG_RET(expr, comment, return_expr)      { if ((expr)) { CxTracer() << (comment); return (return_expr); } }
    ///< check expression, show message with comment and return value
#define xCHECK_MSG_DO(expr, comment, do_expr)           { if ((expr)) { CxTracer() << (comment); do_expr;              } }
    ///< check expression, show message with comment and do instructions

#define xASSERT_STATIC(expr)                            { switch (0) {case 0: case (expr):;} }
    ///< static assert
#define xNOT_IMPLEMENTED_RET(return_expr)               { xASSERT_MSG_RET(false, xT("Not implemented"), (return_expr)); }
    ///< show not implemented message and return value

#define xAUTO_PROFILER(file_path, mode, comment, ...)   CxAutoProfiler _apfProfiler(file_path, mode, comment, __VA_ARGS__)
    ///< auto profiler
#define xAUTO_PROFILER_FUNC(file_path, mode)            CxAutoProfiler _apfProfiler(file_path, mode, xFUNCTION)
    ///< auto profiler, comment contains name of current function

#if xTEST_BLOCK_WITH_TRACE_POINT
    #define xTEST_CASE(cuiLoops)                        xTRACE_POINT; for (size_t _uiBlockLoops = 0U; _uiBlockLoops < (cuiLoops); ++ _uiBlockLoops)
        ///< test block with trace point
#else
    #define xTEST_CASE(cuiLoops)                                      for (size_t _uiBlockLoops = 0U; _uiBlockLoops < (cuiLoops); ++ _uiBlockLoops)
        ///< test block without trace point
#endif
//-------------------------------------------------------------------------
#if xDEBUG_MODE_TRACE
    #define xTRACE(msg)                                 { CxTracer() << (msg);                   }
        ///< tracing
    #define xTRACEV(format, ...)                        { CxTracer::vWrite(format, __VA_ARGS__); }
        ///< tracing
    #define xTRACE_POINT                                { CxTracer::vWrite(xT("Point: %lu (file: %s, function: %s, last error: %s, line: %lu)"), xCOUNTER, xFILE, xFUNCTION, CxLastError::sGet().c_str(), xLINE); }
        ///< trace point (use CxTracer)
#else
    #define xTRACE(msg)                                 { xNA }
        ///< nothing
    #define xTRACEV(format, ...)                        { xNA }
        ///< nothing
    #define xTRACE_POINT                                { xNA }
        ///< nothing
#endif
//---------------------------------------------------------------------------
#endif //xLib_Debug_xDebugH
