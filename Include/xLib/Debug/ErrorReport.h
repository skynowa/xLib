/**
 * \file  ErrorReport.h
 * \brief debug report
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Debug/SourceInfo.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, debug)

class SourceInfo;

class ErrorReport
    /// debug report
{
public:
    enum ExType
        /// type
    {
        rtUnknown,  ///< unknown
        rtMsgbox,   ///< as message box
        rtStdout,   ///< to std::cout
        rtLog,      ///< to log
        rtStdoutLog,///< to std::cout and log
        rtException ///< to exception
    };
    xTYPEDEF_CONST(ExType);

                   ErrorReport(culong_t &nativeError, const SourceInfo &sourceInfo,
                       std::ctstring_t &stackTrace, std::ctstring_t &comment);
        ///< constructor (for Exception)
                   template<class T>
                   ErrorReport(cExType &type, std::ctstring_t &var1, std::ctstring_t &var2,
                       const T &var1ValueT, const T &var2ValueT, std::ctstring_t &exprSign,
                       culong_t &nativeError, const SourceInfo &sourceInfo,
                       std::ctstring_t &stackTrace, std::ctstring_t &comment);
        ///< constructor (for Debugger)
    virtual       ~ErrorReport() {}
        ///< destructor

    ExType         type() const;
        ///< report type
    std::ctstring_t & toString() const;
        ///< report message

private:
    ExType         _type;           ///< report type
    std::tstring_t _report;         ///< report message

    // exe
    std::tstring_t _program;        ///< program name
    ulong_t        _processId;      ///< current process id
    ulong_t        _threadId;       ///< current thread id
    std::tstring_t _fileSize;       ///< file size

    // source
    std::tstring_t _sourceFilePath; ///< source file path
    ulong_t        _sourceLineNum;  ///< source file number
    std::tstring_t _sourceFuncName; ///< source function name
    std::tstring_t _sourceExpr;     ///< source expression

    ulong_t        _nativeError;    ///< system last error
    std::tstring_t _nativeErrorStr; ///< system last error as string

    // other
    std::tstring_t _currentDate;    ///< current date, time

#if xENV_UNIX
    std::tstring_t _glibc;          ///< GLIBC available on the system
    std::tstring_t _libPthread;     ///< POSIX implementation supplied by C library
#endif
    std::tstring_t _stackTrace;     ///< stack trace

    // comment
    std::tstring_t _comment;        ///< comment

    void_t         _construct(cExType &type, const SourceInfo &sourceInfo,
                       std::ctstring_t &var1, std::ctstring_t &var2, std::ctstring_t &var1Value,
                       std::ctstring_t &var2Value, std::ctstring_t &exprSign, culong_t &nativeError,
                       std::ctstring_t &stackTrace, std::ctstring_t &comment);
        ///< initiate class members
    void_t         _initPlain();
        ///< initiate plain report

    xNO_COPY_ASSIGN(ErrorReport)
};

xNAMESPACE_END2(xlib, debug)
//-------------------------------------------------------------------------------------------------
#include "ErrorReport.inl"

#if xOPTION_PROJECT_HEADER_ONLY
    #include "ErrorReport.cpp"
#endif

