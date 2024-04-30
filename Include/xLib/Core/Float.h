/**
 * \file  Float.h
 * \brief Float's operations
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Interface/ICompare.h>
#include <xLib/Interface/IGet.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

template<typename T>
class Float :
	public ICompare<T>,
	public IGetConstRef<T>
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
	int_t    compare(const T &value) const final;
	const T &get() const final;
///\}

///\name operators
///\{
	Float & operator = (const Float &value);
	Float & operator = (const T value);
	Float & operator = (Float &&value);
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

using ffloat_t      = Float<float>;
using fdouble_t     = Float<double>;
using flongdouble_t = Float<long double>;

} // namespace
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Float.inl>

/**
 * TODO: public struct Float :
 * 			IComparable,
 * 			IComparable<double>,
 * 			IConvertible,
 * 			IEquatable<double>,
 * 			IFormattable
 * TODO: delimiter
 * TODO: str()
 * [+] isInf()
 *
 * TODO: C library
 * [+] https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
 * [+] https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
 */
