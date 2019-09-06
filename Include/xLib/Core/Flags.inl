/**
 * \file   Flags.inl
 * \brief  bit mask flags
 */


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
Flags<T>::Flags(
    const Flags &a_values
) :
    _flags(a_values._flags)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
Flags<T>::Flags(
    const T &a_values
) :
    _flags(a_values)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
Flags<T> &
Flags<T>::operator = (
    const Flags &a_values
)
{
    xCHECK_RET(this == &a_values, *this);

    _flags = a_values._flags;

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T &
Flags<T>::operator [] (
    const std::size_t a_index
)
{
	/// TODO:

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T &
Flags<T>::get() const
{
    return _flags;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
Flags<T>::set(
    const T &a_values
)
{
    _flags = a_values;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
Flags<T>::clear()
{
    _flags = 0;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
Flags<T>::test(
	const std::size_t a_index
) const
{
    return _flags & (static_cast<T>(1) << a_index);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
Flags<T>::isSetFlag(
    const T &a_value
) const
{
    return (_flags & a_value) == a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
Flags<T>::isSetAnyFlag(
    const T &a_value
) const
{
    return (_flags & a_value) != 0;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
Flags<T>::setFlag(
    const T &a_value
)
{
    _flags |= a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
Flags<T>::unsetFlag(
    const T &a_value
)
{
    _flags &= ~a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
Flags<T>::flipFlag(
    const T &a_value
)
{
    _flags ^= a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
constexpr
std::size_t
Flags<T>::size() const
{
	return (sizeof(T) * CHAR_BIT);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
template<typename StreamT>
void_t
Flags<T>::print(
	StreamT &a_os
) const
{
	 a_os << xT("xlib::Flags (size = ") << size() << "):" << std::endl;

	for (::ssize_t i = size(); i >= 0; -- i) {
		if ( test(i) )
			a_os << xT("1");
		else
			a_os << xT("0");
	}
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
