/**
 * \file  xTest.h
 * \brief code testing
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#define xTEST_MSG_EQ_IMPL(reportType, val1, val2, msg) \
    if ( !((val1) == (val2)) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT("=="), \
            _lastError, xFILE, xLINE, xFUNCTION, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define xTEST_MSG_DIFF_IMPL(reportType, val1, val2, msg) \
    if ( !((val1) != (val2)) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT("!="), \
            _lastError, xFILE, xLINE, xFUNCTION, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define xTEST_MSG_LESS_IMPL(reportType, val1, val2, msg) \
    if ( !((val1) < (val2)) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT("<"), \
            _lastError, xFILE, xLINE, xFUNCTION, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define xTEST_MSG_GR_IMPL(reportType, val1, val2, msg) \
    if ( !((val1) > (val2)) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT(">"), \
            _lastError, xFILE, xLINE, xFUNCTION, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define xTEST_MSG_LESS_EQ_IMPL(reportType, val1, val2, msg) \
    if ( !((val1) <= (val2)) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT("<="), \
            _lastError, xFILE, xLINE, xFUNCTION, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define xTEST_MSG_GR_EQ_IMPL(reportType, val1, val2, msg) \
    if ( !((val1) >= (val2)) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xT(">="), \
            _lastError, xFILE, xLINE, xFUNCTION, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define xTEST_MSG_PTR_IMPL(reportType, ptr, msg) \
    if ( intptr_t(xPTR_NULL) == intptr_t(ptr) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT("xPTR_NULL"), xT(#ptr), intptr_t(ptr), intptr_t(xPTR_NULL), \
            xT("!="), _lastError, xFILE, xLINE, xFUNCTION, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define xTEST_MSG_PTR_FAIL_IMPL(reportType, ptr, msg) \
    if ( intptr_t(xPTR_NULL) != intptr_t(ptr) ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT("xPTR_NULL"), xT(#ptr), intptr_t(ptr), intptr_t(xPTR_NULL), \
            xT("=="), _lastError, xFILE, xLINE, xFUNCTION, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }
#define xTEST_MSG_FAIL_IMPL(reportType, msg) \
    if ( true ) { \
        culong_t      _lastError = CxLastError::get(); \
        CxErrorReport report(reportType, xT("false"), xT(""), xT(""), xT(""), xT(""), \
            _lastError, xFILE, xLINE, xFUNCTION, CxStackTrace().toString(), (msg)); \
        CxDebugger().reportMake(report); \
    }

// _xREPORT_TYPE
#if   xHAVE_DEBUG_MODE_STDOUT
    #define _xREPORT_TYPE CxErrorReport::rtStdout
#elif xHAVE_DEBUG_MODE_MSGBOX
    #define _xREPORT_TYPE CxErrorReport::rtMsgbox
#elif xHAVE_DEBUG_MODE_LOG
    #define _xREPORT_TYPE CxErrorReport::rtLog
#endif

#ifdef _xREPORT_TYPE
    #define xTEST_EQ(val1, val2) \
        xTEST_MSG_EQ_IMPL      (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_MSG_EQ(val1, val2, msg) \
        xTEST_MSG_EQ_IMPL      (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_DIFF(val1, val2) \
        xTEST_MSG_DIFF_IMPL    (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_MSG_DIFF(val1, val2, msg) \
        xTEST_MSG_DIFF_IMPL    (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_LESS(val1, val2) \
        xTEST_MSG_LESS_IMPL    (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_MSG_LESS(val1, val2, msg) \
        xTEST_MSG_LESS_IMPL    (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_GR(val1, val2) \
        xTEST_MSG_GR_IMPL      (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_MSG_GR(val1, val2, msg) \
        xTEST_MSG_GR_IMPL      (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_LESS_EQ(val1, val2) \
        xTEST_MSG_LESS_EQ_IMPL (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_MSG_LESS_EQ(val1, val2, msg) \
        xTEST_MSG_LESS_EQ_IMPL (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_GR_EQ(val1, val2) \
        xTEST_MSG_GR_EQ_IMPL   (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_MSG_GR_EQ(val1, val2, msg) \
        xTEST_MSG_GR_EQ_IMPL   (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_PTR(ptr) \
        xTEST_MSG_PTR_IMPL     (_xREPORT_TYPE, ptr, xT(""))
    #define xTEST_MSG_PTR(ptr, msg) \
        xTEST_MSG_PTR_IMPL     (_xREPORT_TYPE, ptr, msg)

    #define xTEST_PTR_FAIL(ptr) \
        xTEST_MSG_PTR_FAIL_IMPL(_xREPORT_TYPE, ptr, xT(""))
    #define xTEST_MSG_PTR_FAIL(ptr, msg) \
        xTEST_MSG_PTR_FAIL_IMPL(_xREPORT_TYPE, ptr, msg)

    #define xTEST_FAIL \
        xTEST_MSG_FAIL_IMPL    (_xREPORT_TYPE, xT(""))
    #define xTEST_MSG_FAIL(msg) \
        xTEST_MSG_FAIL_IMPL    (_xREPORT_TYPE, msg)

    #define xTEST(expr) \
        xTEST_MSG_EQ_IMPL      (_xREPORT_TYPE, true, expr, xT(""))
    #define xTEST_MSG(expr, msg) \
        xTEST_MSG_EQ_IMPL      (_xREPORT_TYPE, true, expr, msg)

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

#if xHAVE_TEST_TRACING
    #define xTEST_CASE(caseName, loops) \
        if (loops == 0) { \
            CxTrace() << xT("\tTest case: ") << xT(caseName) << xT(" - skipped"); \
        } else { \
            CxTrace() << xT("\tTest case: ") << xT(caseName); \
        } \
        for (size_t _caseLoops = 0; _caseLoops < (loops); ++ _caseLoops)
#else
    #define xTEST_CASE(caseName, loops) \
        for (size_t _caseLoops = 0; _caseLoops < (loops); ++ _caseLoops)
#endif
    ///< test case
//-------------------------------------------------------------------------------------------------
