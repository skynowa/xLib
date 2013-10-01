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
    const CxFlags &a_cfValues
) : 
    _m_mFlags(a_cfValues._m_mFlags)
{
}
//------------------------------------------------------------------------------
template <class T>
CxFlags<T>::CxFlags(
    const T &a_valuesT
) :
    _m_mFlags(a_valuesT)
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
    const CxFlags &a_cfValues
)
{
    xCHECK_RET(this == &a_cfValues, *this);

    _m_mFlags = a_cfValues._m_mFlags;

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
    const T &a_valuesT
)
{
    _m_mFlags = a_valuesT; 
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
    const T &a_valueT
) const
{
    return (_m_mFlags & a_valueT) == a_valueT;
}
//------------------------------------------------------------------------------        
template <class T>
bool_t 
CxFlags<T>::isSetAnyFlag(
    const T &a_valueT
) const
{
    return (_m_mFlags & a_valueT) != 0;
}
//------------------------------------------------------------------------------  
template <class T>
void_t 
CxFlags<T>::setFlag(
    const T &a_valueT
)
{
    _m_mFlags |= a_valueT;
}
//------------------------------------------------------------------------------        
template <class T>
void_t 
CxFlags<T>::unsetFlag(
    const T &a_valueT
)
{
    _m_mFlags &= ~a_valueT;
}

//------------------------------------------------------------------------------        
template <class T>
void
CxFlags<T>::toggleFlag(
    const T &a_valueT
)
{
    _m_mFlags ^= a_valueT;
}
//------------------------------------------------------------------------------        

xNAMESPACE_END(NxLib)
