/**
 * \file  CxDateTime.h
 * \brief date, time
 */


#pragma once

#ifndef xLib_CxRaiiH
#define xLib_CxRaiiH
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template <class T, void (T::*MemberT)(void)>
class CxRaii
    ///< RAII
{
public:
    CxRaii(T& a_object) :
        _object(a_object)
    {
    }
   ~CxRaii()
    {
        (_object.*MemberT)();
    }

private:
    T& _object;
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxRaiiH
