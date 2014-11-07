/**
 * \file  AtomicLongInt.inl
 * \brief AtomicLongInt operartions with long_t
 */


#if !xOPTION_HEADER_ONLY
    #include "AtomicLongInt.h"
#endif

#if   xENV_WIN
    #include "Platform/Win/AtomicLongInt_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/AtomicLongInt_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/AtomicLongInt_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/AtomicLongInt_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/AtomicLongInt_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
AtomicLongInt::AtomicLongInt() :
    _value(0L)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE AtomicLongInt &
AtomicLongInt::operator += (
    const AtomicLongInt &a_value
)
{
    return _addAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE AtomicLongInt &
AtomicLongInt::operator += (
    clong_t &a_value
)
{
    return _addAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE AtomicLongInt &
AtomicLongInt::operator -= (
    const AtomicLongInt &a_value
)
{
    return _subtractAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE AtomicLongInt &
AtomicLongInt::operator -= (
    clong_t &a_value
)
{
    return _subtractAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE AtomicLongInt &
AtomicLongInt::operator = (
    const AtomicLongInt &a_value
)
{
    return _assign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE AtomicLongInt &
AtomicLongInt::operator = (
    clong_t &a_value
)
{
    return _assign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
AtomicLongInt::operator == (
    const AtomicLongInt &a_value
) const
{
    return (_value == a_value._value);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
AtomicLongInt::operator == (
    clong_t &a_value
) const
{
    return (_value == a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
AtomicLongInt::operator != (
    const AtomicLongInt &a_value
) const
{
    return (_value != a_value._value);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
AtomicLongInt::operator != (
    clong_t &a_value
) const
{
    return (_value != a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
AtomicLongInt::operator < (
    clong_t &a_value
) const
{
    return (_value < a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
AtomicLongInt::operator < (
    const AtomicLongInt &a_value
) const
{
    return (_value < a_value.value());
}
//------------------------------------------------------------------------------
xINLINE bool_t
AtomicLongInt::operator <= (
    clong_t &a_value
) const
{
    return (_value <= a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
AtomicLongInt::operator <= (
    const AtomicLongInt &a_value
) const
{
    return (_value <= a_value.value());
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
AtomicLongInt::operator > (
    clong_t &a_value
) const
{
    return (_value > a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
AtomicLongInt::operator > (
    const AtomicLongInt &a_value
) const
{
    return (_value > a_value.value());
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
AtomicLongInt::operator >= (
    clong_t &a_value
) const
{
    return (_value >= a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
AtomicLongInt::operator >= (
    const AtomicLongInt &a_value
) const
{
    return (_value >= a_value.value());
}
//-------------------------------------------------------------------------------------------------
xINLINE AtomicLongInt &
AtomicLongInt::operator ++ (
    cint_t a_value
)
{
    return _inc_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE AtomicLongInt &
AtomicLongInt::operator -- (
    cint_t a_value
)
{
    return _decr_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE long_t
AtomicLongInt::value() const
{
    return _value_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
