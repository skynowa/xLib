/**
 * \file   Format.cpp
 * \brief  format string
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Format.h"
#endif

#include <xLib/Core/Type.h>


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const bool           &a_value
)
{
    a_ss << std::boolalpha;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const float          &a_value
)
{
    a_ss << std::setprecision( _floatPrecisionMax<float>() );
    a_ss << std::fixed;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const double         &a_value
)
{
    a_ss << std::setprecision( _floatPrecisionMax<double>() );
    a_ss << std::fixed;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const long double    &a_value
)
{
    a_ss << std::setprecision( _floatPrecisionMax<long double>() );
    a_ss << std::fixed;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
xINLINE int
Format::_floatPrecisionMax()
{
#if xOPTION_CPP11
    return std::numeric_limits<T>::max_digits10;
#else
    return std::numeric_limits<T>::digits10 + 1;
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
