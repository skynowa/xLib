/**
 * \file  Raii.h
 * \brief RAII
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, patterns)

template <class T, void (T::*MemberT)(void)>
class Raii
    ///< RAII
{
public:
    explicit Raii(T &a_object) :
        _object(a_object)
    {
    }
        ///< constructor
   ~Raii()
    {
        (_object.*MemberT)();
    }
        ///< destructor

    T& get()
    {
        return _object;
    }
        ///< get object
    const T& get() const
    {
        return _object;
    }
        ///< get object

private:
    T& _object;

    xNO_COPY_ASSIGN(Raii)
};

xNAMESPACE_END2(xlib, patterns)
//-------------------------------------------------------------------------------------------------
