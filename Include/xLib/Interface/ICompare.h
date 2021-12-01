/**
 * \file  ICompare.h
 * \brief Comparable interface. Mix-in that gives its subclass a full set of comparison operators.
 *
 * Simply by inheriting publically from this and implementing
 * compare(), the subclass gains a full set of comparison operators,
 * because all of the operators are implemented in terms of compare().
 *
 * Declares the ICompare<T> mixin
 *
 * \see https://tangentsoft.com/mysqlpp/file?name=lib/comparable.h
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface
{

template <typename T>
class xNO_VTABLE ICompare
	/// Comparable interface
{
public:
///@name ctors, dtor
///@{
			 ICompare() = default;
	virtual ~ICompare() = default;
///@}

	bool_t operator == (const T &value) const;
		///< Returns true if "value" is equal to this object
	bool_t operator != (const T &value) const;
		///< Returns true if "value" is not equal to this object
	bool_t operator < (const T &value) const;
		///< Returns true if "value" is less than this object
	bool_t operator <= (const T &value) const;
		///< Returns true if "value" is less than or equal to this object
	bool_t operator > (const T &value) const;
		///< Returns true if "value" is greater than this object
	bool_t operator >= (const T &value) const;
		///< Returns true if "value" is greater than or equal to this object

protected:
	virtual int_t compare(const T &value) const = 0;
		///< Compare this object to another of the same type
		///<
		///< \return
		///< "< 0" - if this object is "before" the value
		///< "0"   - of they are equal
		///< "> 0" - if this object is "after" the value
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "ICompare.inl"
//-------------------------------------------------------------------------------------------------
/**
 * TODO:
 *
 * - tests
 */
//-------------------------------------------------------------------------------------------------
