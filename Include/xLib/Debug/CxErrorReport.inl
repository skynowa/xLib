/**
 * \file  CxErrorReport.inl
 * \brief debug report
 */


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
template<class T>
CxErrorReport::CxErrorReport(
    const EType          &crtType,
    const T              &cVarT1,
    const T              &cVarT2,
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
    m_rtType         (rtUnknown),
    m_sReport        (),
    m_sProgram       (),
    m_ulProcessId    (0UL),
    m_ulThreadId     (0UL),
    m_sFileSize      (),
    m_sSourceFile    (),
    m_ulSourceLine   (0UL),
    m_sFunctionName  (),
    m_sExpression    (),
    m_ulLastError    (0UL),
    m_sLastErrorStr  (),
    m_sCurrentDate   (),
    m_sBuildDate     (),
    m_sBuildType     (),
    m_sOsVersion     (),
    m_sOsArchitecture(),
    m_sStackTrace    (),
    m_sComment       ()
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

        if (false == m_sComment.empty()) {
            ossStream << xT("\n                      (")  << m_sComment << xT(")");
        }

        sComment = ossStream.str();
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
