/**
 * \file  AtomicLongInt.cpp
 * \brief AtomicLongInt operartions with long_t
 */


#include "AtomicLongInt.h"

#if   xENV_WIN
    #include "Platform/Win/AtomicLongInt_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/AtomicLongInt_unix.inl"
#endif


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
AtomicLongInt::AtomicLongInt(
    const AtomicLongInt &a_value
)
{
    _value = a_value._value;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::operator += (
    const AtomicLongInt &a_value
)
{
    return _addAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::operator += (
    clong_t &a_value
)
{
    return _addAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::operator -= (
    const AtomicLongInt &a_value
)
{
    return _subtractAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::operator -= (
    clong_t &a_value
)
{
    return _subtractAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::operator = (
    const AtomicLongInt &a_value
)
{
    return _assign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::operator = (
    clong_t &a_value
)
{
    return _assign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
bool_t
AtomicLongInt::operator == (
    const AtomicLongInt &a_value
) const
{
    return (_value == a_value._value);
}
//-------------------------------------------------------------------------------------------------
bool_t
AtomicLongInt::operator == (
    clong_t &a_value
) const
{
    return (_value == a_value);
}
//-------------------------------------------------------------------------------------------------
bool_t
AtomicLongInt::operator != (
    const AtomicLongInt &a_value
) const
{
    return (_value != a_value._value);
}
//-------------------------------------------------------------------------------------------------
bool_t
AtomicLongInt::operator != (
    clong_t &a_value
) const
{
    return (_value != a_value);
}
//-------------------------------------------------------------------------------------------------
bool_t
AtomicLongInt::operator < (
    clong_t &a_value
) const
{
    return (_value < a_value);
}
//-------------------------------------------------------------------------------------------------
bool_t
AtomicLongInt::operator < (
    const AtomicLongInt &a_value
) const
{
    return (_value < a_value.value());
}
//------------------------------------------------------------------------------
bool_t
AtomicLongInt::operator <= (
    clong_t &a_value
) const
{
    return (_value <= a_value);
}
//-------------------------------------------------------------------------------------------------
bool_t
AtomicLongInt::operator <= (
    const AtomicLongInt &a_value
) const
{
    return (_value <= a_value.value());
}
//-------------------------------------------------------------------------------------------------
bool_t
AtomicLongInt::operator > (
    clong_t &a_value
) const
{
    return (_value > a_value);
}
//-------------------------------------------------------------------------------------------------
bool_t
AtomicLongInt::operator > (
    const AtomicLongInt &a_value
) const
{
    return (_value > a_value.value());
}
//-------------------------------------------------------------------------------------------------
bool_t
AtomicLongInt::operator >= (
    clong_t &a_value
) const
{
    return (_value >= a_value);
}
//-------------------------------------------------------------------------------------------------
bool_t
AtomicLongInt::operator >= (
    const AtomicLongInt &a_value
) const
{
    return (_value >= a_value.value());
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::operator ++ (
    cint_t a_value
)
{
    return _inc_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::operator -- (
    cint_t a_value
)
{
    return _decr_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
long_t
AtomicLongInt::value() const
{
    return _value_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
