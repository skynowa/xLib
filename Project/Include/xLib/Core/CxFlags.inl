/**
 * \file   CxFlags.cpp
 * \brief  bit mask flags
 */


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
template <class T>
CxFlags<T>::CxFlags() : 
    _m_mFlags(0)
{
}
//------------------------------------------------------------------------------
template <class T>
CxFlags<T>::CxFlags(
    const CxFlags &a_values
) : 
    _m_mFlags(a_values._m_mFlags)
{
}
//------------------------------------------------------------------------------
template <class T>
CxFlags<T>::CxFlags(
    const T &a_values
) :
    _m_mFlags(a_values)
{
}
//------------------------------------------------------------------------------
/* virtual */
template <class T>
CxFlags<T>::~CxFlags()
{
}
//------------------------------------------------------------------------------        
template <class T>
CxFlags<T> & 
CxFlags<T>::operator = (
    const CxFlags &a_values
)
{
    xCHECK_RET(this == &a_values, *this);

    _m_mFlags = a_values._m_mFlags;

    return *this;
}
//------------------------------------------------------------------------------        
template <class T>
size_t &
CxFlags<T>::get() const 
{
    return _m_mFlags;
}
//------------------------------------------------------------------------------        
template <class T>
void_t 
CxFlags<T>::set(
    const T &a_values
)
{
    _m_mFlags = a_values;
}
//------------------------------------------------------------------------------
template <class T>
void_t
CxFlags<T>::clear()
{
    _m_mFlags = 0;
}
//------------------------------------------------------------------------------        
template <class T>
bool_t 
CxFlags<T>::isSetFlag(
    const T &a_value
) const
{
    return (_m_mFlags & a_value) == a_value;
}
//------------------------------------------------------------------------------        
template <class T>
bool_t 
CxFlags<T>::isSetAnyFlag(
    const T &a_value
) const
{
    return (_m_mFlags & a_value) != 0;
}
//------------------------------------------------------------------------------  
template <class T>
void_t 
CxFlags<T>::setFlag(
    const T &a_value
)
{
    _m_mFlags |= a_value;
}
//------------------------------------------------------------------------------        
template <class T>
void_t 
CxFlags<T>::unsetFlag(
    const T &a_value
)
{
    _m_mFlags &= ~a_value;
}

//------------------------------------------------------------------------------        
template <class T>
void
CxFlags<T>::toggleFlag(
    const T &a_value
)
{
    _m_mFlags ^= a_value;
}
//------------------------------------------------------------------------------        

xNAMESPACE_END(NxLib)
