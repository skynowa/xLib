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

    bool_t           isEnabled    () xWARN_UNUSED_RV;
        ///< is debugging enabled
    void           setEnabled   (cbool_t &cbFlag);
        ///< set debugging mode on/off
    bool_t           isActive     () xWARN_UNUSED_RV;
        ///< is OS debugger presents
    bool_t           isDebugBuild () xWARN_UNUSED_RV;
        ///< is debug build (is NDEBUG macros is don't set)
    void           breakPoint   ();
        ///< attach to OS debugger
    void           setLogPath   (std::ctstring_t &csFilePath);
        ///< set log file path
    std::tstring_t logPath      () xWARN_UNUSED_RV;
        ///< get log file path
    void           reportMake   (const CxErrorReport &crpReport);
        ///< make report

private:
    bool_t           _m_bIsEnabled;
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
