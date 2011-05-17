/****************************************************************************
* Class name:  CxReport
* Description: debug message
* File name:   CxReport.inl
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     17.05.2011
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
        const ULONG    culLastError,
        const tString &csFile,
        const ULONG    culLine,
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


    size_t uiAlignWidth = CxMacros::xMax(csExp1.size(), csExp2.size());

    ossStream << xT("\"") << std::left << std::setw(uiAlignWidth) << csExp1 << xT("\"") << xT(": ") << cVarT1 << xT("\n")
              << xT("                 ")
              << xT("\"") << std::left << std::setw(uiAlignWidth) << csExp2 << xT("\"") << xT(": ") << cVarT2;

    if (false == _m_sComment .empty()) {
        ossStream << xT("\n                 ")
                  << xT("  (") << _m_sComment << xT(")");
    }

    sComment = ossStream.str();

    //init vars
    _bInitVars(crtType, sExp, culLastError, csFile, culLine, csFunc, csDate, csTime, sComment);

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
