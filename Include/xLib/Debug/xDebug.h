/**
 * \file  xDebug.h
 * \brief code debugging
 */


#ifndef xLib_Debug_xDebugH
#define xLib_Debug_xDebugH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxReport.h>
#include <xLib/Debug/CxDebugger.h>
//---------------------------------------------------------------------------
#if xDEBUG_MODE_MSGBOX_PLAIN
    #define xASSERT(expr)                                   { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

    #define xASSERT_EQ(expr1, expr2)                        { if ( !((expr1) == (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("=="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_NOT_EQ(expr1, expr2)                    { if ( !((expr1) != (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_LESS(expr1, expr2)                      { if ( !((expr1) <  (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_GREATER(expr1, expr2)                   { if ( !((expr1) >  (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_LESS_EQ(expr1, expr2)                   { if ( !((expr1) <= (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_GREATER_EQ(expr1, expr2)                { if ( !((expr1) >= (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_PTR(ptr)                                { if ( (NULL)    == (ptr)    )  { CxReport rpReport(CxReport::rtMsgboxPlain, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }

#elif xDEBUG_MODE_MSGBOX_FORMATED
    #define xASSERT(expr)                                   { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxFormated, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxFormated, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxFormated, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxFormated, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxFormated, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { CxReport rpReport(CxReport::rtMsgboxFormated, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

    #define xASSERT_EQ(expr1, expr2)                        { if ( !((expr1) == (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxFormated, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("=="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_NOT_EQ(expr1, expr2)                    { if ( !((expr1) != (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxFormated, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_LESS(expr1, expr2)                      { if ( !((expr1) <  (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxFormated, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_GREATER(expr1, expr2)                   { if ( !((expr1) >  (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxFormated, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_LESS_EQ(expr1, expr2)                   { if ( !((expr1) <= (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxFormated, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_GREATER_EQ(expr1, expr2)                { if ( !((expr1) >= (expr2)) )  { CxReport rpReport(CxReport::rtMsgboxFormated, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_PTR(ptr)                                { if ( (NULL)    == (ptr)    )  { CxReport rpReport(CxReport::rtMsgboxFormated, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }

#elif xDEBUG_MODE_STDOUT_PLAIN
    #define xASSERT(expr)                                   { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

    #define xASSERT_EQ(expr1, expr2)                        { if ( !((expr1) == (expr2)) )  { CxReport rpReport(CxReport::rtStdoutPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("=="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_NOT_EQ(expr1, expr2)                    { if ( !((expr1) != (expr2)) )  { CxReport rpReport(CxReport::rtStdoutPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_LESS(expr1, expr2)                      { if ( !((expr1) <  (expr2)) )  { CxReport rpReport(CxReport::rtStdoutPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_GREATER(expr1, expr2)                   { if ( !((expr1) >  (expr2)) )  { CxReport rpReport(CxReport::rtStdoutPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_LESS_EQ(expr1, expr2)                   { if ( !((expr1) <= (expr2)) )  { CxReport rpReport(CxReport::rtStdoutPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_GREATER_EQ(expr1, expr2)                { if ( !((expr1) >= (expr2)) )  { CxReport rpReport(CxReport::rtStdoutPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_PTR(ptr)                                { if ( (NULL)    == (ptr)    )  { CxReport rpReport(CxReport::rtStdoutPlain, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }

#elif xDEBUG_MODE_STDOUT_HTML
    #define xASSERT(expr)                                   { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { CxReport rpReport(CxReport::rtStdoutHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

    #define xASSERT_EQ(expr1, expr2)                        { if ( !((expr1) == (expr2)) )  { CxReport rpReport(CxReport::rtStdoutHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("=="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_NOT_EQ(expr1, expr2)                    { if ( !((expr1) != (expr2)) )  { CxReport rpReport(CxReport::rtStdoutHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_LESS(expr1, expr2)                      { if ( !((expr1) <  (expr2)) )  { CxReport rpReport(CxReport::rtStdoutHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_GREATER(expr1, expr2)                   { if ( !((expr1) >  (expr2)) )  { CxReport rpReport(CxReport::rtStdoutHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_LESS_EQ(expr1, expr2)                   { if ( !((expr1) <= (expr2)) )  { CxReport rpReport(CxReport::rtStdoutHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_GREATER_EQ(expr1, expr2)                { if ( !((expr1) >= (expr2)) )  { CxReport rpReport(CxReport::rtStdoutHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_PTR(ptr)                                { if ( (NULL)    == (ptr)    )  { CxReport rpReport(CxReport::rtStdoutHtml, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }

#elif xDEBUG_MODE_LOGGING_PLAIN
    #define xASSERT(expr)                                   { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

    #define xASSERT_EQ(expr1, expr2)                        { if ( !((expr1) == (expr2)) )  { CxReport rpReport(CxReport::rtLoggingPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("=="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_NOT_EQ(expr1, expr2)                    { if ( !((expr1) != (expr2)) )  { CxReport rpReport(CxReport::rtLoggingPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_LESS(expr1, expr2)                      { if ( !((expr1) <  (expr2)) )  { CxReport rpReport(CxReport::rtLoggingPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_GREATER(expr1, expr2)                   { if ( !((expr1) >  (expr2)) )  { CxReport rpReport(CxReport::rtLoggingPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_LESS_EQ(expr1, expr2)                   { if ( !((expr1) <= (expr2)) )  { CxReport rpReport(CxReport::rtLoggingPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_GREATER_EQ(expr1, expr2)                { if ( !((expr1) >= (expr2)) )  { CxReport rpReport(CxReport::rtLoggingPlain, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_PTR(ptr)                                { if ( (NULL)    == (ptr)    )  { CxReport rpReport(CxReport::rtLoggingPlain, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }

#elif xDEBUG_MODE_LOGGING_HTML
    #define xASSERT(expr)                                   { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { CxReport rpReport(CxReport::rtLoggingHtml, xT(#expr), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

    #define xASSERT_EQ(expr1, expr2)                        { if ( !((expr1) == (expr2)) )  { CxReport rpReport(CxReport::rtLoggingHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("=="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_NOT_EQ(expr1, expr2)                    { if ( !((expr1) != (expr2)) )  { CxReport rpReport(CxReport::rtLoggingHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_LESS(expr1, expr2)                      { if ( !((expr1) <  (expr2)) )  { CxReport rpReport(CxReport::rtLoggingHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_GREATER(expr1, expr2)                   { if ( !((expr1) >  (expr2)) )  { CxReport rpReport(CxReport::rtLoggingHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">"),  CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_LESS_EQ(expr1, expr2)                   { if ( !((expr1) <= (expr2)) )  { CxReport rpReport(CxReport::rtLoggingHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT("<="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_GREATER_EQ(expr1, expr2)                { if ( !((expr1) >= (expr2)) )  { CxReport rpReport(CxReport::rtLoggingHtml, expr1,         expr2,          xT(#expr1), xT(#expr2), xT(">="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_PTR(ptr)                                { if ( (NULL)    == (ptr)    )  { CxReport rpReport(CxReport::rtLoggingHtml, (intptr_t)ptr, (intptr_t)NULL, xT("NULL"), xT(#ptr),   xT("!="), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, xT(""));  CxDebugger::bReportMake(rpReport); } }

#elif xDEBUG_MODE_NOLOGGING
    #define xASSERT(expr)                                   { /* n/a */                                                 }
    #define xASSERT_RET(expr, return_expr)                  { if ( !(expr) )                { return (return_expr); }   }
    #define xASSERT_DO(expr, do_instructions)               { if ( !(expr) )                { do_instructions; }        }
    #define xASSERT_MSG(expr, comment)                      { /* n/a */                                                 }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if ( !(expr) )                { return (return_expr); }   }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if ( !(expr) )                { do_instructions; }        }

    #define xASSERT_EQ(expr1, expr2)                        { /* n/a */ }
    #define xASSERT_NOT_EQ(expr1, expr2)                    { /* n/a */ }
    #define xASSERT_LESS(expr1, expr2)                      { /* n/a */ }
    #define xASSERT_GREATER(expr1, expr2)                   { /* n/a */ }
    #define xASSERT_LESS_EQ(expr1, expr2)                   { /* n/a */ }
    #define xASSERT_GREATER_EQ(expr1, expr2)                { /* n/a */ }
    #define xASSERT_PTR(ptr)                                { /* n/a */ }

#elif xDEBUG_MODE_NO
    #define xASSERT(expr)                                   { /* n/a */ }
    #define xASSERT_RET(expr, return_expr)                  { /* n/a */ }
    #define xASSERT_DO(expr, do_instructions)               { /* n/a */ }
    #define xASSERT_MSG(expr, comment)                      { /* n/a */ }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { /* n/a */ }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { /* n/a */ }

    #define xASSERT_EQ(expr1, expr2)                        { /* n/a */ }
    #define xASSERT_NOT_EQ(expr1, expr2)                    { /* n/a */ }
    #define xASSERT_LESS(expr1, expr2)                      { /* n/a */ }
    #define xASSERT_GREATER(expr1, expr2)                   { /* n/a */ }
    #define xASSERT_LESS_EQ(expr1, expr2)                   { /* n/a */ }
    #define xASSERT_GREATER_EQ(expr1, expr2)                { /* n/a */ }
    #define xASSERT_PTR(ptr)                                { /* n/a */ }

#else
    #error xLib: incorrect debug mode
#endif
//-------------------------------------------------------------------------
#define xCHECK_RET(expr, return_expr)                       { if ((expr)) { return (return_expr);                               } }
#define xCHECK_DO(expr, do_instructions)                    { if ((expr)) { do_instructions;                                    } }
#define xCHECK_MSG(expr, comment)                           { if ((expr)) { std::tcout << (comment) << std::endl;                        } }
#define xCHECK_MSG_RET(expr, comment, return_expr)          { if ((expr)) { std::tcout << (comment) << std::endl; return (return_expr);  } }
#define xCHECK_MSG_DO(expr, comment, do_instructions)       { if ((expr)) { std::tcout << (comment) << std::endl; do_instructions;       } }

#define xASSERT_STATIC(expr)                                { switch (0) {case 0: case (expr):;} }
#define xNOT_IMPLEMENTED_RET(return_expr)                   { xASSERT_MSG_RET(FALSE, xT("Not implemented"), (return_expr)); }

#define xAUTO_PROFILER(file_path, mode, comment, ...)       CxAutoProfiler _apfPerfom(file_path, mode, comment, __VA_ARGS__)
#define xAUTO_PROFILER_FUNC(file_path, mode)                CxAutoProfiler _apfFunc(file_path, mode, xFUNCTION)

#if xTEST_BLOCK_WITH_TRACE_POINT
    #define xTEST_BLOCK(uiLoops)                            xTRACE_POINT; for (size_t _uiBlockLoops = 0; _uiBlockLoops < uiLoops; ++ _uiBlockLoops)
#else
    #define xTEST_BLOCK(uiLoops)                                          for (size_t _uiBlockLoops = 0; _uiBlockLoops < uiLoops; ++ _uiBlockLoops)
#endif
//-------------------------------------------------------------------------
#if xDEBUG_MODE_TRACE
    #define xTRACEV(format, ...)                            { CxDebugger::bTrace(format, __VA_ARGS__);                        }
    #define xTRACE(msg)                                     { CxDebugger::bTrace(msg);                                        }
    #define xTRACE_FUNC                                     { CxDebugger::bTrace(xFUNCTION);                                  }
    #define xTRACE_FUNC_MSG(s)                              { CxDebugger::bTrace(std::tstring(xFUNCTION) + xT(": ") + std::tstring(s)); }
    #define xTRACE_POINT                                    { CxDebugger::bTrace(xT("Point: %li (file: %s, function: %s, last error: %s, line: %li)"), xCOUNTER, xFILE, xFUNCTION, CxLastError::sGet().c_str(), xLINE); }
    #define xSTD_TRACE_POINT                                { std::tcout << xT("<<< Point: ") << xCOUNTER << xT(" (file: ") << xFILE << xT(", function: ") << xFUNCTION << xT(", line: ") << xLINE << xT(")") << std::endl; }
#else
    #define xTRACEV(format, ...)                            { /* n/a */ }
    #define xTRACE(msg)                                     { /* n/a */ }
    #define xTRACE_FUNC                                     { /* n/a */ }
    #define xTRACE_FUNC_MSG(s)                              { /* n/a */ }
    #define xTRACE_POINT                                    { /* n/a */ }
    #define xSTD_TRACE_POINT                                { /* n/a */ }
#endif
//---------------------------------------------------------------------------
#endif //xLib_Debug_xDebugH
