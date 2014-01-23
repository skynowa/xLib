/**
 * \file  CxAtomicLongInt.cpp
 * \brief CxAtomicLongInt operartions with long_t
 */


xNAMESPACE2_BEGIN(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxAtomicLongInt::CxAtomicLongInt() :
    _value(0L)
{
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator += (
    const CxAtomicLongInt &a_value
)
{
#if   xOS_ENV_WIN
    (void_t)::InterlockedExchangeAdd(&_value, a_value._value);
#elif xOS_ENV_UNIX
    (void_t)::__sync_add_and_fetch(&_value, a_value._value);
#endif

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator += (
    clong_t &a_value
)
{
#if   xOS_ENV_WIN
    (void_t)::InterlockedExchangeAdd(&_value, a_value);
#elif xOS_ENV_UNIX
    (void_t)::__sync_add_and_fetch(&_value, a_value);
#endif

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator -= (
    const CxAtomicLongInt &a_value
)
{
#if   xOS_ENV_WIN
    (void_t)::InterlockedExchangeAdd(&_value, - a_value._value);
#elif xOS_ENV_UNIX
    (void_t)::__sync_sub_and_fetch(&_value, a_value._value);
#endif

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator -= (
    clong_t &a_value
)
{
#if   xOS_ENV_WIN
    (void_t)::InterlockedExchangeAdd(&_value, - a_value);
#elif xOS_ENV_UNIX
    (void_t)::__sync_sub_and_fetch(&_value, a_value);
#endif

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator = (
    const CxAtomicLongInt &a_value
)
{
#if   xOS_ENV_WIN
    (void_t)::InterlockedExchange(&_value, a_value._value);
#elif xOS_ENV_UNIX
    (void_t)::__sync_lock_test_and_set (&_value, a_value._value);
#endif

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator = (
    clong_t &a_value
)
{
#if   xOS_ENV_WIN
    (void_t)::InterlockedExchange(&_value, a_value);
#elif xOS_ENV_UNIX
    (void_t)::__sync_lock_test_and_set (&_value, a_value);
#endif

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxAtomicLongInt::operator == (
    const CxAtomicLongInt &a_value
) const
{
    return (_value == a_value._value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxAtomicLongInt::operator == (
    clong_t &a_value
) const
{
    return (_value == a_value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxAtomicLongInt::operator != (
    const CxAtomicLongInt &a_value
) const
{
    return (_value != a_value._value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxAtomicLongInt::operator != (
    clong_t &a_value
) const
{
    return (_value != a_value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxAtomicLongInt::operator < (
    clong_t &a_value
) const
{
    return (_value < a_value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxAtomicLongInt::operator < (
    const CxAtomicLongInt &a_value
) const
{
    return (_value < a_value.value());
}
//------------------------------------------------------------------------------
inline bool_t
CxAtomicLongInt::operator <= (
    clong_t &a_value
) const
{
    return (_value <= a_value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxAtomicLongInt::operator <= (
    const CxAtomicLongInt &a_value
) const
{
    return (_value <= a_value.value());
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxAtomicLongInt::operator > (
    clong_t &a_value
) const
{
    return (_value > a_value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxAtomicLongInt::operator > (
    const CxAtomicLongInt &a_value
) const
{
    return (_value > a_value.value());
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxAtomicLongInt::operator >= (
    clong_t &a_value
) const
{
    return (_value >= a_value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxAtomicLongInt::operator >= (
    const CxAtomicLongInt &a_value
) const
{
    return (_value >= a_value.value());
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator ++ (
    cint_t a_value
)
{
#if   xOS_ENV_WIN
    if (0 == a_value) {
        (void_t)::InterlockedIncrement(&_value);
    } else {
        (void_t)::InterlockedExchangeAdd(&_value, a_value + 1);
    }
#elif xOS_ENV_UNIX
    xUNUSED(a_value);

    (void_t)::__sync_add_and_fetch(&_value, 1);
#endif

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator -- (
    cint_t a_value
)
{
#if   xOS_ENV_WIN
    if (0 == a_value) {
        (void_t)::InterlockedDecrement(&_value);
    } else {
        (void_t)::InterlockedExchangeAdd(&_value, - (a_value + 1));
    }
#elif xOS_ENV_UNIX
    xUNUSED(a_value);

    (void_t)::__sync_sub_and_fetch(&_value, 1);
#endif

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxAtomicLongInt::value() const
{
#if   xOS_ENV_WIN
    return _value;
#elif xOS_ENV_UNIX
    return ::__sync_fetch_and_add(const_cast<volatile long_t *>( &_value ), 0L);
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, sync)
