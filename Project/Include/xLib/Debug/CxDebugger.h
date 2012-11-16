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

        bool                  bIsEnabled     ();
            ///< is debugging enabled
        void                  vSetEnabled     (const bool &cbFlag);
            ///< set debugging mode on/off
        bool                  bIsActive       ();
            ///< is OS debugger presents
        bool                  bIsDebugBuild   ();
            ///< is debug build (is NDEBUG macros is don't set)
        void                  vBreak          ();
            ///< attach to OS debugger
        void                  vSetLogPath     (const std::tstring_t &csFilePath);
            ///< set log file path
        std::tstring_t        sLogPath        ();
            ///< get log file path
        void                  vReportMake     (const CxErrorReport &crpReport);
            ///< make report

    private:
        bool                  _m_bIsEnabled;
            ///< is debugger enabled
        std::tstring_t        _m_sLogPath;
            ///< log path

        void                  _vMsgboxPlain   (const CxErrorReport &crpReport);
            ///< show message box with plain report
        void                  _vMsgboxFormated(const CxErrorReport &crpReport);
            ///< show message box with formated report, std::cerr
        void                  _vStdoutPlain   (const CxErrorReport &crpReport);
            ///< show plain report in std::cout
        void                  _vLoggingPlain  (const CxErrorReport &crpReport);
            ///< log plain report to file
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Debug_CxDebuggerH
