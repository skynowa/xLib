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
        static bool           bGetEnabled     ();
            ///< is debugging enabled
        static bool           bSetEnabled     (const bool cbFlag);
            ///< set debugging mode on/off
        static bool           bIsPresent      ();
            ///< is OS debugger presents
        static bool           bIsDebugBuild   ();
            ///< is debug build (is NDEBUG macros is don't set)
        static bool           bBreak          ();
            ///< attach to OS debugger
        static bool           bSetLogPath     (const std::tstring_t &csFilePath);
            ///< set log file path
        static std::tstring_t sGetLogPath     ();
            ///< get log file path
        static bool           bReportMake     (const CxReport &crpReport);
            ///< make report
        static bool           bTrace          (const tchar_t *pcszFormat, ...);
            ///< tracing to debugger, std::cout
        static bool           bTrace          (const std::tstring_t &csMsg);
            ///< tracing to debugger, std::cout
        static bool           bBeep           (const ulong_t culFrequency = 800, const ulong_t culDuration = 100);
            ///< play sound

    private:
        static bool           _ms_bIsEnabled;
            ///< is debugger enabled
        static std::tstring_t _ms_sLogPath;
            ///< log path

                              CxDebugger      ();
            ///< constructor
        virtual              ~CxDebugger      ();
            ///< destructor

        static bool           _bMsgboxPlain   (const CxReport &crpReport);
            ///< show message box with plain report
        static bool           _bMsgboxFormated(const CxReport &crpReport);
            ///< show message box with formated report, std::cerr

        static bool           _bStdoutPlain   (const CxReport &crpReport);
            ///< show plain report in std::cout
        static bool           _bStdoutHtml    (const CxReport &crpReport);
            ///< show html report in std::cout

        static bool           _bLoggingPlain  (const CxReport &crpReport);
            ///< log plain report to file
        static bool           _bLoggingHtml   (const CxReport &crpReport);
            ///< log html report to file
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Debug_CxDebuggerH
