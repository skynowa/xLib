/**
 * \file  CxDebugger.h
 * \brief debbuger
 */


#ifndef xLib_Debug_CxDebuggerH
#define xLib_Debug_CxDebuggerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Debug/CxReport.h>
//---------------------------------------------------------------------------
class CxReport;

class CxDebugger :
    public CxNonCopyable
    /// debbuger
{
    public:
        static BOOL         bGetEnabled     ();
            ///< is debugging enabled
        static BOOL         bSetEnabled     (const BOOL cbFlag);
            ///< set debugging mode on/off
        static BOOL         bIsPresent      ();
            ///< is OS debugger presents
        static BOOL         bBreak          ();
            ///< attach to OS debugger
        static BOOL         bSetLogPath     (const std::tstring &csFilePath);
            ///< set log file path
        static std::tstring sGetLogPath     ();
            ///< get log file path
        static BOOL         bReportMake     (const CxReport &crpReport);
            ///< make report
        static BOOL         bTrace          (const TCHAR *pcszFormat, ...);
            ///< tracing to debugger, std::cout
        static BOOL         bTrace          (const std::tstring &csMsg);
            ///< tracing to debugger, std::cout
        static BOOL         bBeep           (const ULONG culFrequency = 800, const ULONG culDuration = 100);
            ///< play sound

    private:
        static BOOL         _ms_bIsEnabled;
            ///< is debugger enabled
        static std::tstring _ms_sLogPath;
            ///< log path

                            CxDebugger      ();
            ///< constructor
        virtual            ~CxDebugger      ();
            ///< destructor

        static BOOL         _bMsgboxPlain   (const CxReport &crpReport);
            ///< show message box with plain report
        static BOOL         _bMsgboxFormated(const CxReport &crpReport);
            ///< show message box with formated report, std::cerr

        static BOOL         _bStdoutPlain   (const CxReport &crpReport);
            ///< show plain report in std::cout
        static BOOL         _bStdoutHtml    (const CxReport &crpReport);
            ///< show html report in std::cout

        static BOOL         _bLoggingPlain  (const CxReport &crpReport);
            ///< log plain report to file
        static BOOL         _bLoggingHtml   (const CxReport &crpReport);
            ///< log html report to file
};
//---------------------------------------------------------------------------
#endif    //xLib_Debug_CxDebuggerH
