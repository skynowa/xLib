/**
 * \file  CxException.inl
 * \brief CxException (exception)
 */


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<class T>
CxException &
CxException::operator << (
    const T &a_cMessageT
)
{
    _m_sMessage.append( CxString::string_cast(a_cMessageT) );

    return *this;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
