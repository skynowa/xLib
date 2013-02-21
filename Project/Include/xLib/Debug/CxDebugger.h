/**
 * \file  CxDebugger.h
 * \brief debugger
 */


#ifndef xLib_Debug_CxDebuggerH
#define xLib_Debug_CxDebuggerH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxErrorReport;

class CxDebugger :
    private CxNonCopyable
    /// debugger
{
public:
                   CxDebugger   ();
        ///< constructor
    virtual       ~CxDebugger   ();
        ///< destructor

    bool           isEnabled    () xWARN_UNUSED_RESULT;
        ///< is debugging enabled
    void           setEnabled   (const bool &cbFlag);
        ///< set debugging mode on/off
    bool           isActive     () xWARN_UNUSED_RESULT;
        ///< is OS debugger presents
    bool           isDebugBuild () xWARN_UNUSED_RESULT;
        ///< is debug build (is NDEBUG macros is don't set)
    void           breakPoint   ();
        ///< attach to OS debugger
    void           setLogPath   (const std::tstring_t &csFilePath);
        ///< set log file path
    std::tstring_t logPath      () xWARN_UNUSED_RESULT;
        ///< get log file path
    void           reportMake   (const CxErrorReport &crpReport);
        ///< make report

private:
    bool           _m_bIsEnabled;
        ///< is debugger enabled
    std::tstring_t _m_sLogPath;
        ///< log path

    void           _msgboxPlain (const CxErrorReport &crpReport);
        ///< show message box with plain report
    void           _stdoutPlain (const CxErrorReport &crpReport);
        ///< show plain report in std::cout
    void           _loggingPlain(const CxErrorReport &crpReport);
        ///< log plain report to file
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Debug_CxDebuggerH
