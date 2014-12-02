/**
 * \file  ErrorReport.cpp
 * \brief debug report
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "ErrorReport.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/DateTime.h>
#include <xLib/System/SystemInfo.h>
#include <xLib/System/Console.h>
#include <xLib/Debug/BuildInfo.h>
#include <xLib/Debug/Exception.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>
#include <xLib/Sync/Thread.h>


xNAMESPACE_ANONYM_BEGIN

std::csize_t reportWidthMax = 46U;   // MAGIC: reportWidthMax

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
    _type          (rtUnknown),
    _report        (),
    _program       (),
    _processId     (0UL),
    _threadId      (0UL),
    _fileSize      (),
    _sourceFilePath    (),
    _sourceLineNum    (),
    _sourceFuncName    (),
    _sourceExpr    (),
    _nativeError   (0UL),
    _nativeErrorStr(),
    _currentDate   (),
    _stackTrace    (),
    _comment       ()
{
    _construct(rtStdout, a_sourceInfo, "", "", "", "", "", a_nativeError, a_stackTrace, a_comment);
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
    const ExType     &a_type,
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
#if xENV_UNIX
    SystemInfo sysInfo;
#endif

    _type           = a_type;

    _program        = Path( Path(Path::exe()).brief(::reportWidthMax) ).toUnix(false);
#if   xENV_WIN
    _processId      = ::GetCurrentProcessId();
#elif xENV_UNIX
    _processId      = ::getpid();
#endif
    _threadId       = (ulong_t)Thread::currentId();
    _fileSize       = String::formatBytes( File::size(Path::exe()) );

    _sourceFilePath = Path( Path(a_sourceInfo.filePath()).brief(::reportWidthMax) ).toUnix(false);
    _sourceLineNum  = a_sourceInfo.lineNum();
    _sourceFuncName = a_sourceInfo.funcName();
    _sourceExpr     = String::format(xT("%s (%s) %s %s (%s)"), a_var1.c_str(), a_var1Value.c_str(),
        a_exprSign.c_str(), a_var2.c_str(), a_var2Value.c_str());
    _nativeError    = a_nativeError;
    _nativeErrorStr = NativeError::format(a_nativeError);

    _currentDate    = DateTime::current().format(xT("%Y-%m-%d %H:%M:%S"));

#if xENV_UNIX
    _glibc          = sysInfo.glibcVersion();
    _libPthread     = sysInfo.libPthreadVersion();
#endif

    _stackTrace     = a_stackTrace;
    _comment        = a_comment.empty() ? Const::hyphen() : a_comment;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
ErrorReport::_initPlain()
{
    std::ctstring_t  margin = xT("  ");

    std::tostringstream_t ossRv;
    ossRv
        << margin << xT("ErrorReport")                        << "\n"
                                                              << "\n"
                                                              << "\n"
        << margin << xT("Program:       ") << _program        << "\n"
        << margin << xT("Process id:    ") << _processId      << "\n"
        << margin << xT("Thread id:     ") << _threadId       << "\n"
        << margin << xT("File size:     ") << _fileSize       << "\n"
                                                              << "\n"
        << margin << xT("Source file:   ") << _sourceFilePath << "\n"
        << margin << xT("Source line:   ") << _sourceLineNum  << "\n"
        << margin << xT("Function name: ") << _sourceFuncName << "\n"
        << margin << xT("Expression:    ") << _sourceExpr     << "\n"
        << margin << xT("Native error:  ") << _nativeErrorStr << "\n"
                                                              << "\n"
        << margin << xT("Current date:  ") << _currentDate    << "\n"
    #if xENV_UNIX
                                                              << "\n"
        << margin << xT("GLIBC:         ") << _glibc          << "\n"
        << margin << xT("Pthread lib:   ") << _libPthread     << "\n"
    #endif
                                                              << "\n"
        << margin << xT("Stack trace:   ")                    << "\n"
                                           << _stackTrace     << "\n"
                                                              << "\n"
        << margin << xT("Comment:       ") << _comment        << std::endl;

    _report = ossRv.str();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
