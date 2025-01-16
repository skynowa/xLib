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
inline
Bitset<T>::Bitset(
    const Bitset &a_values
) :
    _flags(a_values._flags)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline
Bitset<T>::Bitset(
    const T a_values
) :
    _flags(a_values)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline Bitset<T> &
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
inline T &
Bitset<T>::operator [] (
    std::csize_t a_index
)
{
	// IMPL: operator []

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline T &
Bitset<T>::get() const
{
    return _flags;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
Bitset<T>::set(
    const T a_values
)
{
    _flags = a_values;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
Bitset<T>::clear()
{
    _flags = 0;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Bitset<T>::test(
	std::csize_t a_index
) const
{
    return _flags & (static_cast<T>(1) << a_index);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
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
inline void_t
Bitset<T>::setBit(
    const T a_value
)
{
    _flags |= a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
Bitset<T>::unsetBit(
    const T a_value
)
{
    _flags &= ~a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
Bitset<T>::flipBit(
    const T a_value
)
{
    _flags ^= a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline constexpr std::size_t
Bitset<T>::size() const
{
	return (sizeof(T) * CHAR_BIT);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
template<typename StreamT>
inline void_t
Bitset<T>::print(
	StreamT &a_os
) const
{
	a_os << xT("xlib::Bitset (size = ") << size() << xT("):") << std::endl;

	const auto size_ = static_cast<std::ssize_t>(size());

	for (std::ssize_t i = size_; i >= 0; -- i) {
		if ( test( static_cast<std::size_t>(i) ) )
			a_os << xT("1");
		else
			a_os << xT("0");
	}
}
//-------------------------------------------------------------------------------------------------

} // namespace
