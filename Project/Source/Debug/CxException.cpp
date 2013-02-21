/**
 * \file  CxException.cpp
 * \brief CxException (exception)
 */


#include <xLib/Debug/CxException.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxException::CxException() :
    _m_sMessage()
{
    xTESTS_NA;
}
//------------------------------------------------------------------------------
/* virtual */
CxException::~CxException() {
    xTESTS_NA;
}
//------------------------------------------------------------------------------
const std::tstring_t &
CxException::what() const {
    xTESTS_NA;

    return _m_sMessage;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
