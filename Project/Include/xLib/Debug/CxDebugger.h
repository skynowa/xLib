/**
 * \file  CxDebugger.h
 * \brief debugger
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxNonCopyable.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

// TODO: class CxErrorReport;

class CxDebugger :
    public CxNonCopyable
    /// debugger
{
public:
                   CxDebugger();
        ///< constructor
    virtual       ~CxDebugger() {}
        ///< destructor

    bool_t         isEnabled() xWARN_UNUSED_RV;
        ///< is debugging enabled
    void_t         setEnabled(cbool_t &flag);
        ///< set debugging mode on/off
    bool_t         isActive() xWARN_UNUSED_RV;
        ///< is OS debugger presents
    bool_t         isDebugBuild() xWARN_UNUSED_RV;
        ///< is debug build (is NDEBUG macros is don't set)
    void_t         breakPoint();
        ///< attach to OS debugger
    void_t         setLogPath(std::ctstring_t &filePath);
        ///< set log file path
    std::tstring_t logPath() xWARN_UNUSED_RV;
        ///< get log file path
    void_t         reportMake(const CxErrorReport &report);
        ///< make report

private:
    bool_t         _isEnabled;
        ///< is debugger enabled
    std::tstring_t _logPath;
        ///< log path

    void_t         _msgboxPlain(const CxErrorReport &report);
        ///< show message box with plain report
    void_t         _stdoutPlain(const CxErrorReport &report);
        ///< show plain report in std::cout
    void_t         _loggingPlain(const CxErrorReport &report);
        ///< log plain report to file
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Debug/CxDebugger.inl>
