/**
 * \file   Enum.cpp
 * \brief  Enumeration
 */


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
std::tstring_t
Enum<T>::toString(
	const T a_value
)
{
	std::tstringstream_t ss;
	ss << static_cast<ssize_t>(a_value);

	return ss.str();
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
T
Enum<T>::fromString(
	const std::tstring_t &a_value
)
{
	return static_cast<T>( std::strtoll(a_value.c_str(), nullptr, 10) );
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
std::tstring_t
Enum<T>::asString(
	const T value
)
{
	std::tstring_t sRv;

	// TODO: Enum::asString()

	return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
T
Enum<T>::inc(
    const T &a_value
)
{
    return static_cast<T>( static_cast<ssize_t>( a_value ) + 1 );
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
T
Enum<T>::dec(
    const T &a_value
)
{
    return static_cast<T>( static_cast<ssize_t>( a_value ) - 1 );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
std::ostream &
operator << (
	std::ostream &a_os, const T a_value
)
{
    a_os << static_cast<ssize_t>(a_value);

    return a_os;
};
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
