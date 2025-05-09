/**
 * \file  AtomicLongInt.inl
 * \brief AtomicLongInt operartions with long_t
 */


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_addAssign_impl(
    const AtomicLongInt &a_value
)
{
    (void_t)::__sync_add_and_fetch(&_value, a_value._value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_addAssign_impl(
    clong_t &a_value
)
{
    (void_t)::__sync_add_and_fetch(&_value, a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_subtractAssign_impl(
    const AtomicLongInt &a_value
)
{
    (void_t)::__sync_sub_and_fetch(&_value, a_value._value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_subtractAssign_impl(
    clong_t &a_value
)
{
    (void_t)::__sync_sub_and_fetch(&_value, a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_assign_impl(
    const AtomicLongInt &a_value
)
{
    (void_t)::__sync_lock_test_and_set (&_value, a_value._value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_assign_impl(
    clong_t &a_value
)
{
    (void_t)::__sync_lock_test_and_set (&_value, a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_inc_impl(
    cint_t a_value
)
{
    xUNUSED(a_value);

    (void_t)::__sync_add_and_fetch(&_value, 1);

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_decr_impl(
    cint_t a_value
)
{
    xUNUSED(a_value);

    (void_t)::__sync_sub_and_fetch(&_value, 1);

    return *this;
}
//-------------------------------------------------------------------------------------------------
long_t
AtomicLongInt::_value_impl() const
{
    return ::__sync_fetch_and_add(const_cast<volatile long_t *>( &_value ), 0L);
}
//-------------------------------------------------------------------------------------------------

} // namespace
