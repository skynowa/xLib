/**
 * \file  StdStreamAlone.h
 * \brief std stream printers
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <tuple>
#include <algorithm>
#include <type_traits>
//-------------------------------------------------------------------------------------------------
///@name Trace variables (variable with value)
///@{
#define TRACE_VAR(v1) \
	#v1 ": " << (v1)
#define TRACE_VAR2(v1, v2) \
	TRACE_VAR(v1) << ", " << TRACE_VAR(v2)
#define TRACE_VAR3(v1, v2, v3) \
	TRACE_VAR2(v1, v2) << ", " << TRACE_VAR(v3)
#define TRACE_VAR4(v1, v2, v3, v4) \
	TRACE_VAR3(v1, v2, v3) << ", " << TRACE_VAR(v4)
#define TRACE_VAR5(v1, v2, v3, v4, v5) \
	TRACE_VAR4(v1, v2, v3, v4) << ", " << TRACE_VAR(v5)
#define TRACE_VAR6(v1, v2, v3, v4, v5, v6) \
	TRACE_VAR5(v1, v2, v3, v4, v5) << ", " << TRACE_VAR(v6)
#define TRACE_VAR7(v1, v2, v3, v4, v5, v6, v7) \
	TRACE_VAR6(v1, v2, v3, v4, v5, v6) << ", " << TRACE_VAR(v7)
#define TRACE_VAR8(v1, v2, v3, v4, v5, v6, v7, v8) \
	TRACE_VAR7(v1, v2, v3, v4, v5, v6, v7) << ", " << TRACE_VAR(v8)
#define TRACE_VAR9(v1, v2, v3, v4, v5, v6, v7, v8, v9) \
	TRACE_VAR8(v1, v2, v3, v4, v5, v6, v7, v8) << ", " << TRACE_VAR(v9)
#define TRACE_VAR10(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) \
	TRACE_VAR9(v1, v2, v3, v4, v5, v6, v7, v8, v9) << ", " << TRACE_VAR(v10)
#define TRACE_VAR11(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) \
	TRACE_VAR10(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) << ", " << TRACE_VAR(v11)

#define UNKNOWN_VAR(v) \
	"Unknown " << TRACE_VAR(v)
#define TRACE_PTR(p) \
     #p ": " << "{" << p << ", " << (p ? *p : 0) << "}"
///@}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   overload operators <<
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/**
 * Overload operators << for std::pair
 */
template<typename T1, typename T2>
inline std::ostream &
operator << (
	std::ostream            &a_os,
	const std::pair<T1, T2> &a_value
)
{
	a_os << "std::pair: {" << a_value.first  << ", " << a_value.second << "}";

	return a_os;
}
//-------------------------------------------------------------------------------------------------
/**
 * Overload operators << for std::vector
 */
template<typename T>
inline std::ostream &
operator << (
	std::ostream         &a_os,
	const std::vector<T> &a_value
)
{
	a_os << "std::vector (" << a_value.size() << " elements)";

	if ( a_value.empty() )  {
		return a_os;
	}

	a_os << ":" << std::endl;

	for (auto it = a_value.begin(); it != a_value.end(); ++ it) {
		a_os << "    [" << std::distance(a_value.begin(), it) << "]: " << *it;

		if (it + 1 != a_value.end()) {
			 a_os << std::endl;
		}
	}

	return a_os;
}
//-------------------------------------------------------------------------------------------------
/**
 * Overload operators << for std::list
 */
template<typename T>
inline std::ostream &
operator << (
	std::ostream       &a_os,
	const std::list<T> &a_value
)
{
	a_os << "std::list (" << a_value.size() << " elements)";

	if ( a_value.empty() ) {
		return a_os;
	}

	a_os << ":" << std::endl;

	for (auto it = a_value.begin(); it != a_value.end(); ++ it) {
		a_os << "    [" << std::distance(a_value.begin(), it) << "]: " << *it;

		if (++ it != a_value.end()) {
			 a_os << std::endl;
		}

		-- it;
	}

	return a_os;
}
//-------------------------------------------------------------------------------------------------
/**
 * Overload operators << for std::map
 */
template<typename T1, typename T2>
inline std::ostream &
operator << (
	std::ostream           &a_os,
	const std::map<T1, T2> &a_value
)
{
	a_os << "std::map (" << a_value.size() << " elements)";

	if ( a_value.empty() ) {
		return a_os;
	}

	a_os << ":" << std::endl;

	for (auto it = a_value.begin(); it != a_value.end(); ++ it) {
		a_os << "    {" << it->first  << ", " << it->second << "}";

		if (++ it != a_value.end()) {
			 a_os << std::endl;
		}

		-- it;
	}

	return a_os;
}
//-------------------------------------------------------------------------------------------------
/**
 * Overload operators << for std::miltimap
 */
template<typename T1, typename T2>
inline std::ostream &
operator << (
	std::ostream                &a_os,
	const std::multimap<T1, T2> &a_value
)
{
	a_os << std::endl;
	a_os << "std::multimap (" << a_value.size() << " elements):" << std::endl;

	typename std::multimap<T1, T2>::const_iterator it;
	for (it = a_value.begin(); it != a_value.end(); ++ it) {
		a_os << "    {" << it->first  << ", " << it->second << "}";

		if (++ it != a_value.end()) {
			 a_os << std::endl;
		}

		-- it;
	}

	return a_os;
}
//-------------------------------------------------------------------------------------------------
/**
 * Overload operators << for ::stringMap
 */
template<typename T1, typename T2>
inline std::ostream &
operator << (
	std::ostream                    &a_os,
	const std::map<T1, T2, ::CmpCI> &a_value
)
{
	a_os << "std::map (" << a_value.size() << " elements)";

	if ( a_value.empty() ) {
		return a_os;
	}

	a_os << ":" << std::endl;

	for (auto it = a_value.begin(); it != a_value.end(); ++ it) {
		a_os << "    {" << it->first  << ", " << it->second << "}";

		if (++ it != a_value.end()) {
			 a_os << std::endl;
		}

		-- it;
	}

	return a_os;
}
//-------------------------------------------------------------------------------------------------
/**
 * Overload operators << for std::tuple
 */
template<typename Tuple, std::size_t N>
struct TuplePrinter
{
	static void
	print(std::ostream &a_os, const Tuple &a_t)
	{
		TuplePrinter<Tuple, N - 1>::print(a_os, a_t);
		a_os << ", " << std::get<N - 1>(a_t);
	}
};

template<typename Tuple>
struct TuplePrinter<Tuple, 1>
{
	static void
	print(std::ostream &a_os, const Tuple &a_t)
	{
		a_os << std::get<0>(a_t);
	}
};

template<typename... Args>
inline std::ostream &
operator << (
	std::ostream              &a_os,
	const std::tuple<Args...> &a_value
)
{
#if 0
	a_os << "std::tuple (" << std::tuple_size<decltype(a_value)>::value << " elements)";

	if ( a_value.empty() ) {
		return a_os;
	}
#else
	a_os << "std::tuple";
#endif

	a_os << ":" << std::endl;

	a_os << "{";
	TuplePrinter<decltype(a_value), sizeof...(Args)>::print(a_os, a_value);
	a_os << "}";

	return a_os;
}
//-------------------------------------------------------------------------------------------------
