/**
 * \file  Test.h
 * \brief code testing
 */


#pragma once

//-------------------------------------------------------------------------------------------------
// _xREPORT_TYPE
#if   cmOPTION_DEBUG_MODE_STDOUT
    #define _xREPORT_TYPE ErrorReport::Type::Stdout
#elif cmOPTION_DEBUG_MODE_MSGBOX
    #define _xREPORT_TYPE ErrorReport::Type::Msgbox
#elif cmOPTION_DEBUG_MODE_LOG
    #define _xREPORT_TYPE ErrorReport::Type::Log
#elif cmOPTION_DEBUG_MODE_STDOUT_LOG
    #define _xREPORT_TYPE ErrorReport::Type::StdoutLog
#elif cmOPTION_DEBUG_MODE_EXCEPTION
    #define _xREPORT_TYPE ErrorReport::Type::Exception
#endif
//-------------------------------------------------------------------------------------------------
#define xTEST_EQ_MSG_PRIVATE(op, reportType, val1, val2, msg) \
	if ( !((val1) op (val2)) ) { \
		culong_t         nativeError    { NativeError::get() }; \
		cSourceInfoData  sourceInfoData {xFILE, xLINE, xFUNCTION, xCOUNTER}; \
		SourceInfo       sourceInfo(sourceInfoData); \
		std::ctstring_t &stackTrace     = StackTrace().str(); \
		\
		ErrorReport report(reportType, xT(#val1), xT(#val2), (val1), (val2), xLEX_TO_STR(op), \
			nativeError, sourceInfo, stackTrace, (msg)); \
		Debugger().reportMake(report); \
	}

#define xTEST_PTR_MSG_PRIVATE(op, reportType, ptr, msg) \
    if ( !(intptr_t(ptr) op intptr_t(nullptr)) ) { \
        culong_t         nativeError    { NativeError::get() }; \
        cSourceInfoData  sourceInfoData {xFILE, xLINE, xFUNCTION, xCOUNTER}; \
        SourceInfo       sourceInfo(sourceInfoData); \
        std::ctstring_t &stackTrace     = StackTrace().str(); \
        \
        ErrorReport report(reportType, xT(#ptr), xLEX_TO_STR(nullptr), intptr_t(ptr), \
            intptr_t(nullptr), xLEX_TO_STR(op), nativeError, sourceInfo, stackTrace, (msg)); \
        Debugger().reportMake(report); \
    }

#define xTEST_EQ_MSG_IMPL(reportType, val1, val2, msg) \
	xTEST_EQ_MSG_PRIVATE(==, reportType, val1, val2, msg)
#define xTEST_DIFF_MSG_IMPL(reportType, val1, val2, msg) \
    xTEST_EQ_MSG_PRIVATE(!=, reportType, val1, val2, msg)
#define xTEST_LESS_MSG_IMPL(reportType, val1, val2, msg) \
	xTEST_EQ_MSG_PRIVATE(<,  reportType, val1, val2, msg)
#define xTEST_GR_MSG_IMPL(reportType, val1, val2, msg) \
	xTEST_EQ_MSG_PRIVATE(>,  reportType, val1, val2, msg)
#define xTEST_LESS_EQ_MSG_IMPL(reportType, val1, val2, msg) \
    xTEST_EQ_MSG_PRIVATE(<=, reportType, val1, val2, msg)
#define xTEST_GR_EQ_MSG_IMPL(reportType, val1, val2, msg) \
    xTEST_EQ_MSG_PRIVATE(>=, reportType, val1, val2, msg)

#define xTEST_PTR_MSG_IMPL(reportType, ptr, msg) \
	xTEST_PTR_MSG_PRIVATE(!=, reportType, ptr, msg)
#define xTEST_PTR_FAIL_MSG_IMPL(reportType, ptr, msg) \
	xTEST_PTR_MSG_PRIVATE(==, reportType, ptr, msg)

#define xTEST_FAIL_MSG_IMPL(reportType, msg) \
    if (true) { \
        culong_t         nativeError    { NativeError::get() }; \
        cSourceInfoData  sourceInfoData {xFILE, xLINE, xFUNCTION, xCOUNTER}; \
        SourceInfo       sourceInfo(sourceInfoData); \
        std::ctstring_t &stackTrace     = StackTrace().str(); \
        \
        ErrorReport report(reportType, xLEX_TO_STR(false), xT(""), xT(""), xT(""), xT(""), \
            nativeError, sourceInfo, stackTrace, (msg)); \
        Debugger().reportMake(report); \
    }

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

#define xTEST_NA(var) \
    xUNUSED(var)
    ///< at this point debug code for variable is not applicable
#define xTESTS_NA \
    ;
    ///< at this point debug code for variables is not applicable

#define xTEST_CASE(caseName) \
	Trace() << xT("\tCase: ") << xT(caseName); \
	for (size_t caseLoops = 0; caseLoops < getData().caseLoops; ++ caseLoops)
    ///< test case

#define xTEST_UNIT(unitClassName) \
	using namespace xl; \
	\
	class unitClassName : \
		public Unit \
	{ \
	public: \
			   unitClassName() = default; \
			  ~unitClassName() = default; \
		bool_t unit() override; \
	}; \
	\
    int_t xTMAIN(int_t a_argsNum, tchar_t *a_args[]) \
    { \
        xUNUSED(a_argsNum); \
        xUNUSED(a_args); \
        \
        bool_t bRv {}; \
        \
        UnitData unitData; \
        unitData.name        = xLEX_TO_STR(unitClassName); \
        unitData.unitLoops   = 1; \
        unitData.caseLoops   = 1; \
        unitData.testDirPath = cmXLIB_DATA_DIR xT("/Tests"); \
        unitData.tempDirPath = {}; \
        \
        unitClassName unit; \
        unit.setData(unitData); \
        \
        try {  \
            bRv = unit.run(); \
        } \
        catch (const xl::debug::Exception &a_xlibException) { \
            Trace() << a_xlibException.what(); \
            bRv = false; \
        } \
        catch (const std::exception &a_stdException) { \
            Trace() << a_stdException.what(); \
            bRv = false; \
        } \
        catch (...) { \
            Trace() << xT("Unknown error"); \
            bRv = false; \
        } \
        \
        return bRv ? EXIT_SUCCESS : EXIT_FAILURE; \
    }
//-------------------------------------------------------------------------------------------------
// TODO: STD_VERIFY - fix
#define STD_VERIFY(x) \
    assert(x)
