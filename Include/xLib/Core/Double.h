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
    explicit Double(const T &value);
        ///< constructor
    virtual ~Double() = default;
        ///< destructor

    Double & operator = (const T &values);
        ///< operator =

	bool_t   isEqual(const T value) const;
		///< compare values
	bool_t   isAlmostEqual(const T &value, const int_t ulp = 2) const;
		///< ???
	bool_t   isNull() const;
		///< compare values
	T	     safeDivision(const T &y, const T &value_default = {}) const;
		///< safe division, if devision by 0.0 return 0.0
    void_t   clear();
        ///< set to 0

    xNO_MOVE(Double)

private:
    T _value {};
};

using dfloat_t  = Double<float>;
using ddouble_t = Double<double>;

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Double.inl"
