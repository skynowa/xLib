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
             Double() = default;
        ///< constructor
    explicit Double(const T value);
        ///< constructor
    virtual ~Double() = default;
        ///< destructor

	// operators
    Double & operator = (const T value);
        ///< operator =

	bool_t   operator <  (const T value) const;
	bool_t   operator >  (const T value) const;
	bool_t   operator <= (const T value) const;
	bool_t   operator >= (const T value) const;
	bool_t   operator == (const T value) const;
	bool_t   operator != (const T value) const;

	// methods
	bool_t   isNull() const;
		///< compare values
	T	     safeDiv(const T y, const T value_default = {}) const;
		///< safe division, if devision by 0.0 return 0.0
    void_t   clear();
        ///< set to 0

    xNO_MOVE(Double)

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
 * TODO: public struct Double : IComparable, IComparable<double>, IConvertible, IEquatable<double>, IFormattable
 * TODO: delimiter
 * TODO: operators <,>,==,<=,=>
 * TODO: toString()
 * TODO: tisInfinite()
 *
 *
 * TODO: C library
 * TODO: https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
 * TODO: https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
 */

