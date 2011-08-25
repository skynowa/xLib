/**
 * \file   CxException.inl
 * \brief  CxException (exception)
 * \author skynowa <skynowa@gmail.com>
 * \date   01.02.2011
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
