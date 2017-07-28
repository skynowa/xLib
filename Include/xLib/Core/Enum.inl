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
std::tstring_t
Enum<T, N>::toString(
	const T a_value
)
{
	std::tstringstream_t ss;
	ss << static_cast<longlong_t>(a_value);

	return ss.str();
}
//-------------------------------------------------------------------------------------------------
template<typename T, const std::size_t N>
std::ostream &
operator << (std::ostream &os, const T &value)
{
    os << static_cast<int>(value);

    return os;
};
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
