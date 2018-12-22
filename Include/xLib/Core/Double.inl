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
Double<T>::Double()
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* virtual */
inline
Double<T>::~Double()
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline
Double<T>::Double(
	const Double &a_value
) :
    _value(a_value._value)
{
}
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
inline
Double<T>::Double(
	Double &&a_value
) :
    _value( std::move(a_value._value) )
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline Double<T> &
Double<T>::operator = (
    const Double &a_value
)
{
    _value = a_value._value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline Double<T> &
Double<T>::operator = (
    Double &&a_value
)
{
    _value = std::move(a_value._value);

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
	const Double a_value
) const
{
	return (_value < a_value._value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::operator > (
	const Double a_value
) const
{
	return (a_value < *this);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::operator <= (
	const Double a_value
) const
{
	return !(*this > a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::operator >= (
	const Double a_value
) const
{
	return !(*this < a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::operator == (
	const Double a_value
) const
{
	return isEqual(_value, a_value._value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::operator != (
	const Double a_value
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
const T &
Double<T>::get() const
{
	return _value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::isNull() const
{
	return (_value == 0.0);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline bool_t
Double<T>::isEqual(
	const T a_value1,
	const T a_value2
)
{
	constexpr T epsilon = std::numeric_limits<T>::epsilon();

	return std::abs(a_value1 - a_value2) <= (epsilon * std::abs(a_value1));
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline T
Double<T>::safeDiv(
	const T a_value,
	const T a_value_default /* = {} */
) const
{
	if ( isEqual(a_value, 0.0) ) {
		return a_value_default;
	}

	return _value / a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
Double<T>::clear()
{
    _value = {};
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
