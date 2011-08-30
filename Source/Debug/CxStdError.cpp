/**
 * \file  CxStdError.cpp
 * \brief standard C library last error
 */


#include <xLib/Debug/CxStdError.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
INT
CxStdError::iGet() {
    /*DEBUG*/// n/a

    INT iCode = 0; /*= ciCodeSuccess*/;

    iCode = errno;

    bReset();
    /*DEBUG*/// n/a

    return iCode;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxStdError::sGet() {
    /*DEBUG*/

    return sFormat(iGet());
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxStdError::bSet(
    const INT ciCode
)
{
    /*DEBUG*/// iCode - n/a

    errno = ciCode;

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxStdError::bReset() {
    /*DEBUG*/// n/a

    const INT ciCodeSuccess = 0;

    return bSet(ciCodeSuccess);
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxStdError::sFormat(
    const INT ciCode
)
{
    /*DEBUG*/// iCode - n/a

    return CxString::sFormat(xT("%i - %s"), ciCode, strerror(ciCode));
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxStdError::CxStdError() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*virtual*/
CxStdError::~CxStdError() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
