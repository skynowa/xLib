/**
 * \file   MsgBox.inl
 * \brief  message box
 */


xNAMESPACE_BEGIN2(xl, ui)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
MsgBox::ModalResult
MsgBox::_show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cType           &a_type    /* = tpOk */
) const
{
    ModalResult mrRv = ModalResult::mrAbort;

    NSString *btnDefault = nil;
    NSString *btnAlt     = nil;
    NSString *btnOther   = nil;

    switch(a_type) {
    default:
    case ModalResult::tpOk:
        btnDefault = @"Ok";
        break;
    case ModalResult::tpOkCancel:
        btnDefault = @"Ok";
        btnAlt     = @"Cancel";
        break;
    case ModalResult::ModalResult::tpYesNo:
        btnDefault = @"Yes";
        btnAlt     = @"No";
        break;
    case ModalResult::tpRetryCancel:
        btnDefault = @"Retry";
        btnAlt     = @"Cancel";
        break;
    case ModalResult::tpYesNoCancel:
        btnDefault = @"Yes";
        btnAlt     = @"No";
        btnOther   = @"Cancel";
        break;
    case ModalResult::tpAbortRetryIgnore:
        btnDefault = @"Abort";
        btnAlt     = @"Retry";
        btnOther   = @"Ignore";
        break;
    case ModalResult::tpCancelTryContinue:
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
        case ModalResult::tpOk:
        case ModalResult::tpOkCancel:
            mrRv = mrOk;
            break;
        case ModalResult::tpYesNo:
        case ModalResult::tpYesNoCancel:
            mrRv = mrYes;
            break;
        case ModalResult::tpRetryCancel:
            mrRv = mrRetry;
            break;
        case ModalResult::tpAbortRetryIgnore:
            mrRv = mrAbort;
            break;
        case ModalResult::tpCancelTryContinue:
            mrRv = mrCancel;
            break;
        }
    }
    else if (iRv == NSAlertAlternateReturn) {
        switch(a_type) {
        case ModalResult::tpOkCancel:
        case ModalResult::tpRetryCancel:
            mrRv = mrCancel;
            break;
        case ModalResult::tpYesNo:
        case ModalResult::tpYesNoCancel:
            mrRv = mrNo;
            break;
        case ModalResult::tpAbortRetryIgnore:
            mrRv = mrRetry;
            break;
        case ModalResult::tpCancelTryContinue:
            mrRv = mrTryAgain;
            break;
        }
    }
    else if (iRv == NSAlertOtherReturn) {
        switch(a_type) {
        case ModalResult::tpYesNoCancel:
            mrRv = mrCancel;
            break;
        case ModalResult::tpAbortRetryIgnore:
            mrRv = mrIgnore;
            break;
        case ModalResult::tpCancelTryContinue:
            mrRv = mrContinue;
            break;
        }
    }

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, ui)
