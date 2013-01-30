/**
 * \file  CxErrorReport.h
 * \brief debug report
 */


#ifndef xLib_Debug_CxReportH
#define xLib_Debug_CxReportH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
//---------------------------------------------------------------------------
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
                   CxErrorReport(const ExType         &crtType,
                                 const std::tstring_t &csVar1,       const std::tstring_t &csVar2,
                                 const T              &cVar1ValueT,  const T              &cVar2ValueT,
                                 const std::tstring_t &csExprSign,
                                 const ulong_t        &culLastError, const std::tstring_t &csFile,
                                 const ulong_t        &culLine,      const std::tstring_t &csFunc,
                                 const std::tstring_t &csDate,       const std::tstring_t &csTime,
                                 const std::tstring_t &csStackTrace, const std::tstring_t &csComment);
        ///< constructor
    virtual       ~CxErrorReport();
        ///< destructor

private:
    void          _construct    (const ExType         &crtType,
                                 const std::tstring_t &csVar1,       const std::tstring_t &csVar2,
                                 const std::tstring_t &csVar1Value,  const std::tstring_t &csVar2Value,
                                 const std::tstring_t &csExprSign,
                                 const ulong_t        &culLastError, const std::tstring_t &csFile,
                                 const ulong_t        &culLine,      const std::tstring_t &csFunc,
                                 const std::tstring_t &csDate,       const std::tstring_t &csTime,
                                 const std::tstring_t &csStackTrace, const std::tstring_t &csComment);
        ///< initiate class members
    void          _initPlain    ();
        ///< initiate plain report
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxErrorReport.inl"
//---------------------------------------------------------------------------
#endif // xLib_Debug_CxReportH
