/**
 * \file  ErrorReport.inl
 * \brief debug report
 */


#include <xLib/Core/StdStream.h>
#include <xLib/Core/StdStreamOp.h>
#include <xLib/Core/Format.h>


xNAMESPACE_BEGIN2(xl, debug)

//-------------------------------------------------------------------------------------------------
template<typename T>
ErrorReport::ErrorReport(
    cType            &a_type,
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
    _type            (rtUnknown),
    _report          (),
    _program         (),
    _processId       (0UL),
    _threadId        (0UL),
    _sourceFilePath  (),
    _sourceLineNum   (),
    _sourceFuncName  (),
    _sourceExpr      (),
    _sourceExprValues(),
    _nativeError     (0UL),
    _nativeErrorStr  (),
    _currentDate     (),
    _stackTrace      (),
    _comment         ()
{
    std::ctstring_t var1Value = Format::str(xT("{}"), a_var1Value);
    std::ctstring_t var2Value = Format::str(xT("{}"), a_var2Value);

    _construct(a_type, a_sourceInfo, a_var1, a_var2, var1Value, var2Value, a_exprSign,
        a_nativeError, a_stackTrace, a_comment);
    switch (a_type) {
    case rtMsgbox:
    case rtStdout:
    case rtLog:
    case rtStdoutLog:
    case rtException:
        _initPlain();
        break;
    default:
        _report = xUNKNOWN_CSTRING;
        break;
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, debug)
