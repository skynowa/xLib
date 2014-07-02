/**
 * \file  AtomicLongInt.inl
 * \brief AtomicLongInt operartions with long_t
 */


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
inline
AtomicLongInt::AtomicLongInt() :
    _value(0L)
{
}
//-------------------------------------------------------------------------------------------------
inline AtomicLongInt &
AtomicLongInt::operator += (
    const AtomicLongInt &a_value
)
{
    return _addAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline AtomicLongInt &
AtomicLongInt::operator += (
    clong_t &a_value
)
{
    return _addAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline AtomicLongInt &
AtomicLongInt::operator -= (
    const AtomicLongInt &a_value
)
{
    return _subtractAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline AtomicLongInt &
AtomicLongInt::operator -= (
    clong_t &a_value
)
{
    return _subtractAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline AtomicLongInt &
AtomicLongInt::operator = (
    const AtomicLongInt &a_value
)
{
    return _assign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline AtomicLongInt &
AtomicLongInt::operator = (
    clong_t &a_value
)
{
    return _assign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
AtomicLongInt::operator == (
    const AtomicLongInt &a_value
) const
{
    return (_value == a_value._value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
AtomicLongInt::operator == (
    clong_t &a_value
) const
{
    return (_value == a_value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
AtomicLongInt::operator != (
    const AtomicLongInt &a_value
) const
{
    return (_value != a_value._value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
AtomicLongInt::operator != (
    clong_t &a_value
) const
{
    return (_value != a_value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
AtomicLongInt::operator < (
    clong_t &a_value
) const
{
    return (_value < a_value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
AtomicLongInt::operator < (
    const AtomicLongInt &a_value
) const
{
    return (_value < a_value.value());
}
//------------------------------------------------------------------------------
inline bool_t
AtomicLongInt::operator <= (
    clong_t &a_value
) const
{
    return (_value <= a_value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
AtomicLongInt::operator <= (
    const AtomicLongInt &a_value
) const
{
    return (_value <= a_value.value());
}
//-------------------------------------------------------------------------------------------------
inline bool_t
AtomicLongInt::operator > (
    clong_t &a_value
) const
{
    return (_value > a_value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
AtomicLongInt::operator > (
    const AtomicLongInt &a_value
) const
{
    return (_value > a_value.value());
}
//-------------------------------------------------------------------------------------------------
inline bool_t
AtomicLongInt::operator >= (
    clong_t &a_value
) const
{
    return (_value >= a_value);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
AtomicLongInt::operator >= (
    const AtomicLongInt &a_value
) const
{
    return (_value >= a_value.value());
}
//-------------------------------------------------------------------------------------------------
inline AtomicLongInt &
AtomicLongInt::operator ++ (
    cint_t a_value
)
{
    return _inc_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline AtomicLongInt &
AtomicLongInt::operator -- (
    cint_t a_value
)
{
    return _decr_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline long_t
AtomicLongInt::value() const
{
    return _value_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
