/**
 * \file   Algos.cpp
 * \brief  Algorithms
 */


#include <xLib/Core/Utils.h>


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, typename UnaryPredicate>
inline bool_t
findIfAll(
    T              &a_container,    ///<
    T              &a_out,          ///< [out]
    UnaryPredicate  a_pred          ///< predicate
)
{
    for (typename T::const_iterator it = std::find_if(a_container.begin(), a_container.end(), a_pred);
        it != a_container.end();
        it = std::find_if(++ it, a_container.end(), a_pred))
    {
        a_out.push_back(*it);
    }

    return !a_out.empty();
}
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
    T a_first,
    T a_last
)
{
    return (std::adjacent_find(a_first, a_last) == a_last);
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
template<typename T>
inline void_t
Algos::remove(
    std::vector<T> &a_vec,
    const T        &a_value
)
{
    a_vec.erase(std::remove(a_vec.begin(), a_vec.end(), a_value), a_vec.end());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
