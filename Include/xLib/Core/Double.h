/**
 * \file   Double.h
 * \brief  Double's operations
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename T>
class Double
    ///< Double's operations
{
public:
	// default
             Double() = default;

    // copy
             Double(const T &value);

    // move
             Double(T &&value);

	// destructor
    virtual ~Double() = default;

	// Copy assignment
    Double & operator = (const T &value);

	// Move assignment
    Double & operator = (T &&value);

	// Comparison
	bool_t   operator <  (const T value) const;
	bool_t   operator >  (const T value) const;
	bool_t   operator <= (const T value) const;
	bool_t   operator >= (const T value) const;
	bool_t   operator == (const T value) const;
	bool_t   operator != (const T value) const;
    static
    bool_t   isEqual(const T value1, const T value2);

	// methods
	const T &get() const;
		///< get native value
	bool_t   isNull() const;
		///< compare values
	T	     safeDiv(const T value, const T value_default = {}) const;
		///< safe division, if devision by 0.0 return 0.0
    void_t   clear();
        ///< set to 0

private:
    T _value {};
};

using dfloat_t      = Double<float>;
using ddouble_t     = Double<double>;
using dlongdouble_t = Double<long double>;

xNAMESPACE_END2(xl, core)
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
 * DONE: operators <,>,==,<=,=>
 * TODO: toString()
 * TODO: isInfinite()
 *
 * TODO: C library
 * TODO: https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
 * TODO: https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
 */
