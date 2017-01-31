/**
 * \file  ErrorReport.cpp
 * \brief debug report
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "ErrorReport.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/DateTime.h>
#include <xLib/System/Console.h>
#include <xLib/Debug/BuildInfo.h>
#include <xLib/Debug/Exception.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>
#include <xLib/Sync/Thread.h>


xNAMESPACE_ANONYM_BEGIN

std::csize_t reportWidthMax = 100 - 17;   // MAGIC: reportWidthMax

xNAMESPACE_ANONYM_END

xNAMESPACE_BEGIN2(xlib, debug)

//-------------------------------------------------------------------------------------------------
xINLINE
ErrorReport::ErrorReport(
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
    _construct(rtStdout, a_sourceInfo, xT(""), xT(""), xT(""), xT(""), xT(""), a_nativeError,
        a_stackTrace, a_comment);
    _initPlain();
}
//-------------------------------------------------------------------------------------------------
xINLINE ErrorReport::ExType
ErrorReport::type() const
{
    return _type;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
ErrorReport::toString() const
{
    return _report;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
ErrorReport::_construct(
    cExType          &a_type,
    const SourceInfo &a_sourceInfo,
    std::ctstring_t  &a_var1,
    std::ctstring_t  &a_var2,
    std::ctstring_t  &a_var1Value,
    std::ctstring_t  &a_var2Value,
    std::ctstring_t  &a_exprSign,
    culong_t         &a_nativeError,
    std::ctstring_t  &a_stackTrace,
    std::ctstring_t  &a_comment
)
{
    _type             = a_type;

    _program          = Path( Path(Path::exe()).brief(::reportWidthMax) ).toUnix(false);
#if   xENV_WIN
    _processId        = ::GetCurrentProcessId();
#elif xENV_UNIX
    _processId        = static_cast<ulong_t>( ::getpid() );
#endif
    _threadId         = (ulong_t)Thread::currentId();

    _sourceFilePath   = Path( Path(a_sourceInfo.data().filePath).brief(::reportWidthMax) ).toUnix(false);
    _sourceLineNum    = a_sourceInfo.data().lineNum;
    _sourceFuncName   = a_sourceInfo.data().funcName;
    _sourceExpr       = Format::str(xT("{} {} {}"), a_var1, a_exprSign, a_var2);
    _sourceExprValues = Format::str(xT("{} {} {}"), a_var1Value, a_exprSign, a_var2Value);

    _nativeError      = a_nativeError;
    _nativeErrorStr   = NativeError::format(a_nativeError);

    _currentDate      = DateTime::current().format(xT("%Y-%m-%d %H:%M:%S"));
    _stackTrace       = a_stackTrace;

    _comment          = a_comment.empty() ? Const::hyphen() : a_comment;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
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

xNAMESPACE_END2(xlib, debug)
