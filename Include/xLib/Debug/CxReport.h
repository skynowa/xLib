/****************************************************************************
* Class name:  CxReport
* Description: debug message
* File name:   CxReport.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.02.2011
*
*****************************************************************************/


#ifndef xLib_Debug_CxReportH
#define xLib_Debug_CxReportH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
//---------------------------------------------------------------------------
class CxReport :
    public CxNonCopyable
{
    public:
        enum EType {
            rtUnknown,
            rtMsgboxPlain,
            rtMsgboxRtf,
            rtStdoutPlain,
            rtStdoutHtml,
            rtLoggingPlain,
            rtLoggingHtml
        };

                         CxReport           (const EType &crtType, const tString &csExp, const ULONG culLastError, const tString &csFile, const ULONG culLine, const tString &csFunc, const tString &csDate, const tString &csTime, const tString &csComment);
                         CxReport           (const EType &crtType, const tString &csExp, const ULONG culLastError, const tString &csFile, const ULONG culLine, const tString &csFunc, const tString &csDate, const tString &csTime, LPCTSTR pcszComment, ...);
                         template<class T>
                         CxReport           (const EType &crtType, const T &cVatT1, const T &cVatT2, const tString &csExpr1, const tString &csExpr2, const tString &csExprSign, const ULONG culLastError, const tString &csFile, const ULONG culLine, const tString &csFunc, const tString &csDate, const tString &csTime, const tString &csComment);

        virtual         ~CxReport           ();

        EType            rtGetType          () const;
        const tString &  sGetReport         () const;
        const tString &  sGetProgram        () const;
        ULONG            ulGetProcessId     () const;
        ULONG            ulGetThreadId      () const;
        const tString &  sGetFileSize       () const;
        const tString &  sGetSourceFile     () const;
        ULONG            ulGetSourceLine    () const;
        const tString &  sGetFunctionName   () const;
        const tString &  sGetExpression     () const;
        ULONG            ulGetLastError     () const;
        const tString &  sGetLastErrorStr   () const;
        const tString &  sGetCurrentDate    () const;
        const tString &  sGetBuildDate      () const;
        const tString &  sGetOsVersion      () const;
        const tString &  sGetOsArchitecture () const;
        const tString &  sGetComment        () const;

    private:
        EType            _m_rtType;
        tString          _m_sReport;

        //exe
        tString          _m_sProgram;
        ULONG            _m_ulProcessId;
        ULONG            _m_ulThreadId;
        tString          _m_sFileSize;

        //source
        tString          _m_sSourceFile;
        ULONG            _m_ulSourceLine;
        tString          _m_sFunctionName;
        tString          _m_sExpression;
        ULONG            _m_ulLastError;
        tString          _m_sLastErrorStr;

        //other
        tString          _m_sCurrentDate;
        tString          _m_sBuildDate;
        tString          _m_sOsVersion;
        tString          _m_sOsArchitecture;

        //comment
        tString          _m_sComment;

        BOOL             _bInitVars         (const EType &crtType, const tString &csExp, const ULONG culLastError, const tString &csFile, const ULONG culLine, const tString &csFunc, const tString &csDate, const tString &csTime, const tString &csComment);
        BOOL             _bInitPlain        ();
        BOOL             _bInitHtml         ();
        BOOL             _bInitRtf          ();
};
//---------------------------------------------------------------------------
#include <Debug/CxReport.inl>
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxReportH
