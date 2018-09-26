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
static Types<MsgBox::ModalResult, ssize_t, 10> modalResults =
{{
#if   xENV_WIN
    {MsgBox::ModalResult::mrUnknown,  - 1},
    {MsgBox::ModalResult::mrOk,       IDOK},
    {MsgBox::ModalResult::mrYes,      IDYES},
    {MsgBox::ModalResult::mrNo,       IDNO},
    {MsgBox::ModalResult::mrAbort,    IDABORT},
    {MsgBox::ModalResult::mrCancel,   IDCANCEL},
    {MsgBox::ModalResult::mrContinue, IDCONTINUE},
    {MsgBox::ModalResult::mrIgnore,   IDIGNORE},
    {MsgBox::ModalResult::mrRetry,    IDRETRY},
    {MsgBox::ModalResult::mrTryAgain, IDTRYAGAIN}
#elif xENV_UNIX
    {MsgBox::ModalResult::mrUnknown,  - 1},
    {MsgBox::ModalResult::mrOk,       0},
    {MsgBox::ModalResult::mrYes,      1},
    {MsgBox::ModalResult::mrNo,       2},
    {MsgBox::ModalResult::mrAbort,    3},
    {MsgBox::ModalResult::mrCancel,   4},
    {MsgBox::ModalResult::mrContinue, 5},
    {MsgBox::ModalResult::mrIgnore,   6},
    {MsgBox::ModalResult::mrRetry,    7},
    {MsgBox::ModalResult::mrTryAgain, 8}
#elif xENV_APPLE
    {MsgBox::ModalResult::mrUnknown,  - 1},
    {MsgBox::ModalResult::mrOk,       0},
    {MsgBox::ModalResult::mrYes,      1},
    {MsgBox::ModalResult::mrNo,       2},
    {MsgBox::ModalResult::mrAbort,    3},
    {MsgBox::ModalResult::mrCancel,   4},
    {MsgBox::ModalResult::mrContinue, 5},
    {MsgBox::ModalResult::mrIgnore,   6},
    {MsgBox::ModalResult::mrRetry,    7},
    {MsgBox::ModalResult::mrTryAgain, 8}
#endif
}};
//-------------------------------------------------------------------------------------------------
static Types<MsgBox::Type, ssize_t, 8> types =
{{
#if   xENV_WIN
    {MsgBox::Type::tpUnknown,           - 1},
    {MsgBox::Type::tpOk,                MB_OK},
    {MsgBox::Type::tpOkCancel,          MB_OKCANCEL},
    {MsgBox::Type::tpYesNo,             MB_YESNO},
    {MsgBox::Type::tpRetryCancel,       MB_RETRYCANCEL},
    {MsgBox::Type::tpYesNoCancel,       MB_YESNOCANCEL},
    {MsgBox::Type::tpAbortRetryIgnore,  MB_ABORTRETRYIGNORE},
    {MsgBox::Type::tpCancelTryContinue, MB_CANCELTRYCONTINUE}
#elif xENV_UNIX
    {MsgBox::Type::tpUnknown,           - 1},
    {MsgBox::Type::tpOk,                0},
    {MsgBox::Type::tpOkCancel,          1},
    {MsgBox::Type::tpYesNo,             2},
    {MsgBox::Type::tpRetryCancel,       3},
    {MsgBox::Type::tpYesNoCancel,       4},
    {MsgBox::Type::tpAbortRetryIgnore,  5},
    {MsgBox::Type::tpCancelTryContinue, 6}
#elif xENV_APPLE
    {MsgBox::Type::tpUnknown,           - 1},
    {MsgBox::Type::tpOk,                0},
    {MsgBox::Type::tpOkCancel,          1},
    {MsgBox::Type::tpYesNo,             2},
    {MsgBox::Type::tpRetryCancel,       3},
    {MsgBox::Type::tpYesNoCancel,       4},
    {MsgBox::Type::tpAbortRetryIgnore,  5},
    {MsgBox::Type::tpCancelTryContinue, 6}
#endif
}};
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END3(xl, internal, enums)
