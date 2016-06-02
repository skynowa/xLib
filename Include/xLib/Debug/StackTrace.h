/**
 * \file   StackTrace.h
 * \brief  stackrace of the caller function
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, debug)

class StackTrace
    /// stack trace
{
public:
    explicit        StackTrace(cint_t &skipFramesNum = 2, std::ctstring_t &linePrefix = xT(""),
                        std::ctstring_t &lineSeparator = xT("\n"),
                        cbool_t &isWrapFilePaths = true, cbool_t &isFuncParamsDisable = true);
        ///< constructor
    virtual        ~StackTrace() {}
        ///< destructor

    std::tstring_t  toString() xWARN_UNUSED_RV;
        ///< get stack trace with format output

private:
    cint_t          _skipFramesNum;
    std::ctstring_t _linePrefix;
    std::ctstring_t _lineSeparator;
    cbool_t         _isWrapFilePaths;
    cbool_t         _isFuncParamsDisable;

    void_t          _get(std::vector<std::vec_tstring_t> *stack) const;
        ///< get stack trace
    void_t          _format(const std::vector<std::vec_tstring_t> &stack, std::tstring_t *stackStr)
                        const;
        ///< format stack trace

    xNO_COPY_ASSIGN(StackTrace)

xPLATFORM_IMPL:
    void_t          _get_impl(std::vector<std::vec_tstring_t> *stack) const;

#if xENV_UNIX
    static
    void_t          _addr2Line(cvoid_t *symbolAddress, std::tstring_t *filePath,
                        std::tstring_t *functionName, ulong_t *sourceLine);
#endif
};

xNAMESPACE_END2(xlib, debug)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "StackTrace.cpp"
#endif
