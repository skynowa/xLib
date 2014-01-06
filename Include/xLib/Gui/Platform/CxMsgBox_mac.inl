/**
 * \file  CxMsgBox.inl
 * \brief message box
 */


#include <xLib/Core/CxString.h>
#include <xLib/System/CxConsole.h>
#include <xLib/Filesystem/CxPath.h>


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

    // int msgbox(string msg, string title, int buttons)

    enum ExButtons
    {
        MB_OK,
        MB_OKCANCEL,
        MB_YESNO,
        MB_RETRYCANCEL,
        MB_YESNOCANCEL,
        MB_ABORTRETRYIGNORE,
        MB_CANCELTRYCONTINUE,
        MB_CANCEL,
        MB_YES,
        MB_NO,
        MB_RETRY,
        MB_IGNORE,
        MB_TRYAGAIN,
        MB_CONTINUE,
        MB_ABORT,
    };

    NSString *defbutton   = nil;
    NSString *altbutton   = nil;
    NSString *otherbutton = nil;

    switch(a_type)
    {
    default:
    case MB_OK:
        defbutton = @"Ok";
        break;
    case MB_OKCANCEL:
        defbutton = @"Ok";
        altbutton = @"Cancel";
        break;
    case MB_RETRYCANCEL:
        defbutton = @"Retry";
        altbutton = @"Cancel";
        break;
    case MB_YESNO:
        defbutton = @"Yes";
        altbutton = @"No";
        break;
    case MB_YESNOCANCEL:
        defbutton = @"Yes";
        altbutton = @"No";
        otherbutton = @"Cancel";
        break;
    case MB_ABORTRETRYIGNORE:
        defbutton = @"Abort";
        altbutton = @"Retry";
        otherbutton = @"Ignore";
        break;
    case MB_CANCELTRYCONTINUE:
        defbutton = @"Cancel";
        altbutton = @"Try Again";
        otherbutton = @"Continue";
        break;
    }

    NSAlert *alert = [NSAlert alertWithMessageText:[NSString stringWithCString:title.c_str()
                        encoding:[NSString defaultCStringEncoding]]
                        defaultButton:defbutton
                        alternateButton:altbutton
                        otherButton:otherbutton
                        informativeTextWithFormat:@"%s", msg.c_str()];

    // brings this 'application' to the front.
    [[NSRunningApplication currentApplication] activateWithOptions:NSApplicationActivateIgnoringOtherApps];
    NSInteger iRv = [alert runModal];

    // Convert the NSAlert return values into my MB_* return values.
    if (iRv == NSAlertDefaultReturn) {
        switch (a_type) {
        case MB_OK:
        case MB_OKCANCEL:
            mrRv = MB_OK;
            break;
        case MB_YESNO:
        case MB_YESNOCANCEL:
            mrRv = MB_YES;
            break;
        case MB_ABORTRETRYIGNORE:
            mrRv = MB_ABORT;
            break;
        case MB_CANCELTRYCONTINUE:
            mrRv = MB_CANCEL;
            break;
        case MB_RETRYCANCEL:
            mrRv = MB_RETRY;
            break;
        }
    }
    else if (iRv == NSAlertAlternateReturn) {
        switch(a_type) {
        case MB_OKCANCEL:
        case MB_RETRYCANCEL:
            mrRv = MB_CANCEL;
            break;
        case MB_YESNO:
        case MB_YESNOCANCEL:
            mrRv = MB_NO;
            break;
        case MB_ABORTRETRYIGNORE:
            mrRv = MB_RETRY;
            break;
        case MB_CANCELTRYCONTINUE:
            mrRv = MB_TRYAGAIN;
            break;
        }
    }
    else if (iRv == NSAlertOtherReturn) {
        switch(a_type) {
        case MB_YESNOCANCEL:
            mrRv = MB_CANCEL;
            break;
        case MB_ABORTRETRYIGNORE:
            mrRv = MB_IGNORE;
            break;
        case MB_CANCELTRYCONTINUE:
            mrRv = MB_CONTINUE;
            break;
        }
    }

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
