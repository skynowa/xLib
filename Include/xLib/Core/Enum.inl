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
template<typename T, const std::size_t N>
Enum<T, N>::Enum()
{
}
//-------------------------------------------------------------------------------------------------
template<typename T, const std::size_t N>
Enum<T, N>::Enum(
	const Array<T, N> &a_enumeration
) :
    Array<T, N>(a_enumeration)
{
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T, const std::size_t N>
std::tstring_t
Enum<T, N>::toString(
	const T a_value
)
{
	std::tstringstream_t ss;
	ss << static_cast<ssize_t>(a_value);

	return ss.str();
}
//-------------------------------------------------------------------------------------------------
template<typename T, const std::size_t N>
bool_t
Enum<T, N>::isValid(
	const ssize_t a_value
) const
{
	return std::find(this->begin(), this->end(), static_cast<T>(a_value)) != this->end();
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T, const std::size_t N>
T
Enum<T, N>::inc(
    const T &a_value
)
{
    return static_cast<T>( static_cast<ssize_t>( a_value ) + 1 );
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T, const std::size_t N>
T
Enum<T, N>::dec(
    const T &a_value
)
{
    return static_cast<T>( static_cast<ssize_t>( a_value ) - 1 );
}
//-------------------------------------------------------------------------------------------------
template<typename T, const std::size_t N>
std::ostream &
operator << (
	std::ostream &os, const T value
)
{
    os << static_cast<int>(value);

    return os;
};
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
