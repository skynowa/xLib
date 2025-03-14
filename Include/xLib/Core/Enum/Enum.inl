/**
 * \file   Enum.inl
 * \brief  Enumeration
 */


#include <xLib/Core/String.h>

namespace xl::core
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline
Enum<T>::Enum(
	const T a_value
) :
	_value{a_value}
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline
Enum<T>::Enum(
	std::tstring_t a_value
) :
	_value{ String::castTo<T>(a_value) }
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline T
Enum<T>::get() const /* final */
{
	return _value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline std::tstring_t
Enum<T>::str() const /* final */
{
	return std::to_tstring( static_cast<::ssize_t>(_value) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline std::ssize_t
Enum<T>::value() const
{
	return static_cast<::ssize_t>(_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline std::tstring_t
Enum<T>::name() const
{
	// TODO: [skynowa] Enum::name()

	std::tstring_t sRv;

	switch (_value) {
	case T::First:
		sRv = xT("First");
		break;
	case T::Second:
		sRv = xT("Second");
		break;
	case T::Third:
		sRv = xT("Third");
		break;
	default:
		sRv = xT("Unknown");
		break;
	}

	return sRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline Enum<T>
Enum<T>::inc() const
{
    return Enum(static_cast<T>( static_cast<::ssize_t>(_value) + 1 ));
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline Enum<T>
Enum<T>::dec() const
{
    return Enum(static_cast<T>( static_cast<::ssize_t>(_value) - 1 ));
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   operator <<
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename EnumT>
inline std::tostream_t &
operator << (
	std::tostream_t   &out_os,
	const Enum<EnumT> &a_value
)
{
	out_os << a_value.name() << ": " << a_value.value();

	return out_os;
}
//-------------------------------------------------------------------------------------------------
// template<typename T>
// inline OStream &
// operator << (
// 	OStream &a_os,
// 	const T  a_value
// )
// {
//     a_os << static_cast<::ssize_t>(a_value);

//     return a_os;
// }
//-------------------------------------------------------------------------------------------------

} // namespace
