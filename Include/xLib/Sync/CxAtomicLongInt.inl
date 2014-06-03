/**
 * \file  CxAtomicLongInt.inl
 * \brief CxAtomicLongInt operartions with long_t
 */


#if   xENV_WIN
    #include "Platform/Win/CxAtomicLongInt_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxAtomicLongInt_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/CxAtomicLongInt_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/CxAtomicLongInt_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/CxAtomicLongInt_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, sync)

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
    return _addAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator += (
    clong_t &a_value
)
{
    return _addAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator -= (
    const CxAtomicLongInt &a_value
)
{
    return _subtractAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator -= (
    clong_t &a_value
)
{
    return _subtractAssign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator = (
    const CxAtomicLongInt &a_value
)
{
    return _assign_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator = (
    clong_t &a_value
)
{
    return _assign_impl(a_value);
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
    return _inc_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::operator -- (
    cint_t a_value
)
{
    return _decr_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxAtomicLongInt::value() const
{
    return _value_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
