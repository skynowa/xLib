/**
 * \file  CxReport.cpp
 * \brief debug report
 */


#include <xLib/Debug/CxReport.h>

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
CxReport::CxReport(
    const EType        &crtType,
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
    _m_rtType         (rtUnknown),
    _m_sReport        (),
    _m_sProgram       (),
    _m_ulProcessId    (0UL),
    _m_ulThreadId     (0UL),
    _m_sFileSize      (),
    _m_sSourceFile    (),
    _m_ulSourceLine   (0UL),
    _m_sFunctionName  (),
    _m_sExpression    (),
    _m_ulLastError    (0UL),
    _m_sLastErrorStr  (),
    _m_sCurrentDate   (),
    _m_sBuildDate     (),
    _m_sBuildType     (),
    _m_sOsVersion     (),
    _m_sOsArchitecture(),
    _m_sStackTrace    (),
    _m_sComment       ()
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
CxReport::CxReport(
    const EType        &crtType,
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
    _m_rtType         (rtUnknown),
    _m_sReport        (),
    _m_sProgram       (),
    _m_ulProcessId    (0UL),
    _m_ulThreadId     (0UL),
    _m_sFileSize      (),
    _m_sSourceFile    (),
    _m_ulSourceLine   (0UL),
    _m_sFunctionName  (),
    _m_sExpression    (),
    _m_ulLastError    (0),
    _m_sLastErrorStr  (),
    _m_sCurrentDate   (),
    _m_sBuildDate     (),
    _m_sBuildType     (),
    _m_sOsVersion     (),
    _m_sOsArchitecture(),
    _m_sStackTrace    (),
    _m_sComment       ()
{
    /*DEBUG*/

    std::tstring_t sComment;
    va_list      palArgs;

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
CxReport::~CxReport() {
    /*DEBUG*/
}
//---------------------------------------------------------------------------
CxReport::EType
CxReport::rtGetType() const {
    /*DEBUG*/

    return _m_rtType;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetReport() const {
    /*DEBUG*/

    return _m_sReport;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetProgram() const {
    /*DEBUG*/

    return _m_sProgram;
}
//---------------------------------------------------------------------------
ulong_t
CxReport::ulGetProcessId() const {
    /*DEBUG*/

    return _m_ulProcessId;
}
//---------------------------------------------------------------------------
ulong_t
CxReport::ulGetThreadId() const {
    /*DEBUG*/

    return _m_ulThreadId;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetFileSize() const {
    /*DEBUG*/

    return _m_sFileSize;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetSourceFile() const {
    /*DEBUG*/

    return _m_sSourceFile;
}
//---------------------------------------------------------------------------
ulong_t
CxReport::ulGetSourceLine() const {
    /*DEBUG*/

    return _m_ulSourceLine;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetFunctionName() const {
    /*DEBUG*/

    return _m_sFunctionName;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetExpression() const {
    /*DEBUG*/

    return _m_sExpression;
}
//---------------------------------------------------------------------------
ulong_t
CxReport::ulGetLastError() const {
    /*DEBUG*/

    return _m_ulLastError;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetLastErrorStr() const {
    /*DEBUG*/

    return _m_sLastErrorStr;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetCurrentDate() const {
    /*DEBUG*/

    return _m_sCurrentDate;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetBuildDate() const {
    /*DEBUG*/

    return _m_sBuildDate;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetBuildType() const {
    /*DEBUG*/

    return _m_sBuildType;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetOsVersion() const {
    /*DEBUG*/

    return _m_sOsVersion;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetOsArchitecture() const {
    /*DEBUG*/

    return _m_sOsArchitecture;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetComment() const {
    /*DEBUG*/

    return _m_sComment;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxReport::sGetStackTrace() const {
    /*DEBUG*/

    return _m_sStackTrace;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxReport::_bInitVars(
    const EType        &crtType,
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

    _m_rtType          = crtType;

#if 1
    _m_sProgram        = CxPath::sGetExe();
    _m_ulProcessId     = (ulong_t)CxCurrentProcess::ulGetId();
    _m_ulThreadId      = (ulong_t)CxCurrentThread::ulGetId();
    _m_sFileSize       = CxString::sFormatBytes( static_cast<ulonglong_t>( CxFile::liGetSize(CxPath::sGetExe())) );

    _m_sSourceFile     = csFile;
    _m_ulSourceLine    = culLine;
    _m_sFunctionName   = csFunc;
    _m_sExpression     = csExp;
    _m_ulLastError     = culLastError;
    _m_sLastErrorStr   = CxLastError::sFormat(culLastError);

    _m_sCurrentDate    = CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftDateTime);
    _m_sBuildDate      = CxString::sFormat(xT("%s/%s"), csDate.c_str(), csTime.c_str());
    _m_sBuildType      = (true == CxDebugger::bIsDebugBuild()) ? xT("debug") : xT("release");
    _m_sOsVersion      = CxSystemInfo::sFormatOsType( CxSystemInfo::osGetOS() );
    _m_sOsArchitecture = CxSystemInfo::sFormatOsArch( CxSystemInfo::oaGetOsArch() );

    _m_sStackTrace     = csStackTrace;
    _m_sComment        = (false == csComment.empty()) ? csComment : CxConst::xHYPHEN;
#else
    _m_sProgram        = xT("");
    _m_ulProcessId     = (ulong_t)CxProcess::ulGetCurrId();
    _m_ulThreadId      = (ulong_t)CxThread::ulGetCurrId();
    _m_sFileSize       = xT("");

    _m_sSourceFile     = csFile;
    _m_ulSourceLine    = culLine;
    _m_sFunctionName   = csFunc;
    _m_sExpression     = csExp;
    _m_ulLastError     = culLastError;
    _m_sLastErrorStr   = CxLastError::sFormat(culLastError);

    _m_sCurrentDate    = xT("");
    _m_sBuildDate      = xT("");
    _m_sBuildType      = xT("");
    _m_sOsVersion      = xT("");
    _m_sOsArchitecture = xT("");

    _m_sStackTrace     = csStackTrace;
    _m_sComment        = (false == csComment.empty()) ? csComment : CxConst::xHYPHEN;
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxReport::_bInitPlain() {
    _m_sReport = CxString::sFormat(
        xT("%s\n")        //CxReport
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

        xT("CxReport         "),

        xT("Program:         "), sGetProgram().c_str(),
        xT("Process id:      "), ulGetProcessId(),
        xT("Thread id:       "), ulGetThreadId(),
        xT("File size:       "), sGetFileSize().c_str(),

        xT("Source file:     "), sGetSourceFile().c_str(),
        xT("Source line:     "), ulGetSourceLine(),
        xT("Function name:   "), sGetFunctionName().c_str(),
        xT("Expression:      "), sGetExpression().c_str(),
        xT("Last error:      "), sGetLastErrorStr().c_str(),

        xT("Current date:    "), sGetCurrentDate().c_str(),
        xT("Build date:      "), sGetBuildDate().c_str(),
        xT("Build type:      "), sGetBuildType().c_str(),
        xT("OS version:      "), sGetOsVersion().c_str(),
        xT("OS architecture: "), sGetOsArchitecture().c_str(),
        xT("Stack trace:     "), sGetStackTrace().c_str(),

        xT("Comment:         "), sGetComment().c_str());

    return true;
}
//---------------------------------------------------------------------------
bool
CxReport::_bInitHtml() {
    _m_sReport = CxString::sFormat(
        xT("<pre>")
        xT("<b><u>%s</u></b>\n") //CxReport
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

        xT("CxReport         "),
        xT("Program:         "), sGetProgram().c_str(),
        xT("Process id:      "), ulGetProcessId(),
        xT("Thread id:       "), ulGetThreadId(),
        xT("File size:       "), sGetFileSize().c_str(),

        xT("Source file:     "), sGetSourceFile().c_str(),
        xT("Source line:     "), ulGetSourceLine(),
        xT("Function name:   "), sGetFunctionName().c_str(),
        xT("Expression:      "), sGetExpression().c_str(),
        xT("Last error:      "), sGetLastErrorStr().c_str(),

        xT("Current date:    "), sGetCurrentDate().c_str(),
        xT("Build date:      "), sGetBuildDate().c_str(),
        xT("Build type:      "), sGetBuildType().c_str(),
        xT("OS version:      "), sGetOsVersion().c_str(),
        xT("OS architecture: "), sGetOsArchitecture().c_str(),
        xT("Stack trace:     "), sGetStackTrace().c_str(),

        xT("Comment:         "), sGetComment().c_str());

    return true;
}
//---------------------------------------------------------------------------
bool
CxReport::_bInitFormated() {
#if xOS_ENV_WIN
    _m_sReport = CxString::sFormat(
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

        xT("CxReport "),

        xT("Program:         "), sGetProgram().c_str(),
        xT("Process id:      "), ulGetProcessId(),
        xT("Thread id:       "), ulGetThreadId(),
        xT("File size:       "), sGetFileSize().c_str(),

        xT("Source file:     "), sGetSourceFile().c_str(),
        xT("Source line:     "), ulGetSourceLine(),
        xT("Function name:   "), sGetFunctionName().c_str(),
        xT("Expression:      "), sGetExpression().c_str(),
        xT("Last error:      "), sGetLastErrorStr().c_str(),

        xT("Current date:    "), sGetCurrentDate().c_str(),
        xT("Build date:      "), sGetBuildDate().c_str(),
        xT("Build type:      "), sGetBuildType().c_str(),
        xT("OS version:      "), sGetOsVersion().c_str(),
        xT("OS architecture: "), sGetOsArchitecture().c_str(),

        xT("Stack trace:     "), sGetStackTrace().c_str(),
        xT("Comment:         "), sGetComment().c_str()
    );
#elif xOS_ENV_UNIX
    _m_sReport = CxString::sFormat(
        xT("%s\n")        //CxReport
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

        xT("#  CxReport         "),

        xT("#  Program:         "), sGetProgram().c_str(),
        xT("#  Process id:      "), ulGetProcessId(),
        xT("#  Thread id:       "), ulGetThreadId(),
        xT("#  File size:       "), sGetFileSize().c_str(),

        xT("#  Source file:     "), CxConsole().bSetTextColor( sGetSourceFile(),                          CxConsole::fgWhite,   true, false, CxConsole::bgBlack, false ).c_str(),
        xT("#  Source line:     "), CxConsole().bSetTextColor( CxString::lexical_cast(ulGetSourceLine()), CxConsole::fgMagenta, true, true,  CxConsole::bgBlack, false ).c_str(),
        xT("#  Function name:   "), CxConsole().bSetTextColor( sGetFunctionName(),                        CxConsole::fgCyan,    true, false, CxConsole::bgBlack, false ).c_str(),
        xT("#  Expression:      "), CxConsole().bSetTextColor( sGetExpression(),                          CxConsole::fgYellow,  true, false, CxConsole::bgBlack, false ).c_str(),
        xT("#  Last error:      "), CxConsole().bSetTextColor( sGetLastErrorStr(),                        CxConsole::fgRed,     true, false, CxConsole::bgBlack, false ).c_str(),

        xT("#  Current date:    "), sGetCurrentDate().c_str(),
        xT("#  Build date:      "), sGetBuildDate().c_str(),
        xT("#  Build type:      "), sGetBuildType().c_str(),
        xT("#  OS version:      "), sGetOsVersion().c_str(),
        xT("#  OS architecture: "), sGetOsArchitecture().c_str(),
        xT("#  Stack trace:     "), sGetStackTrace().c_str(),

        xT("#  Comment:         "), CxConsole().bSetTextColor( sGetComment(),                             CxConsole::fgYellow_, false, false, CxConsole::bgBlue,  false ).c_str()
    );
#endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
