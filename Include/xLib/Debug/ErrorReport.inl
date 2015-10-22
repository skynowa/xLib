/**
 * \file  ErrorReport.inl
 * \brief debug report
 */


xNAMESPACE_BEGIN2(xlib, debug)

//-------------------------------------------------------------------------------------------------
template<class T>
ErrorReport::ErrorReport(
    const ExType     &a_type,
    std::ctstring_t  &a_var1,
    std::ctstring_t  &a_var2,
    const T          &a_var1Value,
    const T          &a_var2Value,
    std::ctstring_t  &a_exprSign,
    culong_t         &a_nativeError,
    const SourceInfo &a_sourceInfo,
    std::ctstring_t  &a_stackTrace,
    std::ctstring_t  &a_comment
) :
    _type          (rtUnknown),
    _report        (),
    _program       (),
    _processId     (0UL),
    _threadId      (0UL),
    _fileSize      (),
    _sourceFilePath(),
    _sourceLineNum (),
    _sourceFuncName(),
    _sourceExpr    (),
    _nativeError   (0UL),
    _nativeErrorStr(),
    _currentDate   (),
    _stackTrace    (),
    _comment       ()
{
    // var1Value
    std::tstring_t var1Value;
    {
        std::tostringstream_t ossRv;
        ossRv << a_var1Value;
        var1Value = ossRv.str();
    }

    // var2Value
    std::tstring_t var2Value;
    {
        std::tostringstream_t ossRv;
        ossRv << a_var2Value;
        var2Value = ossRv.str();
    }

    _construct(a_type, a_sourceInfo, a_var1, a_var2, var1Value, var2Value, a_exprSign,
        a_nativeError, a_stackTrace, a_comment);
    switch (a_type) {
    case rtMsgbox:
    case rtStdout:
    case rtLog:
        _initPlain();
        break;
    default:
        _report = xUNKNOWN_CSTRING;
        break;
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
