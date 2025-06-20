/**
 * \file  StackTrace.cpp
 * \brief Stackrace of the caller function
 */


#include "StackTrace.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Fs/Path.h>
#include <xLib/Log/LogStream.h>

#if   xENV_WIN
    #include "Platform/Win/StackTrace_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/StackTrace_unix.inl"
#endif

namespace
{

std::csize_t columnsNum {5};

}

namespace xl::debug
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
StackTrace::StackTrace() :
	StackTrace( cStackTraceOption() )
{
}
//-------------------------------------------------------------------------------------------------
StackTrace::StackTrace(
    cStackTraceOption &a_option
) :
    _option(a_option)
{
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
StackTrace::str() const /* final */
{
    std::tstring_t                  sRv;
    std::vector<std::vec_tstring_t> stack;

    _get_impl(&stack);

	if (_option.isReverse) {
		std::reverse(stack.begin(), stack.end());
	}

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
void_t
StackTrace::_format(
    std::vector<std::vec_tstring_t> &a_stack,     ///< stack as std::vector
    std::tstring_t                  *a_stackStr   ///< [out] stack as formatted string
) const
{
    xCHECK_DO(a_stack.empty(),       return);
    xCHECK_DO(a_stackStr == nullptr, return);

    std::tstring_t     sRv;
    std::vector<int_t> maxs(::columnsNum, 0);

    // add header
    {
        std::cvec_tstring_t stackHeader
        {
			xT("Module"),
			xT("File"),
			xT("Line"),
			xT("Offset"),
			xT("Function")
        };

        a_stack.insert(a_stack.cbegin(), stackHeader);
    }

    // get elements max sizes
    for (size_t i = 0; i < ::columnsNum; ++ i) {
        for (const auto &it : a_stack) {
            std::csize_t current = it.at(i).size();
            xCHECK_DO(static_cast<int_t>(current) > maxs[i], maxs[i] = static_cast<int_t>(current));
        }
    }

    // formatting
    std::size_t lineNumber {};

    for (auto it = a_stack.cbegin(); it != a_stack.cend(); ++ it) {
        if (it != a_stack.cbegin()) {
            ++ lineNumber;
        }

		std::tstring_t lineNumberStr;
		{
			if (lineNumber == 0) {
				lineNumberStr = xT("#  ");
			} else {
				lineNumberStr = Format::str(xT("[{}]"), lineNumber);
			}

			if (a_stack.size() >= 10 && lineNumber < 10) {
				lineNumberStr.insert(1, xT(" "));
			}
		}

        std::tstringstream_t stackLine;
        stackLine
            << std::setw(0)       << std::right << lineNumberStr << xT(" ")
            << std::setw(maxs[0]) << std::left  << it->at(0)     << xT("  ")
            << std::setw(maxs[1]) << std::left  << it->at(1)     << xT("  ")
            << std::setw(maxs[2]) << std::left  << it->at(2)     << xT("  ")
            << std::setw(maxs[3]) << std::left  << it->at(3)     << xT("  ")
            << std::setw(0)       << std::left  << it->at(4);


        if (it + 1 != a_stack.cend()) {
             stackLine << Const::nl();
        }

        sRv += stackLine.str();
    }

    // out
    a_stackStr->swap(sRv);
}
//-------------------------------------------------------------------------------------------------
void_t
StackTrace::_funcArgsDisable(
	std::tstring_t *out_functionName	///< [in, out] function name with params
) const
{
	xCHECK_DO(out_functionName == nullptr, return);

	// Args - rm
	{
		std::csize_t pos1 = out_functionName->find(xT('('));
		xCHECK_DO(pos1 == std::tstring_t::npos, return);

		std::csize_t pos2 = out_functionName->find(xT(')'));
		xCHECK_DO(pos2 == std::tstring_t::npos, return);

		xSTD_VERIFY(pos1 < pos2);

		// Args - insert placeholder
		std::ctstring_t argsPlaceholder = (pos1 == pos2 - 1) ? xT("") : xT("...");

		// [out]
		*out_functionName = out_functionName->substr(0, pos1 + 1) + argsPlaceholder +
			out_functionName->substr(pos2);
	}

	// Extra strings - rm
	{
		static constexpr ctchar_t *extraStrs[]
		{
			xT("[abi:cxx11]")
		};

		for (const auto it_extraStr : extraStrs) {
			// [out]
			*out_functionName = String::removeAll(*out_functionName, it_extraStr);
		}
	}
}
//-------------------------------------------------------------------------------------------------
void_t
StackTrace::_wrapFilePaths(
	std::tstring_t *out_modulePath,
	std::tstring_t *out_filePath
) const
{
	if (out_modulePath != nullptr) {
		*out_modulePath = Path(*out_modulePath).fileName();
	}

	if (out_filePath != nullptr) {
		*out_filePath = Path(*out_filePath).fileName();
	}
}
//-------------------------------------------------------------------------------------------------

} // namespace
