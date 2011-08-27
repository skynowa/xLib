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
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxStdioFile.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Sync/CxProcess.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxReport
CxReport::CxReport(
    const EType        &crtType,
    const std::tstring &csExp,
    const ULONG         culLastError,
    const std::tstring &csFile,
    const ULONG         culLine,
    const std::tstring &csFunc,
    const std::tstring &csDate,
    const std::tstring &csTime,
    const std::tstring &csComment
) :
    _m_rtType         (rtUnknown),
    _m_sReport        (),
    _m_sProgram       (),
    _m_ulProcessId    (0),
    _m_ulThreadId     (0),
    _m_sFileSize      (),
    _m_sSourceFile    (),
    _m_ulSourceLine   (0),
    _m_sFunctionName  (),
    _m_sExpression    (),
    _m_ulLastError    (0),
    _m_sLastErrorStr  (),
    _m_sCurrentDate   (),
    _m_sBuildDate     (),
    _m_sOsVersion     (),
    _m_sOsArchitecture(),
    _m_sComment       ()
{
    /*DEBUG*/

    _bInitVars(crtType, csExp, culLastError, csFile, culLine, csFunc, csDate, csTime, csComment.c_str());
    /*DEBUG*/// n/a

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
//DONE: CxReport
CxReport::CxReport(
    const EType        &crtType,
    const std::tstring &csExp,
    const ULONG         culLastError,
    const std::tstring &csFile,
    const ULONG         culLine,
    const std::tstring &csFunc,
    const std::tstring &csDate,
    const std::tstring &csTime,
    LPCTSTR             pcszComment, ...
) :
    _m_rtType         (rtUnknown),
    _m_sReport        (),
    _m_sProgram       (),
    _m_ulProcessId    (0),
    _m_ulThreadId     (0),
    _m_sFileSize      (),
    _m_sSourceFile    (),
    _m_ulSourceLine   (0),
    _m_sFunctionName  (),
    _m_sExpression    (),
    _m_ulLastError    (0),
    _m_sLastErrorStr  (),
    _m_sCurrentDate   (),
    _m_sBuildDate     (),
    _m_sOsVersion     (),
    _m_sOsArchitecture(),
    _m_sComment       ()
{
    /*DEBUG*/

    std::tstring sComment;
    va_list      palArgs;

    xVA_START(palArgs, pcszComment);
    sComment = CxString::sFormatV(pcszComment, palArgs);
    xVA_END(palArgs);

    _bInitVars(crtType, csExp, culLastError, csFile, culLine, csFunc, csDate, csTime, sComment.c_str());
    /*DEBUG*/// n/a

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
//DONE: ~CxReport
/*virtual*/
CxReport::~CxReport() {
    /*DEBUG*/
}
//---------------------------------------------------------------------------
//DONE: ulGetLastError (get last error)
CxReport::EType
CxReport::rtGetType() const {
    /*DEBUG*/

    return _m_rtType;
}
//---------------------------------------------------------------------------
//DONE: sGetReport (get report)
const std::tstring &
CxReport::sGetReport() const {
    /*DEBUG*/

    return _m_sReport;
}
//---------------------------------------------------------------------------
//DONE: sGetProgram (get program name)
const std::tstring &
CxReport::sGetProgram() const {
    /*DEBUG*/

    return _m_sProgram;
}
//---------------------------------------------------------------------------
//DONE: ulGetProcessId (get process id)
ULONG
CxReport::ulGetProcessId() const {
    /*DEBUG*/

    return _m_ulProcessId;
}
//---------------------------------------------------------------------------
//DONE: ulGetThreadId (get thread id)
ULONG
CxReport::ulGetThreadId() const {
    /*DEBUG*/

    return _m_ulThreadId;
}
//---------------------------------------------------------------------------
//TODO: sGetFileSize ()
const std::tstring &
CxReport::sGetFileSize() const {
    /*DEBUG*/

    return _m_sFileSize;
}
//---------------------------------------------------------------------------
//DONE: sGetSourceFile (get source file path)
const std::tstring &
CxReport::sGetSourceFile() const {
    /*DEBUG*/

    return _m_sSourceFile;
}
//---------------------------------------------------------------------------
//DONE: ulGetSourceLine (get source file line)
ULONG
CxReport::ulGetSourceLine() const {
    /*DEBUG*/

    return _m_ulSourceLine;
}
//---------------------------------------------------------------------------
//DONE: sGetFunctionName (get source function name)
const std::tstring &
CxReport::sGetFunctionName() const {
    /*DEBUG*/

    return _m_sFunctionName;
}
//---------------------------------------------------------------------------
//DONE: sGetExpression (get expression)
const std::tstring &
CxReport::sGetExpression() const {
    /*DEBUG*/

    return _m_sExpression;
}
//---------------------------------------------------------------------------
//DONE: ulGetLastError (get last error)
ULONG
CxReport::ulGetLastError() const {
    /*DEBUG*/

    return _m_ulLastError;
}
//---------------------------------------------------------------------------
//TODO: sGetLastErrorStr (get formatting last error)
const std::tstring &
CxReport::sGetLastErrorStr() const {
    /*DEBUG*/

    return _m_sLastErrorStr;
}
//---------------------------------------------------------------------------
//DONE: sGetCurrentDate (get current datetime)
const std::tstring &
CxReport::sGetCurrentDate() const {
    /*DEBUG*/

    return _m_sCurrentDate;
}
//---------------------------------------------------------------------------
//DONE: sGetBuildDate (get build datetime)
const std::tstring &
CxReport::sGetBuildDate() const {
    /*DEBUG*/

    return _m_sBuildDate;
}
//---------------------------------------------------------------------------
//DONE: sGetOsVersion (get build OS version)
const std::tstring &
CxReport::sGetOsVersion() const {
    /*DEBUG*/

    return _m_sOsVersion;
}
//---------------------------------------------------------------------------
//DONE: sGetOsArchitecture (get OS architecture)
const std::tstring &
CxReport::sGetOsArchitecture() const {
    /*DEBUG*/

    return _m_sOsArchitecture;
}
//---------------------------------------------------------------------------
//DONE: sGetComment (get comment)
const std::tstring &
CxReport::sGetComment() const {
    /*DEBUG*/

    return _m_sComment;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bInit (formatting message, init class members)
BOOL
CxReport::_bInitVars(
    const EType        &crtType,
    const std::tstring &csExp,
    const ULONG         culLastError,
    const std::tstring &csFile,
    const ULONG         culLine,
    const std::tstring &csFunc,
    const std::tstring &csDate,
    const std::tstring &csTime,
    const std::tstring &csComment
)
{
    /*DEBUG*/

    _m_rtType          = crtType;

#if 1
    _m_sProgram        = CxPath::sGetExe();
    _m_ulProcessId     = CxProcess::ulGetCurrId();
    _m_ulThreadId      = (ULONG)CxThread::ulGetCurrId();
    _m_sFileSize       = CxString::sFormatBytes( static_cast<ULONGLONG>( CxStdioFile::liGetSize(CxPath::sGetExe())) );

    _m_sSourceFile     = csFile;
    _m_ulSourceLine    = culLine;
    _m_sFunctionName   = csFunc;
    _m_sExpression     = csExp;
    _m_ulLastError     = culLastError;
    _m_sLastErrorStr   = CxLastError::sFormat(culLastError);

    _m_sCurrentDate    = CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftDateTime);
    _m_sBuildDate      = CxString::sFormat(xT("%s/%s"), csDate.c_str(), csTime.c_str());
    _m_sOsVersion      = CxSystemInfo::sFormatOsType( CxSystemInfo::osGetOS() );
    _m_sOsArchitecture = CxSystemInfo::sFormatOsArch( CxSystemInfo::oaGetOsArch() );

    _m_sComment        = (false == csComment.empty()) ? csComment : CxConst::xHYPHEN;
#else
    _m_sProgram        = xT("");
    _m_ulProcessId     = CxProcess::ulGetCurrId();
    _m_ulThreadId      = (ULONG)CxThread::ulGetCurrId();
    _m_sFileSize       = xT("");

    _m_sSourceFile     = csFile;
    _m_ulSourceLine    = culLine;
    _m_sFunctionName   = csFunc;
    _m_sExpression     = csExp;
    _m_ulLastError     = culLastError;
    _m_sLastErrorStr   = CxLastError::sFormat(culLastError);

    _m_sCurrentDate    = xT("");
    _m_sBuildDate      = xT("");
    _m_sOsVersion      = xT("");
    _m_sOsArchitecture = xT("");

    _m_sComment        = (false == csComment.empty()) ? csComment : CxConst::xHYPHEN;
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: _bInitPlain
BOOL
CxReport::_bInitPlain() {
    _m_sReport = CxString::sFormat(
        xT("%s\n")        //CxReport
        xT("\n")

        xT("%s%s\n")      //Program
        xT("%s%li\n")     //Process id
        xT("%s%li\n")     //Thread id
        xT("%s%s\n")      //file size
        xT("\n")

        xT("%s%s\n")      //Source file
        xT("%s%li\n")     //Source line
        xT("%s%s\n")      //Function name
        xT("%s%s\n")      //Expression
        xT("%s%s\n")      //Last error
        xT("\n")

        xT("%s%s\n")      //Current date
        xT("%s%s\n")      //Build date
        xT("%s%s\n")      //OS version
        xT("%s%s\n")      //OS architecture
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
        xT("OS version:      "), sGetOsVersion().c_str(),
        xT("OS architecture: "), sGetOsArchitecture().c_str(),

        xT("Comment:         "), sGetComment().c_str());

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: _bInitHtml
BOOL
CxReport::_bInitHtml() {
    _m_sReport = CxString::sFormat(
        xT("<pre>")
        xT("<b><u>%s</u></b>\n") //CxReport
        xT("\n")

        xT("<b>%s</b>%s\n")      //Program
        xT("<b>%s</b>%li\n")     //Process id
        xT("<b>%s</b>%li\n")     //Thread id
        xT("<b>%s</b>%s\n")      //file size
        xT("\n")

        xT("<b>%s</b>%s\n")      //Source file
        xT("<b>%s</b>%li\n")     //Source line
        xT("<b>%s</b>%s\n")      //Function name
        xT("<b>%s</b>%s\n")      //Expression
        xT("<b>%s</b>%s\n")      //Last error
        xT("\n")

        xT("<b>%s</b>%s\n")      //Current date
        xT("<b>%s</b>%s\n")      //Build date
        xT("<b>%s</b>%s\n")      //OS version
        xT("<b>%s</b>%s\n")      //OS architecture
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
        xT("OS version:      "), sGetOsVersion().c_str(),
        xT("OS architecture: "), sGetOsArchitecture().c_str(),

        xT("Comment:         "), sGetComment().c_str());

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: _bInitFormated
BOOL
CxReport::_bInitFormated() {
#if defined(xOS_WIN)
    //TODO: _bInitFormated (add some data)
    _m_sReport = CxString::sFormat(
        xT("{\\rtf1\\ansi\\ansicpg1251\\deff0\\deflang1049{\\fonttbl{\\f0\\fswiss\\fcharset0 Arial;}{\\f1\\fnil DejaVu Sans Mono;}{\\f2\\fswiss\\fcharset204{\\*\\fname Arial;}Arial CYR;}{\\f3\\fswiss\\fprq2\\fcharset204{\\*\\fname Arial;}Arial CYR;}{\\f4\\fswiss\\fprq2\\fcharset0 Arial;}}")
        xT("{\\colortbl ;\\red255\\green0\\blue0;\\red0\\green0\\blue0;\\red255\\green0\\blue255;\\red0\\green255\\blue255;\\red255\\green255\\blue0;}")
        xT("\\viewkind4\\uc1\\pard\\lang1033\\ul\\b\\f0\\fs20 %s\\cf1\\lang1049\\ulnone\\b0\\f1\\fs16\\par")
        xT("\\cf0\\b\\f2\\fs20\\par")
        xT("\\cf2\\b\\f3 %s\\b0   \\lang1033\\f0  \\cf2 %s\\cf1\\lang1049\\f2\\par")
        xT("\\cf2\\b\\f3 %s\\b0   \\lang1033\\f4   \\f0 %li\\cf1\\lang1049\\f2\\par")
        xT("\\cf2\\b\\f3 %s\\b0   \\lang1033\\f4   \\f0 %li\\cf1\\lang1049\\f2\\par")
        xT("\\cf2\\b\\f3 %s\\b0   \\lang1033\\f4     \\f0 %s\\par")
        xT("\\cf1\\lang1049\\f2\\par")
        xT("\\cf0\\b %s\\b0   \\lang1033\\f0   \\b %s\\cf1\\lang1049\\b0\\f2\\par")
        xT("\\cf0\\b %s\\b0   \\lang1033\\f0  \\cf3\\b\\f4 %li\\lang1049\\f3\\par")
        xT("\\cf0\\f2 %s\\lang1033\\f0 \\cf4\\f4 %s\\lang1049\\f3\\par")
        xT("\\cf0\\f2 %s\\b0   \\lang1033\\f0  \\cf5\\b\\f4 %s\\cf0\\lang1049\\b0\\f2\\par")
        xT("\\b %s\\lang1033\\b0\\f0      \\cf1\\b\\f4 %s\\b0\\par")
        xT("\\cf0\\lang1049\\f2\\par")
        xT("\\b %s\\lang1033\\b0\\f0    %s\\lang1049\\f2\\par")
        xT("\\b %s\\lang1033\\b0\\f0     %s\\lang1049\\f2\\par")
        xT("\\b %s\\lang1033\\b0\\f0    %s\\lang1049\\f2\\par")
        xT("\\b %s\\lang1033\\f0  \\b0 %s\\par")
        xT("\\lang1049\\f2\\par")
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
        xT("OS version:      "), sGetOsVersion().c_str(),
        xT("OS architecture: "), sGetOsArchitecture().c_str(),

        xT("Comment:         "), sGetComment().c_str()
    );
#elif defined(xOS_LINUX)
    _m_sReport = CxString::sFormat(
        xT("%s\n")        //CxReport
        xT("#  \n")

        xT("%s%s\n")      //Program
        xT("%s%li\n")     //Process id
        xT("%s%li\n")     //Thread id
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
        xT("%s%s\n")      //OS version
        xT("%s%s\n")      //OS architecture
        xT("#  \n")

        xT("%s%s\n")      //Comment
        xT("#  "),

        xT("#  CxReport         "),

        xT("#  Program:         "), sGetProgram().c_str(),
        xT("#  Process id:      "), ulGetProcessId(),
        xT("#  Thread id:       "), ulGetThreadId(),
        xT("#  File size:       "), sGetFileSize().c_str(),

        xT("#  Source file:     "), CxConsole().bSetTextColor( sGetSourceFile(),                          CxConsole::fgWhite,   TRUE, FALSE, CxConsole::bgBlack, FALSE ).c_str(),
        xT("#  Source line:     "), CxConsole().bSetTextColor( CxString::lexical_cast(ulGetSourceLine()), CxConsole::fgMagenta, TRUE, TRUE,  CxConsole::bgBlack, FALSE ).c_str(),
        xT("#  Function name:   "), CxConsole().bSetTextColor( sGetFunctionName(),                        CxConsole::fgCyan,    TRUE, FALSE, CxConsole::bgBlack, FALSE ).c_str(),
        xT("#  Expression:      "), CxConsole().bSetTextColor( sGetExpression(),                          CxConsole::fgYellow,  TRUE, FALSE, CxConsole::bgBlack, FALSE ).c_str(),
        xT("#  Last error:      "), CxConsole().bSetTextColor( sGetLastErrorStr(),                        CxConsole::fgRed,     TRUE, FALSE, CxConsole::bgBlack, FALSE ).c_str(),

        xT("#  Current date:    "), sGetCurrentDate().c_str(),
        xT("#  Build date:      "), sGetBuildDate().c_str(),
        xT("#  OS version:      "), sGetOsVersion().c_str(),
        xT("#  OS architecture: "), sGetOsArchitecture().c_str(),

        xT("#  Comment:         "), CxConsole().bSetTextColor( sGetComment(),                             CxConsole::fgYellow_, FALSE, FALSE, CxConsole::bgBlue,  FALSE ).c_str()
    );
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
