/****************************************************************************
* Class name:  CxReport
* Description: debug message
* File name:   CxReport.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     1 лют. 2011 13:58:33
*
*****************************************************************************/


#include <xLib/Debug/CxReport.h>

#include <xLib/Common/CxException.h>
#include <xLib/Common/CxDateTime.h>
#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Sync/CxProcess.h>

#if defined(xOS_WIN)

#elif defined(xOS_LINUX)
    #include <pthread.h>
#endif


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxReport (constructor)
CxReport::CxReport(
    const EType   &crtType,
    const tString &csExp,
    const ULONG    culLastError,
    const tString &csFile,
    const ULONG    culLine,
    const tString &csFunc,
    const tString &csDate,
    const tString &csTime,
    const tString &csComment
) :
    _m_rtType         (rtUnknown),
    _m_sReport        (),
    _m_sProgram       (),
    _m_ulProcessId    (0),
    _m_ulThreadId     (0),
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

    switch (crtType) {
        case rtMsgboxPlain:  { _bInitPlain(); }    break;
        case rtMsgboxRtf:    { _bInitRtf();   }    break;
        case rtStdoutPlain:  { _bInitPlain(); }    break;
        case rtStdoutHtml:   { _bInitHtml();  }    break;
        case rtLoggingPlain: { _bInitPlain(); }    break;
        case rtLoggingHtml:  { _bInitHtml();  }    break;

        default:             { _bInitPlain(); }    break;
    }
}
//---------------------------------------------------------------------------
//DONE: CxReport (constructor)
CxReport::CxReport(
    const EType   &crtType,
    const tString &csExp,
    const ULONG    culLastError,
    const tString &csFile,
    const ULONG    culLine,
    const tString &csFunc,
    const tString &csDate,
    const tString &csTime,
    LPCTSTR        pcszComment, ...
) :
    _m_rtType         (rtUnknown),
    _m_sReport        (),
    _m_sProgram       (),
    _m_ulProcessId    (0),
    _m_ulThreadId     (0),
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

    tString sComment;
    va_list palArgs;

    va_start(palArgs, pcszComment);
    sComment = CxString::sFormatV(pcszComment, palArgs);
    va_end(palArgs);

    _bInitVars(crtType, csExp, culLastError, csFile, culLine, csFunc, csDate, csTime, sComment.c_str());

    switch (crtType) {
        case rtMsgboxPlain:  { _bInitPlain(); }  break;
        case rtMsgboxRtf:    { _bInitRtf();   }  break;
        case rtStdoutPlain:  { _bInitPlain(); }  break;
        case rtStdoutHtml:   { _bInitHtml();  }  break;
        case rtLoggingPlain: { _bInitPlain(); }  break;
        case rtLoggingHtml:  { _bInitHtml();  }  break;

        default:             { _bInitPlain(); }  break;
    }
}
//---------------------------------------------------------------------------
//DONE: ~CxReport (destructor)
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
const tString &
CxReport::sGetReport() const {
    /*DEBUG*/

    return _m_sReport;
}
//---------------------------------------------------------------------------
//DONE: sGetProgram (get program name)
const tString &
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
//DONE: sGetSourceFile (get source file path)
const tString &
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
const tString &
CxReport::sGetFunctionName() const {
    /*DEBUG*/

    return _m_sFunctionName;
}
//---------------------------------------------------------------------------
//DONE: sGetExpression (get expression)
const tString &
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
const tString &
CxReport::sGetLastErrorStr() const {
    /*DEBUG*/

    return _m_sLastErrorStr;
}
//---------------------------------------------------------------------------
//DONE: sGetCurrentDate (get current datetime)
const tString &
CxReport::sGetCurrentDate() const {
    /*DEBUG*/

    return _m_sCurrentDate;
}
//---------------------------------------------------------------------------
//DONE: sGetBuildDate (get build datetime)
const tString &
CxReport::sGetBuildDate() const {
    /*DEBUG*/

    return _m_sBuildDate;
}
//---------------------------------------------------------------------------
//DONE: sGetOsVersion (get build OS version)
const tString &
CxReport::sGetOsVersion() const {
    /*DEBUG*/

    return _m_sOsVersion;
}

//---------------------------------------------------------------------------
//DONE: sGetOsArchitecture (get OS architecture)
const tString &
CxReport::sGetOsArchitecture() const {
    /*DEBUG*/

    return _m_sOsArchitecture;
}
//---------------------------------------------------------------------------
//DONE: sGetComment (get comment)
const tString &
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
    const EType   &crtType,
    const tString &csExp,
    const ULONG    culLastError,
    const tString &csFile,
    const ULONG    culLine,
    const tString &csFunc,
    const tString &csDate,
    const tString &csTime,
    const tString &csComment
)
{
    /*DEBUG*/

    _m_rtType          = crtType;

    _m_sProgram        = CxPath::sGetExe();
    _m_ulProcessId     = CxProcess::ulGetCurrId();
    _m_ulThreadId      = (ULONG)CxThread::ulGetCurrId();
    _m_sSourceFile     = csFile;
    _m_ulSourceLine    = culLine;
    _m_sFunctionName   = csFunc;
    _m_sExpression     = csExp;
    _m_ulLastError     = culLastError;
    _m_sLastErrorStr   = CxLastError::sFormat(culLastError);

    _m_sCurrentDate    = CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftDateTime);
    _m_sBuildDate      = CxString::sFormat(xT("%s/%s"), csDate.c_str(), csTime.c_str());
    _m_sOsVersion      = CxSystemInfo::sFormatOsType( CxSystemInfo::osGetOS() );
    _m_sOsArchitecture = _sGetOsArchitecture();

    _m_sComment        = (true == csComment.empty()) ? CxConst::xHYPHEN : tString(csComment.data());

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
        xT("%s%u\n")      //Process id
        xT("%s%u\n")      //Thread id
        xT("\n")

        xT("%s%s\n")      //Source file
        xT("%s%u\n")      //Source line
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
        xT("Program:         "), _m_sProgram.data(),
        xT("Process id:      "), _m_ulProcessId,
        xT("Thread id:       "), _m_ulThreadId,

        xT("Source file:     "), _m_sSourceFile.data(),
        xT("Source line:     "), _m_ulSourceLine,
        xT("Function name:   "), _m_sFunctionName.data(),
        xT("Expression:      "), _m_sExpression.data(),
        xT("Last error:      "), _m_sLastErrorStr.data(),

        xT("Current date:    "), _m_sCurrentDate.data(),
        xT("Build date:      "), _m_sBuildDate.data(),
        xT("OS version:      "), _m_sOsVersion.data(),
        xT("OS architecture: "), _m_sOsArchitecture.data(),

        xT("Comment:         "), _m_sComment.data());

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
        xT("<b>%s</b>%u\n")      //Process id
        xT("<b>%s</b>%u\n")      //Thread id
        xT("\n")

        xT("<b>%s</b>%s\n")      //Source file
        xT("<b>%s</b>%u\n")      //Source line
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
        xT("Program:         "), _m_sProgram.data(),
        xT("Process id:      "), _m_ulProcessId,
        xT("Thread id:       "), _m_ulThreadId,

        xT("Source file:     "), _m_sSourceFile.data(),
        xT("Source line:     "), _m_ulSourceLine,
        xT("Function name:   "), _m_sFunctionName.data(),
        xT("Expression:      "), _m_sExpression.data(),
        xT("Last error:      "), _m_sLastErrorStr.data(),

        xT("Current date:    "), _m_sCurrentDate.data(),
        xT("Build date:      "), _m_sBuildDate.data(),
        xT("OS version:      "), _m_sOsVersion.data(),
        xT("OS architecture: "), _m_sOsArchitecture.data(),

        xT("Comment:         "), _m_sComment.data());

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: _bInitRtf
BOOL
CxReport::_bInitRtf() {
#if defined(xOS_WIN)
    _m_sReport = CxString::sFormat(
        xT("{\\rtf1\\ansi\\ansicpg1251\\deff0\\deflang1049{\\fonttbl{\\f0\\fswiss\\fcharset204{\\*\\fname Arial;}Arial CYR;}{\\f1\\fswiss\\fcharset0 Arial;}}")
        xT("{\\colortbl ;\\red0\\green0\\blue0;\\red255\\green0\\blue0;\\red0\\green0\\blue255;}")
        xT("{\\*\\generator Msftedit 5.41.15.1515;}\\viewkind4\\uc1\\pard\\ul\\b\\f0\\fs20 %s\\ulnone\\b0\\par")
        xT("\\par")
        xT("\\b %s\\b0   \\lang1033\\f1           \\cf1\\lang1049\\f0 %s\\cf2\\par")
        xT("\\cf0\\b %s\\b0   \\lang1033\\f1                   \\cf1\\lang1049\\f0 %s\\cf2\\par")
        xT("\\cf0\\b %s\\b0   \\lang1033\\f1                  \\cf1\\lang1049\\f0 %u\\cf0\\par")
        xT("\\b %s\\b0  \\lang1033\\f1          \\lang1049\\f0  \\lang1033\\f1  \\cf3\\lang1049\\f0 %s\\cf0\\par")
        xT("\\b %s\\b0          \\cf2 %s\\cf0\\par")
        xT("\\b %s\\lang1033\\b0\\f1             \\cf2\\lang1049\\f0 %s\\cf0\\par")
        xT("\\b %s\\lang1033\\b0\\f1           \\cf1\\lang1049\\f0 %s\\cf0\\par")
        xT("\\b %s\\lang1033\\b0\\f1          \\cf1\\lang1049\\f0 %s\\cf0\\par")
        xT("\\b %s\\lang1033\\b0\\f1  \\cf1\\lang1049\\f0 %s\\cf0\\par")
        xT("\\b %s\\b0  \\lang1033\\f1           \\cf1 %s\\lang1049\\f0\\par")
        xT("}"),

        xT("CxReport"),
        xT("Program:"),         _m_sProgram.data(),
        xT("File:"),            _m_sSourceFile.data(),
        xT("Line:"),            _m_ulSourceLine,
        xT("Function:"),        _m_sFunctionName.data(),
        xT("Expression:"),      _m_sExpression.data(),
        xT("LastError:"),       _m_sLastErrorStr.data(),
        xT("Build date:"),      _m_sBuildDate.data(),
        xT("OS version:"),      _m_sOsVersion.data(),
        xT("OS architecture:"), _m_sOsArchitecture.data(),
        xT("Comment:"),         _m_sComment.data()
    );
#elif defined(xOS_LINUX)
    _m_sReport = CxString::sFormat(
        xT("%s\n")        //CxReport
        xT("#  \n")

        xT("%s%s\n")      //Program
        xT("%s%u\n")      //Process id
        xT("%s%u\n")      //Thread id
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

        xT("%s%s\n")        //Comment
        xT("#  "),

        xT("#  CxReport         "),
        xT("#  Program:         "), _m_sProgram.data(),
        xT("#  Process id:      "), _m_ulProcessId,
        xT("#  Thread id:       "), _m_ulThreadId,

        xT("#  Source file:     "), CxString::sFormatNixTerminal( _m_sSourceFile,                          CxString::fgWhite,   TRUE, FALSE, CxString::bgBlack, FALSE ).data(),
        xT("#  Source line:     "), CxString::sFormatNixTerminal( CxString::lexical_cast(_m_ulSourceLine), CxString::fgMagenta, TRUE, TRUE,  CxString::bgBlack, FALSE ).data(),
        xT("#  Function name:   "), CxString::sFormatNixTerminal( _m_sFunctionName,                        CxString::fgCyan,    TRUE, FALSE, CxString::bgBlack, FALSE ).data(),
        xT("#  Expression:      "), CxString::sFormatNixTerminal( _m_sExpression,                          CxString::fgYellow,  TRUE, FALSE, CxString::bgBlack, FALSE ).data(),
        xT("#  Last error:      "), CxString::sFormatNixTerminal( _m_sLastErrorStr,                        CxString::fgRed,     TRUE, FALSE, CxString::bgBlack, FALSE ).data(),

        xT("#  Current date:    "), _m_sCurrentDate.data(),
        xT("#  Build date:      "), _m_sBuildDate.data(),
        xT("#  OS version:      "), _m_sOsVersion.data(),
        xT("#  OS architecture: "), _m_sOsArchitecture.data(),

        xT("#  Comment:         "), CxString::sFormatNixTerminal( _m_sComment,                             CxString::fgYellow_, FALSE, FALSE, CxString::bgBlue,  FALSE ).data()
    );
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: _sGetOsArchitecture (get OS architecture)
tString
CxReport::_sGetOsArchitecture() {
    /*DEBUG*/// n/a

    tString sRes;

    switch (CxSystemInfo::oaGetOsArchitecture()) {
        case CxSystemInfo::oa32bit:     sRes = xT("32-bit");    break;
        case CxSystemInfo::oa64bit:     sRes = xT("64-bit");    break;
        case CxSystemInfo::oaUnknown:   sRes = xT("Unknown");   break;

        default:                        sRes = xT("Unknown");   break;
    }

    return sRes;
}
//---------------------------------------------------------------------------
