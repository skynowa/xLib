/**
 * \file  CxErrorReport.inl
 * \brief debug report
 */


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
template<typename T>
CxErrorReport::CxErrorReport(
    const ExType         &a_crtType,
    const std::tstring_t &a_csVar1,
    const std::tstring_t &a_csVar2,
    const T              &a_cVar1ValueT,
    const T              &a_cVar2ValueT,
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
    m_sExprSign      (),
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
    // sVar1Value
    std::tstring_t sVar1Value;
    {
        std::tostringstream_t ossRes;

        ossRes << a_cVar1ValueT;
        sVar1Value = ossRes.str();
    }

    // sVar2Value
    std::tstring_t sVar2Value;
    {
        std::tostringstream_t ossRes;

        ossRes << a_cVar2ValueT;
        sVar2Value = ossRes.str();
    }

    _construct(a_crtType,
               a_csVar1,   a_csVar2,
               sVar1Value, sVar2Value,
               a_csExprSign,
               a_culLastError, a_csFile, a_culLine, a_csFunc, 
               a_csDate, a_csTime, a_csStackTrace, a_csComment);

    switch (a_crtType) {
        case rtMsgboxPlain:  { _initPlain(); } break;
        case rtStdoutPlain:  { _initPlain(); } break;
        case rtLoggingPlain: { _initPlain(); } break;

        default:             { _initPlain(); } break;
    }
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
