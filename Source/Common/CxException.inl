/****************************************************************************
* Class name:  CxException
* Description: exception
* File name:   CxException.inl
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     17.06.2011
*
*****************************************************************************/


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: operator << (set message)
template<class T>
CxException &
CxException::operator << (
    const T &cValueT
)
{
    _m_sMsg.assign( CxString::lexical_cast(cValueT) );

    return *this;
}
//---------------------------------------------------------------------------
