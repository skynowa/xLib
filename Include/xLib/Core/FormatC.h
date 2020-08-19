/**
 * \file   FormatC.h
 * \brief  C-style format string
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class FormatC
    ///< format string in C style
{
public:
	xNO_DEFAULT_CONSTRUCT(FormatC);

    static std::tstring_t str(cptr_ctchar_t format, ...) xWARN_UNUSED_RV;
    static std::tstring_t strV(cptr_ctchar_t format, va_list args) xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
