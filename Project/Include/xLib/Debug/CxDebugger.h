/**
 * \file  CxDebugger.h
 * \brief debugger
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxNonCopyable.h>
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

    bool_t         isEnabled    () xWARN_UNUSED_RV;
        ///< is debugging enabled
    void_t         setEnabled   (cbool_t &cbFlag);
        ///< set debugging mode on/off
    bool_t         isActive     () xWARN_UNUSED_RV;
        ///< is OS debugger presents
    bool_t         isDebugBuild () xWARN_UNUSED_RV;
        ///< is debug build (is NDEBUG macros is don't set)
    void_t         breakPoint   ();
        ///< attach to OS debugger
    void_t         setLogPath   (std::ctstring_t &csFilePath);
        ///< set log file path
    std::tstring_t logPath      () xWARN_UNUSED_RV;
        ///< get log file path
    void_t         reportMake   (const CxErrorReport &crpReport);
        ///< make report

private:
    bool_t         _m_bIsEnabled;
        ///< is debugger enabled
    std::tstring_t _m_sLogPath;
        ///< log path

    void_t         _msgboxPlain (const CxErrorReport &crpReport);
        ///< show message box with plain report
    void_t         _stdoutPlain (const CxErrorReport &crpReport);
        ///< show plain report in std::cout
    void_t         _loggingPlain(const CxErrorReport &crpReport);
        ///< log plain report to file
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
