/**
 * \file  Debugger.h
 * \brief debugger
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, debug)

class ErrorReport;

class Debugger
    /// debugger
{
public:
                   Debugger() = default;
    virtual       ~Debugger() = default;

    bool_t         isEnabled() const;
        ///< is debugging enabled
    void_t         setEnabled(cbool_t &flag);
        ///< set debugging mode on/off
    bool_t         isActive() const;
        ///< is OS debugger presents
    void_t         coreDumpsEnable(cbool_t &flag);
        ///< core dumps
    void_t         breakPoint() const;
        ///< attach to OS debugger
    void_t         setLogPath(std::ctstring_t &filePath);
        ///< set log file path
    std::tstring_t logPath() const;
        ///< get log file path
    void_t         reportMake(const ErrorReport &report) const;
        ///< make report

private:
    bool_t         _isEnabled {true};
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
    bool_t         _isActive_impl() const;
    void_t         _coreDumpsEnable_impl(cbool_t &flag, bool_t *isEnable);
    void_t         _breakPoint_impl() const;
};

xNAMESPACE_END2(xl, debug)
//-------------------------------------------------------------------------------------------------
