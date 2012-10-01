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
#define _xTEST_EQ(report_type, val1, val2, msg)                        { if ( !((val1) == (val2)) )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, (val1),        (val2),         xT(#val1),  xT(#val2), xT("=="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_DIFF(report_type, val1, val2, msg)                      { if ( !((val1) != (val2)) )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, (val1),        (val2),         xT(#val1),  xT(#val2), xT("!="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_LESS(report_type, val1, val2, msg)                      { if ( !((val1) <  (val2)) )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, (val1),        (val2),         xT(#val1),  xT(#val2), xT("<"),  ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_GR(report_type, val1, val2, msg)                        { if ( !((val1) >  (val2)) )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, (val1),        (val2),         xT(#val1),  xT(#val2), xT(">"),  ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_LESS_EQ(report_type, val1, val2, msg)                   { if ( !((val1) <= (val2)) )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, (val1),        (val2),         xT(#val1),  xT(#val2), xT("<="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_GR_EQ(report_type, val1, val2, msg)                     { if ( !((val1) >= (val2)) )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, (val1),        (val2),         xT(#val1),  xT(#val2), xT(">="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_PTR(report_type, ptr, msg)                              { if ( (NULL)   == (ptr)   )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),  xT("!="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_PTR_FAIL(report_type, ptr, msg)                         { if ( (NULL)   != (ptr)   )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),  xT("=="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().bReportMake(rpReport); } }
#define _xTEST_FAIL(report_type, msg)                                  { if ( true                )  { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(""),        xT(""),         xT("fail"), xT(""),    xT(""),   ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));  CxDebugger().bReportMake(rpReport); } }

#define _xASSERT_MSG(report_type, expr, comment)                  { if ( !(expr) )              { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#expr), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger().bReportMake(rpReport);}                       }
#define _xASSERT_MSG_RET(report_type, expr, comment, return_expr) { if ( !(expr) )              { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#expr), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger().bReportMake(rpReport); return (return_expr);} }
#define _xASSERT_MSG_DO(report_type, expr, comment, do_expr)      { if ( !(expr) )              { ulong_t ulLastError = CxLastError::ulGet(); CxErrorReport rpReport(report_type, xT(#expr), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger().bReportMake(rpReport); do_expr;}              }


#if xDEBUG_MODE_STDOUT_PLAIN
//    #define xASSERT_MSG(expr, comment)                  _xASSERT_MSG(CxErrorReport::rtStdoutPlain, expr, comment)
//    #define xASSERT_MSG_RET(expr, comment, return_expr) _xASSERT_MSG_RET(CxErrorReport::rtStdoutPlain, expr, comment, return_expr)
//    #define xASSERT_MSG_DO(expr, comment, do_expr)      _xASSERT_MSG_DO(CxErrorReport::rtStdoutPlain, expr, comment, do_expr)

    #define xTEST_EQ(val1, val2)                        _xTEST_EQ(CxErrorReport::rtStdoutPlain, val1, val2, xT(""))
    #define xTEST_DIFF(val1, val2)                      _xTEST_DIFF(CxErrorReport::rtStdoutPlain, val1, val2, xT(""))
    #define xTEST_LESS(val1, val2)                      _xTEST_LESS(CxErrorReport::rtStdoutPlain, val1, val2, xT(""))
    #define xTEST_GR(val1, val2)                        _xTEST_GR(CxErrorReport::rtStdoutPlain, val1, val2, xT(""))
    #define xTEST_LESS_EQ(val1, val2)                   _xTEST_LESS_EQ(CxErrorReport::rtStdoutPlain, val1, val2, xT(""))
    #define xTEST_GR_EQ(val1, val2)                     _xTEST_GR_EQ(CxErrorReport::rtStdoutPlain, val1, val2, xT(""))
    #define xTEST_PTR(ptr)                              _xTEST_PTR(CxErrorReport::rtStdoutPlain, ptr, xT(""))
    #define xTEST_PTR_FAIL(ptr)                         _xTEST_PTR_FAIL(CxErrorReport::rtStdoutPlain, ptr, xT(""))
    #define xTEST_FAIL                                  _xTEST_FAIL(CxErrorReport::rtStdoutPlain, xT(""))

    #define xTEST_MSG_EQ(val1, val2, msg)               _xTEST_EQ(CxErrorReport::rtStdoutPlain, val1, val2, msg)
    #define xTEST_MSG_DIFF(val1, val2, msg)             _xTEST_DIFF(CxErrorReport::rtStdoutPlain, val1, val2, msg)
    #define xTEST_MSG_LESS(val1, val2, msg)             _xTEST_LESS(CxErrorReport::rtStdoutPlain, val1, val2, msg)
    #define xTEST_MSG_GR(val1, val2, msg)               _xTEST_GR(CxErrorReport::rtStdoutPlain, val1, val2, msg)
    #define xTEST_MSG_LESS_EQ(val1, val2, msg)          _xTEST_LESS_EQ(CxErrorReport::rtStdoutPlain, val1, val2, msg)
    #define xTEST_MSG_GR_EQ(val1, val2, msg)            _xTEST_GR_EQ(CxErrorReport::rtStdoutPlain, val1, val2, msg)
    #define xTEST_MSG_PTR(ptr, msg)                     _xTEST_PTR(CxErrorReport::rtStdoutPlain, ptr, msg)
    #define xTEST_MSG_PTR_FAIL(ptr, msg)                _xTEST_PTR_FAIL(CxErrorReport::rtStdoutPlain, ptr, msg)
    #define xTEST_MSG_FAIL(msg)                         _xTEST_FAIL(CxErrorReport::rtStdoutPlain, msg)
#else
    #define xASSERT_MSG(expr, comment)                  { xNA }
    #define xASSERT_MSG_RET(expr, comment, return_expr) { xNA }
    #define xASSERT_MSG_DO(expr, comment, do_expr)      { xNA }

    #define xTEST_EQ(val1, val2)                        { xNA }
    #define xTEST_DIFF(val1, val2)                      { xNA }
    #define xTEST_LESS(val1, val2)                      { xNA }
    #define xTEST_GR(val1, val2)                        { xNA }
    #define xTEST_LESS_EQ(val1, val2)                   { xNA }
    #define xTEST_GR_EQ(val1, val2)                     { xNA }
    #define xTEST_PTR(ptr)                              { xNA }
    #define xTEST_PTR_FAIL(ptr)                         { xNA }
    #define xTEST_FAIL                                  { xNA }
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
#define xNOT_IMPLEMENTED_RET(return_expr)               // TODO: { xASSERT_MSG_RET(false, xT("Not implemented"), (return_expr)); }
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
