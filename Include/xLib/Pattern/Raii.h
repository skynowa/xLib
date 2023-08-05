/**
 * \file  Raii.h
 * \brief RAII
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::patterns
{

template<typename T, void_t (T::*MemberT)(void_t)>
class Raii
    ///< RAII
{
public:
///\name ctors, dtor
///\{
	explicit Raii(T &a_object) :
		_object(a_object)
	{
	}

   ~Raii()
	{
		(_object.*MemberT)();
	}

    xNO_DEFAULT_CONSTRUCT(Raii)
    xNO_COPY_ASSIGN(Raii)
///\}

    T &get()
    {
        return _object;
    }
        ///< get object
    const T &get() const
    {
        return _object;
    }
        ///< get object

private:
    T &_object;
};

} // namespace
//-------------------------------------------------------------------------------------------------
