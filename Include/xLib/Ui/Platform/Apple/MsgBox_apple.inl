/**
 * \file   MsgBox.inl
 * \brief  message box
 */


namespace xl::ui
{

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
MsgBox::ModalResult
MsgBox::_show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cType            a_type    /* = Ok */
) const
{
    ModalResult mrRv = ModalResult::Abort;

    NSString *btnDefault = nil;
    NSString *btnAlt     = nil;
    NSString *btnOther   = nil;

    switch(a_type) {
    default:
    case ModalResult::Ok:
        btnDefault = @"Ok";
        break;
    case ModalResult::OkCancel:
        btnDefault = @"Ok";
        btnAlt     = @"Cancel";
        break;
    case ModalResult::ModalResult::YesNo:
        btnDefault = @"Yes";
        btnAlt     = @"No";
        break;
    case ModalResult::RetryCancel:
        btnDefault = @"Retry";
        btnAlt     = @"Cancel";
        break;
    case ModalResult::YesNoCancel:
        btnDefault = @"Yes";
        btnAlt     = @"No";
        btnOther   = @"Cancel";
        break;
    case ModalResult::AbortRetryIgnore:
        btnDefault = @"Abort";
        btnAlt     = @"Retry";
        btnOther   = @"Ignore";
        break;
    case ModalResult::CancelTryContinue:
        btnDefault = @"Cancel";
        btnAlt     = @"Try Again";
        btnOther   = @"Continue";
        break;
    }

    NSAlert *alert = [NSAlert alertWithMessageText:[NSString stringWithCString:title.c_str()
                        encoding:[NSString defaultCStringEncoding]]
                        defaultButton:btnDefault
                        alternateButton:btnAlt
                        otherButton:btnOther
                        informativeTextWithFormat:@"%s", msg.c_str()];

    // brings this 'application' to the front.
    [[NSRunningApplication currentApplication] activateWithOptions:NSApplicationActivateIgnoringOtherApps];
    NSInteger iRv = [alert runModal];

    // Convert the NSAlert return values into my MB_* return values.
    if (iRv == NSAlertDefaultReturn) {
        switch (a_type) {
        case ModalResult::Ok:
        case ModalResult::OkCancel:
            mrRv = Ok;
            break;
        case ModalResult::YesNo:
        case ModalResult::YesNoCancel:
            mrRv = Yes;
            break;
        case ModalResult::RetryCancel:
            mrRv = Retry;
            break;
        case ModalResult::AbortRetryIgnore:
            mrRv = Abort;
            break;
        case ModalResult::CancelTryContinue:
            mrRv = Cancel;
            break;
        }
    }
    else if (iRv == NSAlertAlternateReturn) {
        switch(a_type) {
        case ModalResult::OkCancel:
        case ModalResult::RetryCancel:
            mrRv = Cancel;
            break;
        case ModalResult::YesNo:
        case ModalResult::YesNoCancel:
            mrRv = No;
            break;
        case ModalResult::AbortRetryIgnore:
            mrRv = Retry;
            break;
        case ModalResult::CancelTryContinue:
            mrRv = TryAgain;
            break;
        }
    }
    else if (iRv == NSAlertOtherReturn) {
        switch(a_type) {
        case ModalResult::YesNoCancel:
            mrRv = Cancel;
            break;
        case ModalResult::AbortRetryIgnore:
            mrRv = Ignore;
            break;
        case ModalResult::CancelTryContinue:
            mrRv = Continue;
            break;
        }
    }

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
