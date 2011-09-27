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
    INT iCode = 0; /*= ciCodeSuccess*/;

    iCode = errno;

    (VOID)bReset();

    return iCode;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxStdError::sGet() {
    return sFormat(iGet());
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxStdError::bSet(
    const INT ciCode
)
{
    errno = ciCode;

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxStdError::bReset() {
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
    CHAR szBuff[64 + 1] = {0};

    const TCHAR *pcszError = strerror_r(ciCode, &szBuff[0], xARRAY_SIZE(szBuff));

    return CxString::sFormat(xT("%i - %s"), ciCode, pcszError);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxStdError::CxStdError() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxStdError::~CxStdError() {

}
//---------------------------------------------------------------------------
