/**
 * \file   Enum.cpp
 * \brief  Enumeration
 */


#include <xLib/Core/String.h>

xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
inline std::tstring_t
Enum::str(
	const T &a_value
)
{
	return std::to_tstring( static_cast<::ssize_t>(a_value) );
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
inline ::ssize_t
Enum::value(
	const T &a_value
)
{
	return static_cast<::ssize_t>(a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
inline T
Enum::cast(
	std::ctstring_t &a_value
)
{
#if 0
	return static_cast<T>( std::strtoll(a_value.c_str(), nullptr, 10) );
#else
	return String::castTo<T>(a_value);
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
inline std::tstring_t
Enum::name(
	const T &a_value
)
{
	// TODO: [skynowa] Enum::name()

	std::tstring_t sRv;

	switch (a_value) {
	case T::First:
		sRv = xT("First");
		break;
	case T::Second:
		sRv = xT("Second");
		break;
	case T::Third:
		sRv = xT("Third");
		break;
	default:
		break;
	}

	return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
inline T
Enum::inc(
    const T &a_value
)
{
    return static_cast<T>( static_cast<::ssize_t>(a_value) + 1 );
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
inline T
Enum::dec(
    const T &a_value
)
{
    return static_cast<T>( static_cast<::ssize_t>(a_value) - 1 );
}
//-------------------------------------------------------------------------------------------------
// template<typename T>
// inline std::tostream_t &
// operator << (
// 	std::tostream_t                    &a_os,
// 	const typename Enum<T>::value_type &a_value
// )
// {
//     a_os << static_cast<::ssize_t>(a_value);

//     return a_os;
// }
//-------------------------------------------------------------------------------------------------
// template<typename T>
// inline OStream &
// operator << (
// 	OStream &a_os,
// 	const T  a_value
// )
// {
//     a_os << static_cast<::ssize_t>(a_value);

//     return a_os;
// }
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
