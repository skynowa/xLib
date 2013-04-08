/**
 * \file  CxAtomicLongInt.cpp
 * \brief CxAtomicLongInt operartions with long_t
 */


#include <xLib/Sync/CxAtomicLongInt.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxAtomicLongInt::CxAtomicLongInt() :
    _m_liValue(0L)
{

}
//------------------------------------------------------------------------------
/* virtual */
CxAtomicLongInt::~CxAtomicLongInt() {

}
//------------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator += (
    const CxAtomicLongInt &a_calValue
)
{
#if xOS_ENV_WIN
    (void_t)::InterlockedExchangeAdd(&_m_liValue, a_calValue._m_liValue);
#else
    (void_t)::__sync_add_and_fetch(&_m_liValue, a_calValue._m_liValue);
#endif

    return *this;
}
//------------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator += (
    clong_t &a_cliValue
)
{
#if xOS_ENV_WIN
    (void_t)::InterlockedExchangeAdd(&_m_liValue, a_cliValue);
#else
    (void_t)::__sync_add_and_fetch(&_m_liValue, a_cliValue);
#endif

    return *this;
}
//------------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator -= (
    const CxAtomicLongInt &a_calValue
)
{
#if xOS_ENV_WIN
    (void_t)::InterlockedExchangeAdd(&_m_liValue, - a_calValue._m_liValue);
#else
    (void_t)::__sync_sub_and_fetch(&_m_liValue, a_calValue._m_liValue);
#endif

    return *this;
}
//------------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator -= (
    clong_t &a_cliValue
)
{
#if xOS_ENV_WIN
    (void_t)::InterlockedExchangeAdd(&_m_liValue, - a_cliValue);
#else
    (void_t)::__sync_sub_and_fetch(&_m_liValue, a_cliValue);
#endif

    return *this;
}
//------------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator = (
    const CxAtomicLongInt &a_calValue
)
{
#if xOS_ENV_WIN
    (void_t)::InterlockedExchange(&_m_liValue, a_calValue._m_liValue);
#else
    (void_t)::__sync_lock_test_and_set (&_m_liValue, a_calValue._m_liValue);
#endif

    return *this;
}
//------------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator = (
    clong_t &a_cliValue
)
{
#if xOS_ENV_WIN
    (void_t)::InterlockedExchange(&_m_liValue, a_cliValue);
#else
    (void_t)::__sync_lock_test_and_set (&_m_liValue, a_cliValue);
#endif

    return *this;
}
//------------------------------------------------------------------------------
bool_t
CxAtomicLongInt::operator == (
    const CxAtomicLongInt &a_calValue
) const
{
    return (_m_liValue == a_calValue._m_liValue);
}
//------------------------------------------------------------------------------
bool_t
CxAtomicLongInt::operator == (
    clong_t &a_cliValue
) const
{
    return (_m_liValue == a_cliValue);
}
//------------------------------------------------------------------------------
bool_t
CxAtomicLongInt::operator != (
    const CxAtomicLongInt &a_calValue
) const
{
    return (_m_liValue != a_calValue._m_liValue);
}
//------------------------------------------------------------------------------
bool_t
CxAtomicLongInt::operator != (
    clong_t &a_cliValue
) const
{
    return (_m_liValue != a_cliValue);
}
//------------------------------------------------------------------------------
bool_t
CxAtomicLongInt::operator < (
    clong_t &a_cliValue
) const
{
    return (_m_liValue < a_cliValue);
}
//------------------------------------------------------------------------------
bool_t
CxAtomicLongInt::operator < (
    const CxAtomicLongInt &a_calValue
) const
{
    return (_m_liValue < a_calValue.value());
}
//------------------------------------------------------------------------------
bool_t
CxAtomicLongInt::operator <= (
    clong_t &a_cliValue
) const
{
    return (_m_liValue <= a_cliValue);
}
//------------------------------------------------------------------------------
bool_t
CxAtomicLongInt::operator <= (
    const CxAtomicLongInt &a_calValue
) const
{
    return (_m_liValue <= a_calValue.value());
}
//------------------------------------------------------------------------------
bool_t
CxAtomicLongInt::operator > (
    clong_t &a_cliValue
) const
{
    return (_m_liValue > a_cliValue);
}
//------------------------------------------------------------------------------
bool_t
CxAtomicLongInt::operator > (
    const CxAtomicLongInt &a_calValue
) const
{
    return (_m_liValue > a_calValue.value());
}
//------------------------------------------------------------------------------
bool_t
CxAtomicLongInt::operator >= (
    clong_t &cliValue
) const
{
    return (_m_liValue >= cliValue);
}
//------------------------------------------------------------------------------
bool_t
CxAtomicLongInt::operator >= (
    const CxAtomicLongInt &a_calValue
) const
{
    return (_m_liValue >= a_calValue.value());
}
//------------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator ++ (
    cint_t a_ciValue
)
{
#if xOS_ENV_WIN
    if (0 == a_ciValue) {
        (void_t)::InterlockedIncrement(&_m_liValue);
    } else {
        (void_t)::InterlockedExchangeAdd(&_m_liValue, a_ciValue + 1);
    }
#else
    (void_t)::__sync_add_and_fetch(&_m_liValue, 1);
#endif

    return *this;
}
//------------------------------------------------------------------------------
CxAtomicLongInt &
CxAtomicLongInt::operator -- (
    cint_t a_ciValue
)
{
#if xOS_ENV_WIN
    if (0 == a_ciValue) {
        (void_t)::InterlockedDecrement(&_m_liValue);
    } else {
        (void_t)::InterlockedExchangeAdd(&_m_liValue, - (a_ciValue + 1));
    }
#else
    (void_t)::__sync_sub_and_fetch(&_m_liValue, 1);
#endif

    return *this;
}
//------------------------------------------------------------------------------
long_t
CxAtomicLongInt::value() const {
#if xOS_ENV_WIN
    return _m_liValue;
#else
    return ::__sync_fetch_and_add(const_cast<volatile long_t *>( &_m_liValue ), 0L);
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
