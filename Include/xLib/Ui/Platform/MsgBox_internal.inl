/**
 * \file   MsgBox_internal.inl
 * \brief  message box (for internal use)
 */


#include <xLib/Internal/Internal.h>


/**************************************************************************************************
*    public
*
**************************************************************************************************/

namespace xl::internal::enums
{

//-------------------------------------------------------------------------------------------------
static Types<MsgBox::ModalResult, std::ssize_t, 10> modalResults =
{{
#if   xENV_WIN
    {MsgBox::ModalResult::Unknown,  - 1},
    {MsgBox::ModalResult::Ok,       IDOK},
    {MsgBox::ModalResult::Yes,      IDYES},
    {MsgBox::ModalResult::No,       IDNO},
    {MsgBox::ModalResult::Abort,    IDABORT},
    {MsgBox::ModalResult::Cancel,   IDCANCEL},
    {MsgBox::ModalResult::Continue, IDCONTINUE},
    {MsgBox::ModalResult::Ignore,   IDIGNORE},
    {MsgBox::ModalResult::Retry,    IDRETRY},
    {MsgBox::ModalResult::TryAgain, IDTRYAGAIN}
#elif xENV_UNIX
    {MsgBox::ModalResult::Unknown,  - 1},
    {MsgBox::ModalResult::Ok,       0},
    {MsgBox::ModalResult::Yes,      1},
    {MsgBox::ModalResult::No,       2},
    {MsgBox::ModalResult::Abort,    3},
    {MsgBox::ModalResult::Cancel,   4},
    {MsgBox::ModalResult::Continue, 5},
    {MsgBox::ModalResult::Ignore,   6},
    {MsgBox::ModalResult::Retry,    7},
    {MsgBox::ModalResult::TryAgain, 8}
#elif xENV_APPLE
    {MsgBox::ModalResult::Unknown,  - 1},
    {MsgBox::ModalResult::Ok,       0},
    {MsgBox::ModalResult::Yes,      1},
    {MsgBox::ModalResult::No,       2},
    {MsgBox::ModalResult::Abort,    3},
    {MsgBox::ModalResult::Cancel,   4},
    {MsgBox::ModalResult::Continue, 5},
    {MsgBox::ModalResult::Ignore,   6},
    {MsgBox::ModalResult::Retry,    7},
    {MsgBox::ModalResult::TryAgain, 8}
#endif
}};
//-------------------------------------------------------------------------------------------------
static Types<MsgBox::Type, std::ssize_t, 8> types =
{{
#if   xENV_WIN
    {MsgBox::Type::Unknown,           - 1},
    {MsgBox::Type::Ok,                MB_OK},
    {MsgBox::Type::OkCancel,          MB_OKCANCEL},
    {MsgBox::Type::YesNo,             MB_YESNO},
    {MsgBox::Type::RetryCancel,       MB_RETRYCANCEL},
    {MsgBox::Type::YesNoCancel,       MB_YESNOCANCEL},
    {MsgBox::Type::AbortRetryIgnore,  MB_ABORTRETRYIGNORE},
    {MsgBox::Type::CancelTryContinue, MB_CANCELTRYCONTINUE}
#elif xENV_UNIX
    {MsgBox::Type::Unknown,           - 1},
    {MsgBox::Type::Ok,                0},
    {MsgBox::Type::OkCancel,          1},
    {MsgBox::Type::YesNo,             2},
    {MsgBox::Type::RetryCancel,       3},
    {MsgBox::Type::YesNoCancel,       4},
    {MsgBox::Type::AbortRetryIgnore,  5},
    {MsgBox::Type::CancelTryContinue, 6}
#elif xENV_APPLE
    {MsgBox::Type::Unknown,           - 1},
    {MsgBox::Type::Ok,                0},
    {MsgBox::Type::OkCancel,          1},
    {MsgBox::Type::YesNo,             2},
    {MsgBox::Type::RetryCancel,       3},
    {MsgBox::Type::YesNoCancel,       4},
    {MsgBox::Type::AbortRetryIgnore,  5},
    {MsgBox::Type::CancelTryContinue, 6}
#endif
}};
//-------------------------------------------------------------------------------------------------

} // namespace
