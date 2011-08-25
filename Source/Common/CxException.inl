/**
 * \file  CxException.inl
 * \brief CxException (exception)
 */


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<class T>
CxException &
CxException::operator << (
    const T &cMessageT
)
{
    _m_sMsg.assign( CxString::lexical_cast(cMessageT) );

    return *this;
}
//---------------------------------------------------------------------------
