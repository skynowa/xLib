/**
 * \file  xTest.h
 * \brief code testing
 */


#pragma once

#ifndef xLib_xTestH
#define xLib_xTestH
//-------------------------------------------------------------------------------------------------
#define _xTEST_MSG_EQ(reportType, val1, val2, msg) \
    if ( !((val1) == (val2)) ) { \
        ulong_t _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT("=="), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_DIFF(reportType, val1, val2, msg) \
    if ( !((val1) != (val2)) ) { \
        ulong_t _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT("!="), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_LESS(reportType, val1, val2, msg) \
    if ( !((val1) < (val2)) ) { \
        ulong_t _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT("<"), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_GR(reportType, val1, val2, msg) \
    if ( !((val1) > (val2)) ) { \
        ulong_t _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT(">"), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_LESS_EQ(reportType, val1, val2, msg) \
    if ( !((val1) <= (val2)) ) { \
        ulong_t _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT("<="), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_GR_EQ(reportType, val1, val2, msg) \
    if ( !((val1) >= (val2)) ) { \
        ulong_t _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT(">="), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_PTR(reportType, ptr, msg) \
    if ( NULL == (ptr) ) { \
        ulong_t _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT("NULL"), xT(#ptr), intptr_t(ptr), intptr_t(NULL), \
            xT("!="), _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, \
            CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_PTR_FAIL(reportType, ptr, msg) \
    if ( NULL != (ptr) ) { \
        ulong_t _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT("NULL"), xT(#ptr), intptr_t(ptr), intptr_t(NULL), \
            xT("=="), _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, \
            CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_FAIL(reportType, msg) \
    if ( true ) { \
        ulong_t _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT("false"), xT(""), xT(""), xT(""), xT(""), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, \
            CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }

// xREPORT_TYPE
#if xDEBUG_MODE_STDOUT_PLAIN
    #define xREPORT_TYPE CxErrorReport::rtStdoutPlain
#elif xDEBUG_MODE_MSGBOX_PLAIN
    #define xREPORT_TYPE CxErrorReport::rtMsgboxPlain
#else
    #define xTEST_EQ(val1, val2) \
        { xNA }
    #define xTEST_DIFF(val1, val2) \
        { xNA }
    #define xTEST_LESS(val1, val2) \
        { xNA }
    #define xTEST_GR(val1, val2) \
        { xNA }
    #define xTEST_LESS_EQ(val1, val2) \
        { xNA }
    #define xTEST_GR_EQ(val1, val2) \
        { xNA }
    #define xTEST_PTR(ptr) \
        { xNA }
    #define xTEST_PTR_FAIL(ptr) \
        { xNA }
    #define xTEST_FAIL \
        { xNA }
    #define xTEST(expr) \
        { xNA }

    #define xTEST_MSG_EQ(val1, val2, msg) \
        { xNA }
    #define xTEST_MSG_DIFF(val1, val2, msg) \
        { xNA }
    #define xTEST_MSG_LESS(val1, val2, msg) \
        { xNA }
    #define xTEST_MSG_GR(val1, val2, msg) \
        { xNA }
    #define xTEST_MSG_LESS_EQ(val1, val2, msg) \
        { xNA }
    #define xTEST_MSG_GR_EQ(val1, val2, msg) \
        { xNA }
    #define xTEST_MSG_PTR(ptr, msg) \
        { xNA }
    #define xTEST_MSG_PTR_FAIL(ptr, msg) \
        { xNA }
    #define xTEST_MSG_FAIL(msg) \
        { xNA }
    #define xTEST_MSG(expr, msg) \
        { xNA }
#endif


#define xTEST_EQ(val1, val2) \
    _xTEST_MSG_EQ      (xREPORT_TYPE, val1, val2, xT(""))
#define xTEST_DIFF(val1, val2) \
    _xTEST_MSG_DIFF    (xREPORT_TYPE, val1, val2, xT(""))
#define xTEST_LESS(val1, val2) \
    _xTEST_MSG_LESS    (xREPORT_TYPE, val1, val2, xT(""))
#define xTEST_GR(val1, val2) \
    _xTEST_MSG_GR      (xREPORT_TYPE, val1, val2, xT(""))
#define xTEST_LESS_EQ(val1, val2) \
    _xTEST_MSG_LESS_EQ (xREPORT_TYPE, val1, val2, xT(""))
#define xTEST_GR_EQ(val1, val2) \
    _xTEST_MSG_GR_EQ   (xREPORT_TYPE, val1, val2, xT(""))
#define xTEST_PTR(ptr) \
    _xTEST_MSG_PTR     (xREPORT_TYPE, ptr, xT(""))
#define xTEST_PTR_FAIL(ptr) \
    _xTEST_MSG_PTR_FAIL(xREPORT_TYPE, ptr, xT(""))
#define xTEST_FAIL \
    _xTEST_MSG_FAIL    (xREPORT_TYPE, xT(""))
#define xTEST(expr) \
    _xTEST_MSG_EQ      (xREPORT_TYPE, true, expr, xT(""))

#define xTEST_MSG_EQ(val1, val2, msg) \
    _xTEST_MSG_EQ      (xREPORT_TYPE, val1, val2, msg)
#define xTEST_MSG_DIFF(val1, val2, msg) \
    _xTEST_MSG_DIFF    (xREPORT_TYPE, val1, val2, msg)
#define xTEST_MSG_LESS(val1, val2, msg) \
    _xTEST_MSG_LESS    (xREPORT_TYPE, val1, val2, msg)
#define xTEST_MSG_GR(val1, val2, msg) \
    _xTEST_MSG_GR      (xREPORT_TYPE, val1, val2, msg)
#define xTEST_MSG_LESS_EQ(val1, val2, msg) \
    _xTEST_MSG_LESS_EQ (xREPORT_TYPE, val1, val2, msg)
#define xTEST_MSG_GR_EQ(val1, val2, msg) \
    _xTEST_MSG_GR_EQ   (xREPORT_TYPE, val1, val2, msg)
#define xTEST_MSG_PTR(ptr, msg) \
    _xTEST_MSG_PTR     (xREPORT_TYPE, ptr, msg)
#define xTEST_MSG_PTR_FAIL(ptr, msg) \
    _xTEST_MSG_PTR_FAIL(xREPORT_TYPE, ptr, msg)
#define xTEST_MSG_FAIL(msg) \
    _xTEST_MSG_FAIL    (xREPORT_TYPE, msg)
#define xTEST_MSG(expr, msg) \
    _xTEST_MSG_EQ      (xREPORT_TYPE, true, expr, msg)

#define xTEST_THROWS(expr, exception_t) \
    { \
        bool isExpected = false; \
        try { \
            expr; \
        } \
        catch (const exception_t &) { \
            isExpected = true; \
        } \
        catch (...) { \
        } \
        xTEST_EQ(isExpected, true); \
    }

#define xTEST_MSG_THROWS(expr, exception_t, msg) \
    { \
        bool isExpected = false; \
        try { \
            expr; \
        } \
        catch (const exception_t &) { \
            isExpected = true; \
        } \
        catch (...) { \
        } \
        xTEST_MSG_EQ(isExpected, msg); \
    }

#define xTEST_THROWS_ANYTHING(expr) \
    { \
        bool isExpected = false; \
        try { \
            expr; \
        } \
        catch (...) { \
            isExpected = true; \
        } \
        xTEST_EQ(isExpected, true); \
    }

#define xTEST_MSG_THROWS_ANYTHING(expr, msg) \
    { \
        bool isExpected = false; \
        try { \
            expr; \
        } \
        catch (...) { \
            isExpected = true; \
        } \
        xTEST_MSG_EQ(isExpected, msg); \
    }

#define xTEST_THROWS_NOTHING(expr) \
    { \
        bool isExpected = true; \
        try { \
            expr; \
        } \
        catch (...) { \
            isExpected = false; \
        } \
        xTEST_EQ(isExpected, true); \
    }

#define xTEST_MSG_THROWS_NOTHING(expr, msg) \
    { \
        bool isExpected = true; \
        try { \
            expr; \
        } \
        catch (...) { \
            isExpected = false; \
        } \
        xTEST_MSG_EQ(isExpected, msg); \
    }

#define xTEST_NA(var) \
    ;
    ///< at this point debug code for variable is not applicable
#define xTESTS_NA \
    ;
    ///< at this point debug code for variables is not applicable
//-------------------------------------------------------------------------------------------------
#define xTEST_STATIC(expr) \
    { switch (0) {case 0: case (expr):;} }
    ///< static assert

#define xTEST_CASE(caseName, loops) \
    CxTracer() << xT("\tCase name: ") << caseName; \
    for (size_t _caseLoops = 0U; _caseLoops < (loops); ++ _caseLoops)
    ///< test case
//-------------------------------------------------------------------------------------------------
#endif // xLib_xTestH
