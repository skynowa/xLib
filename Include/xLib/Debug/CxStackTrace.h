/**
 * \file   CxStackTrace.h
 * \brief  get stack backtrace of the caller function
 */


#pragma once

#ifndef xLib_CxStackTraceH
#define xLib_CxStackTraceH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, debug)

class CxStackTrace
    /// stack trace
{
public:
    explicit        CxStackTrace(std::ctstring_t &linePrefix = xT("\t\t"),
                        std::ctstring_t &elementSeparator = xT("  "),
                        std::ctstring_t &lineSeparator = xT("\n"),
                        cbool_t &isWrapFilePaths = true, cbool_t &isFuncParamsDisable = true);
        ///< constructor
    virtual        ~CxStackTrace() {}
        ///< destructor

    std::tstring_t  toString() xWARN_UNUSED_RV;
        ///< get stack trace with format output

private:
    std::ctstring_t _linePrefix;
    std::ctstring_t _elementSeparator;
    std::ctstring_t _lineSeparator;
    cbool_t         _isWrapFilePaths;
    cbool_t         _isFuncParamsDisable;

    void_t          _get(std::vector<std::vec_tstring_t> *stack) const;
        ///< get stack trace
    void_t          _format(const std::vector<std::vec_tstring_t> &stack, std::tstring_t *stackStr)
                        const;
        ///< format stack trace
#if xOS_ENV_UNIX
    static
    void_t          _addr2Line(cvoid_t *symbolAddress, std::tstring_t *filePath,
                        std::tstring_t *functionName, ulong_t *sourceLine);
#endif

    xNO_COPY_ASSIGN(CxStackTrace)
};

xNAMESPACE2_END(xlib, debug)
//-------------------------------------------------------------------------------------------------
#include "CxStackTrace.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxStackTraceH
