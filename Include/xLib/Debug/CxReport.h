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
xNAMESPACE_BEGIN(NxLib)

class CxReport :
    private CxNonCopyable
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

                                CxReport          (const EType &crtType, const std::tstring_t &csExp, const ulong_t culLastError, const std::tstring_t &csFile, const ulong_t culLine, const std::tstring_t &csFunc, const std::tstring_t &csDate, const std::tstring_t &csTime, const std::tstring_t &csStackTrace, const std::tstring_t &csComment);
            ///< constructor
                                CxReport          (const EType &crtType, const std::tstring_t &csExp, const ulong_t culLastError, const std::tstring_t &csFile, const ulong_t culLine, const std::tstring_t &csFunc, const std::tstring_t &csDate, const std::tstring_t &csTime, const std::tstring_t &csStackTrace, const tchar_t *pcszComment, ...);
            ///< constructor
                                template<class T>
                                CxReport          (const EType &crtType, const T &cVatT1, const T &cVatT2, const std::tstring_t &csExpr1, const std::tstring_t &csExpr2, const std::tstring_t &csExprSign, const ulong_t culLastError, const std::tstring_t &csFile, const ulong_t culLine, const std::tstring_t &csFunc, const std::tstring_t &csDate, const std::tstring_t &csTime, const std::tstring_t &csStackTrace, const std::tstring_t &csComment);
            ///< constructor
        virtual                ~CxReport          ();
            ///< destructor

        EType                   rtGetType         () const;
            ///< get type
        const std::tstring_t &  sGetReport        () const;
            ///< get report
        const std::tstring_t &  sGetProgram       () const;
            ///< get program name
        ulong_t                 ulGetProcessId    () const;
            ///< get current process id
        ulong_t                 ulGetThreadId     () const;
            ///< get current thread id
        const std::tstring_t &  sGetFileSize      () const;
            ///< get file size
        const std::tstring_t &  sGetSourceFile    () const;
            ///< get source file path
        ulong_t                 ulGetSourceLine   () const;
            ///< get source file line
        const std::tstring_t &  sGetFunctionName  () const;
            ///< get source function name
        const std::tstring_t &  sGetExpression    () const;
            ///< get expression
        ulong_t                 ulGetLastError    () const;
            ///< get system last error
        const std::tstring_t &  sGetLastErrorStr  () const;
            ///< get formatting last error
        const std::tstring_t &  sGetCurrentDate   () const;
            ///< get current date, time
        const std::tstring_t &  sGetBuildDate     () const;
            ///< get build date, time
        const std::tstring_t &  sGetBuildType     () const;
            ///< get build type (debug or release)
        const std::tstring_t &  sGetOsVersion     () const;
            ///< get build OS version
        const std::tstring_t &  sGetOsArchitecture() const;
            ///< get OS architecture
        const std::tstring_t &  sGetComment       () const;
            ///< get comment
        const std::tstring_t &  sGetStackTrace    () const;
            ///< get comment


    private:
        EType                   _m_rtType;          ///< report type
        std::tstring_t          _m_sReport;         ///< repoer message

        //exe
        std::tstring_t          _m_sProgram;        ///< program name
        ulong_t                 _m_ulProcessId;     ///< current process id
        ulong_t                 _m_ulThreadId;      ///< current thread id
        std::tstring_t          _m_sFileSize;       ///< file size

        //source
        std::tstring_t          _m_sSourceFile;     ///< source file path
        ulong_t                 _m_ulSourceLine;    ///< source file line
        std::tstring_t          _m_sFunctionName;   ///< source function name
        std::tstring_t          _m_sExpression;     ///< expression
        ulong_t                 _m_ulLastError;     ///< system last error
        std::tstring_t          _m_sLastErrorStr;   ///< system last error as string

        //other
        std::tstring_t          _m_sCurrentDate;    ///< current date, time
        std::tstring_t          _m_sBuildDate;      ///< build date, time
        std::tstring_t          _m_sBuildType;      ///< get build type
        std::tstring_t          _m_sOsVersion;      ///< build OS version
        std::tstring_t          _m_sOsArchitecture; ///< OS architecture
        std::tstring_t          _m_sStackTrace;     ///< stack trace

        //comment
        std::tstring_t          _m_sComment;        ///< comment


        bool                    _bInitVars        (const EType &crtType, const std::tstring_t &csExp, const ulong_t culLastError, const std::tstring_t &csFile, const ulong_t culLine, const std::tstring_t &csFunc, const std::tstring_t &csDate, const std::tstring_t &csTime, const std::tstring_t &csStackTrace, const std::tstring_t &csComment);
            ///< initiate class members
        bool                    _bInitPlain       ();
            ///< initiate plain report
        bool                    _bInitHtml        ();
            ///< initiate HTML report
        bool                    _bInitFormated    ();
            ///< initiate formatrd report
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxReport.inl"
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxReportH
