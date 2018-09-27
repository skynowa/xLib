/**
 * \file   Operators.inl
 * \brief  Type operators
 *
 * http://blog.bitwigglers.org/using-enum-classes-as-type-safe-bitmasks/#
 * https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Type_Safe_Enum
 */


xNAMESPACE_BEGIN2(xl, core)


/*******************************************************************************
*   global
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline
T &
operator ++ (T &a_value)
{
	static_assert(std::is_enum<T>::value, "template parameter - not enum type");

	using ul_t = typename std::underlying_type<T>::type;

    return a_value = static_cast<T>( static_cast<ul_t>(a_value) + static_cast<ul_t>(1) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline
T &
operator -- (T &a_value)
{
	static_assert(std::is_enum<T>::value, "template parameter - not enum type");

	using ul_t = typename std::underlying_type<T>::type;

    return a_value = static_cast<T>( static_cast<ul_t>(a_value) - static_cast<ul_t>(1) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
operator | (T lhs, T rhs)
{
	static_assert(std::is_enum<T>::value, "template parameter - not enum type");

	using ul_t = typename std::underlying_type<T>::type;

    return static_cast<T>( static_cast<ul_t>(lhs) | static_cast<ul_t>(rhs) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
operator & (T lhs, T rhs)
{
	static_assert(std::is_enum<T>::value, "template parameter - not enum type");

	using ul_t = typename std::underlying_type<T>::type;

    return static_cast<T>( static_cast<ul_t>(lhs) & static_cast<ul_t>(rhs) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
operator ^ (T lhs, T rhs)
{
	static_assert(std::is_enum<T>::value, "template parameter - not enum type");

	using ul_t = typename std::underlying_type<T>::type;

    return static_cast<T>( static_cast<ul_t>(lhs) ^ static_cast<ul_t>(rhs) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
operator ~ (T rhs)
{
	static_assert(std::is_enum<T>::value, "template parameter - not enum type");

	using ul_t = typename std::underlying_type<T>::type;

    return static_cast<T>( ~static_cast<ul_t>(rhs) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T &
operator |= (T &lhs, T rhs)
{
	static_assert(std::is_enum<T>::value, "template parameter - not enum type");

	using ul_t = typename std::underlying_type<T>::type;

    lhs = static_cast<T>( static_cast<ul_t>(lhs) | static_cast<ul_t>(rhs) );

    return lhs;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T &
operator &= (T &lhs, T rhs)
{
	static_assert(std::is_enum<T>::value, "template parameter - not enum type");

	using ul_t = typename std::underlying_type<T>::type;

    lhs = static_cast<T>( static_cast<ul_t>(lhs) & static_cast<ul_t>(rhs) );

    return lhs;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T &
operator ^= (T &lhs, T rhs)
{
	static_assert(std::is_enum<T>::value, "template parameter - not enum type");

	using ul_t = typename std::underlying_type<T>::type;

    lhs = static_cast<T>( static_cast<ul_t>(lhs) ^ static_cast<ul_t>(rhs) );

    return lhs;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
