/**
 * \file  CxMsgBox.inl
 * \brief message box
 */


#include <xLib/Core/CxString.h>
#include <xLib/System/CxConsole.h>
#include <xLib/Filesystem/CxPath.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

CxMsgBox::ExModalResult
CxMsgBox::show(
    const HWND      &a_parentWnd,
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cuint_t         &a_type
) const
{
    ExModalResult mrRes = mrAbort;

    mrRes = static_cast<ExModalResult>( ::MessageBox(a_parentWnd, a_text.c_str(), a_title.c_str(),
        a_type) );

    return mrRes;
}

#endif
//-------------------------------------------------------------------------------------------------
CxMsgBox::ExModalResult
CxMsgBox::show(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
    ExModalResult mrRes = mrAbort;
    std::string   title = a_title;

    // title
    if ( title.empty() ) {
        title = CxPath(CxPath::exe()).fileName();
    }

#if   xOS_ENV_WIN
    UINT type = MB_OK;
    {
        switch (a_type) {
        case tpOk:
        default:
            type = MB_OK;
            break;
        case tpAbortRetryIgnore:
            type = MB_ABORTRETRYIGNORE | MB_ICONSTOP;
            break;
        }
    }

    mrRes = static_cast<ExModalResult>( ::MessageBox(NULL, a_text.c_str(), title.c_str(), a_type) );
#elif xOS_ENV_UNIX
    #if xHAVE_XMESSAGE
        std::tstring_t type = xT("Ok");
        {
            switch (a_type) {
            case tpOk:
            default:
                type = xT("Ok");
                break;
            case tpAbortRetryIgnore:
                type = xT("Abort, Ignore, Retry");
                break;
            }
        }

        std::ctstring_t msg = CxString::format(
            xT("xmessage -center \"%s\" -title \"%s\" -buttons \"%s\""),
            a_text.c_str(), title.c_str(), type.c_str());

        mrRes = static_cast<ExModalResult>( xTSYSTEM(msg.c_str()) );
    #else
        #pragma message("xLib: CxMsgBox::show() - n/a")
        mrRes = mrUnknown;
    #endif
#elif xOS_ENV_MAC
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

    switch(buttons)
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
    NSInteger retval = [alert runModal];

    // Convert the NSAlert return values into my MB_* return values.
    if (retval == NSAlertDefaultReturn) {
        switch (buttons) {
        case MB_OK:
        case MB_OKCANCEL:
            return MB_OK;
        case MB_YESNO:
        case MB_YESNOCANCEL:
            return MB_YES;
        case MB_ABORTRETRYIGNORE:
            return MB_ABORT;
        case MB_CANCELTRYCONTINUE:
            return MB_CANCEL;
        case MB_RETRYCANCEL:
            return MB_RETRY;
        }
    }
    else if (retval == NSAlertAlternateReturn) {
        switch(buttons) {
        case MB_OKCANCEL:
        case MB_RETRYCANCEL:
            return MB_CANCEL;
        case MB_YESNO:
        case MB_YESNOCANCEL:
            return MB_NO;
        case MB_ABORTRETRYIGNORE:
            return MB_RETRY;
        case MB_CANCELTRYCONTINUE:
            return MB_TRYAGAIN;
        }
    }
    else if (retval == NSAlertOtherReturn) {
        switch(buttons) {
        case MB_YESNOCANCEL:
            return MB_CANCEL;
        case MB_ABORTRETRYIGNORE:
            return MB_IGNORE;
        case MB_CANCELTRYCONTINUE:
            return MB_CONTINUE;
        }
    }

    return NULL;
#endif

    return mrRes;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
