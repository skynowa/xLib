/**
 * \file  ErrorReport.inl
 * \brief debug report
 */


#include <xLib/Core/Format.h>


namespace xl::debug
{

//-------------------------------------------------------------------------------------------------
template<typename T>
ErrorReport::ErrorReport(
    cType             a_type,
    std::ctstring_t  &a_var1,
    std::ctstring_t  &a_var2,
    const T          &a_var1Value,
    const T          &a_var2Value,
    std::ctstring_t  &a_exprSign,
    culong_t          a_nativeError,
    const SourceInfo &a_sourceInfo,
    std::ctstring_t  &a_stackTrace,
    std::ctstring_t  &a_comment
)
{
    std::ctstring_t &var1Value = Format::str(xT("{}"), a_var1Value);
    std::ctstring_t &var2Value = Format::str(xT("{}"), a_var2Value);

    _construct(a_type, a_sourceInfo, a_var1, a_var2, var1Value, var2Value, a_exprSign,
        a_nativeError, a_stackTrace, a_comment);

    switch (a_type) {
    case Type::rtMsgbox:
    case Type::rtStdout:
    case Type::rtLog:
    case Type::rtStdoutLog:
    case Type::rtException:
        _initPlain();
        break;
    }
}
//-------------------------------------------------------------------------------------------------

} // namespace
