/**
 * \file   Double.h
 * \brief  Double's operations
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Interface/ICompare.h>
#include <xLib/Interface/IGet.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

template<typename T>
class Double :
	public ICompare<T>,
	public IGetConstRef<T>
    ///< Double's operations
{
public:
///\name ctors, dtor
///\{
			 Double();
			 Double(const Double &value);
	explicit Double(const T &value);
			 Double(Double &&value);
	virtual ~Double();
///\}

///\name Overrides
///\{
	int_t    compare(const T &value) const final;
	const T &get() const final;
///\}

///\name operators
///\{
	Double & operator = (const Double &value);
	Double & operator = (const T &value);
	Double & operator = (Double &&value);
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
///\}

	T	   safeDiv(const T value, const T value_default = {}) const;
		///< safe division, if devision by 0.0 return 0.0

xPUBLIC_STATIC:
	static bool_t isEqual(const T value1, const T value2);

private:
    T _value {};
};

using dfloat_t      = Double<float>;
using ddouble_t     = Double<double>;
using dlongdouble_t = Double<long double>;

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Double.inl"

/**
 * TODO: public struct Double :
 * 			IComparable,
 * 			IComparable<double>,
 * 			IConvertible,
 * 			IEquatable<double>,
 * 			IFormattable
 * TODO: delimiter
 * TODO: str()
 * TODO: isInfinite()
 *
 * TODO: C library
 * TODO: https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
 * TODO: https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
 */
