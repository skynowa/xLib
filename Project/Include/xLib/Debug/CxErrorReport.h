/**
 * \file  CxErrorReport.h
 * \brief debug report
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxNonCopyable.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxErrorReport :
    private CxNonCopyable
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

                   template<typename T>
                   CxErrorReport(const ExType    &crtType,
                                 std::ctstring_t &csVar1,       std::ctstring_t &csVar2,
                                 const T         &cVar1ValueT,  const T         &cVar2ValueT,
                                 std::ctstring_t &csExprSign,
                                 culong_t        &culLastError, std::ctstring_t &csFile,
                                 culong_t        &culLine,      std::ctstring_t &csFunc,
                                 std::ctstring_t &csDate,       std::ctstring_t &csTime,
                                 std::ctstring_t &csStackTrace, std::ctstring_t &csComment);
        ///< constructor
    virtual       ~CxErrorReport();
        ///< destructor

private:
    void_t        _construct    (const ExType    &crtType,
                                 std::ctstring_t &csVar1,       std::ctstring_t &csVar2,
                                 std::ctstring_t &csVar1Value,  std::ctstring_t &csVar2Value,
                                 std::ctstring_t &csExprSign,
                                 culong_t        &culLastError, std::ctstring_t &csFile,
                                 culong_t        &culLine,      std::ctstring_t &csFunc,
                                 std::ctstring_t &csDate,       std::ctstring_t &csTime,
                                 std::ctstring_t &csStackTrace, std::ctstring_t &csComment);
        ///< initiate class members
    void_t        _initPlain    ();
        ///< initiate plain report
};

xNAMESPACE_END(NxLib)

//------------------------------------------------------------------------------
#include "CxErrorReport.inl"

#if xXLIB_HEADER_ONLY

#endif
