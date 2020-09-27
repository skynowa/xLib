/**
 * \file   Bitset.inl
 * \brief  bit mask flags
 */


namespace xl::core
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
Bitset<T>::Bitset(
    const Bitset &a_values
) :
    _flags(a_values._flags)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
Bitset<T>::Bitset(
    const T a_values
) :
    _flags(a_values)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
Bitset<T> &
Bitset<T>::operator = (
    const Bitset &a_values
)
{
    xCHECK_RET(this == &a_values, *this);

    _flags = a_values._flags;

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T &
Bitset<T>::operator [] (
    const std::size_t a_index
)
{
	// IMPL: operator []

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T &
Bitset<T>::get() const
{
    return _flags;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
Bitset<T>::set(
    const T a_values
)
{
    _flags = a_values;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
Bitset<T>::clear()
{
    _flags = 0;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
Bitset<T>::test(
	const std::size_t a_index
) const
{
    return _flags & (static_cast<T>(1) << a_index);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
Bitset<T>::isSetBit(
    const T a_value
) const
{
    return (_flags & a_value) == a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
Bitset<T>::isSetAnyBit(
    const T a_value
) const
{
    return (_flags & a_value) != 0;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
Bitset<T>::setBit(
    const T a_value
)
{
    _flags |= a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
Bitset<T>::unsetBit(
    const T a_value
)
{
    _flags &= ~a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
Bitset<T>::flipBit(
    const T a_value
)
{
    _flags ^= a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
constexpr
std::size_t
Bitset<T>::size() const
{
	return (sizeof(T) * CHAR_BIT);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
template<typename StreamT>
void_t
Bitset<T>::print(
	StreamT &a_os
) const
{
	 a_os << xT("xlib::Bitset (size = ") << size() << "):" << std::endl;

	for (::ssize_t i = size(); i >= 0; -- i) {
		if ( test(i) )
			a_os << xT("1");
		else
			a_os << xT("0");
	}
}
//-------------------------------------------------------------------------------------------------

} // namespace
