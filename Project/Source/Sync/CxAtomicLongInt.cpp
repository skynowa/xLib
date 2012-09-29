/**
 * \file  CxAtomicLongInt.cpp
 * \brief CxAtomicLongInt operartions with long_t
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
/* virtual */
CxAtomicLongInt::~CxAtomicLongInt() {

}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator += (
    const CxAtomicLongInt &a_calValue
)
{
#if   xOS_ENV_WIN
    (void)::InterlockedExchangeAdd(&_m_liValue, a_calValue._m_liValue);
#elif xOS_ENV_UNIX
    (void)::__sync_add_and_fetch(&_m_liValue, a_calValue._m_liValue);
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator += (
    const long_t a_cliValue
)
{
#if   xOS_ENV_WIN
    (void)::InterlockedExchangeAdd(&_m_liValue, a_cliValue);
#elif xOS_ENV_UNIX
    (void)::__sync_add_and_fetch(&_m_liValue, a_cliValue);
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator -= (
    const CxAtomicLongInt &a_calValue
)
{
#if   xOS_ENV_WIN
    (void)::InterlockedExchangeAdd(&_m_liValue, - a_calValue._m_liValue);
#elif xOS_ENV_UNIX
    (void)::__sync_sub_and_fetch(&_m_liValue, a_calValue._m_liValue);
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator -= (
    const long_t a_cliValue
)
{
#if   xOS_ENV_WIN
    (void)::InterlockedExchangeAdd(&_m_liValue, - a_cliValue);
#elif xOS_ENV_UNIX
    (void)::__sync_sub_and_fetch(&_m_liValue, a_cliValue);
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator = (
    const CxAtomicLongInt &a_calValue
)
{
#if   xOS_ENV_WIN
    (void)::InterlockedExchange(&_m_liValue, a_calValue._m_liValue);
#elif xOS_ENV_UNIX
    (void)::__sync_lock_test_and_set (&_m_liValue, a_calValue._m_liValue);
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator = (
    const long_t a_cliValue
)
{
#if   xOS_ENV_WIN
    (void)::InterlockedExchange(&_m_liValue, a_cliValue);
#elif xOS_ENV_UNIX
    (void)::__sync_lock_test_and_set (&_m_liValue, a_cliValue);
#endif

    return *this;
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator == (
    const CxAtomicLongInt &a_calValue
) const
{
    return (_m_liValue == a_calValue._m_liValue);
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator == (
    const long_t a_cliValue
) const
{
    return (_m_liValue == a_cliValue);
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator != (
    const CxAtomicLongInt &a_calValue
) const
{
    return (_m_liValue != a_calValue._m_liValue);
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator != (
    const long_t a_cliValue
) const
{
    return (_m_liValue != a_cliValue);
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator < (
    const long_t &a_cliValue
) const
{
    return (_m_liValue < a_cliValue);
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator < (
    const CxAtomicLongInt &a_calValue
) const
{
    return (_m_liValue < a_calValue.liGetValue());
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator <= (
    const long_t &a_cliValue
) const
{
    return (_m_liValue <= a_cliValue);
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator <= (
    const CxAtomicLongInt &a_calValue
) const
{
    return (_m_liValue <= a_calValue.liGetValue());
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator > (
    const long_t &a_cliValue
) const
{
    return (_m_liValue > a_cliValue);
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator > (
    const CxAtomicLongInt &a_calValue
) const
{
    return (_m_liValue > a_calValue.liGetValue());
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator >= (
    const long_t &cliValue
) const
{
    return (_m_liValue >= cliValue);
}
//---------------------------------------------------------------------------
bool
CxAtomicLongInt::operator >= (
    const CxAtomicLongInt &a_calValue
) const
{
    return (_m_liValue >= a_calValue.liGetValue());
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator ++ (
    const int a_ciValue
)
{
#if   xOS_ENV_WIN
    if (0 == a_ciValue) {
        (void)::InterlockedIncrement(&_m_liValue);
    } else {
        (void)::InterlockedExchangeAdd(&_m_liValue, a_ciValue + 1);
    }
#elif xOS_ENV_UNIX
    (void)::__sync_add_and_fetch(&_m_liValue, 1);
#endif

    return *this;
}
//---------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator -- (
    const int a_ciValue
)
{
#if   xOS_ENV_WIN
    if (0 == a_ciValue) {
        (void)::InterlockedDecrement(&_m_liValue);
    } else {
        (void)::InterlockedExchangeAdd(&_m_liValue, - (a_ciValue + 1));
    }
#elif xOS_ENV_UNIX
    (void)::__sync_sub_and_fetch(&_m_liValue, 1);
#endif

    return *this;
}
//---------------------------------------------------------------------------
long_t
CxAtomicLongInt::liGetValue() const {
#if   xOS_ENV_WIN
    return _m_liValue;
#elif xOS_ENV_UNIX
    return ::__sync_fetch_and_add(const_cast<volatile long_t *>( &_m_liValue ), 0L);
#endif
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
