/**
 * \file  CxRaii.h
 * \brief RAII
 */


#pragma once

#ifndef xLib_CxRaiiH
#define xLib_CxRaiiH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template <class T, void (T::*MemberT)(void)>
class CxRaii
    ///< RAII
{
public:
    CxRaii(T &a_object) :
        _object(a_object)
    {
    }
        ///< constructor
   ~CxRaii()
    {
        (_object.*MemberT)();
    }
        ///< destructor

private:
    T &_object;

    xNO_COPY_ASSIGN(CxRaii)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxRaiiH
