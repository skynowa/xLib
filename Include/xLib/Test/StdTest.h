/**
 * \file   StdTest.h
 * \brief  test, using C library and STL
 */


#pragma once

// FreeBSD
#if defined(__FreeBSD__)
    #include <sys/sysctl.h>
#endif

// C library
#include <cerrno>
#include <ctime>
#include <cstring>

// STL
#include <string>
#include <iostream>
//-------------------------------------------------------------------------------------------------
///@name check condition
///@{
#define STD_CHECK_RET(expr, return_expr) \
    { if ((expr)) { return (return_expr); } }
    ///< check expression and return value
#define STD_CHECK_DO(expr, do_expr) \
    { if ((expr)) { do_expr; } }
    ///< check expression and do instructions
#define STD_CHECK_MSG(expr, comment) \
    { if ((expr)) { std::cout << (comment) << std::endl; } }
    ///< check expression and show message with comment
#define STD_CHECK_MSG_RET(expr, comment, return_expr) \
    { if ((expr)) { std::cout << (comment) << std::endl; return (return_expr); } }
    ///< check expression, show message with comment and return value
#define STD_CHECK_MSG_DO(expr, comment, do_expr) \
    { if ((expr)) { std::cout << (comment) << std::endl; do_expr; } }
    ///< check expression, show message with comment and do instructions
#define STD_CHECK_NA(var) \
    ;
    ///< at this point check code for variable is not applicable
#define STD_CHECKS_NA \
    ;
    ///< at this point check code for variables is not applicable
///@}
//-------------------------------------------------------------------------------------------------
///@name Trace variables (variable with value)
///@{
#define STD_TRACE_VAR(v1) \
    #v1 ": " << (v1)
#define STD_TRACE_VAR2(v1, v2) \
    STD_TRACE_VAR(v1) << ", " << STD_TRACE_VAR(v2)
#define STD_TRACE_VAR3(v1, v2, v3) \
    STD_TRACE_VAR2(v1, v2) << ", " << STD_TRACE_VAR(v3)
#define STD_TRACE_VAR4(v1, v2, v3, v4) \
    STD_TRACE_VAR3(v1, v2, v3) << ", " << STD_TRACE_VAR(v4)
#define STD_TRACE_VAR5(v1, v2, v3, v4, v5) \
    STD_TRACE_VAR4(v1, v2, v3, v4) << ", " << STD_TRACE_VAR(v5)
#define STD_TRACE_VAR6(v1, v2, v3, v4, v5, v6) \
    STD_TRACE_VAR5(v1, v2, v3, v4, v5) << ", " << STD_TRACE_VAR(v6)
#define STD_TRACE_VAR7(v1, v2, v3, v4, v5, v6, v7) \
    STD_TRACE_VAR6(v1, v2, v3, v4, v5, v6) << ", " << STD_TRACE_VAR(v7)
#define STD_TRACE_VAR8(v1, v2, v3, v4, v5, v6, v7, v8) \
    STD_TRACE_VAR7(v1, v2, v3, v4, v5, v6, v7) << ", " << STD_TRACE_VAR(v8)
#define STD_TRACE_VAR9(v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    STD_TRACE_VAR8(v1, v2, v3, v4, v5, v6, v7, v8) << ", " << STD_TRACE_VAR(v9)

#define STD_UNKNOWN_VAR(v) \
    "Unknown " << STD_TRACE_VAR(v)

#define STD_TRACE_PTR(p) \
    #p ": " << "{" << p << ", " << (p ? *p : 0) << "}"
///@}
//-------------------------------------------------------------------------------------------------
#define STD_TRACE_POINT \
    { \
        std::cout \
            << "\t::: " \
            << " in "      << __FILE__ \
            << ":"         << __LINE__ \
            << ", error: " << std::strerror(errno) \
            << " :::"      << std::endl; \
    }
    ///< trace point
#define STD_TRACE_FUNC \
    { \
        std::cout << "\t::: " << __FUNCTION__ << " :::" << std::endl; \
    }
    ///< trace function
#define STD_NOT_IMPLEMENTED \
    { \
        STD_TEST(false && "Not implemented"); \
    }
    ///< show not implemented message and return value
//-------------------------------------------------------------------------------------------------
#define STD_VERIFY(expr) \
    { \
        if ( !(expr) ) { \
            std::cout \
                << "\n" \
                << "------------------- STD_VERIFY -------------------" << "\n" \
                << " Module:     " << stdtest::modulePath()             << "\n" \
                << " Expression: " << #expr                             << "\n" \
                << " File:       " << __FILE__                          << "\n" \
                << " Function:   " << __FUNCTION__                      << "\n" \
                << " Line:       " << __LINE__                          << "\n" \
                << " Last error: " << std::strerror(errno)              << "\n" \
                << " Date time:  " << stdtest::currentDateTime()        << "\n" \
                << "--------------------------------------------------" << "\n" \
                << std::flush; \
            \
            (void)::exit(EXIT_FAILURE); \
        } \
    }
    ///< check expression (work in debug and release modes)
#define STD_TEST_DO(expr, do_expr) \
    { \
        if ( !(expr) ) { \
            std::cout \
                << "\n" \
                << "-------------------- STD_TEST --------------------" << "\n" \
                << " Module:     " << stdtest::modulePath()             << "\n" \
                << " Expression: " << #expr                             << "\n" \
                << " File:       " << __FILE__                          << "\n" \
                << " Function:   " << __FUNCTION__                      << "\n" \
                << " Line:       " << __LINE__                          << "\n" \
                << " Last error: " << std::strerror(errno)              << "\n" \
                << " Date time:  " << stdtest::currentDateTime()        << "\n" \
                << "--------------------------------------------------" << "\n" \
                << std::flush; \
            { \
                do_expr; \
            } \
        } \
    }
    ///< test macros
#define STD_TEST(expr) \
    STD_TEST_DO(expr, {})
    ///< test macros
#define STD_TEST_RET(expr, ret_expr) \
    STD_TEST_DO(expr, return ret_expr)
    ///< test macros

#define STD_TEST_PTR(expr) \
    STD_TEST_DO(expr != nullptr, {})
    ///< test macros
#define STD_TEST_PTR_DO(expr, do_expr) \
    STD_TEST_DO(expr != nullptr, do_expr)
    ///< test macros
#define STD_TEST_PTR_RET(expr, ret_expr) \
    STD_TEST_DO(expr != nullptr, return ret_expr)
    ///< test macros

#define STD_TEST_NA(expr) \
    ;
    ///< test macros
//-------------------------------------------------------------------------------------------------


namespace stdtest
{

//-------------------------------------------------------------------------------------------------
/**
 * current date/time, format is %Y-%m-%d.%X
 */
inline std::string
currentDateTime()
{
    std::string sRv;
    char        buff[80 + 1] {};
    time_t      timeNow      {std::time(nullptr)};
    std::tm    *timeLocal    {};

    timeLocal = std::localtime(&timeNow);
    if (timeLocal == nullptr) {
        return {};
    }

    size_t uiRv = std::strftime(buff, sizeof(buff) - 1, "%Y-%m-%d.%X", timeLocal);
    if (uiRv == 0) {
        return {};
    }

    sRv.assign(&buff[0], uiRv);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/**
 * Get module path
 */
inline std::string
modulePath()
{
    std::string srv;

#if defined(KERN_PROC_PATHNAME)
    const u_int mibSize            {4};
    int         mib[mibSize]       {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, - 1};
    char        buff[PATH_MAX + 1] {};
    std::size_t buffSize           {sizeof(buff) - 1};

    int iRv = ::sysctl(mib, mibSize, buff, &buffSize, nuulptr, 0U);
    if (iRv == - 1) {
        return "<unknown>";
    }

    srv.assign(buff);
#else
    srv = "<unknown>";
#endif

    return srv;
}
//-------------------------------------------------------------------------------------------------

} // stdtest
