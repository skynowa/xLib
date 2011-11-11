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
    _m_sMsg()
{
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*virtual*/
CxException::~CxException() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
const std::string_t &
CxException::sGetWhat() const {
    /*DEBUG*/

    return _m_sMsg;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
