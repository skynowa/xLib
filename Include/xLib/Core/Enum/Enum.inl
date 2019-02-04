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
Enum<T>::toString(
	const T a_value
)
{
	return std::to_tstring( static_cast<::ssize_t>(a_value) );
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
inline T
Enum<T>::fromString(
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
Enum<T>::asString(
	const T value
)
{
	std::tstring_t sRv;

	// TODO: [skynowa] Enum::asString()

	return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
inline T
Enum<T>::inc(
    const T &a_value
)
{
    return static_cast<T>( static_cast<::ssize_t>(a_value) + 1 );
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
inline T
Enum<T>::dec(
    const T &a_value
)
{
    return static_cast<T>( static_cast<::ssize_t>(a_value) - 1 );
}
//-------------------------------------------------------------------------------------------------
// template<typename T>
// inline std::tostream_t &
// operator << (
// 	std::tostream_t &a_os,
// 	const T          a_value
// )
// {
//     a_os << static_cast<::ssize_t>(a_value);

//     return a_os;
// }
//-------------------------------------------------------------------------------------------------
template<typename T>
inline OStream &
operator << (
	OStream &a_os,
	const T  a_value
)
{
    a_os << static_cast<::ssize_t>(a_value);

    return a_os;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
