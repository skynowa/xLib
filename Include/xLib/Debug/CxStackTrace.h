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
xNAMESPACE_BEGIN(NxLib)

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

    void_t          get(std::vector<std::vec_tstring_t> *stack) const;
        ///< get stack trace
    std::tstring_t  toString() xWARN_UNUSED_RV;
        ///< get stack trace with format output

private:
    std::ctstring_t _linePrefix;
    std::ctstring_t _elementSeparator;
    std::ctstring_t _lineSeparator;
    cbool_t         _isWrapFilePaths;
    cbool_t         _isFuncParamsDisable;

    std::tstring_t  _format(std::vector<std::vec_tstring_t> *stack) xWARN_UNUSED_RV;
        ///< format stack trace
#if !xOS_ENV_WIN
    static void_t   _addr2Line(cvoid_t *symbolAddress, std::tstring_t *filePath,
                        std::tstring_t *functionName, ulong_t *sourceLine);
#endif

xNO_COPY_ASSIGN(CxStackTrace)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxStackTrace.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxStackTraceH
