/**
 * \file  ErrorReport.h
 * \brief debug report
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Debug/SourceInfo.h>
//-------------------------------------------------------------------------------------------------
namespace xl::debug
{

class SourceInfo;

class ErrorReport
    /// debug report
{
public:
    enum class Type
        /// type
    {
        Unknown,  ///< unknown
        Msgbox,   ///< as message box
        Stdout,   ///< to std::cout
        Log,      ///< to log
        StdoutLog,///< to std::cout and log
        Exception ///< to exception
    };
    xUSING_CONST(Type);

///@name ctors, dtor
///@{
             ErrorReport(culong_t nativeError, const SourceInfo &sourceInfo,
                 std::ctstring_t &stackTrace, std::ctstring_t &comment);
        ///< for Exception
             template<typename T>
             ErrorReport(cType type, std::ctstring_t &var1, std::ctstring_t &var2,
                 const T &var1ValueT, const T &var2ValueT, std::ctstring_t &exprSign,
                 culong_t nativeError, const SourceInfo &sourceInfo, std::ctstring_t &stackTrace,
                 std::ctstring_t &comment);
        ///< for Debugger
    virtual ~ErrorReport() = default;

	xNO_DEFAULT_CONSTRUCT(ErrorReport)
    xNO_COPY_ASSIGN(ErrorReport)
///@}

    Type           type() const;
        ///< report type
    std::ctstring_t & str() const;
        ///< report message

private:
    Type           _type {Type::Unknown}; ///< report type
    std::tstring_t _report;           ///< report message

    // exe
    std::tstring_t _program;          ///< program name
    ulong_t        _processId {};     ///< current process id
    ulong_t        _threadId {};      ///< current thread id

    // source
    std::tstring_t _sourceFilePath;   ///< source file path
    ulong_t        _sourceLineNum {}; ///< source file number
    std::tstring_t _sourceFuncName;   ///< source function name
    std::tstring_t _sourceExpr;       ///< source expression
    std::tstring_t _sourceExprValues; ///< source expression values
    ulong_t        _nativeError {};   ///< system last error
    std::tstring_t _nativeErrorStr;   ///< system last error as string

    // other
    std::tstring_t _currentDate;      ///< current date, time
    std::tstring_t _stackTrace;       ///< stack trace

    // comment
    std::tstring_t _comment;          ///< comment

    void_t _construct(cType type, const SourceInfo &sourceInfo,
                std::ctstring_t &var1, std::ctstring_t &var2, std::ctstring_t &var1Value,
                std::ctstring_t &var2Value, std::ctstring_t &exprSign, culong_t &nativeError,
                std::ctstring_t &stackTrace, std::ctstring_t &comment);
        ///< initiate class members
    void_t _initPlain();
        ///< initiate plain report
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "ErrorReport.inl"
//-------------------------------------------------------------------------------------------------
// TODO: https://abseil.io/docs/cpp/guides/status
