/****************************************************************************
* Class name:  CxAtomicLongInt
* Description: atomic operartions with LONG
* File name:   CxAtomicLongInt.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     25.11.2009 10:03:17
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Sync/CxAtomicLongInt.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxAtomicLongInt ()
CxAtomicLongInt::CxAtomicLongInt() : 
    _m_liValue(0)      
{ 
#if defined(xOS_WIN)
    ::InterlockedExchange(&_m_liValue, 0);
#elif defined(xOS_LINUX)
    //TODO:
#endif
}
//---------------------------------------------------------------------------
//TODO: + ~CxAtomicLongInt ()
CxAtomicLongInt::~CxAtomicLongInt() {

}
//---------------------------------------------------------------------------
//TODO: + operator += ()
CxAtomicLongInt & 
CxAtomicLongInt::operator += (const CxAtomicLongInt &cRight) {
#if defined(xOS_WIN)
    ::InterlockedExchangeAdd(&_m_liValue, cRight._m_liValue);
#elif defined(xOS_LINUX)
    //TODO:
#endif

	return *this;
}
//---------------------------------------------------------------------------
//TODO: + operator -= ()
CxAtomicLongInt & 
CxAtomicLongInt::operator -= (const CxAtomicLongInt &cRight) {
#if defined(xOS_WIN)
    ::InterlockedExchange(&_m_liValue, _m_liValue - cRight._m_liValue);
#elif defined(xOS_LINUX)
    //TODO:
#endif

	return *this;
}
//---------------------------------------------------------------------------
//TODO: + operator = ()
CxAtomicLongInt & 
CxAtomicLongInt::operator = (const CxAtomicLongInt &cRight)	{
#if defined(xOS_WIN)
    ::InterlockedExchange(&_m_liValue, cRight._m_liValue);
#elif defined(xOS_LINUX)
    //TODO:
#endif

	return *this;
}
//---------------------------------------------------------------------------
//TODO: + operator += ()
CxAtomicLongInt & 
CxAtomicLongInt::operator += (const LONG cliRight) {
#if defined(xOS_WIN)
    ::InterlockedExchangeAdd(&_m_liValue, cliRight);
#elif defined(xOS_LINUX)
    //TODO:
#endif

	return *this;
}
//---------------------------------------------------------------------------
//TODO: + operator -= ()
CxAtomicLongInt & 
CxAtomicLongInt::operator -= (const LONG cliRight) {
#if defined(xOS_WIN)
    ::InterlockedExchange(&_m_liValue, _m_liValue - cliRight);
#elif defined(xOS_LINUX)
    //TODO:
#endif

	return *this;
}
//---------------------------------------------------------------------------
//TODO: + operator = ()
CxAtomicLongInt & 
CxAtomicLongInt::operator = (const LONG cliRight) {
#if defined(xOS_WIN)
    ::InterlockedExchange(&_m_liValue, cliRight);
#elif defined(xOS_LINUX)
    //TODO:
#endif

	return *this;
}
//---------------------------------------------------------------------------
//TODO: + operator == ()
BOOL 
CxAtomicLongInt::operator == (const CxAtomicLongInt &cRight) const {
	return (BOOL)(_m_liValue == cRight._m_liValue);
}
//---------------------------------------------------------------------------
//TODO: + operator != ()
BOOL 
CxAtomicLongInt::operator != (const CxAtomicLongInt &cRight) const {
	return (BOOL)(!(_m_liValue == cRight._m_liValue));
}
//---------------------------------------------------------------------------
//TODO: + operator == ()
BOOL 
CxAtomicLongInt::operator == (const LONG cliRight) const {
	return (BOOL)(_m_liValue == cliRight);
}
//---------------------------------------------------------------------------
//TODO: + operator != ()
BOOL 
CxAtomicLongInt::operator != (const LONG cliRight) const {
	return (BOOL)( !(_m_liValue == cliRight) );
}
//---------------------------------------------------------------------------
//TODO: + operator LONG ()
CxAtomicLongInt::operator LONG () const {
	return _m_liValue;
}
//---------------------------------------------------------------------------
//TODO: + operator BOOL ()
CxAtomicLongInt::operator BOOL () const {
	return _m_liValue ? TRUE : FALSE; 
}
//---------------------------------------------------------------------------
//TODO: + operator ++ ()
CxAtomicLongInt &
CxAtomicLongInt::operator ++ (INT iPos) {
	#if defined(xOS_WIN)
        if (0 == iPos) {
            ::InterlockedIncrement(&_m_liValue);
        } else {
            ::InterlockedExchangeAdd(&_m_liValue, iPos + 1);
        }
    #elif defined(xOS_LINUX)
        //TODO:
    #endif

	return *this;
}
//---------------------------------------------------------------------------
//TODO: + operator -- ()
CxAtomicLongInt &
CxAtomicLongInt::operator -- (INT iPos) {
	#if defined(xOS_WIN)
        if (0 == iPos) {
            ::InterlockedDecrement(&_m_liValue);
        } else {
            ::InterlockedExchangeAdd(&_m_liValue, - (iPos + 1));
        }
    #elif defined(xOS_LINUX)
        //TODO:
    #endif

	return *this;
}
//---------------------------------------------------------------------------
