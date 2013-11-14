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


xNAMESPACE_BEGIN(NxLib)

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
    case rtMsgboxPlain:
        _initPlain();
        break;
    case rtStdoutPlain:
        _initPlain();
        break;
    case rtLoggingPlain:
        _initPlain();
        break;
    default:
        _initPlain();
        break;
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
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

    std::csize_t reportWidthMax = 46U;   // MAGIC: reportWidthMax

    type           = a_type;

    program        = CxPath( CxPath(CxPath::exe()).brief(reportWidthMax) ).toUnix(false);
#if xOS_ENV_WIN
    processId      = ::GetCurrentProcessId();
#else
    processId      = ::getpid();
#endif
    threadId       = (ulong_t)CxThread::currentId();
    fileSize       = CxString::formatBytes( static_cast<ulonglong_t>( CxFile::size(CxPath::exe())) );

    sourceFile     = CxPath( CxPath(a_file).brief(reportWidthMax) ).toUnix(false);
    sourceLine     = a_line;
    functionName   = a_func;
    expression     = CxString::format(xT("%s (%s) %s %s (%s)"),
                                          a_var1.c_str(), a_var1Value.c_str(), a_exprSign.c_str(),
                                          a_var2.c_str(), a_var2Value.c_str());
    exprSign       = a_exprSign;
    lastError      = a_lastError;
    lastErrorStr   = CxLastError::format(a_lastError);

    currentDate    = CxDateTime::current().format(CxDateTime::ftDateTime);
    buildDate      = CxString::format(xT("%s/%s"), a_date.c_str(), a_time.c_str());
    buildType      = CxDebugger().isDebugBuild() ? xT("debug") : xT("release");
    osVersion      = sysInfo.formatOsType( sysInfo.os() );
    osArchitecture = sysInfo.formatOsArch( sysInfo.osArch() );

    stackTrace     = a_stackTrace;
    comment        = a_comment.empty() ? CxConst::hyphen() : a_comment;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxErrorReport::_initPlain()
{
    std::tostringstream_t ossRv;

    ossRv
        << xT("CxErrorReport    ")                   << std::endl
                                                     << std::endl
                                                     << std::endl
        << xT("Program:         ") << program        << std::endl
        << xT("Process id:      ") << processId      << std::endl
        << xT("Thread id:       ") << threadId       << std::endl
        << xT("File size:       ") << fileSize       << std::endl
                                                     << std::endl
        << xT("Source file:     ") << sourceFile     << std::endl
        << xT("Source line:     ") << sourceLine     << std::endl
        << xT("Function name:   ") << functionName   << std::endl
        << xT("Expression:      ") << expression     << std::endl
        << xT("Last error:      ") << lastErrorStr   << std::endl
                                                     << std::endl
        << xT("Current date:    ") << currentDate    << std::endl
        << xT("Build date:      ") << buildDate      << std::endl
        << xT("Build type:      ") << buildType      << std::endl
        << xT("OS version:      ") << osVersion      << std::endl
        << xT("OS architecture: ") << osArchitecture << std::endl
                                                     << std::endl
        << xT("Stack trace:     ")                   << std::endl
                                   << stackTrace     << std::endl
                                                     << std::endl
        << xT("Comment:         ") << comment        << std::endl;

    report = ossRv.str();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
