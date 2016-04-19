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
xINLINE void
Format::setManipulators(
    std::tstringstream_t &a_ss,
    bool                  a_value
)
{
    a_ss << std::boolalpha;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::setManipulators(
    std::tstringstream_t &a_ss,
    float                 a_value
)
{
#if xOPTION_CPP11
    cint_t precision_max = std::numeric_limits<float>::max_digits10;
#else
    cint_t precision_max = std::numeric_limits<float>::digits10 + 1;
#endif

    a_ss << std::setprecision(precision_max);
    a_ss << std::fixed;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::setManipulators(
    std::tstringstream_t &a_ss,
    double                a_value
)
{
#if xOPTION_CPP11
    cint_t precision_max = std::numeric_limits<double>::max_digits10;
#else
    cint_t precision_max = std::numeric_limits<double>::digits10 + 1;
#endif

    a_ss << std::setprecision(precision_max);
    a_ss << std::fixed;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::setManipulators(
    std::tstringstream_t &a_ss,
    long double           a_value
)
{
#if xOPTION_CPP11
    cint_t precision_max = std::numeric_limits<long double>::max_digits10;
#else
    cint_t precision_max = std::numeric_limits<long double>::digits10 + 1;
#endif

    a_ss << std::setprecision(precision_max);
    a_ss << std::fixed;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
