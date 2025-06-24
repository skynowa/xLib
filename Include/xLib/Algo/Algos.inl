/**
 * \file   Algos.inl
 * \brief  Algorithms
 */


// #include <xLib/Core/Utils.h>


namespace xl::algos
{

/**************************************************************************************************
*   Common
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
    return std::find(a_cont.cbegin(), a_cont.cend(), a_value) != a_cont.cend();
}
//-------------------------------------------------------------------------------------------------
template<typename ContT, typename UnaryPredicateT>
/* static */
inline bool_t
Algos::findIfAll(
    const ContT     &a_cont, ///< container
    ContT           &a_out,  ///< [out]
    UnaryPredicateT  a_pred  ///< predicate
)
{
    for (typename ContT::const_iterator it = std::find_if(a_cont.cbegin(), a_cont.cend(), a_pred);
        it != a_cont.cend();
        it = std::find_if(++ it, a_cont.cend(), a_pred))
    {
        a_out.push_back(*it);
    }

    return !a_out.empty();
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
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
/* static */
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
/* static */
inline void_t
Algos::deleteAll(
    ContT &a_cont
)
{
    for (const auto &it : a_cont) {
        // Utils::ptrDeleteT(it);
    }
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
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
/* static */
inline bool_t
Algos::isUniqueAll(
    const ContT &a_cont
)
{
    return isUnique(a_cont.cbegin(), a_cont.cend());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   std::vector
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
Algos::vectorUnique(
	std::vector<T> &a_cont	///< [in, out] container
)
{
	std::sort(a_cont.begin(), a_cont.end());

	a_cont.erase(std::unique(a_cont.begin(), a_cont.end()), a_cont.end());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
Algos::vectorRemove(
    std::vector<T> &a_vec,
    const T        &a_value
)
{
    a_vec.erase(std::remove(a_vec.begin(), a_vec.end(), a_value), a_vec.cend());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   std::list
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void
Algos::listUnique(
	std::list<T> &a_cont ///< [in,out] container
)
{
	a_cont.sort();
	a_cont.unique();
}
//-------------------------------------------------------------------------------------------------



/**************************************************************************************************
*   std::map
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
/* static */
inline T1
Algos::mapFindByValue(
	const std::map<T1, T2> &a_cont,	///< container
	const T2               &a_value	///< search value
)
{
	auto pred =	[&](const typename std::map<T1, T2>::value_type &a_it) -> bool
	{
		return (a_it.second == a_value);
	};

	auto it = std::find_if(a_cont.cbegin(), a_cont.cend(), pred);
	if (it != a_cont.end()) {
		return it->first;
	}

	return {};
}
//-------------------------------------------------------------------------------------------------

} // namespace
