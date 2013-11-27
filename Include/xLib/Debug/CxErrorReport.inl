/**
 * \file  CxErrorReport.inl
 * \brief debug report
 */

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxDateTime.h>
#include <xLib/System/CxSystemInfo.h>
#include <xLib/System/CxConsole.h>
#include <xLib/Debug/CxException.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxThread.h>


xNAMESPACE_ANONYM_BEGIN

std::csize_t reportWidthMax = 46U;   // MAGIC: reportWidthMax

xNAMESPACE_ANONYM_END

xNAMESPACE_BEGIN(NxLib)

//-------------------------------------------------------------------------------------------------
inline
CxErrorReport::CxErrorReport(
    culong_t        &a_lastError,
    std::ctstring_t &a_file,
    culong_t        &a_line,
    std::ctstring_t &a_func,
    std::ctstring_t &a_date,
    std::ctstring_t &a_time,
    std::ctstring_t &a_stackTrace
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
    _lastError     (0UL),
    _lastErrorStr  (),
    _currentDate   (),
    _buildDate     (),
    _buildType     (),
    _osVersion     (),
    _osArchitecture(),
    _stackTrace    (),
    _comment       ()
{
    _construct(rtStdout, "", "", "", "", "", a_lastError, a_file, a_line, a_func, a_date, a_time,
        a_stackTrace, "");
    _initPlain();
}
//-------------------------------------------------------------------------------------------------
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
    _lastError     (0UL),
    _lastErrorStr  (),
    _currentDate   (),
    _buildDate     (),
    _buildType     (),
    _osVersion     (),
    _osArchitecture(),
    _stackTrace    (),
    _comment       ()
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

    _construct(a_type, a_var1, a_var2, var1Value, var2Value, a_exprSign, a_lastError, a_file,
        a_line, a_func, a_date, a_time, a_stackTrace, a_comment);
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
inline CxErrorReport::ExType
CxErrorReport::type() const
{
    return _type;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxErrorReport::toString() const
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
CxErrorReport::_construct(
    const ExType    &a_type,
    std::ctstring_t &a_var1,
    std::ctstring_t &a_var2,
    std::ctstring_t &a_var1Value,
    std::ctstring_t &a_var2Value,
    std::ctstring_t &a_exprSign,
    culong_t        &a_lastError,
    std::ctstring_t &a_file,
    culong_t        &a_line,
    std::ctstring_t &a_func,
    std::ctstring_t &a_date,
    std::ctstring_t &a_time,
    std::ctstring_t &a_stackTrace,
    std::ctstring_t &a_comment
)
{
    CxSystemInfo sysInfo;

    _type           = a_type;

    _program        = CxPath( CxPath(CxPath::exe()).brief(::reportWidthMax) ).toUnix(false);
#if xOS_ENV_WIN
    _processId      = ::GetCurrentProcessId();
#else
    _processId      = ::getpid();
#endif
    _threadId       = (ulong_t)CxThread::currentId();
    _fileSize       = CxString::formatBytes( static_cast<ulonglong_t>( CxFile::size(CxPath::exe())) );

    _sourceFile     = CxPath( CxPath(a_file).brief(::reportWidthMax) ).toUnix(false);
    _sourceLine     = a_line;
    _functionName   = a_func;
    _expression     = CxString::format(xT("%s (%s) %s %s (%s)"), a_var1.c_str(),
        a_var1Value.c_str(), a_exprSign.c_str(), a_var2.c_str(), a_var2Value.c_str());
    _lastError      = a_lastError;
    _lastErrorStr   = CxLastError::format(a_lastError);

    _currentDate    = CxDateTime::current().format(CxDateTime::ftDateTime);
    _buildDate      = CxString::format(xT("%s/%s"), a_date.c_str(), a_time.c_str());
    _buildType      = CxDebugger().isDebugBuild() ? xT("debug") : xT("release");
    _osVersion      = sysInfo.formatOsType();
    _osArchitecture = sysInfo.formatOsArch();

    _stackTrace     = a_stackTrace;
    _comment        = a_comment.empty() ? CxConst::hyphen() : a_comment;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxErrorReport::_initPlain()
{
    std::tostringstream_t ossRv;

    ossRv
        << xT("CxErrorReport    ")                    << "\n"
                                                      << "\n"
                                                      << "\n"
        << xT("Program:         ") << _program        << "\n"
        << xT("Process id:      ") << _processId      << "\n"
        << xT("Thread id:       ") << _threadId       << "\n"
        << xT("File size:       ") << _fileSize       << "\n"
                                                      << "\n"
        << xT("Source file:     ") << _sourceFile     << "\n"
        << xT("Source line:     ") << _sourceLine     << "\n"
        << xT("Function name:   ") << _functionName   << "\n"
        << xT("Expression:      ") << _expression     << "\n"
        << xT("Last error:      ") << _lastErrorStr   << "\n"
                                                      << "\n"
        << xT("Current date:    ") << _currentDate    << "\n"
        << xT("Build date:      ") << _buildDate      << "\n"
        << xT("Build type:      ") << _buildType      << "\n"
        << xT("OS version:      ") << _osVersion      << "\n"
        << xT("OS architecture: ") << _osArchitecture << "\n"
                                                      << "\n"
        << xT("Stack trace:     ")                    << "\n"
                                   << _stackTrace     << "\n"
                                                      << "\n"
        << xT("Comment:         ") << _comment        << std::endl;

    _report = ossRv.str();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
