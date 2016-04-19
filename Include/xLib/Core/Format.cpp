/**
 * \file   Format.cpp
 * \brief  format string
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Format.h"
#endif

#include <xLib/Core/Type.h>


xNAMESPACE_BEGIN2(xlib, core)

//-------------------------------------------------------------------------------------------------
/* static */
void
Format::_setOptions(
    std::tstringstream_t &a_ss,
    bool                  a_value
)
{
    a_ss << std::boolalpha;
}
//-------------------------------------------------------------------------------------------------
/* static */
void
Format::_setOptions(
    std::tstringstream_t &a_ss,
    float                 a_value
)
{
    a_ss << std::setprecision(5);
    a_ss << std::fixed;
}
//-------------------------------------------------------------------------------------------------
/* static */
void
Format::_setOptions(
    std::tstringstream_t &a_ss,
    double                a_value
)
{
    a_ss << std::setprecision(10);
    a_ss << std::fixed;
}
//-------------------------------------------------------------------------------------------------
/* static */
void
Format::_setOptions(
    std::tstringstream_t &a_ss,
    long double           a_value
)
{
    a_ss << std::setprecision(20);
    a_ss << std::fixed;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
