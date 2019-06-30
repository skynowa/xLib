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
template<typename ContT, typename ValueT>
/* static */
inline bool_t
Algos::isContains(
    const ContT  &a_cont,   ///< container
    const ValueT &a_value   ///< search value
)
{
    return std::find(a_cont.begin(), a_cont.end(), a_value) != a_cont.end();
}
//-------------------------------------------------------------------------------------------------
template<typename ContT, typename UnaryPredicateT>
inline bool_t
Algos::findIfAll(
    const ContT     &a_cont, ///<
    ContT           &a_out,  ///< [out]
    UnaryPredicateT  a_pred  ///< predicate
)
{
    for (typename ContT::const_iterator it = std::find_if(a_cont.begin(), a_cont.end(), a_pred);
        it != a_cont.end();
        it = std::find_if(++ it, a_cont.end(), a_pred))
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
template<typename ContT>
inline void_t
Algos::deleteAll(
    ContT &a_cont
)
{
    typename ContT::const_iterator it    = a_cont.begin();
    typename ContT::const_iterator itEnd = a_cont.end();

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
template<typename ContT>
inline bool_t
Algos::isUniqueAll(
    const ContT &a_cont
)
{
    return isUnique(a_cont.begin(), a_cont.end());
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
