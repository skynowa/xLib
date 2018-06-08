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
#define xFORMAT_STR_DECLARE(n) \
    template<xVA_TYPES_##n> \
    static \
    std::tstring_t str(std::ctstring_t &format, xVA_VARS_##n) xWARN_UNUSED_RV

    xFORMAT_STR_DECLARE(1);
    xFORMAT_STR_DECLARE(2);
    xFORMAT_STR_DECLARE(3);
    xFORMAT_STR_DECLARE(4);
    xFORMAT_STR_DECLARE(5);
    xFORMAT_STR_DECLARE(6);
    xFORMAT_STR_DECLARE(7);
    xFORMAT_STR_DECLARE(8);
    xFORMAT_STR_DECLARE(9);
    xFORMAT_STR_DECLARE(10);
    xFORMAT_STR_DECLARE(11);
    xFORMAT_STR_DECLARE(12);
    xFORMAT_STR_DECLARE(13);
    xFORMAT_STR_DECLARE(14);
    xFORMAT_STR_DECLARE(15);
    xFORMAT_STR_DECLARE(16);
    xFORMAT_STR_DECLARE(17);
    xFORMAT_STR_DECLARE(18);
    xFORMAT_STR_DECLARE(19);
    xFORMAT_STR_DECLARE(20);

private:
    static
    std::ctstring_t & _specifier() xWARN_UNUSED_RV;
        ///< open specifier

    template<typename T>
    static
    void_t _format(StreamT &os, const T &value);

    xNO_INSTANCE(FormatT)
    xNO_COPY_ASSIGN(FormatT)
};

typedef FormatT<std::tstringstream_t> FormatStd;
typedef FormatT<xl::core::OStream>    Format;

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Format.inl"
