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


    ExType         m_rtType;          ///< report type
    std::tstring_t m_sReport;         ///< report message

    // exe
    std::tstring_t m_sProgram;        ///< program name
    ulong_t        m_ulProcessId;     ///< current process id
    ulong_t        m_ulThreadId;      ///< current thread id
    std::tstring_t m_sFileSize;       ///< file size

    // source
    std::tstring_t m_sSourceFile;     ///< source file path
    ulong_t        m_ulSourceLine;    ///< source file line
    std::tstring_t m_sFunctionName;   ///< source function name
    std::tstring_t m_sExpression;     ///< expression
    std::tstring_t m_sExprSign;       ///< expression sign


    ulong_t        m_ulLastError;     ///< system last error
    std::tstring_t m_sLastErrorStr;   ///< system last error as string

    // other
    std::tstring_t m_sCurrentDate;    ///< current date, time
    std::tstring_t m_sBuildDate;      ///< build date, time
    std::tstring_t m_sBuildType;      ///< get build type
    std::tstring_t m_sOsVersion;      ///< build OS version
    std::tstring_t m_sOsArchitecture; ///< OS architecture
    std::tstring_t m_sStackTrace;     ///< stack trace

    // comment
    std::tstring_t m_sComment;        ///< comment

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
//------------------------------------------------------------------------------
