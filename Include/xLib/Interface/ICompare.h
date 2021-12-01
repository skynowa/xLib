/**
 * \file  ICompare.h
 * \brief Comparable interface. Mix-in that gives its subclass a full set of comparison operators.
 *
 * Simply by inheriting publically from this and implementing
 * compare(), the subclass gains a full set of comparison operators,
 * because all of the operators are implemented in terms of compare().
 *
 * Declares the ICompare<T> mixin
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

template <typename T>
class xNO_VTABLE ICompare
	/// Comparable interface
{
public:
	/// \brief Returns true if "other" is equal to this object
	bool operator == (const T &other) const
	{
		return !compare(other);
	}

	/// \brief Returns true if "other" is not equal to this object
	bool operator != (const T &other) const
	{
		return compare(other);
	}

	/// \brief Returns true if "other" is less than this object
	bool operator < (const T &other) const
	{
		return compare(other) < 0;
	}

	/// \brief Returns true if "other" is less than or equal to this object
	bool operator <= (const T &other) const
	{
		return compare(other) <= 0;
	}

	/// \brief Returns true if "other" is greater than this object
	bool operator > (const T &other) const
	{
		return compare(other) > 0;
	}

	/// \brief Returns true if "other" is greater than or equal to this object
	bool operator >= (const T &other) const
	{
		return compare(other) >= 0;
	}

protected:
	/// \brief Destroy object
	///
	/// This class has nothing to destroy, but declaring the dtor
	/// virtual placates some compilers set to high warning levels.
	/// Protecting it ensures you can't delete subclasses through base
	/// class pointers, which makes no sense because this class isn't
	/// made for polymorphism.  It's just a mixin.
	virtual ~ICompare() { }

	/// \brief Compare this object to another of the same type
	///
	/// Returns < 0 if this object is "before" the other, 0 of they are
	/// equal, and > 0 if this object is "after" the other.
	virtual int compare(const T& other) const = 0;
};

} // namespace
//-------------------------------------------------------------------------------------------------
