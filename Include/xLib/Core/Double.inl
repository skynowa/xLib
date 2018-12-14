/**
 * \file   Double.cpp
 * \brief  Double's operations
 */


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline
Double<T>::Double(
	const T &a_value
) :
    _value(a_value)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline Double<T> &
Double<T>::operator = (
    const T &a_value
)
{
    xCHECK_RET(_value == a_value, *this);

    _value = a_value._value;

    return *this;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public / operators
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::operator < (
	const T &a_value
) const
{
	return (_value < a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::operator > (
	const T &a_value
) const
{
	return (a_value < *this);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::operator <= (
	const T &a_value
) const
{
	return !(*this > a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::operator >= (
	const T &a_value
) const
{
	return !(*this < a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::operator == (
	const T &a_value
) const
{
	return (_value == a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::operator != (
	const T &a_value
) const
{
	return !(*this == a_value);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public / methods
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::isEqual(
	const T &a_value	///< value
) const
{
	constexpr T epsilon = std::numeric_limits<T>::epsilon();

	return std::abs(_value - a_value) <= (epsilon * std::abs(_value));
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::isNull() const
{
	return isEqual(_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline T
Double<T>::safeDiv(
	const T &a_value,
	const T &a_value_default /* = {} */
) const
{
	if ( isNull() ) {
		return a_value_default;
	}

	return _value / a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
Double<T>::clear()
{
    _value = {};
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
