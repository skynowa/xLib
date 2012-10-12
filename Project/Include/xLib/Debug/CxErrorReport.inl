/**
 * \file  CxErrorReport.inl
 * \brief debug report
 */


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
template<class T>
CxErrorReport::CxErrorReport(
    const ExType         &a_crtType,
    const T              &a_cVarT1,
    const T              &a_cVarT2,
    const std::tstring_t &a_csExpr1,
    const std::tstring_t &a_csExpr2,
    const std::tstring_t &a_csExprSign,
    const ulong_t        &a_culLastError,
    const std::tstring_t &a_csFile,
    const ulong_t        &a_culLine,
    const std::tstring_t &a_csFunc,
    const std::tstring_t &a_csDate,
    const std::tstring_t &a_csTime,
    const std::tstring_t &a_csStackTrace,
    const std::tstring_t &a_csComment
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

#if 0
    CxErrorReport rpReport(report_type, 
                           xT(""), xT(""),          // a_cVarT1, a_cVarT2
                           xT("false"), xT(""),     // a_csExpr1, a_csExpr2 
                           xT(""),                  // a_csExprSign
                           ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), (msg));
#endif

    // sExpr
    std::tstring_t sExpr = a_csExpr1 + xT(" ") + a_csExprSign + xT(" ") + a_csExpr2;

    // sComment
    std::tstring_t sComment;

    {
        std::tostringstream_t ossStream;
        ossStream.exceptions(std::tostringstream_t::eofbit | std::tostringstream_t::failbit | std::tostringstream_t::badbit);

        size_t uiAlignWidth = xMAX(a_csExpr1.size(), a_csExpr2.size());

        ossStream << std::left << std::setw(uiAlignWidth) << a_csExpr1 << xT(": ") << a_cVarT1 << xT("\n")
                  << xT("                 ")
                  << std::left << std::setw(uiAlignWidth) << a_csExpr2 << xT(": ") << a_cVarT2;

        if (false == a_csComment.empty()) {
            ossStream << xT("\n                 (")  << a_csComment << xT(")");
        }

        sComment = ossStream.str();
    }

    _vConstruct(a_crtType, sExpr, a_culLastError, a_csFile, a_culLine, a_csFunc, a_csDate, a_csTime, a_csStackTrace, sComment);

    switch (a_crtType) {
        case rtMsgboxPlain:     { _vInitPlain();    } break;
        case rtMsgboxFormated:  { _vInitFormated(); } break;
        case rtStdoutPlain:     { _vInitPlain();    } break;
        case rtStdoutHtml:      { _vInitHtml();     } break;
        case rtLoggingPlain:    { _vInitPlain();    } break;
        case rtLoggingHtml:     { _vInitHtml();     } break;

        default:                { _vInitPlain();    } break;
    }
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
