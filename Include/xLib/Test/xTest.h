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
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT("=="), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_DIFF(reportType, val1, val2, msg) \
    if ( !((val1) != (val2)) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT("!="), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_LESS(reportType, val1, val2, msg) \
    if ( !((val1) < (val2)) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT("<"), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_GR(reportType, val1, val2, msg) \
    if ( !((val1) > (val2)) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT(">"), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_LESS_EQ(reportType, val1, val2, msg) \
    if ( !((val1) <= (val2)) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT("<="), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_GR_EQ(reportType, val1, val2, msg) \
    if ( !((val1) >= (val2)) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT(">="), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_PTR(reportType, ptr, msg) \
    if ( intptr_t(NULL) == intptr_t(ptr) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT("NULL"), xT(#ptr), intptr_t(ptr), intptr_t(NULL), \
            xT("!="), _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, \
            CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_PTR_FAIL(reportType, ptr, msg) \
    if ( intptr_t(NULL) != intptr_t(ptr) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT("NULL"), xT(#ptr), intptr_t(ptr), intptr_t(NULL), \
            xT("=="), _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, \
            CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define _xTEST_MSG_FAIL(reportType, msg) \
    if ( true ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT("false"), xT(""), xT(""), xT(""), xT(""), \
            _lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, \
            CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }

// _xREPORT_TYPE
#if   xDEBUG_MODE_STDOUT
    #define _xREPORT_TYPE CxErrorReport::rtStdout
#elif xDEBUG_MODE_MSGBOX
    #define _xREPORT_TYPE CxErrorReport::rtMsgbox
#elif xDEBUG_MODE_LOG
    #define _xREPORT_TYPE CxErrorReport::rtLog
#endif

#ifdef _xREPORT_TYPE
    #define xTEST_EQ(val1, val2) \
        _xTEST_MSG_EQ      (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_MSG_EQ(val1, val2, msg) \
        _xTEST_MSG_EQ      (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_DIFF(val1, val2) \
        _xTEST_MSG_DIFF    (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_MSG_DIFF(val1, val2, msg) \
        _xTEST_MSG_DIFF    (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_LESS(val1, val2) \
        _xTEST_MSG_LESS    (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_MSG_LESS(val1, val2, msg) \
        _xTEST_MSG_LESS    (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_GR(val1, val2) \
        _xTEST_MSG_GR      (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_MSG_GR(val1, val2, msg) \
        _xTEST_MSG_GR      (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_LESS_EQ(val1, val2) \
        _xTEST_MSG_LESS_EQ (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_MSG_LESS_EQ(val1, val2, msg) \
        _xTEST_MSG_LESS_EQ (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_GR_EQ(val1, val2) \
        _xTEST_MSG_GR_EQ   (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_MSG_GR_EQ(val1, val2, msg) \
        _xTEST_MSG_GR_EQ   (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_PTR(ptr) \
        _xTEST_MSG_PTR     (_xREPORT_TYPE, ptr, xT(""))
    #define xTEST_MSG_PTR(ptr, msg) \
        _xTEST_MSG_PTR     (_xREPORT_TYPE, ptr, msg)

    #define xTEST_PTR_FAIL(ptr) \
        _xTEST_MSG_PTR_FAIL(_xREPORT_TYPE, ptr, xT(""))
    #define xTEST_MSG_PTR_FAIL(ptr, msg) \
        _xTEST_MSG_PTR_FAIL(_xREPORT_TYPE, ptr, msg)

    #define xTEST_FAIL \
        _xTEST_MSG_FAIL    (_xREPORT_TYPE, xT(""))
    #define xTEST_MSG_FAIL(msg) \
        _xTEST_MSG_FAIL    (_xREPORT_TYPE, msg)

    #define xTEST(expr) \
        _xTEST_MSG_EQ      (_xREPORT_TYPE, true, expr, xT(""))
    #define xTEST_MSG(expr, msg) \
        _xTEST_MSG_EQ      (_xREPORT_TYPE, true, expr, msg)

    #define xTEST_THROW(expr, exception_t)          \
        {                                           \
            bool_t isExpected = false;              \
            try {                                   \
                expr;                               \
            }                                       \
            catch (const exception_t &) {           \
                isExpected = true;                  \
            }                                       \
            catch (...) {                           \
            }                                       \
            xTEST_EQ(isExpected, true);             \
        }
    #define xTEST_MSG_THROW(expr, exception_t, msg) \
        {                                           \
            bool_t isExpected = false;              \
            try {                                   \
                expr;                               \
            }                                       \
            catch (const exception_t &) {           \
                isExpected = true;                  \
            }                                       \
            catch (...) {                           \
            }                                       \
            xTEST_MSG_EQ(isExpected, true, msg);    \
        }

    #define xTEST_THROW_ALL(expr)                   \
        {                                           \
            bool_t isExpected = false;              \
            try {                                   \
                expr;                               \
            }                                       \
            catch (...) {                           \
                isExpected = true;                  \
            }                                       \
            xTEST_EQ(isExpected, true);             \
        }
    #define xTEST_MSG_THROW_ALL(expr, msg)          \
        {                                           \
            bool_t isExpected = false;              \
            try {                                   \
                expr;                               \
            }                                       \
            catch (...) {                           \
                isExpected = true;                  \
            }                                       \
            xTEST_MSG_EQ(isExpected, true, msg);    \
        }

    #define xTEST_THROW_NO(expr)                    \
        {                                           \
            bool_t isExpected = true;               \
            try {                                   \
                expr;                               \
            }                                       \
            catch (...) {                           \
                isExpected = false;                 \
            }                                       \
            xTEST_EQ(isExpected, true);             \
        }
    #define xTEST_MSG_THROW_NO(expr, msg)           \
        {                                           \
            bool_t isExpected = true;               \
            try {                                   \
                expr;                               \
            }                                       \
            catch (...) {                           \
                isExpected = false;                 \
            }                                       \
            xTEST_MSG_EQ(isExpected, true, msg);    \
        }
#else
    // just empty macros
    #define xTEST_EQ(val1, val2)
    #define xTEST_MSG_EQ(val1, val2, msg)

    #define xTEST_DIFF(val1, val2)
    #define xTEST_MSG_DIFF(val1, val2, msg)

    #define xTEST_LESS(val1, val2)
    #define xTEST_MSG_LESS(val1, val2, msg)

    #define xTEST_GR(val1, val2)
    #define xTEST_MSG_GR(val1, val2, msg)

    #define xTEST_LESS_EQ(val1, val2)
    #define xTEST_MSG_LESS_EQ(val1, val2, msg)

    #define xTEST_GR_EQ(val1, val2)
    #define xTEST_MSG_GR_EQ(val1, val2, msg)

    #define xTEST_PTR(ptr)
    #define xTEST_MSG_PTR(ptr, msg)

    #define xTEST_PTR_FAIL(ptr)
    #define xTEST_MSG_PTR_FAIL(ptr, msg)

    #define xTEST_FAIL
    #define xTEST_MSG_FAIL(msg)

    #define xTEST(expr)
    #define xTEST_MSG(expr, msg)

    #define xTEST_THROW(expr, exception_t)
    #define xTEST_MSG_THROW(expr, exception_t, msg)

    #define xTEST_THROW_ALL(expr)
    #define xTEST_MSG_THROW_ALL(expr, msg)

    #define xTEST_THROW_NO(expr)
    #define xTEST_MSG_THROW_NO(expr, msg)
#endif

#define xTEST_NA(var) \
    ;
    ///< at this point debug code for variable is not applicable
#define xTESTS_NA \
    ;
    ///< at this point debug code for variables is not applicable

#define xTEST_STATIC(expr) \
    { switch (0) {case 0: case (expr):;} }
    ///< static assert

#if xTEST_TRACING
    #define xTEST_CASE(caseName, loops) \
        CxTrace() << xT("\tCase name: ") << xT(caseName); \
        for (size_t _caseLoops = 0; _caseLoops < (loops); ++ _caseLoops)
#else
    #define xTEST_CASE(caseName, loops) \
        for (size_t _caseLoops = 0; _caseLoops < (loops); ++ _caseLoops)
#endif
    ///< test case
//-------------------------------------------------------------------------------------------------
#endif // xLib_xTestH
