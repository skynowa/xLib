/**
 * \file  CxAtomicLongInt.cpp
 * \brief atomic operartions with LONG
 */


#include <xLib/Sync/CxAtomicLongInt.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxAtomicLongInt ()
CxAtomicLongInt::CxAtomicLongInt() :
    _m_liValue(0)
{
#if xOS_ENV_WIN
    ::InterlockedExchange(&_m_liValue, 0);
#elif xOS_ENV_UNIX
    //TODO:
#endif
}
//---------------------------------------------------------------------------
//DONE: ~CxAtomicLongInt ()
CxAtomicLongInt::~CxAtomicLongInt() {

}
//---------------------------------------------------------------------------
//DONE: operator += ()
CxAtomicLongInt &
CxAtomicLongInt::operator += (const CxAtomicLongInt &cRight) {
#if xOS_ENV_WIN
    ::InterlockedExchangeAdd(&_m_liValue, cRight._m_liValue);
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------
//DONE: operator -= ()
CxAtomicLongInt &
CxAtomicLongInt::operator -= (const CxAtomicLongInt &cRight) {
#if xOS_ENV_WIN
    ::InterlockedExchange(&_m_liValue, _m_liValue - cRight._m_liValue);
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------
//DONE: operator = ()
CxAtomicLongInt &
CxAtomicLongInt::operator = (const CxAtomicLongInt &cRight)    {
#if xOS_ENV_WIN
    ::InterlockedExchange(&_m_liValue, cRight._m_liValue);
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------
//DONE: operator += ()
CxAtomicLongInt &
CxAtomicLongInt::operator += (const LONG cliRight) {
#if xOS_ENV_WIN
    ::InterlockedExchangeAdd(&_m_liValue, cliRight);
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------
//DONE: operator -= ()
CxAtomicLongInt &
CxAtomicLongInt::operator -= (const LONG cliRight) {
#if xOS_ENV_WIN
    ::InterlockedExchange(&_m_liValue, _m_liValue - cliRight);
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------
//DONE: operator = ()
CxAtomicLongInt &
CxAtomicLongInt::operator = (const LONG cliRight) {
#if xOS_ENV_WIN
    ::InterlockedExchange(&_m_liValue, cliRight);
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------
//DONE: operator == ()
BOOL
CxAtomicLongInt::operator == (const CxAtomicLongInt &cRight) const {
    return (BOOL)(_m_liValue == cRight._m_liValue);
}
//---------------------------------------------------------------------------
//DONE: operator != ()
BOOL
CxAtomicLongInt::operator != (const CxAtomicLongInt &cRight) const {
    return (BOOL)(!(_m_liValue == cRight._m_liValue));
}
//---------------------------------------------------------------------------
//DONE: operator == ()
BOOL
CxAtomicLongInt::operator == (const LONG cliRight) const {
    return (BOOL)(_m_liValue == cliRight);
}
//---------------------------------------------------------------------------
//DONE: operator != ()
BOOL
CxAtomicLongInt::operator != (const LONG cliRight) const {
    return (BOOL)( !(_m_liValue == cliRight) );
}
//---------------------------------------------------------------------------
//DONE: operator LONG ()
CxAtomicLongInt::operator LONG () const {
    return _m_liValue;
}
//---------------------------------------------------------------------------
//DONE: operator BOOL ()
CxAtomicLongInt::operator BOOL () const {
    return _m_liValue ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
//DONE: operator ++ ()
CxAtomicLongInt &
CxAtomicLongInt::operator ++ (int iPos) {
    #if xOS_ENV_WIN
        if (0 == iPos) {
            ::InterlockedIncrement(&_m_liValue);
        } else {
            ::InterlockedExchangeAdd(&_m_liValue, iPos + 1);
        }
    #elif xOS_ENV_UNIX
        //TODO:
    #endif

    return *this;
}
//---------------------------------------------------------------------------
//DONE: operator -- ()
CxAtomicLongInt &
CxAtomicLongInt::operator -- (int iPos) {
    #if xOS_ENV_WIN
        if (0 == iPos) {
            ::InterlockedDecrement(&_m_liValue);
        } else {
            ::InterlockedExchangeAdd(&_m_liValue, - (iPos + 1));
        }
    #elif xOS_ENV_UNIX
        //TODO:
    #endif

    return *this;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
