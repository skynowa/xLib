/**
 * \file  CxErrorReport.inl
 * \brief debug report
 */


xNAMESPACE_BEGIN(NxLib)

//------------------------------------------------------------------------------
template<class T>
CxErrorReport::CxErrorReport(
    const ExType    &a_type,
    std::ctstring_t &a_var1,
    std::ctstring_t &a_var2,
    const T         &a_var1Value,
    const T         &a_var2Value,
    std::ctstring_t &a_exprSign,
    culong_t        &a_lastError,
    std::ctstring_t &a_file,
    culong_t        &a_line,
    std::ctstring_t &a_func,
    std::ctstring_t &a_date,
    std::ctstring_t &a_time,
    std::ctstring_t &a_stackTrace,
    std::ctstring_t &a_comment
) :
    type          (rtUnknown),
    report        (),
    program       (),
    processId     (0UL),
    threadId      (0UL),
    fileSize      (),
    sourceFile    (),
    sourceLine    (0UL),
    functionName  (),
    expression    (),
    exprSign      (),
    lastError     (0UL),
    lastErrorStr  (),
    currentDate   (),
    buildDate     (),
    buildType     (),
    osVersion     (),
    osArchitecture(),
    stackTrace    (),
    comment       ()
{
    // var1Value
    std::tstring_t var1Value;
    {
        std::tostringstream_t ossRes;

        ossRes << a_var1Value;
        var1Value = ossRes.str();
    }

    // var2Value
    std::tstring_t var2Value;
    {
        std::tostringstream_t ossRes;

        ossRes << a_var2Value;
        var2Value = ossRes.str();
    }

    _construct(a_type,
               a_var1,     a_var2,
               var1Value, var2Value,
               a_exprSign,
               a_lastError, a_file, a_line, a_func,
               a_date, a_time, a_stackTrace, a_comment);

    switch (a_type) {
        case rtMsgboxPlain:  { _initPlain(); } break;
        case rtStdoutPlain:  { _initPlain(); } break;
        case rtLoggingPlain: { _initPlain(); } break;

        default:             { _initPlain(); } break;
    }
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
