/**
 * \file   CxFlags.cpp
 * \brief  bit mask flags
 */


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template <class T>
CxFlags<T>::CxFlags() :
    _flags(0)
{
}
//-------------------------------------------------------------------------------------------------
template <class T>
CxFlags<T>::CxFlags(
    const CxFlags &a_values
) :
    _flags(a_values._flags)
{
}
//-------------------------------------------------------------------------------------------------
template <class T>
CxFlags<T>::CxFlags(
    const T &a_values
) :
    _flags(a_values)
{
}
//-------------------------------------------------------------------------------------------------
template <class T>
CxFlags<T> &
CxFlags<T>::operator = (
    const CxFlags &a_values
)
{
    xCHECK_RET(this == &a_values, *this);

    _flags = a_values._flags;

    return *this;
}
//-------------------------------------------------------------------------------------------------
template <class T>
size_t &
CxFlags<T>::get() const
{
    return _flags;
}
//-------------------------------------------------------------------------------------------------
template <class T>
void_t
CxFlags<T>::set(
    const T &a_values
)
{
    _flags = a_values;
}
//-------------------------------------------------------------------------------------------------
template <class T>
void_t
CxFlags<T>::clear()
{
    _flags = 0;
}
//-------------------------------------------------------------------------------------------------
template <class T>
bool_t
CxFlags<T>::isSetFlag(
    const T &a_value
) const
{
    return (_flags & a_value) == a_value;
}
//-------------------------------------------------------------------------------------------------
template <class T>
bool_t
CxFlags<T>::isSetAnyFlag(
    const T &a_value
) const
{
    return (_flags & a_value) != 0;
}
//-------------------------------------------------------------------------------------------------
template <class T>
void_t
CxFlags<T>::setFlag(
    const T &a_value
)
{
    _flags |= a_value;
}
//-------------------------------------------------------------------------------------------------
template <class T>
void_t
CxFlags<T>::unsetFlag(
    const T &a_value
)
{
    _flags &= ~a_value;
}

//-------------------------------------------------------------------------------------------------
template <class T>
void
CxFlags<T>::toggleFlag(
    const T &a_value
)
{
    _flags ^= a_value;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
