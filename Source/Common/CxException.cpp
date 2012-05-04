/**
 * \file  CxException.cpp
 * \brief CxException (exception)
 */


#include <xLib/Common/CxException.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxException::CxException() :
    _m_sMessage()
{
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*virtual*/
CxException::~CxException() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxException::sGetWhat() const {
    /*DEBUG*/

    return _m_sMessage;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
