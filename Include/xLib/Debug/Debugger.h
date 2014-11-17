/**
 * \file  Debugger.h
 * \brief debugger
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, debug)

class ErrorReport;

class Debugger
    /// debugger
{
public:
                   Debugger();
        ///< constructor
    virtual       ~Debugger() {}
        ///< destructor

    bool_t         isEnabled() const xWARN_UNUSED_RV;
        ///< is debugging enabled
    void_t         setEnabled(cbool_t &flag);
        ///< set debugging mode on/off
    bool_t         isActive() const xWARN_UNUSED_RV;
        ///< is OS debugger presents
    void_t         coreDumpsEnable(cbool_t &flag);
        ///< core dumps
    void_t         breakPoint() const;
        ///< attach to OS debugger
    void_t         setLogPath(std::ctstring_t &filePath);
        ///< set log file path
    std::tstring_t logPath() const xWARN_UNUSED_RV;
        ///< get log file path
    void_t         reportMake(const ErrorReport &report);
        ///< make report

private:
    bool_t         _isEnabled;
        ///< is debugger enabled
    std::tstring_t _logPath;
        ///< log path

    void_t         _msgboxPlain(const ErrorReport &report) const;
        ///< show message box with plain report
    void_t         _stdoutPlain(const ErrorReport &report) const;
        ///< show plain report in std::cout
    void_t         _loggingPlain(const ErrorReport &report) const;
        ///< log plain report to file

    xNO_COPY_ASSIGN(Debugger)

xPLATFORM_IMPL:
    bool_t         _isActive_impl() const xWARN_UNUSED_RV;
    void_t         _coreDumpsEnable_impl(cbool_t &flag, bool_t *isEnable);
    void_t         _breakPoint_impl() const;
};

xNAMESPACE_END2(xlib, debug)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "Debugger.cpp"
#endif
