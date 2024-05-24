/**
 * \file  Float.inl
 * \brief Float's operations
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
Float<T>::Float()
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline
Float<T>::Float(
	const Float &a_value
) :
    _value(a_value._value)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline
Float<T>::Float(
	const T a_value
) :
    _value(a_value)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline
Float<T>::Float(
	Float &&a_value
) :
    _value( std::move(a_value._value) )
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
const T &
Float<T>::get() const /* final */
{
	return _value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
std::tstring_t
Float<T>::str() const /* final */
{
	return std::to_string(_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
int_t
Float<T>::compare(
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


/**************************************************************************************************
*   public / operators
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline Float<T> &
Float<T>::operator = (
    const Float &a_value
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
inline Float<T> &
Float<T>::operator = (
    const T a_value
)
{
    _value = a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline Float<T> &
Float<T>::operator = (
    Float &&a_value
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
Float<T>::isNull() const
{
	return isEqual(_value, 0.0);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline int_t
Float<T>::classify() const
{
	return std::fpclassify(_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Float<T>::isFinite() const
{
	return static_cast<bool_t>( std::isfinite(_value) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Float<T>::isInf() const
{
	return static_cast<bool_t>( std::isinf(_value) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Float<T>::isNan() const
{
	return static_cast<bool_t>( std::isnan(_value) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Float<T>::isNormal() const
{
	return static_cast<bool_t>( std::isnormal(_value) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Float<T>::isUnordered(
	const T a_value
) const
{
	return static_cast<bool_t>( std::isunordered(_value, a_value) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline T
Float<T>::safeDiv(
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
Float<T>::isEqual(
	const T a_value1,
	const T a_value2,
	cint_t  a_ulp /* = 2 */
)
{
	const auto customEpsilon =
		std::numeric_limits<T>::epsilon() *
		std::max(std::fabs(a_value1), std::fabs(a_value2)) *
		a_ulp;

	return std::fabs(a_value1 - a_value2) <= customEpsilon;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   Free functions - User-defined literals
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline FFloat
operator ""xf (
	clongdouble_t a_value
)
{
	return FFloat( static_cast<float>(a_value) );
}
//-------------------------------------------------------------------------------------------------
inline FFloat
operator ""xf (
	culonglong_t a_value
)
{
	return FFloat( static_cast<float>(a_value) );
}
//-------------------------------------------------------------------------------------------------
inline FDouble
operator ""xd (
	clongdouble_t a_value
)
{
	return FDouble( static_cast<double>(a_value) );
}
//-------------------------------------------------------------------------------------------------
inline FDouble
operator ""xd (
	culonglong_t a_value
)
{
	return FDouble( static_cast<double>(a_value) );
}
//-------------------------------------------------------------------------------------------------
inline FLongDouble
operator ""xld (
	clongdouble_t a_value
)
{
	return FLongDouble(a_value);
}
//-------------------------------------------------------------------------------------------------
inline FLongDouble
operator ""xld (
	culonglong_t a_value
)
{
	return FLongDouble(a_value);
}
//-------------------------------------------------------------------------------------------------

} // namespace
