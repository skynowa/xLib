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


    ExType         type;          ///< report type
    std::tstring_t report;        ///< report message

    // exe
    std::tstring_t program;       ///< program name
    ulong_t        processId;     ///< current process id
    ulong_t        threadId;      ///< current thread id
    std::tstring_t fileSize;      ///< file size

    // source
    std::tstring_t sourceFile;    ///< source file path
    ulong_t        sourceLine;    ///< source file line
    std::tstring_t functionName;  ///< source function name
    std::tstring_t expression;    ///< expression
    std::tstring_t exprSign;      ///< expression sign


    ulong_t        lastError;     ///< system last error
    std::tstring_t lastErrorStr;  ///< system last error as string

    // other
    std::tstring_t currentDate;    ///< current date, time
    std::tstring_t buildDate;      ///< build date, time
    std::tstring_t buildType;      ///< get build type
    std::tstring_t osVersion;      ///< build OS version
    std::tstring_t osArchitecture; ///< OS architecture
    std::tstring_t stackTrace;     ///< stack trace

    // comment
    std::tstring_t comment;        ///< comment

                   template<class T>
                   CxErrorReport(const ExType    &type,
                                 std::ctstring_t &var1,       std::ctstring_t &var2,
                                 const T         &var1ValueT, const T         &var2ValueT,
                                 std::ctstring_t &exprSign,
                                 culong_t        &lastError,  std::ctstring_t &file,
                                 culong_t        &line,       std::ctstring_t &func,
                                 std::ctstring_t &date,       std::ctstring_t &time,
                                 std::ctstring_t &stackTrace, std::ctstring_t &comment);
        ///< constructor
    virtual       ~CxErrorReport() {}
        ///< destructor

private:
    void_t        _construct    (const ExType    &type,
                                 std::ctstring_t &var1,       std::ctstring_t &var2,
                                 std::ctstring_t &var1Value,  std::ctstring_t &var2Value,
                                 std::ctstring_t &exprSign,
                                 culong_t        &lastError,  std::ctstring_t &file,
                                 culong_t        &line,       std::ctstring_t &func,
                                 std::ctstring_t &date,       std::ctstring_t &time,
                                 std::ctstring_t &stackTrace, std::ctstring_t &comment);
        ///< initiate class members
    void_t        _initPlain    ();
        ///< initiate plain report

xNO_COPY_ASSIGN(CxErrorReport)
};

xNAMESPACE_END(NxLib)

//-------------------------------------------------------------------------------------------------
#include "CxErrorReport.inl"
#include <Debug/CxErrorReport.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxErrorReportH
