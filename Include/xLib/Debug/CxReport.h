/**
 * \file  CxReport.h
 * \brief debug report
 */


#ifndef xLib_Debug_CxReportH
#define xLib_Debug_CxReportH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
//---------------------------------------------------------------------------
class CxReport :
    public CxNonCopyable
    /// debug report
{
    public:
        enum EType
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

                              CxReport           (const EType &crtType, const std::tstring &csExp, const ULONG culLastError, const std::tstring &csFile, const ULONG culLine, const std::tstring &csFunc, const std::tstring &csDate, const std::tstring &csTime, const std::tstring &csComment);
            ///< constructor
                              CxReport           (const EType &crtType, const std::tstring &csExp, const ULONG culLastError, const std::tstring &csFile, const ULONG culLine, const std::tstring &csFunc, const std::tstring &csDate, const std::tstring &csTime, LPCTSTR pcszComment, ...);
            ///< constructor
                              template<class T>
                              CxReport           (const EType &crtType, const T &cVatT1, const T &cVatT2, const std::tstring &csExpr1, const std::tstring &csExpr2, const std::tstring &csExprSign, const ULONG culLastError, const std::tstring &csFile, const ULONG culLine, const std::tstring &csFunc, const std::tstring &csDate, const std::tstring &csTime, const std::tstring &csComment);
            ///< constructor
        virtual              ~CxReport           ();
            ///< destructor

        EType                 rtGetType          () const;
            ///< get type
        const std::tstring &  sGetReport         () const;
            ///< get report
        const std::tstring &  sGetProgram        () const;
            ///< get program name
        ULONG                 ulGetProcessId     () const;
            ///< get current process id
        ULONG                 ulGetThreadId      () const;
            ///< get current thread id
        const std::tstring &  sGetFileSize       () const;
            ///< get file size
        const std::tstring &  sGetSourceFile     () const;
            ///< get source file path
        ULONG                 ulGetSourceLine    () const;
            ///< get source file line
        const std::tstring &  sGetFunctionName   () const;
            ///< get source function name
        const std::tstring &  sGetExpression     () const;
            ///< get expression
        ULONG                 ulGetLastError     () const;
            ///< get system last error
        const std::tstring &  sGetLastErrorStr   () const;
            ///< get formatting last error
        const std::tstring &  sGetCurrentDate    () const;
            ///< get current date, time
        const std::tstring &  sGetBuildDate      () const;
            ///< get build date, time
        const std::tstring &  sGetOsVersion      () const;
            ///< get build OS version
        const std::tstring &  sGetOsArchitecture () const;
            ///< get OS architecture
        const std::tstring &  sGetComment        () const;
            ///< get comment

    private:
        EType                 _m_rtType;            ///< report type
        std::tstring          _m_sReport;           ///< repoer message

        //exe
        std::tstring          _m_sProgram;          ///< program name
        ULONG                 _m_ulProcessId;       ///< current process id
        ULONG                 _m_ulThreadId;        ///< current thread id
        std::tstring          _m_sFileSize;         ///< file size

        //source
        std::tstring          _m_sSourceFile;       ///< source file path
        ULONG                 _m_ulSourceLine;      ///< source file line
        std::tstring          _m_sFunctionName;     ///< source function name
        std::tstring          _m_sExpression;       ///< expression
        ULONG                 _m_ulLastError;       ///< system last error
        std::tstring          _m_sLastErrorStr;     ///< system last error as string

        //other
        std::tstring          _m_sCurrentDate;      ///< current date, time
        std::tstring          _m_sBuildDate;        ///< build date, time
        std::tstring          _m_sOsVersion;        ///< build OS version
        std::tstring          _m_sOsArchitecture;   ///< OS architecture

        //comment
        std::tstring          _m_sComment;          ///< comment

        BOOL                  _bInitVars         (const EType &crtType, const std::tstring &csExp, const ULONG culLastError, const std::tstring &csFile, const ULONG culLine, const std::tstring &csFunc, const std::tstring &csDate, const std::tstring &csTime, const std::tstring &csComment);
            ///< initiate class members
        BOOL                  _bInitPlain        ();
            ///< initiate plain report
        BOOL                  _bInitHtml         ();
            ///< initiate HTML report
        BOOL                  _bInitFormated     ();
            ///< initiate formatrd report
};
//---------------------------------------------------------------------------
#include <Debug/CxReport.inl>
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxReportH
