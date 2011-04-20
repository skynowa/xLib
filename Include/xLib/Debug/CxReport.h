/****************************************************************************
* Class name:  CxReport
* Description: debug message
* File name:   CxReport.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     1 лют. 2011 13:58:33
*
*****************************************************************************/


#ifndef xLib_Debug_CxReportH
#define xLib_Debug_CxReportH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
//---------------------------------------------------------------------------
class CxReport : public CxNonCopyable  {
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

                       CxReport          (const EType &crtType, const tString &csExp, ULONG ulLastError, const tString &csFile, ULONG ulLine, const tString &csFunc, const tString &csDate, const tString &csTime, const tString &csComment);
                       CxReport          (const EType &crtType, const tString &csExp, ULONG ulLastError, const tString &csFile, ULONG ulLine, const tString &csFunc, const tString &csDate, const tString &csTime, LPCTSTR pcszComment, ...);
      template<class T>CxReport          (const EType &crtType, const T &cVatT1, const T &cVatT2, const tString &csExp1, const tString &csExp2, ULONG ulLastError, const tString &csFile, ULONG ulLine, const tString &csFunc, const tString &csDate, const tString &csTime, const tString &csComment);

        virtual       ~CxReport          ();

        EType          rtGetType         () const;
        const tString &sGetReport        () const;
        const tString &sGetProgram       () const;
        ULONG          ulGetProcessId    () const;
        ULONG          ulGetThreadId     () const;
        const tString &sGetSourceFile    () const;
        ULONG          ulGetSourceLine   () const;
        const tString &sGetFunctionName  () const;
        const tString &sGetExpression    () const;
        ULONG          ulGetLastError    () const;
        const tString &sGetLastErrorStr  () const;
        const tString &sGetCurrentDate   () const;
        const tString &sGetBuildDate     () const;
        const tString &sGetOsVersion     () const;
        const tString &sGetOsArchitecture() const;
        const tString &sGetComment       () const;

    private:
        EType          _m_rtType;
        tString        _m_sReport;

        //exe
        tString        _m_sProgram;
        ULONG          _m_ulProcessId;
        ULONG          _m_ulThreadId;

        //source
        tString        _m_sSourceFile;
        ULONG          _m_ulSourceLine;
        tString        _m_sFunctionName;
        tString        _m_sExpression;
        ULONG          _m_ulLastError;
        tString        _m_sLastErrorStr;

        //other
        tString        _m_sCurrentDate;
        tString        _m_sBuildDate;
        tString        _m_sOsVersion;
        tString        _m_sOsArchitecture;

        //comment
        tString        _m_sComment;

        BOOL           _bInitVars         (const EType &crtType, const tString &csExp, ULONG ulLastError, const tString &csFile, ULONG ulLine, const tString &csFunc, const tString &csDate, const tString &csTime, const tString &csComment);
        BOOL           _bInitPlain        ();
        BOOL           _bInitHtml         ();
        BOOL           _bInitRtf          ();

        tString        _sGetOsArchitecture();
};
//---------------------------------------------------------------------------


/****************************************************************************
*    tamlpates
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxReport (constructor)
template<class T>
CxReport::CxReport(
        const EType   &crtType,
        const T       &cVarT1,
        const T       &cVarT2,
        const tString &csExp1,
        const tString &csExp2,
        ULONG          ulLastError,
        const tString &csFile,
        ULONG          ulLine,
        const tString &csFunc,
        const tString &csDate,
        const tString &csTime,
        const tString &csComment
) :
    _m_rtType         (rtUnknown),
    _m_sReport        (),
    _m_sProgram       (),
    _m_ulProcessId    (0),
    _m_ulThreadId     (0),
    _m_sSourceFile    (),
    _m_ulSourceLine   (0),
    _m_sFunctionName  (),
    _m_sExpression    (),
    _m_ulLastError    (),
    _m_sLastErrorStr  (),
    _m_sCurrentDate   (),
    _m_sBuildDate     (),
    _m_sOsVersion     (),
    _m_sOsArchitecture(),
    _m_sComment       ()
{
    /*DEBUG*/

    //sExp
    tString sExp = csExp1 + xT(" == ") + csExp2;

    //sComment
    tString sComment;

    tostringstream ossStream;
    ossStream.exceptions(tostringstream::eofbit | tostringstream::failbit | tostringstream::badbit);


    size_t uiAlignWidth = std::max(csExp1.size(), csExp2.size());

    ossStream << xT("\"") << std::left << std::setw(uiAlignWidth) << csExp1 << xT("\"") << xT(": ") << cVarT1 << xT("\n")
              << xT("                 ")
              << xT("\"") << std::left << std::setw(uiAlignWidth) << csExp2 << xT("\"") << xT(": ") << cVarT2;

    if (false == _m_sComment .empty()) {
        ossStream << xT("\n                 ")
                  << xT("  (") << _m_sComment << xT(")");
    }

    sComment = ossStream.str();

    //init vars
    _bInitVars(crtType, sExp, ulLastError, csFile, ulLine, csFunc, csDate, csTime, sComment);

    //init report
    switch (crtType) {
        case rtMsgboxPlain:  { _bInitPlain(); } break;
        case rtMsgboxRtf:    { _bInitRtf();   } break;
        case rtStdoutPlain:  { _bInitPlain(); } break;
        case rtStdoutHtml:   { _bInitHtml();  } break;
        case rtLoggingPlain: { _bInitPlain(); } break;
        case rtLoggingHtml:  { _bInitHtml();  } break;

        default:             { _bInitPlain(); } break;
    }
}
//---------------------------------------------------------------------------
#endif //xLib_CxReportH




