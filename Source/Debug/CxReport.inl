/**
 * \file  CxReport.inl
 * \brief debug report
 */


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
template<class T>
CxReport::CxReport(
    const EType        &crtType,
    const T            &cVarT1,
    const T            &cVarT2,
    const std::tstring_t &csExpr1,
    const std::tstring_t &csExpr2,
    const std::tstring_t &csExprSign,
    const ulong_t         culLastError,
    const std::tstring_t &csFile,
    const ulong_t         culLine,
    const std::tstring_t &csFunc,
    const std::tstring_t &csDate,
    const std::tstring_t &csTime,
    const std::tstring_t &csStackTrace,
    const std::tstring_t &csComment
) :
    _m_rtType         (rtUnknown),
    _m_sReport        (),
    _m_sProgram       (),
    _m_ulProcessId    (0UL),
    _m_ulThreadId     (0UL),
    _m_sFileSize      (),
    _m_sSourceFile    (),
    _m_ulSourceLine   (0UL),
    _m_sFunctionName  (),
    _m_sExpression    (),
    _m_ulLastError    (0UL),
    _m_sLastErrorStr  (),
    _m_sCurrentDate   (),
    _m_sBuildDate     (),
    _m_sBuildType     (),
    _m_sOsVersion     (),
    _m_sOsArchitecture(),
    _m_sStackTrace    (),
    _m_sComment       ()
{
    /*DEBUG*/

    //sExpr
    std::tstring_t sExpr = csExpr1 + xT(" ") + csExprSign + xT(" ") + csExpr2;

    //sComment
    std::tstring_t sComment;

    {
        std::tostringstream_t ossStream;
        ossStream.exceptions(std::tostringstream_t::eofbit | std::tostringstream_t::failbit | std::tostringstream_t::badbit);

        size_t uiAlignWidth = CxMacros::xMax(csExpr1.size(), csExpr2.size());

        ossStream << std::left << std::setw(uiAlignWidth) << csExpr1 << xT(": ") << cVarT1 << xT("\n")
                  << xT("                    ")
                  << std::left << std::setw(uiAlignWidth) << csExpr2 << xT(": ") << cVarT2;

        if (false == _m_sComment.empty()) {
            ossStream << xT("\n                      (")  << _m_sComment << xT(")");
        }

        sComment.assign( ossStream.str() );
    }

    (void)_bInitVars(crtType, sExpr, culLastError, csFile, culLine, csFunc, csDate, csTime, csStackTrace, sComment);

    switch (crtType) {
        case rtMsgboxPlain:     { (void)_bInitPlain();    } break;
        case rtMsgboxFormated:  { (void)_bInitFormated(); } break;
        case rtStdoutPlain:     { (void)_bInitPlain();    } break;
        case rtStdoutHtml:      { (void)_bInitHtml();     } break;
        case rtLoggingPlain:    { (void)_bInitPlain();    } break;
        case rtLoggingHtml:     { (void)_bInitHtml();     } break;

        default:                { (void)_bInitPlain();    } break;
    }
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
