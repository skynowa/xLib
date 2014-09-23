/**
 * \file  ErrorReport.inl
 * \brief debug report
 */

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
inline
ErrorReport::ErrorReport(
    culong_t        &a_nativeError,
    std::ctstring_t &a_file,
    culong_t        &a_line,
    std::ctstring_t &a_func,
    std::ctstring_t &a_stackTrace,
    std::ctstring_t &a_comment
) :
    _type          (rtUnknown),
    _report        (),
    _program       (),
    _processId     (0UL),
    _threadId      (0UL),
    _fileSize      (),
    _sourceFile    (),
    _sourceLine    (0UL),
    _functionName  (),
    _expression    (),
    _nativeError   (0UL),
    _nativeErrorStr(),
    _currentDate   (),
    _stackTrace    (),
    _comment       ()
{
    _construct(rtStdout, "", "", "", "", "", a_nativeError, a_file, a_line, a_func, a_stackTrace,
        a_comment);
    _initPlain();
}
//-------------------------------------------------------------------------------------------------
template<class T>
ErrorReport::ErrorReport(
    const ExType    &a_type,
    std::ctstring_t &a_var1,
    std::ctstring_t &a_var2,
    const T         &a_var1Value,
    const T         &a_var2Value,
    std::ctstring_t &a_exprSign,
    culong_t        &a_nativeError,
    std::ctstring_t &a_file,
    culong_t        &a_line,
    std::ctstring_t &a_func,
    std::ctstring_t &a_stackTrace,
    std::ctstring_t &a_comment
) :
    _type          (rtUnknown),
    _report        (),
    _program       (),
    _processId     (0UL),
    _threadId      (0UL),
    _fileSize      (),
    _sourceFile    (),
    _sourceLine    (0UL),
    _functionName  (),
    _expression    (),
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

    _construct(a_type, a_var1, a_var2, var1Value, var2Value, a_exprSign, a_nativeError, a_file,
        a_line, a_func, a_stackTrace, a_comment);
    switch (a_type) {
    case rtMsgbox:
        _initPlain();
        break;
    case rtStdout:
        _initPlain();
        break;
    case rtLog:
        _initPlain();
        break;
    default:
        _initPlain();
        break;
    }
}
//-------------------------------------------------------------------------------------------------
inline ErrorReport::ExType
ErrorReport::type() const
{
    return _type;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
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
inline void_t
ErrorReport::_construct(
    const ExType    &a_type,
    std::ctstring_t &a_var1,
    std::ctstring_t &a_var2,
    std::ctstring_t &a_var1Value,
    std::ctstring_t &a_var2Value,
    std::ctstring_t &a_exprSign,
    culong_t        &a_nativeError,
    std::ctstring_t &a_file,
    culong_t        &a_line,
    std::ctstring_t &a_func,
    std::ctstring_t &a_stackTrace,
    std::ctstring_t &a_comment
)
{
    SystemInfo sysInfo;

    _type         = a_type;

    _program      = Path( Path(Path::exe()).brief(::reportWidthMax) ).toUnix(false);
#if   xENV_WIN
    _processId    = ::GetCurrentProcessId();
#elif xENV_UNIX
    _processId    = ::getpid();
#endif
    _threadId     = (ulong_t)Thread::currentId();
    _fileSize     = String::formatBytes( static_cast<ulonglong_t>( File::size(Path::exe())) );

    _sourceFile   = Path( Path(a_file).brief(::reportWidthMax) ).toUnix(false);
    _sourceLine   = a_line;
    _functionName = a_func;
    _expression   = String::format(xT("%s (%s) %s %s (%s)"), a_var1.c_str(), a_var1Value.c_str(),
        a_exprSign.c_str(), a_var2.c_str(), a_var2Value.c_str());
    _nativeError  = a_nativeError;
    _nativeErrorStr = NativeError::format(a_nativeError);

    _currentDate  = DateTime::current().format(xT("%Y-%m-%d %H:%M:%S"));

#if xENV_UNIX
    _glibc        = sysInfo.glibcVersion();
    _libPthread   = sysInfo.libPthreadVersion();
#endif

    _stackTrace   = a_stackTrace;
    _comment      = a_comment.empty() ? Const::hyphen() : a_comment;
}
//-------------------------------------------------------------------------------------------------
inline void_t
ErrorReport::_initPlain()
{
    std::tostringstream_t ossRv;
    std::ctstring_t       margin = xT("  ");

    ossRv
        << margin << xT("ErrorReport")                        << "\n"
                                                              << "\n"
                                                              << "\n"
        << margin << xT("Program:       ") << _program        << "\n"
        << margin << xT("Process id:    ") << _processId      << "\n"
        << margin << xT("Thread id:     ") << _threadId       << "\n"
        << margin << xT("File size:     ") << _fileSize       << "\n"
                                                              << "\n"
        << margin << xT("Source file:   ") << _sourceFile     << "\n"
        << margin << xT("Source line:   ") << _sourceLine     << "\n"
        << margin << xT("Function name: ") << _functionName   << "\n"
        << margin << xT("Expression:    ") << _expression     << "\n"
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
