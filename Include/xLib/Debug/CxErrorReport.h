/**
 * \file  CxErrorReport.h
 * \brief debug report
 */


#pragma once

#ifndef xLib_CxErrorReportH
#define xLib_CxErrorReportH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxErrorReport
    /// debug report
{
public:
    enum ExType
        /// type
    {
        rtUnknown,      ///< unknown
        rtMsgboxPlain,  ///< as message box with plain text (GUI)
        rtStdoutPlain,  ///< to std::cout with plain text
        rtLoggingPlain, ///< to log with plain text
    };

                   template<class T>
                   CxErrorReport(const ExType &type, std::ctstring_t &var1, std::ctstring_t &var2,
                       const T &var1ValueT, const T &var2ValueT, std::ctstring_t &exprSign,
                       culong_t &lastError, std::ctstring_t &file, culong_t &line,
                       std::ctstring_t &func, std::ctstring_t &date, std::ctstring_t &time,
                       std::ctstring_t &stackTrace, std::ctstring_t &comment);
        ///< constructor
    virtual       ~CxErrorReport() {}
        ///< destructor

    ExType         type() const;
        ///< report type
    std::tstring_t toString() const;
        ///< report message

private:
    ExType         _type;          ///< report type
    std::tstring_t _report;        ///< report message

    // exe
    std::tstring_t _program;       ///< program name
    ulong_t        _processId;     ///< current process id
    ulong_t        _threadId;      ///< current thread id
    std::tstring_t _fileSize;      ///< file size

    // source
    std::tstring_t _sourceFile;    ///< source file path
    ulong_t        _sourceLine;    ///< source file line
    std::tstring_t _functionName;  ///< source function name
    std::tstring_t _expression;    ///< expression
    std::tstring_t _exprSign;      ///< expression sign


    ulong_t        _lastError;     ///< system last error
    std::tstring_t _lastErrorStr;  ///< system last error as string

    // other
    std::tstring_t _currentDate;    ///< current date, time
    std::tstring_t _buildDate;      ///< build date, time
    std::tstring_t _buildType;      ///< get build type
    std::tstring_t _osVersion;      ///< build OS version
    std::tstring_t _osArchitecture; ///< OS architecture
    std::tstring_t _stackTrace;     ///< stack trace

    // comment
    std::tstring_t _comment;        ///< comment

    void_t         _construct(const ExType &type, std::ctstring_t &var1, std::ctstring_t &var2,
                       std::ctstring_t &var1Value, std::ctstring_t &var2Value,
                       std::ctstring_t &exprSign, culong_t &lastError,  std::ctstring_t &file,
                       culong_t &line, std::ctstring_t &func, std::ctstring_t &date,
                       std::ctstring_t &time, std::ctstring_t &stackTrace, std::ctstring_t &comment);
        ///< initiate class members
    void_t         _initPlain();
        ///< initiate plain report

xNO_COPY_ASSIGN(CxErrorReport)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxErrorReport.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxErrorReportH
