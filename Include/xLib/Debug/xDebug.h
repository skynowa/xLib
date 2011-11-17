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
#include <xLib/Debug/CxReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
//---------------------------------------------------------------------------
#if xDEBUG_MODE_MSGBOX_PLAIN
    #define xASSERT(expr)                                   { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

    #define xTEST_EQ(expr1, expr2)                          { if ( !((expr1) == (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("=="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_DIFF(expr1, expr2)                        { if ( !((expr1) != (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_LESS(expr1, expr2)                        { if ( !((expr1) <  (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_GREATER(expr1, expr2)                     { if ( !((expr1) >  (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_LESS_EQ(expr1, expr2)                     { if ( !((expr1) <= (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_GREATER_EQ(expr1, expr2)                  { if ( !((expr1) >= (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_PTR(ptr)                                  { if ( (NULL)    == (ptr)    )  { CxReport rpReport(CxReport::rtMsgboxPlain, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_FAIL                                      { if ( true                  )  { CxReport rpReport(CxReport::rtMsgboxPlain, xT(""),        xT(""),         xT("fail"), xT(""),     xT(""),   CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }

#elif xDEBUG_MODE_MSGBOX_FORMATED
    #define xASSERT(expr)                                   { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxFormated, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxFormated, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxFormated, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxFormated, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxFormated, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxFormated, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

    #define xTEST_EQ(expr1, expr2)                          { if ( !((expr1) == (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxFormated, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("=="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_DIFF(expr1, expr2)                        { if ( !((expr1) != (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxFormated, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_LESS(expr1, expr2)                        { if ( !((expr1) <  (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxFormated, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_GREATER(expr1, expr2)                     { if ( !((expr1) >  (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxFormated, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_LESS_EQ(expr1, expr2)                     { if ( !((expr1) <= (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxFormated, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_GREATER_EQ(expr1, expr2)                  { if ( !((expr1) >= (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxFormated, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_PTR(ptr)                                  { if ( (NULL)    == (ptr)    )  { CxReport rpReport(CxReport::rtMsgboxFormated, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_FAIL                                      { if ( true                  )  { CxReport rpReport(CxReport::rtMsgboxFormated, xT(""),        xT(""),         xT("fail"), xT(""),     xT(""),   CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }

#elif xDEBUG_MODE_STDOUT_PLAIN
    #define xASSERT(expr)                                   { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

    #define xTEST_EQ(expr1, expr2)                          { if ( !((expr1) == (expr2)) )  { CxReport rpReport(CxReport::rtStdoutPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("=="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_DIFF(expr1, expr2)                        { if ( !((expr1) != (expr2)) )  { CxReport rpReport(CxReport::rtStdoutPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_LESS(expr1, expr2)                        { if ( !((expr1) <  (expr2)) )  { CxReport rpReport(CxReport::rtStdoutPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_GREATER(expr1, expr2)                     { if ( !((expr1) >  (expr2)) )  { CxReport rpReport(CxReport::rtStdoutPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_LESS_EQ(expr1, expr2)                     { if ( !((expr1) <= (expr2)) )  { CxReport rpReport(CxReport::rtStdoutPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_GREATER_EQ(expr1, expr2)                  { if ( !((expr1) >= (expr2)) )  { CxReport rpReport(CxReport::rtStdoutPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_PTR(ptr)                                  { if ( (NULL)    == (ptr)    )  { CxReport rpReport(CxReport::rtStdoutPlain, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_FAIL                                      { if ( true                  )  { CxReport rpReport(CxReport::rtStdoutPlain, xT(""),        xT(""),         xT("fail"), xT(""),     xT(""),   CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }

#elif xDEBUG_MODE_STDOUT_HTML
    #define xASSERT(expr)                                   { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

    #define xTEST_EQ(expr1, expr2)                          { if ( !((expr1) == (expr2)) )  { CxReport rpReport(CxReport::rtStdoutHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("=="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_DIFF(expr1, expr2)                        { if ( !((expr1) != (expr2)) )  { CxReport rpReport(CxReport::rtStdoutHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_LESS(expr1, expr2)                        { if ( !((expr1) <  (expr2)) )  { CxReport rpReport(CxReport::rtStdoutHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_GREATER(expr1, expr2)                     { if ( !((expr1) >  (expr2)) )  { CxReport rpReport(CxReport::rtStdoutHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_LESS_EQ(expr1, expr2)                     { if ( !((expr1) <= (expr2)) )  { CxReport rpReport(CxReport::rtStdoutHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_GREATER_EQ(expr1, expr2)                  { if ( !((expr1) >= (expr2)) )  { CxReport rpReport(CxReport::rtStdoutHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_PTR(ptr)                                  { if ( (NULL)    == (ptr)    )  { CxReport rpReport(CxReport::rtStdoutHtml, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_FAIL                                      { if ( true                  )  { CxReport rpReport(CxReport::rtStdoutHtml, xT(""),        xT(""),         xT("fail"), xT(""),     xT(""),   CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }

#elif xDEBUG_MODE_LOGGING_PLAIN
    #define xASSERT(expr)                                   { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

    #define xTEST_EQ(expr1, expr2)                          { if ( !((expr1) == (expr2)) )  { CxReport rpReport(CxReport::rtLoggingPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("=="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_DIFF(expr1, expr2)                        { if ( !((expr1) != (expr2)) )  { CxReport rpReport(CxReport::rtLoggingPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_LESS(expr1, expr2)                        { if ( !((expr1) <  (expr2)) )  { CxReport rpReport(CxReport::rtLoggingPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_GREATER(expr1, expr2)                     { if ( !((expr1) >  (expr2)) )  { CxReport rpReport(CxReport::rtLoggingPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_LESS_EQ(expr1, expr2)                     { if ( !((expr1) <= (expr2)) )  { CxReport rpReport(CxReport::rtLoggingPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_GREATER_EQ(expr1, expr2)                  { if ( !((expr1) >= (expr2)) )  { CxReport rpReport(CxReport::rtLoggingPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_PTR(ptr)                                  { if ( (NULL)    == (ptr)    )  { CxReport rpReport(CxReport::rtLoggingPlain, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_FAIL                                      { if ( true                  )  { CxReport rpReport(CxReport::rtLoggingPlain, xT(""),        xT(""),         xT("fail"), xT(""),     xT(""),   CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }

#elif xDEBUG_MODE_LOGGING_HTML
    #define xASSERT(expr)                                   { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

    #define xTEST_EQ(expr1, expr2)                          { if ( !((expr1) == (expr2)) )  { CxReport rpReport(CxReport::rtLoggingHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("=="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_DIFF(expr1, expr2)                        { if ( !((expr1) != (expr2)) )  { CxReport rpReport(CxReport::rtLoggingHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_LESS(expr1, expr2)                        { if ( !((expr1) <  (expr2)) )  { CxReport rpReport(CxReport::rtLoggingHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_GREATER(expr1, expr2)                     { if ( !((expr1) >  (expr2)) )  { CxReport rpReport(CxReport::rtLoggingHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_LESS_EQ(expr1, expr2)                     { if ( !((expr1) <= (expr2)) )  { CxReport rpReport(CxReport::rtLoggingHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_GREATER_EQ(expr1, expr2)                  { if ( !((expr1) >= (expr2)) )  { CxReport rpReport(CxReport::rtLoggingHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_PTR(ptr)                                  { if ( (NULL)    == (ptr)    )  { CxReport rpReport(CxReport::rtLoggingHtml, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xTEST_FAIL                                      { if ( true                  )  { CxReport rpReport(CxReport::rtLoggingHtml, xT(""),        xT(""),         xT("fail"), xT(""),     xT(""),   CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT(""));  CxDebugger::bReportMake(rpReport); } }

#elif xDEBUG_MODE_NOLOGGING
    #define xASSERT(expr)                                   { /* n/a */                                                 }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { return (return_expr); }   }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { do_instructions; }        }
    #define xASSERT_MSG(expr, comment)                      { /* n/a */                                                 }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { return (return_expr); }   }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { do_instructions; }        }

    #define xTEST_EQ(expr1, expr2)                          { /* n/a */ }
    #define xTEST_DIFF(expr1, expr2)                        { /* n/a */ }
    #define xTEST_LESS(expr1, expr2)                        { /* n/a */ }
    #define xTEST_GREATER(expr1, expr2)                     { /* n/a */ }
    #define xTEST_LESS_EQ(expr1, expr2)                     { /* n/a */ }
    #define xTEST_GREATER_EQ(expr1, expr2)                  { /* n/a */ }
    #define xTEST_PTR(ptr)                                  { /* n/a */ }
    #define xTEST_FAIL                                      { /* n/a */ }

#elif xDEBUG_MODE_NO
    #define xASSERT(expr)                                   { /* n/a */ }
    #define xASSERT_RET(expr, return_expr)                  { /* n/a */ }
    #define xASSERT_DO(expr, do_instructions)               { /* n/a */ }
    #define xASSERT_MSG(expr, comment)                      { /* n/a */ }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { /* n/a */ }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { /* n/a */ }

    #define xTEST_EQ(expr1, expr2)                          { /* n/a */ }
    #define xTEST_DIFF(expr1, expr2)                        { /* n/a */ }
    #define xTEST_LESS(expr1, expr2)                        { /* n/a */ }
    #define xTEST_GREATER(expr1, expr2)                     { /* n/a */ }
    #define xTEST_LESS_EQ(expr1, expr2)                     { /* n/a */ }
    #define xTEST_GREATER_EQ(expr1, expr2)                  { /* n/a */ }
    #define xTEST_PTR(ptr)                                  { /* n/a */ }
    #define xTEST_FAIL                                      { /* n/a */ }

#else
    #error xLib: incorrect debug mode
#endif
//-------------------------------------------------------------------------
#define xCHECK_RET(expr, return_expr)                       { if ((expr)) { return (return_expr);                               } }
    ///< check expression and return value
#define xCHECK_DO(expr, do_instructions)                    { if ((expr)) { do_instructions;                                    } }
    ///< check expression and do instructions
#define xCHECK_MSG(expr, comment)                           { if ((expr)) { std::tcout << (comment) << std::endl;                        } }
    ///< check expression and show message with comment
#define xCHECK_MSG_RET(expr, comment, return_expr)          { if ((expr)) { std::tcout << (comment) << std::endl; return (return_expr);  } }
    ///< check expression, show message with comment and return value
#define xCHECK_MSG_DO(expr, comment, do_instructions)       { if ((expr)) { std::tcout << (comment) << std::endl; do_instructions;       } }
    ///< check expression, show message with comment and do instructions

#define xASSERT_STATIC(expr)                                { switch (0) {case 0: case (expr):;} }
    ///< static assert
#define xNOT_IMPLEMENTED_RET(return_expr)                   { xASSERT_MSG_RET(FALSE, xT("Not implemented"), (return_expr)); }
    ///< show not implemented message and return value

#define xAUTO_PROFILER(file_path, mode, comment, ...)       CxAutoProfiler _apfPerfom(file_path, mode, comment, __VA_ARGS__)
    ///< auto profiler
#define xAUTO_PROFILER_FUNC(file_path, mode)                CxAutoProfiler _apfFunc(file_path, mode, xFUNCTION)
    ///< auto profiler, comment contains name of current function

#if xTEST_BLOCK_WITH_TRACE_POINT
    #define xTEST_BLOCK(uiLoops)                            xTRACE_POINT; for (size_t _uiBlockLoops = 0; _uiBlockLoops < uiLoops; ++ _uiBlockLoops)
        ///< test block with trace point
#else
    #define xTEST_BLOCK(uiLoops)                                          for (size_t _uiBlockLoops = 0; _uiBlockLoops < uiLoops; ++ _uiBlockLoops)
        ///< test block without trace point
#endif
//-------------------------------------------------------------------------
#if xDEBUG_MODE_TRACE
    #define xTRACEV(format, ...)                            { CxDebugger::bTrace(format, __VA_ARGS__);                        }
        ///< tracing
    #define xTRACE(msg)                                     { CxDebugger::bTrace(msg);                                        }
        ///< tracing
    #define xTRACE_FUNC                                     { CxDebugger::bTrace(xFUNCTION);                                  }
        ///< tracing, comment with current function name
    #define xTRACE_FUNC_MSG(s)                              { CxDebugger::bTrace(std::string_t(xFUNCTION) + xT(": ") + std::string_t(s)); }
        ///< tracing, comment with current function name and message
    #define xTRACE_POINT                                    { CxDebugger::bTrace(xT("Point: %li (file: %s, function: %s, last error: %s, line: %li)"), xCOUNTER, xFILE, xFUNCTION, CxLastError::sGet().c_str(), xLINE); }
        ///< trace point (use CxDebugger)
    #define xSTD_TRACE_POINT                                { std::tcout << xT("<<< Point: ") << xCOUNTER << xT(" (file: ") << xFILE << xT(", function: ") << xFUNCTION << xT(", line: ") << xLINE << xT(")") << std::endl; }
        ///< trace point (use std::cout)
#else
    #define xTRACEV(format, ...)                            { /* n/a */ }
        ///< nothing
    #define xTRACE(msg)                                     { /* n/a */ }
        ///< nothing
    #define xTRACE_FUNC                                     { /* n/a */ }
        ///< nothing
    #define xTRACE_FUNC_MSG(s)                              { /* n/a */ }
        ///< nothing
    #define xTRACE_POINT                                    { /* n/a */ }
        ///< nothing
    #define xSTD_TRACE_POINT                                { /* n/a */ }
        ///< nothing
#endif
//---------------------------------------------------------------------------
#endif //xLib_Debug_xDebugH
