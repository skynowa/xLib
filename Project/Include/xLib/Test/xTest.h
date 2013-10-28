/**
 * \file  xTest.h
 * \brief code testing
 */


#pragma once

//------------------------------------------------------------------------------
#define _xTEST_MSG_EQ(report_type, val1, val2, msg)      { if ( !((val1) == (val2)) ) { ulong_t ulLastError = CxLastError::get(); CxErrorReport rpReport(report_type, xT(#val1),   xT(#val2), (val1),        (val2),         xT("=="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_DIFF(report_type, val1, val2, msg)    { if ( !((val1) != (val2)) ) { ulong_t ulLastError = CxLastError::get(); CxErrorReport rpReport(report_type, xT(#val1),   xT(#val2), (val1),        (val2),         xT("!="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_LESS(report_type, val1, val2, msg)    { if ( !((val1) <  (val2)) ) { ulong_t ulLastError = CxLastError::get(); CxErrorReport rpReport(report_type, xT(#val1),   xT(#val2), (val1),        (val2),         xT("<"),  ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_GR(report_type, val1, val2, msg)      { if ( !((val1) >  (val2)) ) { ulong_t ulLastError = CxLastError::get(); CxErrorReport rpReport(report_type, xT(#val1),   xT(#val2), (val1),        (val2),         xT(">"),  ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_LESS_EQ(report_type, val1, val2, msg) { if ( !((val1) <= (val2)) ) { ulong_t ulLastError = CxLastError::get(); CxErrorReport rpReport(report_type, xT(#val1),   xT(#val2), (val1),        (val2),         xT("<="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_GR_EQ(report_type, val1, val2, msg)   { if ( !((val1) >= (val2)) ) { ulong_t ulLastError = CxLastError::get(); CxErrorReport rpReport(report_type, xT(#val1),   xT(#val2), (val1),        (val2),         xT(">="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_PTR(report_type, ptr, msg)            { if ( NULL     == (ptr)   ) { ulong_t ulLastError = CxLastError::get(); CxErrorReport rpReport(report_type, xT("NULL"),  xT(#ptr),  (intptr_t)ptr, (intptr_t)NULL, xT("!="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_PTR_FAIL(report_type, ptr, msg)       { if ( NULL     != (ptr)   ) { ulong_t ulLastError = CxLastError::get(); CxErrorReport rpReport(report_type, xT("NULL"),  xT(#ptr),  (intptr_t)ptr, (intptr_t)NULL, xT("=="), ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg));  CxDebugger().reportMake(rpReport); } }
#define _xTEST_MSG_FAIL(report_type, msg)                { if ( true                ) { ulong_t ulLastError = CxLastError::get(); CxErrorReport rpReport(report_type, xT("false"), xT(""),    xT(""),        xT(""),         xT(""),   ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg));  CxDebugger().reportMake(rpReport); } }

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
#define xTEST_STATIC(expr)                               { switch (0) {case 0: case (expr):;} }
    ///< static assert

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
