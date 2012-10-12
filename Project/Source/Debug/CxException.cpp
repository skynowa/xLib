/**
 * \file  CxException.cpp
 * \brief CxException (exception)
 */


#include <xLib/Debug/CxException.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxException::CxException() :
    _m_sMessage()
{
    xDEBUG_VARS_NA;
}
//---------------------------------------------------------------------------
/* virtual */
CxException::~CxException() {
    xDEBUG_VARS_NA;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxException::sWhat() const {
    xDEBUG_VARS_NA;

    return _m_sMessage;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
