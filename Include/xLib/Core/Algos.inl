/**
 * \file   Algos.cpp
 * \brief  Algorithms
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Algos.h"
#endif

#include <xLib/Core/Utils.h>


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Algos::isInBounds(
    const T &a_value,
    const T &a_low,
    const T &a_high
)
{
    return !(a_value < a_low) && !(a_high < a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T, typename R, typename ComparatorT>
inline bool_t
Algos::isInBounds(
    const T     &a_value,
    const R     &a_low,
    const R     &a_high,
    ComparatorT  a_comp
)
{
    return !a_comp(a_value, a_low) && a_comp(a_value, a_high);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
Algos::deleteAll(
    T &a_container
)
{
    typename T::const_iterator it    = a_container.begin();
    typename T::const_iterator itEnd = a_container.end();

    for ( ; it != itEnd; ++ it) {
        Utils::ptrDeleteT(*it);
    }
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Algos::isUnique(
    T a_it_first,
    T a_it_last
)
{
    return (std::adjacent_find(a_it_first, a_it_last) == a_it_last);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Algos::isUniqueAll(
    const T &a_container
)
{
    return isUnique(a_container.begin(), a_container.end());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
