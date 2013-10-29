/**
 * \file  CxErrorReport.cpp
 * \brief debug report
 */


#include <xLib/Debug/CxErrorReport.h>

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
#include <xLib/Sync/CxProcess.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxErrorReport::_construct(
    const ExType    &a_crtType,
    std::ctstring_t &a_csVar1,
    std::ctstring_t &a_csVar2,
    std::ctstring_t &a_csVar1Value,
    std::ctstring_t &a_csVar2Value,
    std::ctstring_t &a_csExprSign,
    culong_t        &a_culLastError,
    std::ctstring_t &a_csFile,
    culong_t        &a_culLine,
    std::ctstring_t &a_csFunc,
    std::ctstring_t &a_csDate,
    std::ctstring_t &a_csTime,
    std::ctstring_t &a_csStackTrace,
    std::ctstring_t &a_csComment
)
{
    std::csize_t cuiReportWidthMax = 46U;   // MAGIC: cuiReportWidthMax

    type          = a_crtType;

    program        = CxPath( CxPath(CxPath::exe()).brief(cuiReportWidthMax) ).toUnix(false);
    processId     = (ulong_t)CxProcess::currentId();
    threadId      = (ulong_t)CxThread::currentId();
    fileSize       = CxString::formatBytes( static_cast<ulonglong_t>( CxFile::size(CxPath::exe())) );

    sourceFile     = CxPath( CxPath(a_csFile).brief(cuiReportWidthMax) ).toUnix(false);
    sourceLine    = a_culLine;
    functionName   = a_csFunc;
    expression     = CxString::format(xT("%s (%s) %s %s (%s)"),
                                          a_csVar1.c_str(), a_csVar1Value.c_str(), a_csExprSign.c_str(),
                                          a_csVar2.c_str(), a_csVar2Value.c_str());
    exprSign       = a_csExprSign;
    lastError     = a_culLastError;
    lastErrorStr   = CxLastError::format(a_culLastError);

    currentDate    = CxDateTime::current().format(CxDateTime::ftDateTime);
    buildDate      = CxString::format(xT("%s/%s"), a_csDate.c_str(), a_csTime.c_str());
    buildType      = CxDebugger().isDebugBuild() ? xT("debug") : xT("release");
    osVersion      = CxSystemInfo::formatOsType( CxSystemInfo::os() );
    osArchitecture = CxSystemInfo::formatOsArch( CxSystemInfo::osArch() );

    stackTrace     = a_csStackTrace;
    comment        = a_csComment.empty() ? CxConst::xHYPHEN() : a_csComment;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxErrorReport::_initPlain()
{
    std::tostringstream_t ossReport;

    ossReport
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

    report = ossReport.str();
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
