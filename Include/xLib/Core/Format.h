/**
 * \file   Format.h
 * \brief  format string
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
#include <xLib/Core/OStream.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename StreamT>
class FormatT
    ///< format string
{
public:
    template<typename ...ArgsT>
    static
    std::tstring_t str(std::ctstring_t &fmt, ArgsT &&...args);

    xNO_INSTANCE(FormatT)
    xNO_COPY_ASSIGN(FormatT)
};

using FormatStd = FormatT<std::tstringstream_t>;
using Format    = FormatT<xl::core::OStream>;

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Format.inl"
