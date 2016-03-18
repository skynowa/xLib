/**
 * \file  Test.h
 * \brief code testing
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#define xTEST_EQ_MSG_IMPL(reportType, val1, val2, msg) \
    if ( !((val1) == (val2)) ) { \
        culong_t    nativeError = NativeError::get(); \
        ErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xLEX_TO_STR(==), \
            nativeError, xSOURCE_INFO, StackTrace().toString(), (msg)); \
        Debugger().reportMake(report); \
    }
#define xTEST_DIFF_MSG_IMPL(reportType, val1, val2, msg) \
    if ( !((val1) != (val2)) ) { \
        culong_t    nativeError = NativeError::get(); \
        ErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xLEX_TO_STR(!=), \
            nativeError, xSOURCE_INFO, StackTrace().toString(), (msg)); \
        Debugger().reportMake(report); \
    }
#define xTEST_LESS_MSG_IMPL(reportType, val1, val2, msg) \
    if ( !((val1) < (val2)) ) { \
        culong_t    nativeError = NativeError::get(); \
        ErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xLEX_TO_STR(<), \
            nativeError, xSOURCE_INFO, StackTrace().toString(), (msg)); \
        Debugger().reportMake(report); \
    }
#define xTEST_GR_MSG_IMPL(reportType, val1, val2, msg) \
    if ( !((val1) > (val2)) ) { \
        culong_t    nativeError = NativeError::get(); \
        ErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xLEX_TO_STR(>), \
            nativeError, xSOURCE_INFO, StackTrace().toString(), (msg)); \
        Debugger().reportMake(report); \
    }
#define xTEST_LESS_EQ_MSG_IMPL(reportType, val1, val2, msg) \
    if ( !((val1) <= (val2)) ) { \
        culong_t    nativeError = NativeError::get(); \
        ErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xLEX_TO_STR(<=), \
            nativeError, xSOURCE_INFO, StackTrace().toString(), (msg)); \
        Debugger().reportMake(report); \
    }
#define xTEST_GR_EQ_MSG_IMPL(reportType, val1, val2, msg) \
    if ( !((val1) >= (val2)) ) { \
        culong_t    nativeError = NativeError::get(); \
        ErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xLEX_TO_STR(>=), \
            nativeError, xSOURCE_INFO, StackTrace().toString(), (msg)); \
        Debugger().reportMake(report); \
    }
#define xTEST_PTR_MSG_IMPL(reportType, ptr, msg) \
    if ( intptr_t(ptr) == intptr_t(xPTR_NULL) ) { \
        culong_t    nativeError = NativeError::get(); \
        ErrorReport report(reportType, xLEX_TO_STR(xPTR_NULL), xT(#ptr), intptr_t(ptr), \
            intptr_t(xPTR_NULL), xLEX_TO_STR(!=), nativeError, xSOURCE_INFO, \
            StackTrace().toString(), (msg)); \
        Debugger().reportMake(report); \
    }
#define xTEST_PTR_FAIL_MSG_IMPL(reportType, ptr, msg) \
    if ( intptr_t(ptr) != intptr_t(xPTR_NULL) ) { \
        culong_t    nativeError = NativeError::get(); \
        ErrorReport report(reportType, xLEX_TO_STR(xPTR_NULL), xT(#ptr), intptr_t(ptr), \
            intptr_t(xPTR_NULL), xLEX_TO_STR(==), nativeError, xSOURCE_INFO, \
            StackTrace().toString(), (msg)); \
        Debugger().reportMake(report); \
    }
#define xTEST_FAIL_MSG_IMPL(reportType, msg) \
    if ( true ) { \
        culong_t    nativeError = NativeError::get(); \
        ErrorReport report(reportType, xLEX_TO_STR(false), xT(""), xT(""), xT(""), xT(""), \
            nativeError, xSOURCE_INFO, StackTrace().toString(), (msg)); \
        Debugger().reportMake(report); \
    }

// _xREPORT_TYPE
#if   xOPTION_DEBUG_MODE_STDOUT
    #define _xREPORT_TYPE ErrorReport::rtStdout
#elif xOPTION_DEBUG_MODE_MSGBOX
    #define _xREPORT_TYPE ErrorReport::rtMsgbox
#elif xOPTION_DEBUG_MODE_LOG
    #define _xREPORT_TYPE ErrorReport::rtLog
#elif xOPTION_DEBUG_MODE_STDOUT_LOG
    #define _xREPORT_TYPE ErrorReport::rtStdoutLog
#endif

#ifdef _xREPORT_TYPE
    #define xTEST_EQ(val1, val2) \
        xTEST_EQ_MSG_IMPL      (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_EQ_MSG(val1, val2, msg) \
        xTEST_EQ_MSG_IMPL      (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_DIFF(val1, val2) \
        xTEST_DIFF_MSG_IMPL    (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_DIFF_MSG(val1, val2, msg) \
        xTEST_DIFF_MSG_IMPL    (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_LESS(val1, val2) \
        xTEST_LESS_MSG_IMPL    (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_LESS_MSG(val1, val2, msg) \
        xTEST_LESS_MSG_IMPL    (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_GR(val1, val2) \
        xTEST_GR_MSG_IMPL      (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_GR_MSG(val1, val2, msg) \
        xTEST_GR_MSG_IMPL      (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_LESS_EQ(val1, val2) \
        xTEST_LESS_EQ_MSG_IMPL (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_LESS_EQ_MSG(val1, val2, msg) \
        xTEST_LESS_EQ_MSG_IMPL (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_GR_EQ(val1, val2) \
        xTEST_GR_EQ_MSG_IMPL   (_xREPORT_TYPE, val1, val2, xT(""))
    #define xTEST_GR_EQ_MSG(val1, val2, msg) \
        xTEST_GR_EQ_MSG_IMPL   (_xREPORT_TYPE, val1, val2, msg)

    #define xTEST_PTR(ptr) \
        xTEST_PTR_MSG_IMPL     (_xREPORT_TYPE, ptr, xT(""))
    #define xTEST_PTR_MSG(ptr, msg) \
        xTEST_PTR_MSG_IMPL     (_xREPORT_TYPE, ptr, msg)

    #define xTEST_PTR_FAIL(ptr) \
        xTEST_PTR_FAIL_MSG_IMPL(_xREPORT_TYPE, ptr, xT(""))
    #define xTEST_PTR_FAIL_MSG(ptr, msg) \
        xTEST_PTR_FAIL_MSG_IMPL(_xREPORT_TYPE, ptr, msg)

    #define xTEST_FAIL \
        xTEST_FAIL_MSG_IMPL    (_xREPORT_TYPE, xT(""))
    #define xTEST_FAIL_MSG(msg) \
        xTEST_FAIL_MSG_IMPL    (_xREPORT_TYPE, msg)

    #define xTEST(expr) \
        xTEST_EQ_MSG_IMPL      (_xREPORT_TYPE, true, expr, xT(""))
    #define xTEST_MSG(expr, msg) \
        xTEST_EQ_MSG_IMPL      (_xREPORT_TYPE, true, expr, msg)

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
    #define xTEST_THROW_MSG(expr, exception_t, msg) \
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
            xTEST_EQ_MSG(isExpected, true, msg);    \
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
    #define xTEST_THROW_ALL_MSG(expr, msg)          \
        {                                           \
            bool_t isExpected = false;              \
            try {                                   \
                expr;                               \
            }                                       \
            catch (...) {                           \
                isExpected = true;                  \
            }                                       \
            xTEST_EQ_MSG(isExpected, true, msg);    \
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
    #define xTEST_THROW_NO_MSG(expr, msg)           \
        {                                           \
            bool_t isExpected = true;               \
            try {                                   \
                expr;                               \
            }                                       \
            catch (...) {                           \
                isExpected = false;                 \
            }                                       \
            xTEST_EQ_MSG(isExpected, true, msg);    \
        }
#else
    // just empty macros
    #define xTEST_EQ(val1, val2)
    #define xTEST_EQ_MSG(val1, val2, msg)

    #define xTEST_DIFF(val1, val2)
    #define xTEST_DIFF_MSG(val1, val2, msg)

    #define xTEST_LESS(val1, val2)
    #define xTEST_LESS_MSG(val1, val2, msg)

    #define xTEST_GR(val1, val2)
    #define xTEST_GR_MSG(val1, val2, msg)

    #define xTEST_LESS_EQ(val1, val2)
    #define xTEST_LESS_EQ_MSG(val1, val2, msg)

    #define xTEST_GR_EQ(val1, val2)
    #define xTEST_GR_EQ_MSG(val1, val2, msg)

    #define xTEST_PTR(ptr)
    #define xTEST_PTR_MSG(ptr, msg)

    #define xTEST_PTR_FAIL(ptr)
    #define xTEST_PTR_FAIL_MSG(ptr, msg)

    #define xTEST_FAIL
    #define xTEST_FAIL_MSG(msg)

    #define xTEST(expr)
    #define xTEST_MSG(expr, msg)

    #define xTEST_THROW(expr, exception_t)
    #define xTEST_THROW_MSG(expr, exception_t, msg)

    #define xTEST_THROW_ALL(expr)
    #define xTEST_THROW_ALL_MSG(expr, msg)

    #define xTEST_THROW_NO(expr)
    #define xTEST_THROW_NO_MSG(expr, msg)
#endif

#define xTEST_NA(var) \
    xUNUSED(var)
    ///< at this point debug code for variable is not applicable
#define xTESTS_NA \
    ;
    ///< at this point debug code for variables is not applicable

#define xTEST_STATIC(expr) \
    { switch (0) {case 0: case (expr):;} }
    ///< static assert

#if xOPTION_TEST_TRACING
    #define xTEST_CASE(caseName, loops) \
        if (loops == 0) { \
            Trace() << xT("\tCase: ") << xT(caseName) << xT(" - skipped"); \
        } else { \
            Trace() << xT("\tCase: ") << xT(caseName); \
        } \
        for (size_t _caseLoops = 0; _caseLoops < (loops); ++ _caseLoops)
#else
    #define xTEST_CASE(caseName, loops) \
        for (size_t _caseLoops = 0; _caseLoops < (loops); ++ _caseLoops)
#endif
    ///< test case

#define xTEST_UNIT(unitClassName) \
    int_t xTMAIN(int_t a_argsNum, tchar_t *a_args[]) \
    { \
        unitClassName unit; \
        unit.setName( xLEX_TO_STR(unitClassName) ); \
        unit.run(1, 1); \
        \
        return EXIT_SUCCESS; \
    }
//-------------------------------------------------------------------------------------------------
