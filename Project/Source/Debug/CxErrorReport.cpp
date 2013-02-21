/**
 * \file  CxErrorReport.cpp
 * \brief debug report
 */


#include <xLib/Debug/CxErrorReport.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>
#include <xLib/Common/CxDateTime.h>
#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Common/CxConsole.h>
#include <xLib/Debug/CxException.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxCurrentThread.h>
#include <xLib/Sync/CxCurrentProcess.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* virtual */
CxErrorReport::~CxErrorReport() {
    
}
//------------------------------------------------------------------------------
void
CxErrorReport::_construct(
    const ExType         &a_crtType,
    const std::tstring_t &a_csVar1,       
    const std::tstring_t &a_csVar2,
    const std::tstring_t &a_csVar1Value,  
    const std::tstring_t &a_csVar2Value,
    const std::tstring_t &a_csExprSign,
    const ulong_t        &a_culLastError,
    const std::tstring_t &a_csFile,
    const ulong_t        &a_culLine,
    const std::tstring_t &a_csFunc,
    const std::tstring_t &a_csDate,
    const std::tstring_t &a_csTime,
    const std::tstring_t &a_csStackTrace,
    const std::tstring_t &a_csComment
)
{
    const size_t cuiReportWidthMax = 46U;   // MAGIC: cuiReportWidthMax


    m_rtType          = a_crtType;

    m_sProgram        = CxPath( CxPath(CxPath::exe()).brief(cuiReportWidthMax) ).toUnix(false);
    m_ulProcessId     = (ulong_t)CxCurrentProcess::id();
    m_ulThreadId      = (ulong_t)CxCurrentThread::id();
    m_sFileSize       = CxString::formatBytes( static_cast<ulonglong_t>( CxFile::size(CxPath::exe())) );

    m_sSourceFile     = CxPath( CxPath(a_csFile).brief(cuiReportWidthMax) ).toUnix(false);
    m_ulSourceLine    = a_culLine;
    m_sFunctionName   = a_csFunc;
    m_sExpression     = CxString::format(xT("%s (%s) %s %s (%s)"), 
                                          a_csVar1.c_str(), a_csVar1Value.c_str(), a_csExprSign.c_str(), 
                                          a_csVar2.c_str(), a_csVar2Value.c_str());
    m_sExprSign       = a_csExprSign;
    m_ulLastError     = a_culLastError;
    m_sLastErrorStr   = CxLastError::format(a_culLastError);

    m_sCurrentDate    = CxDateTime::current().format(CxDateTime::ftDateTime);
    m_sBuildDate      = CxString::format(xT("%s/%s"), a_csDate.c_str(), a_csTime.c_str());
    m_sBuildType      = CxDebugger().isDebugBuild() ? xT("debug") : xT("release");
    m_sOsVersion      = CxSystemInfo::formatOsType( CxSystemInfo::os() );
    m_sOsArchitecture = CxSystemInfo::formatOsArch( CxSystemInfo::osArch() );

    m_sStackTrace     = a_csStackTrace;
    m_sComment        = a_csComment.empty() ? CxConst::xHYPHEN : a_csComment;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CxErrorReport::_initPlain() {
    std::tostringstream_t ossReport;

    ossReport
        << xT("CxErrorReport    ")                      << std::endl
                                                        << std::endl
                                                        << std::endl
        << xT("Program:         ") << m_sProgram        << std::endl
        << xT("Process id:      ") << m_ulProcessId     << std::endl
        << xT("Thread id:       ") << m_ulThreadId      << std::endl
        << xT("File size:       ") << m_sFileSize       << std::endl
                                                        << std::endl
        << xT("Source file:     ") << m_sSourceFile     << std::endl
        << xT("Source line:     ") << m_ulSourceLine    << std::endl
        << xT("Function name:   ") << m_sFunctionName   << std::endl
        << xT("Expression:      ") << m_sExpression     << std::endl
        << xT("Last error:      ") << m_sLastErrorStr   << std::endl
                                                        << std::endl
        << xT("Current date:    ") << m_sCurrentDate    << std::endl
        << xT("Build date:      ") << m_sBuildDate      << std::endl
        << xT("Build type:      ") << m_sBuildType      << std::endl
        << xT("OS version:      ") << m_sOsVersion      << std::endl
        << xT("OS architecture: ") << m_sOsArchitecture << std::endl
                                                        << std::endl
        << xT("Stack trace:     ")                      << std::endl
                                   << m_sStackTrace     << std::endl
                                                        << std::endl
        << xT("Comment:         ") << m_sComment        << std::endl;

    m_sReport = ossReport.str();
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
