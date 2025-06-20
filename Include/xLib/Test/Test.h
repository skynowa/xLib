/**
 * \file  Test.h
 * \brief code testing
 *
 * \libs
 *
 * - https://github.com/doctest/doctest
 * - https://github.com/google/fuzztest
 * - https://github.com/CxxTest/cxxtest
 * - https://github.com/smikes/CppUnitLite
 */


#pragma once

#ifndef XLIB_TEST_TEST_H
#define XLIB_TEST_TEST_H

//-------------------------------------------------------------------------------------------------
#if 0

namespace core
{

template<typename StreamT>
class FormatT;

}

namespace xl::debug
{

class ErrorReport;
class SourceInfoOption;
class SourceInfo;
class StackTrace;
class Debugger;

}

#endif
//-------------------------------------------------------------------------------------------------
#if 0
	#define xTEST_EQ_MSG_PRIVATE(op, val1, val2, msg) \
		if ( !((val1) op (val2)) ) { \
			culong_t         nativeError__ { NativeError::get() }; \
			\
			cSourceInfoOption sourceInfoOption__ \
			{ \
				xFILE, xLINE, xFUNCTION, xCOUNTER, \
				xT(#val1), xT(#val2), \
				Format::str(xT("{}"), val1), Format::str(xT("{}"), val2), \
				xLEX_TO_STR(op) \
			}; \
			\
			SourceInfo       sourceInfo__(sourceInfoOption__); \
			std::ctstring_t &stackTrace__ = StackTrace().str(); \
			\
			ErrorReport report__(nativeError__, sourceInfo__, stackTrace__, (msg)); \
			Debugger().reportMake(report__); \
		}
#else
	#define xTEST_EQ_MSG_PRIVATE(op, val1, val2, msg) \
		if ( !((val1) op (val2)) ) { \
			testEqMsg_impl( \
				NativeError::get(), \
				xFILE, \
				xLINE, \
				xFUNCTION, \
				xCOUNTER, \
				xT(#val1), \
				xT(#val2), \
				val1, \
				val2, \
				xLEX_TO_STR(op) \
				msg); \
		}
#endif

#if 0
	#define xTEST_PTR_MSG_PRIVATE(op, ptr, msg) \
		if ( !(ptr op nullptr) ) { \
			culong_t         nativeError__ { NativeError::get() }; \
			\
			cSourceInfoOption sourceInfoOption__ \
			{ \
				xFILE, xLINE, xFUNCTION, xCOUNTER, \
				xT(#ptr), xLEX_TO_STR(nullptr), \
				Format::str(xT("{}"), ptr), xT("nullptr"), \
				xLEX_TO_STR(op) \
			}; \
			\
			SourceInfo       sourceInfo__(sourceInfoOption__); \
			std::ctstring_t &stackTrace__ = StackTrace().str(); \
			\
			ErrorReport report__(nativeError__, sourceInfo__, stackTrace__, (msg)); \
			Debugger().reportMake(report__); \
		}
#else
	#define xTEST_PTR_MSG_PRIVATE(op, ptr, msg) {}
#endif

#define xTEST_EQ_MSG_IMPL(val1, val2, msg) \
	xTEST_EQ_MSG_PRIVATE(==, val1, val2, msg)
#define xTEST_DIFF_MSG_IMPL(val1, val2, msg) \
    xTEST_EQ_MSG_PRIVATE(!=, val1, val2, msg)
#define xTEST_LESS_MSG_IMPL(val1, val2, msg) \
	xTEST_EQ_MSG_PRIVATE(<,  val1, val2, msg)
#define xTEST_GR_MSG_IMPL(val1, val2, msg) \
	xTEST_EQ_MSG_PRIVATE(>,  val1, val2, msg)
#define xTEST_LESS_EQ_MSG_IMPL(val1, val2, msg) \
    xTEST_EQ_MSG_PRIVATE(<=, val1, val2, msg)
#define xTEST_GR_EQ_MSG_IMPL(val1, val2, msg) \
    xTEST_EQ_MSG_PRIVATE(>=, val1, val2, msg)

#define xTEST_PTR_MSG_IMPL(ptr, msg) \
	xTEST_PTR_MSG_PRIVATE(!=, ptr, msg)
#define xTEST_PTR_FAIL_MSG_IMPL(ptr, msg) \
	xTEST_PTR_MSG_PRIVATE(==, ptr, msg)

#if 0
	#define xTEST_FAIL_MSG_IMPL(msg) \
		if (true) { \
			culong_t          nativeError__ { NativeError::get() }; \
			cSourceInfoOption sourceInfoOption__ {xFILE, xLINE, xFUNCTION, xCOUNTER, \
				xLEX_TO_STR(false), {}, {}, {}, {}}; \
			SourceInfo        sourceInfo__(sourceInfoOption__); \
			std::ctstring_t  &stackTrace__ = StackTrace().str(); \
			\
			ErrorReport report__(nativeError__, sourceInfo__, stackTrace__, (msg)); \
			Debugger().reportMake(report__); \
		}
#else
	#define xTEST_FAIL_MSG_IMPL(msg) \
		if (true) { \
			testEqMsg_impl( \
				NativeError::get(), \
				xFILE, \
				xLINE, \
				xFUNCTION, \
				xCOUNTER, \
				{}, \
				{}, \
				{}, \
				{}, \
				"false" \
				msg); \
		}
#endif

#define xTEST_EQ(val1, val2) \
	xTEST_EQ_MSG_IMPL      (val1, val2, xT(""))
#define xTEST_EQ_MSG(val1, val2, msg) \
	xTEST_EQ_MSG_IMPL      (val1, val2, msg)

#define xTEST_DIFF(val1, val2) \
	xTEST_DIFF_MSG_IMPL    (val1, val2, xT(""))
#define xTEST_DIFF_MSG(val1, val2, msg) \
	xTEST_DIFF_MSG_IMPL    (val1, val2, msg)

#define xTEST_LESS(val1, val2) \
	xTEST_LESS_MSG_IMPL    (val1, val2, xT(""))
#define xTEST_LESS_MSG(val1, val2, msg) \
	xTEST_LESS_MSG_IMPL    (val1, val2, msg)

#define xTEST_GR(val1, val2) \
	xTEST_GR_MSG_IMPL      (val1, val2, xT(""))
#define xTEST_GR_MSG(val1, val2, msg) \
	xTEST_GR_MSG_IMPL      (val1, val2, msg)

#define xTEST_LESS_EQ(val1, val2) \
	xTEST_LESS_EQ_MSG_IMPL (val1, val2, xT(""))
#define xTEST_LESS_EQ_MSG(val1, val2, msg) \
	xTEST_LESS_EQ_MSG_IMPL (val1, val2, msg)

#define xTEST_GR_EQ(val1, val2) \
	xTEST_GR_EQ_MSG_IMPL   (val1, val2, xT(""))
#define xTEST_GR_EQ_MSG(val1, val2, msg) \
	xTEST_GR_EQ_MSG_IMPL   (val1, val2, msg)

#define xTEST_PTR(ptr) \
	xTEST_PTR_MSG_IMPL     (ptr, xT(""))
#define xTEST_PTR_MSG(ptr, msg) \
	xTEST_PTR_MSG_IMPL     (ptr, msg)

#define xTEST_PTR_FAIL(ptr) \
	xTEST_PTR_FAIL_MSG_IMPL(ptr, xT(""))
#define xTEST_PTR_FAIL_MSG(ptr, msg) \
	xTEST_PTR_FAIL_MSG_IMPL(ptr, msg)

#define xTEST_FAIL \
	xTEST_FAIL_MSG_IMPL    (xT(""))
#define xTEST_FAIL_MSG(msg) \
	xTEST_FAIL_MSG_IMPL    (msg)

#define xTEST(expr) \
	xTEST_EQ_MSG_IMPL      (expr, true, xT(""))
#define xTEST_MSG(expr, msg) \
	xTEST_EQ_MSG_IMPL      (expr, true, msg)

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
		xTEST(isExpected);                      \
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
		xTEST(isExpected);                      \
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
		xTEST(isExpected);                      \
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

#define xTEST_NA(var) \
    xUNUSED(var)
    ///< at this point debug code for variable is not applicable
#define xTESTS_NA \
    ;
    ///< at this point debug code for variables is not applicable

#define xTEST_GROUP(groupName) \
	LogCout() << xT("\n\t[") << xT(groupName) << xT("]")
	///< test group of cases

#define xTEST_CASE(caseName) \
	LogCout() << xT("\tCase: ") << xT(caseName); \
	for (size_t caseLoops = 0; caseLoops < option().caseLoops; ++ caseLoops)
    ///< test case

#define xTEST_UNIT(unitClassName) \
	using namespace xl; \
	\
	class unitClassName : \
		public Unit \
	{ \
	public: \
		unitClassName(const UnitOption &a_option) : \
			Unit(a_option) \
		{ \
		} \
		\
	   ~unitClassName() = default; \
		\
		bool_t unit() final; \
	}; \
	\
    int_t xTMAIN(int_t a_argsNum, tchar_t *a_args[]) \
    { \
        xUNUSED(a_argsNum); \
        xUNUSED(a_args); \
        \
        bool_t bRv {}; \
        \
        UnitOption unitOption; \
        unitOption.name        = xLEX_TO_STR(unitClassName); \
        unitOption.unitLoops   = 1; \
        unitOption.caseLoops   = 1; \
        unitOption.testDirPath = cmXLIB_DATA_DIR; \
        unitOption.tempDirPath = {}; \
        \
        unitClassName unit(unitOption); \
        \
        try {  \
            bRv = unit.run(); \
        } \
        catch (const xl::debug::Exception &a_xlibException) { \
            LogCout() << a_xlibException.what(); \
            bRv = false; \
        } \
        catch (const std::exception &a_stdException) { \
            LogCout() << a_stdException.what(); \
            bRv = false; \
        } \
        catch (...) { \
            LogCout() << xT("Unknown error"); \
            bRv = false; \
        } \
        \
        return bRv ? EXIT_SUCCESS : EXIT_FAILURE; \
    }
//-------------------------------------------------------------------------------------------------
// REVIEW: xSTD_VERIFY
#define xSTD_VERIFY(expr) \
    { \
        if ( !(expr) ) { \
            std::cout \
                << "[xSTD_VERIFY] " << __FILE__ << ": " << __LINE__ << ", " \
                << __FUNCTION__ << ": (" << #expr << ")" << std::endl; \
        } \
    }
//-------------------------------------------------------------------------------------------------
#include <xLib/Test/TestMsg.cpp>
//-------------------------------------------------------------------------------------------------
#endif

//-------------------------------------------------------------------------------------------------
/**
 * \file  Test.h
 *
 * \todo
 *
 * - [ ] xTEST_EQ_MSG_PRIVATE impl - as function
 */
//-------------------------------------------------------------------------------------------------
