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

}
//---------------------------------------------------------------------------
/*virtual*/
CxAtomicLongInt::~CxAtomicLongInt() {

}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator += (
    const CxAtomicLongInt &calValue
)
{
#if xOS_ENV_WIN
    (void)::InterlockedExchangeAdd(&_m_liValue, calValue._m_liValue);
#elif xOS_ENV_UNIX
    (void)::__sync_add_and_fetch(&_m_liValue, calValue._m_liValue);
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
    (void)::InterlockedExchangeAdd(&_m_liValue, cliRight);
#elif xOS_ENV_UNIX
    (void)::__sync_add_and_fetch(&_m_liValue, cliRight);
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator -= (
    const CxAtomicLongInt &calValue
)
{
#if xOS_ENV_WIN
    (void)::InterlockedExchange(&_m_liValue, _m_liValue - calValue._m_liValue);
#elif xOS_ENV_UNIX
    (void)::__sync_sub_and_fetch(&_m_liValue, calValue._m_liValue);
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
    (void)::InterlockedExchange(&_m_liValue, _m_liValue - cliRight);
#elif xOS_ENV_UNIX
    (void)::__sync_sub_and_fetch(&_m_liValue, cliRight);
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator = (
    const CxAtomicLongInt &calValue
)
{
#if xOS_ENV_WIN
    (void)::InterlockedExchange(&_m_liValue, calValue._m_liValue);
#elif xOS_ENV_UNIX
    (void)::__sync_lock_test_and_set (&_m_liValue, calValue._m_liValue);
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
    (void)::InterlockedExchange(&_m_liValue, cliRight);
#elif xOS_ENV_UNIX
    (void)::__sync_lock_test_and_set (&_m_liValue, cliRight);
#endif

    return *this;
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator == (
    const CxAtomicLongInt &calValue
) const
{
    return (_m_liValue == calValue._m_liValue);
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
    const CxAtomicLongInt &calValue
) const
{
    return (_m_liValue != calValue._m_liValue);
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator != (
    const long_t cliRight
) const
{
    return (_m_liValue != cliRight);
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator ++ (
    const int ciValue
)
{
#if xOS_ENV_WIN
    if (0 == ciValue) {
        (void)::InterlockedIncrement(&_m_liValue);
    } else {
        (void)::InterlockedExchangeAdd(&_m_liValue, ciValue + 1);
    }
#elif xOS_ENV_UNIX
    (void)::__sync_fetch_and_add(&_m_liValue, 1);
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator -- (
    const int ciValue
)
{
#if xOS_ENV_WIN
    if (0 == ciValue) {
        (void)::InterlockedDecrement(&_m_liValue);
    } else {
        (void)::InterlockedExchangeAdd(&_m_liValue, - (ciValue + 1));
    }
#elif xOS_ENV_UNIX
    (void)::__sync_fetch_and_sub(&_m_liValue, 1);
#endif

    return *this;
}
//---------------------------------------------------------------------------
long_t
CxAtomicLongInt::liGetValue() const {
    return _m_liValue;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
