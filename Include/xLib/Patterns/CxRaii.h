/**
 * \file  CxRaii.h
 * \brief RAII
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, patterns)

template <class T, void (T::*MemberT)(void)>
class CxRaii
    ///< RAII
{
public:
    explicit CxRaii(T &a_object) :
        _object(a_object)
    {
    }
        ///< constructor
   ~CxRaii()
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

    xNO_COPY_ASSIGN(CxRaii)
};

xNAMESPACE_END2(xlib, patterns)
//-------------------------------------------------------------------------------------------------
