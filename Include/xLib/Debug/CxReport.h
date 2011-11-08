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

                              CxReport           (const EType &crtType, const std::string_t &csExp, const ULONG culLastError, const std::string_t &csFile, const ULONG culLine, const std::string_t &csFunc, const std::string_t &csDate, const std::string_t &csTime, const std::string_t &csStackTrace, const std::string_t &csComment);
            ///< constructor
                              CxReport           (const EType &crtType, const std::string_t &csExp, const ULONG culLastError, const std::string_t &csFile, const ULONG culLine, const std::string_t &csFunc, const std::string_t &csDate, const std::string_t &csTime, const std::string_t &csStackTrace, const TCHAR *pcszComment, ...);
            ///< constructor
                              template<class T>
                              CxReport           (const EType &crtType, const T &cVatT1, const T &cVatT2, const std::string_t &csExpr1, const std::string_t &csExpr2, const std::string_t &csExprSign, const ULONG culLastError, const std::string_t &csFile, const ULONG culLine, const std::string_t &csFunc, const std::string_t &csDate, const std::string_t &csTime, const std::string_t &csStackTrace, const std::string_t &csComment);
            ///< constructor
        virtual              ~CxReport           ();
            ///< destructor

        EType                 rtGetType          () const;
            ///< get type
        const std::string_t &  sGetReport         () const;
            ///< get report
        const std::string_t &  sGetProgram        () const;
            ///< get program name
        ULONG                 ulGetProcessId     () const;
            ///< get current process id
        ULONG                 ulGetThreadId      () const;
            ///< get current thread id
        const std::string_t &  sGetFileSize       () const;
            ///< get file size
        const std::string_t &  sGetSourceFile     () const;
            ///< get source file path
        ULONG                 ulGetSourceLine    () const;
            ///< get source file line
        const std::string_t &  sGetFunctionName   () const;
            ///< get source function name
        const std::string_t &  sGetExpression     () const;
            ///< get expression
        ULONG                 ulGetLastError     () const;
            ///< get system last error
        const std::string_t &  sGetLastErrorStr   () const;
            ///< get formatting last error
        const std::string_t &  sGetCurrentDate    () const;
            ///< get current date, time
        const std::string_t &  sGetBuildDate      () const;
            ///< get build date, time
        const std::string_t &  sGetOsVersion      () const;
            ///< get build OS version
        const std::string_t &  sGetOsArchitecture () const;
            ///< get OS architecture
        const std::string_t &  sGetComment        () const;
            ///< get comment
        const std::string_t &  sGetStackTrace     () const;
            ///< get comment


    private:
        EType                 _m_rtType;            ///< report type
        std::string_t          _m_sReport;           ///< repoer message

        //exe
        std::string_t          _m_sProgram;          ///< program name
        ULONG                 _m_ulProcessId;       ///< current process id
        ULONG                 _m_ulThreadId;        ///< current thread id
        std::string_t          _m_sFileSize;         ///< file size

        //source
        std::string_t          _m_sSourceFile;       ///< source file path
        ULONG                 _m_ulSourceLine;      ///< source file line
        std::string_t          _m_sFunctionName;     ///< source function name
        std::string_t          _m_sExpression;       ///< expression
        ULONG                 _m_ulLastError;       ///< system last error
        std::string_t          _m_sLastErrorStr;     ///< system last error as string

        //other
        std::string_t          _m_sCurrentDate;      ///< current date, time
        std::string_t          _m_sBuildDate;        ///< build date, time
        std::string_t          _m_sOsVersion;        ///< build OS version
        std::string_t          _m_sOsArchitecture;   ///< OS architecture
        std::string_t          _m_sStackTrace;       ///< stack trace

        //comment
        std::string_t          _m_sComment;          ///< comment


        BOOL                  _bInitVars         (const EType &crtType, const std::string_t &csExp, const ULONG culLastError, const std::string_t &csFile, const ULONG culLine, const std::string_t &csFunc, const std::string_t &csDate, const std::string_t &csTime, const std::string_t &csStackTrace, const std::string_t &csComment);
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
