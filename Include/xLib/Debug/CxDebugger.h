/**
 * \file  CxDebugger.h
 * \brief debugger
 */


#ifndef xLib_Debug_CxDebuggerH
#define xLib_Debug_CxDebuggerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Common/CxString.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxString;
class CxErrorReport;

class CxDebugger :
    private CxNonCopyable
    /// debbuger
{
    public:
                              CxDebugger      ();
            ///< constructor
        virtual              ~CxDebugger      ();
            ///< destructor

        template<class T>
        friend CxDebugger &   operator <<     (CxDebugger &cdbgDebugger, const T &cMessageT);
            ///< tracing to debugger, std::cout

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
        static bool           bReportMake     (const CxErrorReport &crpReport);
            ///< make report
        static bool           bTrace          (const tchar_t *pcszFormat, ...);
            ///< tracing to debugger, std::cout
        static bool           bTrace          (const std::tstring_t &csMsg);
            ///< tracing to debugger, std::cout
        static bool           bBeep           (const ulong_t culFrequency = 800, const ulong_t culDuration = 100);
            ///< play sound

    private:
        std::tostringstream_t _m_ossTracer;

        static bool           _ms_bIsEnabled;
            ///< is debugger enabled
        static std::tstring_t _ms_sLogPath;
            ///< log path

        static bool           _bMsgboxPlain   (const CxErrorReport &crpReport);
            ///< show message box with plain report
        static bool           _bMsgboxFormated(const CxErrorReport &crpReport);
            ///< show message box with formated report, std::cerr
        static bool           _bStdoutPlain   (const CxErrorReport &crpReport);
            ///< show plain report in std::cout
        static bool           _bStdoutHtml    (const CxErrorReport &crpReport);
            ///< show html report in std::cout
        static bool           _bLoggingPlain  (const CxErrorReport &crpReport);
            ///< log plain report to file
        static bool           _bLoggingHtml   (const CxErrorReport &crpReport);
            ///< log html report to file
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxDebugger.inl"
//---------------------------------------------------------------------------
#endif    //xLib_Debug_CxDebuggerH
