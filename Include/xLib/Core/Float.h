/**
 * \file  Float.h
 * \brief Float's operations
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Interface/ICompare.h>
#include <xLib/Interface/IGet.h>
#include <xLib/Interface/IStr.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

template<typename T>
class Float final :
	public IGetConstRef<T>,
	public IStr,
	public ICompare<T>
    ///< Float's operations
{
	static_assert(std::is_floating_point_v<T>, "T must be a floating-point type");

public:
///\name ctors, dtor
///\{
			 Float();
			 Float(const Float &value);
	explicit Float(const T value);
			 Float(Float &&value);
	virtual ~Float() = default;
///\}

///\name Overrides
///\{
	const T        &get() const final;
	std::tstring_t  str() const final;
	int_t           compare(const T &value) const final;
///\}

///\name operators
///\{
	Float & operator = (const Float &value);
	Float & operator = (const T value);
	Float & operator = (Float &&value);

#define xFLOAT_OPERATOR(op) \
	Float operator op (const Float &a_value) const \
	{ \
		return Float(_value op a_value._value); \
	}
#define xFLOAT_T_OPERATOR(op) \
	Float operator op (const T &a_value) const \
	{ \
		return Float(_value op a_value); \
	}

	xFLOAT_OPERATOR(+);
	xFLOAT_OPERATOR(-);
	xFLOAT_OPERATOR(*);
	xFLOAT_OPERATOR(/);

	xFLOAT_T_OPERATOR(+);
	xFLOAT_T_OPERATOR(-);
	xFLOAT_T_OPERATOR(*);
	xFLOAT_T_OPERATOR(/);

#undef xFLOAT_OPERATOR
#undef xFLOAT_T_OPERATOR
///\}

///\name Determines
///\{
	bool_t isNull() const;
		///< checks if the given number is 0.0
	int_t  classify() const;
		///< categorizes the given floating-point value
		///< \return FP_NORMAL, FP_SUBNORMAL, FP_ZERO, FP_INFINITE, FP_NAN
	bool_t isFinite() const;
		///< checks if the given number has finite value
	bool_t isInf() const;
		///< checks if the given number is infinite
	bool_t isNan() const;
		///< checks if the given number is NaN
	bool_t isNormal() const;
		///< checks if the given number is normal
	bool_t isUnordered(const T value) const;
		///< checks if two floating-point values are unordered
///\}

	T safeDiv(const T value, const T value_default = {}) const;
		///< safe division, if devision by 0.0 return 0.0

xPUBLIC_STATIC:
	static bool_t isEqual(const T value1, const T value2, cint_t ulp = 2);

private:
    T _value {};
};

using FFloat      = Float<float>;
using FDouble     = Float<double>;
using FLongDouble = Float<long double>;
//-------------------------------------------------------------------------------------------------
///\name User-defined literals
///\{
FFloat      operator ""xf (clongdouble_t value);
FFloat      operator ""xf (culonglong_t value);

FDouble     operator ""xd (clongdouble_t value);
FDouble     operator ""xd (culonglong_t value);

FLongDouble operator ""xld (clongdouble_t value);
FLongDouble operator ""xld (culonglong_t value);
///\}

} // namespace
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Float.inl>

/**
 * [+] struct Float :
 * 			IComparable,
 * 			IComparable<double>,
 * 			IConvertible,
 * 			IEquatable<double>,
 * 			IFormattable
 * TODO: delimiter
 * [+] str(), format float ???
 * [+] isInf()
 *
 * TODO: C library
 * [+] https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
 * [+] https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
 */
