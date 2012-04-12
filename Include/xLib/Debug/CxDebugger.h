/**
 * \file  CxDebugger.h
 * \brief debugger
 */


#ifndef xLib_Debug_CxDebuggerH
#define xLib_Debug_CxDebuggerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxErrorReport;

class CxDebugger :
    private CxNonCopyable
    /// debugger
{
    public:
                              CxDebugger      ();
            ///< constructor
        virtual              ~CxDebugger      ();
            ///< destructor

        template<class T>
        friend CxDebugger &   operator <<     (CxDebugger &cdbgDebugger, const T &cMessageT);
            ///< tracing to debugger, std::cout

        bool                  bGetEnabled     ();
            ///< is debugging enabled
        bool                  bSetEnabled     (const bool cbFlag);
            ///< set debugging mode on/off
        bool                  bIsPresent      ();
            ///< is OS debugger presents
        bool                  bIsDebugBuild   ();
            ///< is debug build (is NDEBUG macros is don't set)
        bool                  bBreak          ();
            ///< attach to OS debugger
        bool                  bSetLogPath     (const std::tstring_t &csFilePath);
            ///< set log file path
        std::tstring_t        sGetLogPath     ();
            ///< get log file path
        bool                  bReportMake     (const CxErrorReport &crpReport);
            ///< make report
        static bool           bTrace          (const tchar_t *pcszFormat, ...);
            ///< tracing to debugger, std::cout
        static bool           bTrace          (const std::tstring_t &csMsg);
            ///< tracing to debugger, std::cout
        static bool           bBeep           (const ulong_t culFrequency = 800UL, const ulong_t culDuration = 100UL);
            ///< play sound

    private:
        bool                  _m_bIsEnabled;
            ///< is debugger enabled
        std::tstring_t        _m_sLogPath;
            ///< log path
        std::tostringstream_t _m_ossTracer;
            ///< 

        bool                  _bMsgboxPlain   (const CxErrorReport &crpReport);
            ///< show message box with plain report
        bool                  _bMsgboxFormated(const CxErrorReport &crpReport);
            ///< show message box with formated report, std::cerr
        bool                  _bStdoutPlain   (const CxErrorReport &crpReport);
            ///< show plain report in std::cout
        bool                  _bStdoutHtml    (const CxErrorReport &crpReport);
            ///< show html report in std::cout
        bool                  _bLoggingPlain  (const CxErrorReport &crpReport);
            ///< log plain report to file
        bool                  _bLoggingHtml   (const CxErrorReport &crpReport);
            ///< log html report to file
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxDebugger.inl"
//---------------------------------------------------------------------------
#endif    //xLib_Debug_CxDebuggerH
