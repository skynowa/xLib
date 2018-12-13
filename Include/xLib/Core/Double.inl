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
inline bool
Double<T>::isEqual(
	const double a_value	///< value 2
)
{
	return isAlmostEqual(_value, a_value);
}
//-------------------------------------------------------------------------------------------------
template <typename T>
inline bool
Double<T>::isAlmostEqual(
	const T   &a_value,
	const int  ulp /* = 2 */
)
{
	return
		std::abs(_value - a_value) <=
		std::numeric_limits<T>::epsilon() * std::max(std::abs(_value), std::abs(a_value)) * ulp;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool
Double<T>::isNull()
{
	return isAlmostEqual(_value, 0.0);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline T
Double<T>::safeDivision(
	const T &a_value,
	const T &a_value_default /* = {} */
)
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
