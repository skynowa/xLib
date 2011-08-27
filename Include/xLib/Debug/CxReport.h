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
        enum EType {
            rtUnknown,
            rtMsgboxPlain,
            rtMsgboxFormated,
            rtStdoutPlain,
            rtStdoutHtml,
            rtLoggingPlain,
            rtLoggingHtml
        };

                              CxReport           (const EType &crtType, const std::tstring &csExp, const ULONG culLastError, const std::tstring &csFile, const ULONG culLine, const std::tstring &csFunc, const std::tstring &csDate, const std::tstring &csTime, const std::tstring &csComment);
                              CxReport           (const EType &crtType, const std::tstring &csExp, const ULONG culLastError, const std::tstring &csFile, const ULONG culLine, const std::tstring &csFunc, const std::tstring &csDate, const std::tstring &csTime, LPCTSTR pcszComment, ...);
                              template<class T>
                              CxReport           (const EType &crtType, const T &cVatT1, const T &cVatT2, const std::tstring &csExpr1, const std::tstring &csExpr2, const std::tstring &csExprSign, const ULONG culLastError, const std::tstring &csFile, const ULONG culLine, const std::tstring &csFunc, const std::tstring &csDate, const std::tstring &csTime, const std::tstring &csComment);

        virtual              ~CxReport           ();

        EType                 rtGetType          () const;
        const std::tstring &  sGetReport         () const;
        const std::tstring &  sGetProgram        () const;
        ULONG                 ulGetProcessId     () const;
        ULONG                 ulGetThreadId      () const;
        const std::tstring &  sGetFileSize       () const;
        const std::tstring &  sGetSourceFile     () const;
        ULONG                 ulGetSourceLine    () const;
        const std::tstring &  sGetFunctionName   () const;
        const std::tstring &  sGetExpression     () const;
        ULONG                 ulGetLastError     () const;
        const std::tstring &  sGetLastErrorStr   () const;
        const std::tstring &  sGetCurrentDate    () const;
        const std::tstring &  sGetBuildDate      () const;
        const std::tstring &  sGetOsVersion      () const;
        const std::tstring &  sGetOsArchitecture () const;
        const std::tstring &  sGetComment        () const;

    private:
        EType                 _m_rtType;
        std::tstring          _m_sReport;

        //exe
        std::tstring          _m_sProgram;
        ULONG                 _m_ulProcessId;
        ULONG                 _m_ulThreadId;
        std::tstring          _m_sFileSize;

        //source
        std::tstring          _m_sSourceFile;
        ULONG                 _m_ulSourceLine;
        std::tstring          _m_sFunctionName;
        std::tstring          _m_sExpression;
        ULONG                 _m_ulLastError;
        std::tstring          _m_sLastErrorStr;

        //other
        std::tstring          _m_sCurrentDate;
        std::tstring          _m_sBuildDate;
        std::tstring          _m_sOsVersion;
        std::tstring          _m_sOsArchitecture;

        //comment
        std::tstring          _m_sComment;

        BOOL                  _bInitVars         (const EType &crtType, const std::tstring &csExp, const ULONG culLastError, const std::tstring &csFile, const ULONG culLine, const std::tstring &csFunc, const std::tstring &csDate, const std::tstring &csTime, const std::tstring &csComment);
        BOOL                  _bInitPlain        ();
        BOOL                  _bInitHtml         ();
        BOOL                  _bInitFormated     ();
};
//---------------------------------------------------------------------------
#include <Debug/CxReport.inl>
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxReportH
