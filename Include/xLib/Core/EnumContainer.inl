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
EnumContainer<T, N>::EnumContainer()
{
}
//-------------------------------------------------------------------------------------------------
template<typename T, const std::size_t N>
EnumContainer<T, N>::EnumContainer(
	const Array<T, N> &a_enumeration
) :
    Array<T, N>(a_enumeration)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T, const std::size_t N>
bool_t
EnumContainer<T, N>::isValid(
	const ssize_t a_value
) const
{
	return std::find(this->begin(), this->end(), static_cast<T>(a_value)) != this->end();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
