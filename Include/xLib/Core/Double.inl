/**
 * \file   Double.inl
 * \brief  Double's operations
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
Double<T>::Double()
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
	const T a_value
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
int_t
Double<T>::compare(
	const T &a_value
) const /* final */
{
	if (_value < a_value) {
		return - 1;
	}

	if (_value > a_value) {
		return 1;
	}

	return 0;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
const T &
Double<T>::get() const /* final */
{
	return _value;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public / operators
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline Double<T> &
Double<T>::operator = (
    const Double &a_value
)
{
	if (this == &a_value) {
		return *this;
	}

    _value = a_value._value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline Double<T> &
Double<T>::operator = (
    const T a_value
)
{
    _value = a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline Double<T> &
Double<T>::operator = (
    Double &&a_value
)
{
	if (this == &a_value) {
		return *this;
	}

    _value = std::move(a_value._value);

    return *this;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public / methods
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::isNull() const
{
	return isEqual(_value, 0.0);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline int_t
Double<T>::classify() const
{
	return std::fpclassify(_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::isFinite() const
{
	return static_cast<bool_t>( std::isfinite(_value) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::isInf() const
{
	return static_cast<bool_t>( std::isinf(_value) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::isNan() const
{
	return static_cast<bool_t>( std::isnan(_value) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::isNormal() const
{
	return static_cast<bool_t>( std::isnormal(_value) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Double<T>::isUnordered(
	const T a_value
) const
{
	return static_cast<bool_t>( std::isunordered(_value, a_value) );
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


/**************************************************************************************************
*   public / methods
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline bool_t
Double<T>::isEqual(
	const T a_value1,
	const T a_value2,
	cint_t  a_ulp /* = 2 */
)
{
	const auto customEpsilon =
		std::numeric_limits<T>::epsilon() *
		std::max(std::abs(a_value1), std::abs(a_value2)) *
		a_ulp;

	return std::abs(a_value1 - a_value2) <= customEpsilon;
}
//-------------------------------------------------------------------------------------------------

} // namespace
