/**
 * \file  CxMsgBox_internal.inl
 * \brief
 */


#include <xLib/Internal/xInternal.h>


/**************************************************************************************************
*    public
*
**************************************************************************************************/

xNAMESPACE_BEGIN(xlib)

//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(internal, enums)

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


static Types<CxMsgBox::ExType, ssize_t, 8> types =
{{
#if   xOS_ENV_WIN
    {CxMsgBox::tpUnknown,           - 1},
    {CxMsgBox::tpOk,                MB_OK},
    {CxMsgBox::tpOkCancel,          MB_OKCANCEL},
    {CxMsgBox::tpYesNo,             MB_YESNO},
    {CxMsgBox::tpRetryCancel,       MB_RETRYCANCEL},
    {CxMsgBox::tpYesNoCancel,       MB_YESNOCANCEL},
    {CxMsgBox::tpAbortRetryIgnore,  MB_ABORTRETRYIGNORE},
    {CxMsgBox::tpCancelTryContinue, MB_CANCELTRYCONTINUE}
#elif xOS_ENV_UNIX
    {CxMsgBox::tpUnknown,           - 1},
    {CxMsgBox::tpOk,                0},
    {CxMsgBox::tpOkCancel,          1},
    {CxMsgBox::tpYesNo,             2},
    {CxMsgBox::tpRetryCancel,       3},
    {CxMsgBox::tpYesNoCancel,       4},
    {CxMsgBox::tpAbortRetryIgnore,  5},
    {CxMsgBox::tpCancelTryContinue, 6}
#elif xOS_ENV_MAC
    {CxMsgBox::tpUnknown,           - 1},
    {CxMsgBox::tpOk,                0},
    {CxMsgBox::tpOkCancel,          1},
    {CxMsgBox::tpYesNo,             2},
    {CxMsgBox::tpRetryCancel,       3},
    {CxMsgBox::tpYesNoCancel,       4},
    {CxMsgBox::tpAbortRetryIgnore,  5},
    {CxMsgBox::tpCancelTryContinue, 6}
#endif
}};

xNAMESPACE2_END(internal, enums)
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(xlib)
