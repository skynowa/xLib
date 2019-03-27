/**
 * \file   IData.h
 * \brief  Data struct
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, interface)

template<typename T>
class xNO_VTABLE IContainer
	/// Container interface
{
public:
	// types
	using value_type             = T;
	using size_type              = std::size_t;
	using difference_type        = std::ptrdiff_t;

	using reference              = value_type &;
	using const_reference        = const value_type &;
	using pointer	             = T *;
	using const_pointer          = const T *;

	using iterator               = value_type *;
	using const_iterator         = const value_type *;
	using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	// iterators
	virtual iterator       begin() = 0;
	virtual const_iterator cbegin() const = 0;
	virtual iterator       end() = 0;
	virtual const_iterator cend() const = 0;

	// capacity
	virtual size_type      size() const = 0;

	// element access
	virtual pointer        data() = 0;

public:
	// capacity
	bool
	empty() const
	{
		return (size() == 0);
	}

	// iterators
	reverse_iterator
	rbegin()
	{
		return reverse_iterator( end() );
	}

	const_reverse_iterator
	crbegin() const
	{
		return const_reverse_iterator( end() );
	}

	reverse_iterator
	rend()
	{
		return reverse_iterator( begin() );
	}

	const_reverse_iterator
	crend() const
	{
		return const_reverse_iterator( begin() );
	}

	// element access
	reference
	front()
	{
		return *begin();
	}

	const_reference
	front() const
	{
		return *begin();
	}

	reference
	back()
	{
		return size() ? *(end() - 1) : *end();
	}

	const_reference
	back() const
	{
		return back();
	}

	const_pointer
	data() const
	{
		return data();
	}
};
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, interface)
//-------------------------------------------------------------------------------------------------
