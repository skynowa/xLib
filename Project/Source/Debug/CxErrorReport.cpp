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

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* virtual */
CxErrorReport::~CxErrorReport() {
    
}
void
CxErrorReport::_vConstruct(
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
    

    const size_t cuiReportWidthMax = 46U;


    m_rtType          = a_crtType;

    m_sProgram        = CxPath::sToUnix( CxPath::sShort(CxPath::sExe(), cuiReportWidthMax), false );
    m_ulProcessId     = (ulong_t)CxCurrentProcess::ulId();
    m_ulThreadId      = (ulong_t)CxCurrentThread::ulId();
    m_sFileSize       = CxString::sFormatBytes( static_cast<ulonglong_t>( CxFile::llSize(CxPath::sExe())) );

    m_sSourceFile     = CxPath::sToUnix( CxPath::sShort(a_csFile, cuiReportWidthMax), false );
    m_ulSourceLine    = a_culLine;
    m_sFunctionName   = a_csFunc;
    m_sExpression     = CxString::sFormat(xT("%s (%s) %s %s (%s)"), 
                                          a_csVar1.c_str(), a_csVar1Value.c_str(), a_csExprSign.c_str(), 
                                          a_csVar2.c_str(), a_csVar2Value.c_str());
    m_sExprSign       = a_csExprSign;
    m_ulLastError     = a_culLastError;
    m_sLastErrorStr   = CxLastError::sFormat(a_culLastError);

    m_sCurrentDate    = CxDateTime::dtCurrent().sFormat(CxDateTime::ftDateTime);
    m_sBuildDate      = CxString::sFormat(xT("%s/%s"), a_csDate.c_str(), a_csTime.c_str());
    m_sBuildType      = CxDebugger().bIsDebugBuild() ? xT("debug") : xT("release");
    m_sOsVersion      = CxSystemInfo::sFormatOsType( CxSystemInfo::osOS() );
    m_sOsArchitecture = CxSystemInfo::sFormatOsArch( CxSystemInfo::oaOsArch() );

    m_sStackTrace     = a_csStackTrace;
    m_sComment        = a_csComment.empty() ? CxConst::xHYPHEN : a_csComment;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxErrorReport::_vInitPlain() {
    std::tostringstream_t ossReport;

    ossReport \
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
        << xT("Stack trace:     ") << std::endl 
                                   << m_sStackTrace     << std::endl
                                                        << std::endl
        << xT("Comment:         ") << m_sComment        << std::endl;

    m_sReport = ossReport.str();
}
//---------------------------------------------------------------------------
void
CxErrorReport::_vInitHtml() {
    std::tostringstream_t ossReport;

    ossReport \
        << xT("<pre>")                                         << std::endl
        << xT("<b><u>CxErrorReport</u></b>")                   << std::endl
                                                               << std::endl
                                                               << std::endl
        << xT("<b>Program:</b>         ") << m_sProgram        << std::endl
        << xT("<b>Process id:</b>      ") << m_ulProcessId     << std::endl
        << xT("<b>Thread id:</b>       ") << m_ulThreadId      << std::endl
        << xT("<b>File size:</b>       ") << m_sFileSize       << std::endl
                                                               << std::endl
        << xT("<b>Source file:</b>     ") << m_sSourceFile     << std::endl
        << xT("<b>Source line:</b>     ") << m_ulSourceLine    << std::endl
        << xT("<b>Function name:</b>   ") << m_sFunctionName   << std::endl
        << xT("<b>Expression:</b>      ") << m_sExpression     << std::endl
        << xT("<b>Last error:</b>      ") << m_sLastErrorStr   << std::endl
                                                               << std::endl
        << xT("<b>Current date:</b>    ") << m_sCurrentDate    << std::endl
        << xT("<b>Build date:</b>      ") << m_sBuildDate      << std::endl
        << xT("<b>Build type:</b>      ") << m_sBuildType      << std::endl
        << xT("<b>OS version:</b>      ") << m_sOsVersion      << std::endl
        << xT("<b>OS architecture:</b> ") << m_sOsArchitecture << std::endl
                                                               << std::endl
        << xT("<b>Stack trace:</b>     ") << std::endl 
                                          << m_sStackTrace     << std::endl
                                                               << std::endl
        << xT("<b>Comment:</b>         ") << m_sComment        << std::endl
        << xT("<pre>")                                         << std::endl;

    m_sReport = ossReport.str();
}
//---------------------------------------------------------------------------
void
CxErrorReport::_vInitFormated() {
#if   xOS_ENV_WIN
    m_sReport = CxString::sFormat(
        xT("{\\rtf1\\ansi\\ansicpg1251\\deff0\\deflang1049{\\fonttbl{\\f0\\fswiss\\fcharset0 Arial;}{\\f1\\fnil DejaVu Sans Mono;}{\\f2\\fswiss\\fcharset204{\\*\\fname Arial;}Arial CYR;}{\\f3\\fswiss\\fprq2\\fcharset204{\\*\\fname Arial;}Arial CYR;}{\\f4\\fswiss\\fprq2\\fcharset0 Arial;}}")
        xT("{\\colortbl ;\\red255\\green0\\blue0;\\red0\\green0\\blue0;\\red255\\green0\\blue255;\\red0\\green255\\blue255;\\red255\\green255\\blue0;}")
        xT("\\viewkind4\\uc1\\pard\\lang1033\\ul\\b\\f0\\fs20 %s\\cf1\\lang1049\\ulnone\\b0\\f1\\fs16\\par")
        xT("\\cf0\\b\\f2\\fs20\\par")
        xT("\\cf2\\b\\f3 %s\\b0   \\lang1033\\f0  \\cf2 %s\\cf1\\lang1049\\f2\\par")
        xT("\\cf2\\b\\f3 %s\\b0   \\lang1033\\f4   \\f0 %lu\\cf1\\lang1049\\f2\\par")
        xT("\\cf2\\b\\f3 %s\\b0   \\lang1033\\f4   \\f0 %lu\\cf1\\lang1049\\f2\\par")
        xT("\\cf2\\b\\f3 %s\\b0   \\lang1033\\f4     \\f0 %s\\par")
        xT("\\cf1\\lang1049\\f2\\par")
        xT("\\cf0\\b %s\\b0   \\lang1033\\f0   \\b %s\\cf1\\lang1049\\b0\\f2\\par")
        xT("\\cf0\\b %s\\b0   \\lang1033\\f0  \\cf3\\b\\f4 %lu\\lang1049\\f3\\par")
        xT("\\cf0\\f2 %s\\lang1033\\f0 \\cf4\\f4 %s\\lang1049\\f3\\par")
        xT("\\cf0\\f2 %s\\b0   \\lang1033\\f0  \\cf5\\b\\f4 %s\\cf0\\lang1049\\b0\\f2\\par")
        xT("\\b %s\\lang1033\\b0\\f0      \\cf1\\b\\f4 %s\\b0\\par")
        xT("\\cf0\\lang1049\\f2\\par")
        xT("\\b %s\\lang1033\\b0\\f0    %s\\lang1049\\f2\\par")
        xT("\\b %s\\lang1033\\b0\\f0     %s\\lang1049\\f2\\par")
        xT("\\b %s\\lang1033\\b0\\f0     %s\\lang1049\\f2\\par")
        xT("\\b %s\\lang1033\\b0\\f0    %s\\lang1049\\f2\\par")
        xT("\\b %s\\lang1033\\f0  \\b0 %s\\par")
        xT("\\lang1049\\f2\\par")
        xT("\\b %s\\b0  \\lang1033\\f0   %s\\lang1049\\f2\\par")
        xT("\\lang1049\\f2\\par")
        xT("\\b %s\\b0  \\lang1033\\f0   %s\\lang1049\\f2\\par")
        xT("}"),

        xT("CxErrorReport "),

        xT("Program:         "), m_sProgram.c_str(),
        xT("Process id:      "), m_ulProcessId,
        xT("Thread id:       "), m_ulThreadId,
        xT("File size:       "), m_sFileSize.c_str(),

        xT("Source file:     "), m_sSourceFile.c_str(),
        xT("Source line:     "), m_ulSourceLine,
        xT("Function name:   "), m_sFunctionName.c_str(),
        xT("Expression:      "), m_sExpression.c_str(),
        xT("Last error:      "), m_sLastErrorStr.c_str(),

        xT("Current date:    "), m_sCurrentDate.c_str(),
        xT("Build date:      "), m_sBuildDate.c_str(),
        xT("Build type:      "), m_sBuildType.c_str(),
        xT("OS version:      "), m_sOsVersion.c_str(),
        xT("OS architecture: "), m_sOsArchitecture.c_str(),

        xT("Stack trace:     "), m_sStackTrace.c_str(),

        xT("Comment:         "), m_sComment.c_str()
    );
#elif xOS_ENV_UNIX
    m_sReport = CxString::sFormat(
        xT("%s\n")        //CxErrorReport
        xT("#  \n")

        xT("%s%s\n")      //Program
        xT("%s%lu\n")     //Process id
        xT("%s%lu\n")     //Thread id
        xT("%s%s\n")      //file size
        xT("#  \n")

        xT("%s%s\n")      //Source file
        xT("%s%s\n")      //Source line
        xT("%s%s\n")      //Function name
        xT("%s%s\n")      //Expression
        xT("%s%s\n")      //Last error
        xT("#  \n")

        xT("%s%s\n")      //Current date
        xT("%s%s\n")      //Build date
        xT("%s%s\n")      //Build type
        xT("%s%s\n")      //OS version
        xT("%s%s\n")      //OS architecture
        xT("#  \n")

        xT("%s\n%s\n")    //stack trace
        xT("#  \n")

        xT("%s%s\n")      //Comment
        xT("#  "),

        xT("#  CxErrorReport    "),

        xT("#  Program:         "), m_sProgram.c_str(),
        xT("#  Process id:      "), m_ulProcessId,
        xT("#  Thread id:       "), m_ulThreadId,
        xT("#  File size:       "), m_sFileSize.c_str(),

        xT("#  Source file:     "), CxConsole().sSetTextColor( m_sSourceFile,                         CxConsole::fgWhite,   true, false, CxConsole::bgBlack, false ).c_str(),
        xT("#  Source line:     "), CxConsole().sSetTextColor( CxString::string_cast(m_ulSourceLine), CxConsole::fgMagenta, true, true,  CxConsole::bgBlack, false ).c_str(),
        xT("#  Function name:   "), CxConsole().sSetTextColor( m_sFunctionName,                       CxConsole::fgCyan,    true, false, CxConsole::bgBlack, false ).c_str(),
        xT("#  Expression:      "), CxConsole().sSetTextColor( m_sExpression,                         CxConsole::fgYellow,  true, false, CxConsole::bgBlack, false ).c_str(),
        xT("#  Last error:      "), CxConsole().sSetTextColor( m_sLastErrorStr,                       CxConsole::fgRed,     true, false, CxConsole::bgBlack, false ).c_str(),

        xT("#  Current date:    "), m_sCurrentDate.c_str(),
        xT("#  Build date:      "), m_sBuildDate.c_str(),
        xT("#  Build type:      "), m_sBuildType.c_str(),
        xT("#  OS version:      "), m_sOsVersion.c_str(),
        xT("#  OS architecture: "), m_sOsArchitecture.c_str(),
        xT("#  Stack trace:     "), m_sStackTrace.c_str(),

        xT("#  Comment:         "), CxConsole().sSetTextColor( m_sComment,                             CxConsole::fgYellow_, false, false, CxConsole::bgBlue,  false ).c_str()
    );
#endif
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
