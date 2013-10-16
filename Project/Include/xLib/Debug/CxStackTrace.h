/**
 * \file   CxStackTrace.h
 * \brief  get stack backtrace of the caller function
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxStackTrace :
    private CxNonCopyable
    /// stack trace
{
public:
    explicit        CxStackTrace(std::ctstring_t &linePrefix = xT("\t\t"),
                        std::ctstring_t &elementSeparator = xT("  "),
                        std::ctstring_t &lineSeparator = xT("\n"),
                        cbool_t &isWrapFilePaths = true, cbool_t &isFuncParamsDisable = true);
        ///< constructor
    virtual        ~CxStackTrace();
        ///< destructor

    void_t          get(std::vector<std::vec_tstring_t> *stack);
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
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
