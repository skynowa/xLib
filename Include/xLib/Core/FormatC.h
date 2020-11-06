/**
 * \file   FormatC.h
 * \brief  C-style format string
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

class FormatC
    ///< format string in C style
{
public:
///@name ctors, dtor
///@{
	xNO_DEFAULT_CONSTRUCT(FormatC);
	xNO_COPY_ASSIGN(FormatC);
///@}

    static std::tstring_t str(cptr_ctchar_t format, ...);
    static std::tstring_t strV(cptr_ctchar_t format, va_list args);
};

} // namespace
//-------------------------------------------------------------------------------------------------
