/**
 * \file  CxMsgBox_internal.inl
 * \brief
 */


#include <xLib/Internal/xInternal.h>


/**************************************************************************************************
*    public
*
**************************************************************************************************/

xNAMESPACE_BEGIN(NxLib)

//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(NxInternal, NxEnum)

static Types<CxMsgBox::ExModalResult, ssize_t, 10> modalResults =
{{
#if   xOS_ENV_WIN
    {CxMsgBox::mrUnknown,  - 1},
    {CxMsgBox::mrOk,       IDOK},
    {CxMsgBox::mrYes,      IDYES},
    {CxMsgBox::mrNo,       IDNO},
    {CxMsgBox::mrAbort,    IDABORT},
    {CxMsgBox::mrCancel,   IDCANCEL},
    {CxMsgBox::mrContinue, IDCONTINUE},
    {CxMsgBox::mrIgnore,   IDIGNORE},
    {CxMsgBox::mrRetry,    IDRETRY},
    {CxMsgBox::mrTryAgain, IDTRYAGAIN}
#elif xOS_ENV_UNIX
    {CxMsgBox::mrUnknown,  - 1},
    {CxMsgBox::mrOk,       0},
    {CxMsgBox::mrYes,      1},
    {CxMsgBox::mrNo,       2},
    {CxMsgBox::mrAbort,    3},
    {CxMsgBox::mrCancel,   4},
    {CxMsgBox::mrContinue, 5},
    {CxMsgBox::mrIgnore,   6},
    {CxMsgBox::mrRetry,    7},
    {CxMsgBox::mrTryAgain, 8}
#elif xOS_ENV_MAC
    {CxMsgBox::mrUnknown,  - 1},
    {CxMsgBox::mrOk,       0},
    {CxMsgBox::mrYes,      1},
    {CxMsgBox::mrNo,       2},
    {CxMsgBox::mrAbort,    3},
    {CxMsgBox::mrCancel,   4},
    {CxMsgBox::mrContinue, 5},
    {CxMsgBox::mrIgnore,   6},
    {CxMsgBox::mrRetry,    7},
    {CxMsgBox::mrTryAgain, 8}
#endif
}};

xNAMESPACE2_END(NxInternal, NxEnum)
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
