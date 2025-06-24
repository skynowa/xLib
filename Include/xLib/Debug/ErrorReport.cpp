/**
 * \file  ErrorReport.cpp
 * \brief debug report
 */


#include "ErrorReport.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/DateTime.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Fs/Path.h>
#include <xLib/Sync/ThreadCurrent.h>

//-------------------------------------------------------------------------------------------------
namespace
{

std::csize_t reportWidthMax = 100 - 17;   // MAGIC: reportWidthMax

}
//-------------------------------------------------------------------------------------------------
namespace xl::debug
{
//-------------------------------------------------------------------------------------------------
ErrorReport::ErrorReport(
    cType             a_type,
    culong_t          a_nativeError,
    const SourceInfo &a_sourceInfo,
    std::ctstring_t  &a_stackTrace,
    std::ctstring_t  &a_comment
)
{
    _construct(a_type, a_sourceInfo, a_nativeError, a_stackTrace, a_comment);

    switch (a_type) {
    case Type::Stdout:
    case Type::Log:
    case Type::StdoutLog:
    case Type::Exception:
    	_initPlain();
    	break;
    case Type::Unknown:
    	break;
    }
}
//-------------------------------------------------------------------------------------------------
ErrorReport::ErrorReport(
    culong_t          a_nativeError,
    const SourceInfo &a_sourceInfo,
    std::ctstring_t  &a_stackTrace,
    std::ctstring_t  &a_comment
) :
	ErrorReport(Type::StdoutLog, a_nativeError, a_sourceInfo, a_stackTrace, a_comment)
{
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
ErrorReport::str() const /* final */
{
    return _report;
}
//-------------------------------------------------------------------------------------------------
ErrorReport::Type
ErrorReport::type() const
{
    return _type;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
ErrorReport::_construct(
    cType             a_type,
    const SourceInfo &a_sourceInfo,
    culong_t          a_nativeError,
    std::ctstring_t  &a_stackTrace,
    std::ctstring_t  &a_comment
)
{
	const auto &option = a_sourceInfo.option();

    _type             = a_type;

    _program          = Path::exe().brief(::reportWidthMax).toUnix(false).str();
#if   xENV_WIN
    _processId        = ::GetCurrentProcessId();
#elif xENV_UNIX
    _processId        = static_cast<ulong_t>( ::getpid() );
#endif
    _threadId         = (ulong_t)ThreadCurrent::id();

    _sourceFilePath   = Path(option.filePath).brief(::reportWidthMax).toUnix(false).str();
    _sourceLineNum    = option.lineNum;
    _sourceFuncName   = option.funcName;
    _sourceExpr       = a_sourceInfo.expr();
    _sourceExprValues = a_sourceInfo.exprValues();

    _nativeError      = a_nativeError;
    _nativeErrorStr   = NativeError::format(a_nativeError);

    _currentDate      = DateTime::current().format(xT("%Y-%m-%d %H:%M:%S"));
    _stackTrace       = a_stackTrace;

    _comment          = a_comment.empty() ? Const::hyphen() : a_comment;
}
//-------------------------------------------------------------------------------------------------
void_t
ErrorReport::_initPlain()
{
    _report = Format::str(
        xT("Program:       {}\n")
        xT("Process id:    {}\n")
        xT("Thread id:     {}\n")
        xT("\n")
        xT("Source file:   {}\n")
        xT("Source line:   {}\n")
        xT("Function name: {}\n")
        xT("Expression:    {}\n")
        xT("Expr Values:   {}\n")
        xT("Native error:  {}\n")
        xT("\n")
        xT("Current date:  {}\n")
        xT("\n")
        xT("Stack trace:\n")
        xT("{}\n")
        xT("\n")
        xT("Comment:       {}"),
        _program,
        _processId,
        _threadId,
        _sourceFilePath,
        _sourceLineNum,
        _sourceFuncName,
        _sourceExpr,
        _sourceExprValues,
        _nativeErrorStr,
        _currentDate,
        _stackTrace,
        _comment);
}
//-------------------------------------------------------------------------------------------------

} // namespace
