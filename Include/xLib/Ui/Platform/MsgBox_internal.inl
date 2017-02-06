/**
 * \file   MsgBox_internal.inl
 * \brief  message box (for internal use)
 */


#include <xLib/Internal/Internal.h>


/**************************************************************************************************
*    public
*
**************************************************************************************************/

xNAMESPACE_BEGIN3(xl, internal, enums)

//-------------------------------------------------------------------------------------------------
static Types<MsgBox::ExModalResult, ssize_t, 10> modalResults =
{{
#if   xENV_WIN
    {MsgBox::mrUnknown,  - 1},
    {MsgBox::mrOk,       IDOK},
    {MsgBox::mrYes,      IDYES},
    {MsgBox::mrNo,       IDNO},
    {MsgBox::mrAbort,    IDABORT},
    {MsgBox::mrCancel,   IDCANCEL},
    {MsgBox::mrContinue, IDCONTINUE},
    {MsgBox::mrIgnore,   IDIGNORE},
    {MsgBox::mrRetry,    IDRETRY},
    {MsgBox::mrTryAgain, IDTRYAGAIN}
#elif xENV_UNIX
    {MsgBox::mrUnknown,  - 1},
    {MsgBox::mrOk,       0},
    {MsgBox::mrYes,      1},
    {MsgBox::mrNo,       2},
    {MsgBox::mrAbort,    3},
    {MsgBox::mrCancel,   4},
    {MsgBox::mrContinue, 5},
    {MsgBox::mrIgnore,   6},
    {MsgBox::mrRetry,    7},
    {MsgBox::mrTryAgain, 8}
#elif xENV_APPLE
    {MsgBox::mrUnknown,  - 1},
    {MsgBox::mrOk,       0},
    {MsgBox::mrYes,      1},
    {MsgBox::mrNo,       2},
    {MsgBox::mrAbort,    3},
    {MsgBox::mrCancel,   4},
    {MsgBox::mrContinue, 5},
    {MsgBox::mrIgnore,   6},
    {MsgBox::mrRetry,    7},
    {MsgBox::mrTryAgain, 8}
#endif
}};
//-------------------------------------------------------------------------------------------------
static Types<MsgBox::ExType, ssize_t, 8> types =
{{
#if   xENV_WIN
    {MsgBox::tpUnknown,           - 1},
    {MsgBox::tpOk,                MB_OK},
    {MsgBox::tpOkCancel,          MB_OKCANCEL},
    {MsgBox::tpYesNo,             MB_YESNO},
    {MsgBox::tpRetryCancel,       MB_RETRYCANCEL},
    {MsgBox::tpYesNoCancel,       MB_YESNOCANCEL},
    {MsgBox::tpAbortRetryIgnore,  MB_ABORTRETRYIGNORE},
    {MsgBox::tpCancelTryContinue, MB_CANCELTRYCONTINUE}
#elif xENV_UNIX
    {MsgBox::tpUnknown,           - 1},
    {MsgBox::tpOk,                0},
    {MsgBox::tpOkCancel,          1},
    {MsgBox::tpYesNo,             2},
    {MsgBox::tpRetryCancel,       3},
    {MsgBox::tpYesNoCancel,       4},
    {MsgBox::tpAbortRetryIgnore,  5},
    {MsgBox::tpCancelTryContinue, 6}
#elif xENV_APPLE
    {MsgBox::tpUnknown,           - 1},
    {MsgBox::tpOk,                0},
    {MsgBox::tpOkCancel,          1},
    {MsgBox::tpYesNo,             2},
    {MsgBox::tpRetryCancel,       3},
    {MsgBox::tpYesNoCancel,       4},
    {MsgBox::tpAbortRetryIgnore,  5},
    {MsgBox::tpCancelTryContinue, 6}
#endif
}};
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END3(xl, internal, enums)
