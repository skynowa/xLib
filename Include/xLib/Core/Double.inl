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
Double<T>::Double(
	const T &a_value
) :
    _value(a_value)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
Double<T> &
Double<T>::operator = (
    const T &a_value
)
{
    xCHECK_RET(this == &a_value, *this);

    _value = a_value._value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::isEqual(
	const T a_value	///< value
) const
{
	return isAlmostEqual(_value, a_value);
}
//-------------------------------------------------------------------------------------------------
template <typename T>
inline bool_t
Double<T>::isAlmostEqual(
	const T     &a_value,		///<
	const int_t  a_ulp /* = 2 *////< ULP (Units in the Last Place):
								///< difference between the integer representations tells us
								///< how many Units in the Last Place the numbers differ by
) const
{
	return
		std::abs(_value - a_value) <=
		std::numeric_limits<T>::epsilon() * std::max(std::abs(_value), std::abs(a_value)) * a_ulp;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::isNull() const
{
	return isAlmostEqual(_value);
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
