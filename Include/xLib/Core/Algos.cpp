/**
 * \file   Algos.cpp
 * \brief  Algorithms
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Algos.h"
#endif


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template <typename T>
/* static */
bool
Algos::isInBounds(
    const T &a_value,
    const T &a_low,
    const T &a_high
)
{
    return !(a_value < a_low) && !(a_high < a_value);
}
//-------------------------------------------------------------------------------------------------
template <typename T, typename R, typename Comparator>
/* static */
bool
Algos::isInBounds(
    const T    &a_value,
    const R    &a_low,
    const R    &a_high,
    Comparator  a_comp
)
{
    return !comp(a_value, a_low) && comp(a_value, a_high);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
