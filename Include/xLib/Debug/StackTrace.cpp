/**
 * \file   StackTrace.h
 * \brief  stackrace of the caller function
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "StackTrace.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/IO/Path.h>
#include <xLib/Log/Trace.h>
#include <xLib/Test/StdTest.h>

xNAMESPACE_ANONYM_BEGIN

std::csize_t elementsNum = 5;
    ///< number of elements

xNAMESPACE_ANONYM_END

#if   xENV_WIN
    #include "Platform/Win/StackTrace_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/StackTrace_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/StackTrace_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/StackTrace_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/StackTrace_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
StackTrace::StackTrace(
    cint_t          &a_skipFramesNum,      /* = 2 */    ///< Skip number of frames
    cbool_t         &a_isWrapFilePaths,    /* = true */
    cbool_t         &a_isFuncParamsDisable /* = true */
) :
    _skipFramesNum      (a_skipFramesNum),
    _isWrapFilePaths    (a_isWrapFilePaths),
    _isFuncParamsDisable(a_isFuncParamsDisable)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
StackTrace::toString()
{
    std::tstring_t                  sRv;
    std::vector<std::vec_tstring_t> stack;

    _get_impl(&stack);
    _format(stack, &sRv);
    xCHECK_RET(sRv.empty(), Const::strUnknown());

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
StackTrace::_get(
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
xINLINE void_t
StackTrace::_format(
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
        xFOR_EACH_CONST(std::vector<std::vec_tstring_t>, it, a_stack) {
            cint_t current = static_cast<int_t>( it->at(i).size() );
            xCHECK_DO(current > maxs[i], maxs[i] = current);
        }
    }

    // formatting
    std::size_t lineNumber = 0;

    xFOR_EACH_CONST(std::vector<std::vec_tstring_t>, it, a_stack) {
        ++ lineNumber;

        std::tstringstream_t stackLine;
        stackLine
            << std::setw(0)       << std::right << lineNumber << xT(". ")
            << std::setw(maxs[0]) << std::left  << it->at(0)  << xT("  ")
            << std::setw(maxs[1]) << std::left  << it->at(1)  << xT("  ")
            << std::setw(maxs[2]) << std::right << it->at(2)  << xT("  ")
            << std::setw(maxs[3]) << std::left  << it->at(3)  << xT("  ")
            << std::setw(maxs[4]) << std::left  << it->at(4);

        if (it + 1 != a_stack.end()) {
             stackLine << Const::nl();
        }

        sRv.append( stackLine.str() );
    }

    // out
    a_stackStr->swap(sRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
