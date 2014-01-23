/**
 * \file  CxDebugger.h
 * \brief debugger
 */


#pragma once

#ifndef xLib_CxDebuggerH
#define xLib_CxDebuggerH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, debug)

class CxDebugger
    /// debugger
{
public:
                   CxDebugger();
        ///< constructor
    virtual       ~CxDebugger() {}
        ///< destructor

    bool_t         isEnabled() const xWARN_UNUSED_RV;
        ///< is debugging enabled
    void_t         setEnabled(cbool_t &flag);
        ///< set debugging mode on/off
    bool_t         isActive() const xWARN_UNUSED_RV;
        ///< is OS debugger presents
    bool_t         isDebugBuild() const xWARN_UNUSED_RV;
        ///< is debug build (is NDEBUG macros is don't set)
    void           coreDumpsEnable(cbool_t &flag);
        ///< core dumps
    void_t         breakPoint() const;
        ///< attach to OS debugger
    void_t         setLogPath(std::ctstring_t &filePath);
        ///< set log file path
    std::tstring_t logPath() const xWARN_UNUSED_RV;
        ///< get log file path
    void_t         reportMake(const CxErrorReport &report);
        ///< make report

private:
    bool_t         _isEnabled;
        ///< is debugger enabled
    std::tstring_t _logPath;
        ///< log path

    void_t         _msgboxPlain(const CxErrorReport &report) const;
        ///< show message box with plain report
    void_t         _stdoutPlain(const CxErrorReport &report) const;
        ///< show plain report in std::cout
    void_t         _loggingPlain(const CxErrorReport &report) const;
        ///< log plain report to file

    xNO_COPY_ASSIGN(CxDebugger)
};

xNAMESPACE2_END(xlib, debug)
//-------------------------------------------------------------------------------------------------
#include "CxDebugger.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxDebuggerH
