/**
 * \file  Raii.h
 * \brief RAII
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::patterns
{

template<typename T, void (T::*MemberT)(void)>
class Raii
    ///< RAII
{
public:
///@name ctors, dtor
///@{
	explicit Raii(T &a_object) :
		_object(a_object)
	{
	}

   ~Raii()
	{
		(_object.*MemberT)();
	}

    xNO_COPY_ASSIGN(Raii)
///@}

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
