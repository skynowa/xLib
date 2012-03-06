/**
 * \file  CxAtomicLongInt.cpp
 * \brief atomic operartions with long_t
 */


#include <xLib/Sync/CxAtomicLongInt.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxAtomicLongInt::CxAtomicLongInt() :
    _m_liValue(0L)
{
#if xOS_ENV_WIN
    ::InterlockedExchange(&_m_liValue, 0L);
#elif xOS_ENV_UNIX
    //TODO:
#endif
}
//---------------------------------------------------------------------------
CxAtomicLongInt::~CxAtomicLongInt() {

}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator += (
    const CxAtomicLongInt &cRight
)
{
#if xOS_ENV_WIN
    ::InterlockedExchangeAdd(&_m_liValue, cRight._m_liValue);
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator -= (
    const CxAtomicLongInt &cRight
)
{
#if xOS_ENV_WIN
    ::InterlockedExchange(&_m_liValue, _m_liValue - cRight._m_liValue);
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator = (
    const CxAtomicLongInt &cRight
)
{
#if xOS_ENV_WIN
    ::InterlockedExchange(&_m_liValue, cRight._m_liValue);
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator += (
    const long_t cliRight
)
{
#if xOS_ENV_WIN
    ::InterlockedExchangeAdd(&_m_liValue, cliRight);
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator -= (
    const long_t cliRight
)
{
#if xOS_ENV_WIN
    ::InterlockedExchange(&_m_liValue, _m_liValue - cliRight);
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator = (
    const long_t cliRight
)
{
#if xOS_ENV_WIN
    ::InterlockedExchange(&_m_liValue, cliRight);
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator == (
    const CxAtomicLongInt &cRight
) const
{
    return (_m_liValue == cRight._m_liValue);
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator != (
    const CxAtomicLongInt &cRight
) const
{
    return !(_m_liValue == cRight._m_liValue);
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator == (
    const long_t cliRight
) const
{
    return (_m_liValue == cliRight);
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator != (
    const long_t cliRight
) const
{
    return !(_m_liValue == cliRight);
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator ++ (
    const long_t cliPos
)
{
#if xOS_ENV_WIN
    if (0L == cliPos) {
        ::InterlockedIncrement(&_m_liValue);
    } else {
        ::InterlockedExchangeAdd(&_m_liValue, cliPos + 1L);
    }
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator -- (
    const long_t cliPos
)
{
#if xOS_ENV_WIN
    if (0L == cilPos) {
        ::InterlockedDecrement(&_m_liValue);
    } else {
        ::InterlockedExchangeAdd(&_m_liValue, - (cliPos + 1L));
    }
#elif xOS_ENV_UNIX
    //TODO:
#endif

    return *this;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
