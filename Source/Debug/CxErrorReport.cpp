/**
 * \file  CxErrorReport.cpp
 * \brief debug report
 */


#include <xLib/Debug/CxErrorReport.h>

#include <xLib/Common/CxException.h>
#include <xLib/Common/CxString.h>
#include <xLib/Common/CxDateTime.h>
#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Common/CxConsole.h>
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
CxErrorReport::CxErrorReport(
    const EType          &crtType,
    const std::tstring_t &csExp,
    const ulong_t         culLastError,
    const std::tstring_t &csFile,
    const ulong_t         culLine,
    const std::tstring_t &csFunc,
    const std::tstring_t &csDate,
    const std::tstring_t &csTime,
    const std::tstring_t &csStackTrace,
    const std::tstring_t &csComment
) :
    m_rtType         (rtUnknown),
    m_sReport        (),
    m_sProgram       (),
    m_ulProcessId    (0UL),
    m_ulThreadId     (0UL),
    m_sFileSize      (),
    m_sSourceFile    (),
    m_ulSourceLine   (0UL),
    m_sFunctionName  (),
    m_sExpression    (),
    m_ulLastError    (0UL),
    m_sLastErrorStr  (),
    m_sCurrentDate   (),
    m_sBuildDate     (),
    m_sBuildType     (),
    m_sOsVersion     (),
    m_sOsArchitecture(),
    m_sStackTrace    (),
    m_sComment       ()
{
    /*DEBUG*/

    (void)_bInitVars(crtType, csExp, culLastError, csFile, culLine, csFunc, csDate, csTime, csStackTrace, csComment.c_str());

    switch (crtType) {
        case rtMsgboxPlain:     { _bInitPlain();    }   break;
        case rtMsgboxFormated:  { _bInitFormated(); }   break;
        case rtStdoutPlain:     { _bInitPlain();    }   break;
        case rtStdoutHtml:      { _bInitHtml();     }   break;
        case rtLoggingPlain:    { _bInitPlain();    }   break;
        case rtLoggingHtml:     { _bInitHtml();     }   break;

        default:                { _bInitPlain();    }   break;
    }
}
//---------------------------------------------------------------------------
CxErrorReport::CxErrorReport(
    const EType          &crtType,
    const std::tstring_t &csExp,
    const ulong_t         culLastError,
    const std::tstring_t &csFile,
    const ulong_t         culLine,
    const std::tstring_t &csFunc,
    const std::tstring_t &csDate,
    const std::tstring_t &csTime,
    const std::tstring_t &csStackTrace,
    const tchar_t        *pcszComment, ...
) :
    m_rtType         (rtUnknown),
    m_sReport        (),
    m_sProgram       (),
    m_ulProcessId    (0UL),
    m_ulThreadId     (0UL),
    m_sFileSize      (),
    m_sSourceFile    (),
    m_ulSourceLine   (0UL),
    m_sFunctionName  (),
    m_sExpression    (),
    m_ulLastError    (0),
    m_sLastErrorStr  (),
    m_sCurrentDate   (),
    m_sBuildDate     (),
    m_sBuildType     (),
    m_sOsVersion     (),
    m_sOsArchitecture(),
    m_sStackTrace    (),
    m_sComment       ()
{
    /*DEBUG*/

    std::tstring_t sComment;
    va_list        palArgs;

    xVA_START(palArgs, pcszComment);
    sComment = CxString::sFormatV(pcszComment, palArgs);
    xVA_END(palArgs);

    (void)_bInitVars(crtType, csExp, culLastError, csFile, culLine, csFunc, csDate, csTime, csStackTrace, sComment.c_str());

    switch (crtType) {
        case rtMsgboxPlain:     { (void)_bInitPlain();    }   break;
        case rtMsgboxFormated:  { (void)_bInitFormated(); }   break;
        case rtStdoutPlain:     { (void)_bInitPlain();    }   break;
        case rtStdoutHtml:      { (void)_bInitHtml();     }   break;
        case rtLoggingPlain:    { (void)_bInitPlain();    }   break;
        case rtLoggingHtml:     { (void)_bInitHtml();     }   break;

        default:                { (void)_bInitPlain();    }   break;
    }
}
//---------------------------------------------------------------------------
/*virtual*/
CxErrorReport::~CxErrorReport() {
    /*DEBUG*/
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxErrorReport::_bInitVars(
    const EType          &crtType,
    const std::tstring_t &csExp,
    const ulong_t         culLastError,
    const std::tstring_t &csFile,
    const ulong_t         culLine,
    const std::tstring_t &csFunc,
    const std::tstring_t &csDate,
    const std::tstring_t &csTime,
    const std::tstring_t &csStackTrace,
    const std::tstring_t &csComment
)
{
    /*DEBUG*/

    const size_t cuiReportWidthMax = 46;


    m_rtType          = crtType;

#if 1
    m_sProgram        = CxPath::sToUnix( CxPath::sGetShort(CxPath::sGetExe(), cuiReportWidthMax), false );
    m_ulProcessId     = (ulong_t)CxCurrentProcess::ulGetId();
    m_ulThreadId      = (ulong_t)CxCurrentThread::ulGetId();
    m_sFileSize       = CxString::sFormatBytes( static_cast<ulonglong_t>( CxFile::llGetSize(CxPath::sGetExe())) );

    m_sSourceFile     = CxPath::sToUnix( CxPath::sGetShort(csFile, cuiReportWidthMax), false );
    m_ulSourceLine    = culLine;
    m_sFunctionName   = csFunc;
    m_sExpression     = csExp;
    m_ulLastError     = culLastError;
    m_sLastErrorStr   = CxLastError::sFormat(culLastError);

    m_sCurrentDate    = CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftDateTime);
    m_sBuildDate      = CxString::sFormat(xT("%s/%s"), csDate.c_str(), csTime.c_str());
    m_sBuildType      = (true == CxDebugger().bIsDebugBuild()) ? xT("debug") : xT("release");
    m_sOsVersion      = CxSystemInfo::sFormatOsType( CxSystemInfo::osGetOS() );
    m_sOsArchitecture = CxSystemInfo::sFormatOsArch( CxSystemInfo::oaGetOsArch() );

    m_sStackTrace     = csStackTrace;
    m_sComment        = (false == csComment.empty()) ? csComment : CxConst::xHYPHEN;
#else
    m_sProgram        = xT("");
    m_ulProcessId     = (ulong_t)CxCurrentProcess::ulGetId();
    m_ulThreadId      = (ulong_t)CxCurrentThread::ulGetId();
    m_sFileSize       = xT("");

    m_sSourceFile     = csFile;
    m_ulSourceLine    = culLine;
    m_sFunctionName   = csFunc;
    m_sExpression     = csExp;
    m_ulLastError     = culLastError;
    m_sLastErrorStr   = CxLastError::sFormat(culLastError);

    m_sCurrentDate    = xT("");
    m_sBuildDate      = xT("");
    m_sBuildType      = xT("");
    m_sOsVersion      = xT("");
    m_sOsArchitecture = xT("");

    m_sStackTrace     = csStackTrace;
    m_sComment        = (false == csComment.empty()) ? csComment : CxConst::xHYPHEN;
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxErrorReport::_bInitPlain() {
    m_sReport = CxString::sFormat(
        xT("%s\n")        //CxErrorReport
        xT("\n")

        xT("%s%s\n")      //Program
        xT("%s%lu\n")     //Process id
        xT("%s%lu\n")     //Thread id
        xT("%s%s\n")      //file size
        xT("\n")

        xT("%s%s\n")      //Source file
        xT("%s%lu\n")     //Source line
        xT("%s%s\n")      //Function name
        xT("%s%s\n")      //Expression
        xT("%s%s\n")      //Last error
        xT("\n")

        xT("%s%s\n")      //Current date
        xT("%s%s\n")      //Build date
        xT("%s%s\n")      //Build type
        xT("%s%s\n")      //OS version
        xT("%s%s\n")      //OS architecture
        xT("%s%s\n")      //stack trace
        xT("\n")

        xT("%s%s"),       //Comment

        xT("CxErrorReport    "),

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

        xT("Comment:         "), m_sComment.c_str());

    return true;
}
//---------------------------------------------------------------------------
bool
CxErrorReport::_bInitHtml() {
    m_sReport = CxString::sFormat(
        xT("<pre>")
        xT("<b><u>%s</u></b>\n") //CxErrorReport
        xT("\n")

        xT("<b>%s</b>%s\n")      //Program
        xT("<b>%s</b>%lu\n")     //Process id
        xT("<b>%s</b>%lu\n")     //Thread id
        xT("<b>%s</b>%s\n")      //file size
        xT("\n")

        xT("<b>%s</b>%s\n")      //Source file
        xT("<b>%s</b>%lu\n")     //Source line
        xT("<b>%s</b>%s\n")      //Function name
        xT("<b>%s</b>%s\n")      //Expression
        xT("<b>%s</b>%s\n")      //Last error
        xT("\n")

        xT("<b>%s</b>%s\n")      //Current date
        xT("<b>%s</b>%s\n")      //Build date
        xT("<b>%s</b>%s\n")      //Build type
        xT("<b>%s</b>%s\n")      //OS version
        xT("<b>%s</b>%s\n")      //OS architecture
        xT("<b>%s</b>%s\n")      //stack trace
        xT("\n")

        xT("<b>%s</b>%s")        //Comment
        xT("</pre>"),

        xT("CxErrorReport    "),
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

        xT("Comment:         "), m_sComment.c_str());

    return true;
}
//---------------------------------------------------------------------------
bool
CxErrorReport::_bInitFormated() {
#if xOS_ENV_WIN
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
        xT("%s%s\n")      //stack trace
        xT("#  \n")

        xT("%s%s\n")      //Comment
        xT("#  "),

        xT("#  CxErrorReport    "),

        xT("#  Program:         "), m_sProgram.c_str(),
        xT("#  Process id:      "), m_ulProcessId,
        xT("#  Thread id:       "), m_ulThreadId,
        xT("#  File size:       "), m_sFileSize.c_str(),

        xT("#  Source file:     "), CxConsole().bSetTextColor( m_sSourceFile,                          CxConsole::fgWhite,   true, false, CxConsole::bgBlack, false ).c_str(),
        xT("#  Source line:     "), CxConsole().bSetTextColor( CxString::lexical_cast(m_ulSourceLine), CxConsole::fgMagenta, true, true,  CxConsole::bgBlack, false ).c_str(),
        xT("#  Function name:   "), CxConsole().bSetTextColor( m_sFunctionName,                        CxConsole::fgCyan,    true, false, CxConsole::bgBlack, false ).c_str(),
        xT("#  Expression:      "), CxConsole().bSetTextColor( m_sExpression,                          CxConsole::fgYellow,  true, false, CxConsole::bgBlack, false ).c_str(),
        xT("#  Last error:      "), CxConsole().bSetTextColor( m_sLastErrorStr,                        CxConsole::fgRed,     true, false, CxConsole::bgBlack, false ).c_str(),

        xT("#  Current date:    "), m_sCurrentDate.c_str(),
        xT("#  Build date:      "), m_sBuildDate.c_str(),
        xT("#  Build type:      "), m_sBuildType.c_str(),
        xT("#  OS version:      "), m_sOsVersion.c_str(),
        xT("#  OS architecture: "), m_sOsArchitecture.c_str(),
        xT("#  Stack trace:     "), m_sStackTrace.c_str(),

        xT("#  Comment:         "), CxConsole().bSetTextColor( m_sComment,                             CxConsole::fgYellow_, false, false, CxConsole::bgBlue,  false ).c_str()
    );
#endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
