/**
 * \file   CxStackTrace.h
 * \brief  stackrace of the caller function
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Log/CxTrace.h>
#include <xLib/Debug/xStdDebug.h>

xNAMESPACE_ANONYM_BEGIN

std::csize_t elementsNum   = 5;
    ///< number of elements
std::csize_t skipFramesNum = 2;
   /**
    * Skip number of frames
    *
    * Skip 2 first elements of a real stack - it's a class internals:
    *   0  xLib_test  ??  0  0x46d314  xlib::CxStackTrace::_get() const
    *   1  xLib_test  ??  0  0x46e090  xlib::CxStackTrace::toString()
    */
xNAMESPACE_ANONYM_END

#if   xENV_WIN
    #include "Platform/Win/CxStackTrace_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxStackTrace_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxStackTrace_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxStackTrace_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxStackTrace::CxStackTrace(
    std::ctstring_t &a_linePrefix,         /* = xT("\t") */
    std::ctstring_t &a_elementSeparator,   /* = xT("  ") */
    std::ctstring_t &a_lineSeparator,      /* = xT("\n") */
    cbool_t         &a_isWrapFilePaths,    /* = true */
    cbool_t         &a_isFuncParamsDisable /* = true */
) :
    _linePrefix         (a_linePrefix),
    _elementSeparator   (a_elementSeparator),
    _lineSeparator      (a_lineSeparator),
    _isWrapFilePaths    (a_isWrapFilePaths),
    _isFuncParamsDisable(a_isFuncParamsDisable)
{
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxStackTrace::toString()
{
    std::tstring_t                  sRv;
    std::vector<std::vec_tstring_t> stack;

    _get_impl(&stack);
    _format(stack, &sRv);
    xCHECK_RET(sRv.empty(), CxConst::strUnknown());

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxStackTrace::_get(
    std::vector<std::vec_tstring_t> *a_stack
) const
{
    xCHECK_DO(a_stack == xPTR_NULL, return);

    std::vector<std::vec_tstring_t> stack;

    _get_impl(&stack);
    std::reverse(stack.begin(), stack.end());

    // out
    a_stack->swap(stack);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxStackTrace::_format(
    const std::vector<std::vec_tstring_t> &a_stack,     ///< stack as std::vector
    std::tstring_t                        *a_stackStr   ///< [out] stack as formatted string
) const
{
    xCHECK_DO(a_stack.empty(),         return);
    xCHECK_DO(a_stackStr == xPTR_NULL, return);

    std::tstring_t     sRv;
    std::vector<int_t> maxs(::elementsNum, 0);

    // get elements max sizes
    for (size_t i = 0; i < ::elementsNum; ++ i) {
        xFOREACH_CONST(std::vector<std::vec_tstring_t>, it, a_stack) {
            cint_t current = static_cast<int_t>( it->at(i).size() );
            xCHECK_DO(current > maxs[i], maxs[i] = current);
        }
    }

    // formatting
    std::size_t lineNumber = 0;

    xFOREACH_CONST(std::vector<std::vec_tstring_t>, it, a_stack) {
        std::tstringstream_t stackLine;

        stackLine
            << _linePrefix
            << std::setw(2)       << std::right << (++ lineNumber) << "." << _elementSeparator
            << std::setw(maxs[0]) << std::left  << it->at(0)              << _elementSeparator
            << std::setw(maxs[1]) << std::left  << it->at(1)              << _elementSeparator
            << std::setw(maxs[2]) << std::right << it->at(2)              << _elementSeparator
            << std::setw(maxs[3]) << std::left  << it->at(3)              << _elementSeparator
            << std::setw(maxs[4]) << std::left  << it->at(4)
            << _lineSeparator;

        sRv.append(stackLine.str());
    }

    // out
    a_stackStr->swap(sRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
