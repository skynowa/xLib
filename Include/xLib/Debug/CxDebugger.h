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
xNAMESPACE_BEGIN(NxLib)

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
        static BOOL         bIsDebugBuild   ();
            ///< is debug build (is NDEBUG macros is don't set)
        static BOOL         bBreak          ();
            ///< attach to OS debugger
        static BOOL         bSetLogPath     (const std::string_t &csFilePath);
            ///< set log file path
        static std::string_t sGetLogPath     ();
            ///< get log file path
        static BOOL         bReportMake     (const CxReport &crpReport);
            ///< make report
        static BOOL         bTrace          (const char_t *pcszFormat, ...);
            ///< tracing to debugger, std::cout
        static BOOL         bTrace          (const std::string_t &csMsg);
            ///< tracing to debugger, std::cout
        static BOOL         bBeep           (const ULONG culFrequency = 800, const ULONG culDuration = 100);
            ///< play sound

    private:
        static BOOL         _ms_bIsEnabled;
            ///< is debugger enabled
        static std::string_t _ms_sLogPath;
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

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Debug_CxDebuggerH
