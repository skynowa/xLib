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
            rtUnknown,          ///< unknown
            rtMsgboxPlain,      ///< as message box with plain text (GUI)
            rtMsgboxFormated,   ///< as message box with formated text (GUI)
            rtStdoutPlain,      ///< to std::cout with plain text
            rtStdoutHtml,       ///< to std::cout with HTML text
            rtLoggingPlain,     ///< to log with plain text
            rtLoggingHtml       ///< to log with HTML text
        };


        ExType         m_rtType;          ///< report type
        std::tstring_t m_sReport;         ///< repoer message

        //exe
        std::tstring_t m_sProgram;        ///< program name
        ulong_t        m_ulProcessId;     ///< current process id
        ulong_t        m_ulThreadId;      ///< current thread id
        std::tstring_t m_sFileSize;       ///< file size

        //source
        std::tstring_t m_sSourceFile;     ///< source file path
        ulong_t        m_ulSourceLine;    ///< source file line
        std::tstring_t m_sFunctionName;   ///< source function name
        std::tstring_t m_sExpression;     ///< expression
        ulong_t        m_ulLastError;     ///< system last error
        std::tstring_t m_sLastErrorStr;   ///< system last error as string

        //other
        std::tstring_t m_sCurrentDate;    ///< current date, time
        std::tstring_t m_sBuildDate;      ///< build date, time
        std::tstring_t m_sBuildType;      ///< get build type
        std::tstring_t m_sOsVersion;      ///< build OS version
        std::tstring_t m_sOsArchitecture; ///< OS architecture
        std::tstring_t m_sStackTrace;     ///< stack trace

        //comment
        std::tstring_t m_sComment;        ///< comment

                       template<class T>
                       CxErrorReport(const ExType         &crtType,      const T &cVatT1,
                                     const T              &cVatT2,       const std::tstring_t &csExpr1,
                                     const std::tstring_t &csExpr2,      const std::tstring_t &csExprSign,
                                     const ulong_t        &culLastError, const std::tstring_t &csFile,
                                     const ulong_t        &culLine,      const std::tstring_t &csFunc,
                                     const std::tstring_t &csDate,       const std::tstring_t &csTime,
                                     const std::tstring_t &csStackTrace, const std::tstring_t &csComment);
            ///< constructor
        virtual       ~CxErrorReport();
            ///< destructor

    private:
        bool          _bConstruct   (const ExType         &crtType,      const std::tstring_t &csExp,
                                     const ulong_t        &culLastError, const std::tstring_t &csFile,
                                     const ulong_t        &culLine,      const std::tstring_t &csFunc,
                                     const std::tstring_t &csDate,       const std::tstring_t &csTime,
                                     const std::tstring_t &csStackTrace, const std::tstring_t &csComment);
            ///< initiate class members
        bool          _bInitPlain   ();
            ///< initiate plain report
        bool          _bInitHtml    ();
            ///< initiate HTML report
        bool          _bInitFormated();
            ///< initiate formatrd report
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxErrorReport.inl"
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxReportH
