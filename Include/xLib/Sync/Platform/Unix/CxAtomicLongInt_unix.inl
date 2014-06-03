/**
 * \file  CxAtomicLongInt.inl
 * \brief CxAtomicLongInt operartions with long_t
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_addAssign_impl(
    const CxAtomicLongInt &a_value
)
{
    (void_t)::__sync_add_and_fetch(&_value, a_value._value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_addAssign_impl(
    clong_t &a_value
)
{
    (void_t)::__sync_add_and_fetch(&_value, a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_subtractAssign_impl(
    const CxAtomicLongInt &a_value
)
{
    (void_t)::__sync_sub_and_fetch(&_value, a_value._value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_subtractAssign_impl(
    clong_t &a_value
)
{
    (void_t)::__sync_sub_and_fetch(&_value, a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_assign_impl(
    const CxAtomicLongInt &a_value
)
{
    (void_t)::__sync_lock_test_and_set (&_value, a_value._value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_assign_impl(
    clong_t &a_value
)
{
    (void_t)::__sync_lock_test_and_set (&_value, a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_inc_impl(
    cint_t a_value
)
{
    xUNUSED(a_value);

    (void_t)::__sync_add_and_fetch(&_value, 1);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_decr_impl(
    cint_t a_value
)
{
    xUNUSED(a_value);

    (void_t)::__sync_sub_and_fetch(&_value, 1);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxAtomicLongInt::_value_impl() const
{
    return ::__sync_fetch_and_add(const_cast<volatile long_t *>( &_value ), 0L);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
