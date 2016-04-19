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
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const char           &a_value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const unsigned char  &a_value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
//// wchar_t
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const short          &a_value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const unsigned short &a_value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const int            &a_value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const unsigned int   &a_value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const long           &a_value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const unsigned long  &a_value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const long long      &a_value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t     &a_ss,
    const unsigned long long &a_value
)
{
    a_ss << a_value;
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
    a_ss << a_value;
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
    a_ss << a_value;
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
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const void *         &a_value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const std::string    &a_value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
//// std::wstring
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t &a_ss,
    const char *         &a_value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
//// wchar_t *
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_setManipulators(
    std::tstringstream_t     &a_ss,
    const std::vec_tstring_t &a_value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

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
