/**
 * \file  CxReport.inl
 * \brief debug report
 */


//---------------------------------------------------------------------------
template<class T>
CxReport::CxReport(
    const EType        &crtType,
    const T            &cVarT1,
    const T            &cVarT2,
    const std::tstring &csExpr1,
    const std::tstring &csExpr2,
    const std::tstring &csExprSign,
    const ULONG         culLastError,
    const std::tstring &csFile,
    const ULONG         culLine,
    const std::tstring &csFunc,
    const std::tstring &csDate,
    const std::tstring &csTime,
    const std::tstring &csComment
) :
    _m_rtType         (rtUnknown),
    _m_sReport        (),
    _m_sProgram       (),
    _m_ulProcessId    (0),
    _m_ulThreadId     (0),
    _m_sFileSize      (),
    _m_sSourceFile    (),
    _m_ulSourceLine   (0),
    _m_sFunctionName  (),
    _m_sExpression    (),
    _m_ulLastError    (0),
    _m_sLastErrorStr  (),
    _m_sCurrentDate   (),
    _m_sBuildDate     (),
    _m_sOsVersion     (),
    _m_sOsArchitecture(),
    _m_sComment       ()
{
    /*DEBUG*/

    //sExpr
    std::tstring sExpr = csExpr1 + xT(" ") + csExprSign + xT(" ") + csExpr2;

    //sComment
    std::tstring sComment;

    {
        std::tostringstream ossStream;
        ossStream.exceptions(std::tostringstream::eofbit | std::tostringstream::failbit | std::tostringstream::badbit);

        size_t uiAlignWidth = CxMacros::xMax(csExpr1.size(), csExpr2.size());

        ossStream << std::left << std::setw(uiAlignWidth) << csExpr1 << xT(": ") << cVarT1 << xT("\n")
                  << xT("                    ")
                  << std::left << std::setw(uiAlignWidth) << csExpr2 << xT(": ") << cVarT2;

        if (false == _m_sComment.empty()) {
            ossStream << xT("\n                      (")  << _m_sComment << xT(")");
        }

        sComment.assign( ossStream.str() );
    }

    _bInitVars(crtType, sExpr, culLastError, csFile, culLine, csFunc, csDate, csTime, sComment);
    /*DEBUG*/// n/a

    switch (crtType) {
        case rtMsgboxPlain:     { _bInitPlain();    } break;
        case rtMsgboxFormated:  { _bInitFormated(); } break;
        case rtStdoutPlain:     { _bInitPlain();    } break;
        case rtStdoutHtml:      { _bInitHtml();     } break;
        case rtLoggingPlain:    { _bInitPlain();    } break;
        case rtLoggingHtml:     { _bInitHtml();     } break;

        default:                { _bInitPlain();    } break;
    }
}
//---------------------------------------------------------------------------
