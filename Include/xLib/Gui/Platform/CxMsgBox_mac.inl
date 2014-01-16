/**
 * \file  CxMsgBox.inl
 * \brief message box
 */


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxMsgBox::ExModalResult
CxMsgBox::show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
    ExModalResult mrRv = mrAbort;

    NSString *btnDefault = nil;
    NSString *btnAlt     = nil;
    NSString *btnOther   = nil;

    switch(a_type)
    {
    default:
    case tpOk:
        btnDefault = @"Ok";
        break;
    case tpOkCancel:
        btnDefault = @"Ok";
        btnAlt     = @"Cancel";
        break;
    case tpYesNo:
        btnDefault = @"Yes";
        btnAlt     = @"No";
        break;
    case tpRetryCancel:
        btnDefault = @"Retry";
        btnAlt     = @"Cancel";
        break;
    case tpYesNoCancel:
        btnDefault = @"Yes";
        btnAlt     = @"No";
        btnOther   = @"Cancel";
        break;
    case tpAbortRetryIgnore:
        btnDefault = @"Abort";
        btnAlt     = @"Retry";
        btnOther   = @"Ignore";
        break;
    case tpCancelTryContinue:
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
        case tpOk:
        case tpOkCancel:
            mrRv = mrOk;
            break;
        case tpYesNo:
        case tpYesNoCancel:
            mrRv = mrYes;
            break;
        case tpRetryCancel:
            mrRv = mrRetry;
            break;
        case tpAbortRetryIgnore:
            mrRv = mrAbort;
            break;
        case tpCancelTryContinue:
            mrRv = mrCancel;
            break;
        }
    }
    else if (iRv == NSAlertAlternateReturn) {
        switch(a_type) {
        case tpOkCancel:
        case tpRetryCancel:
            mrRv = mrCancel;
            break;
        case tpYesNo:
        case tpYesNoCancel:
            mrRv = mrNo;
            break;
        case tpAbortRetryIgnore:
            mrRv = mrRetry;
            break;
        case tpCancelTryContinue:
            mrRv = mrTryAgain;
            break;
        }
    }
    else if (iRv == NSAlertOtherReturn) {
        switch(a_type) {
        case tpYesNoCancel:
            mrRv = mrCancel;
            break;
        case tpAbortRetryIgnore:
            mrRv = mrIgnore;
            break;
        case tpCancelTryContinue:
            mrRv = mrContinue;
            break;
        }
    }

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
