/**
 * \file  CxMsgBox.inl
 * \brief message box
 */


#include <xLib/Core/CxString.h>
#include <xLib/System/CxConsole.h>
#include <xLib/Filesystem/CxPath.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

std::ctstring_t
xlib_errorFormat
(
    Display *a_display,
    cint_t  &a_code
)
{
    std::tstring_t sRv;
    tchar_t        buff[1024 + 1] = {0};

    int_t iRv = ::XGetErrorText(a_display, a_code, buff, sizeof(buff) - 1);
    xUNUSED(iRv);
    // xTEST_DIFF(iRv, 0);

    sRv.assign(buff);

    return sRv;
}

int
xlib_errorHandler(
    Display     *a_display,
    XErrorEvent *a_errorEvent
)
{
    CxTrace() << "XLIB error: " << ::xlib_errorFormat(a_display, a_errorEvent->error_code);

    return 0;
}

xNAMESPACE_ANONYM_END
//-------------------------------------------------------------------------------------------------
inline CxMsgBox::ExModalResult
CxMsgBox::show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
    xUNUSED(a_type);

    ExModalResult mrRv = mrUnknown;

#if xHAVE_X11
    int_t iRv = - 1;    xUNUSED(iRv);

    std::ctstring_t btnUnknown  = xT("");
    std::ctstring_t btnOk       = xT("OK");
    std::ctstring_t btnYes      = xT("Yes");
    std::ctstring_t btnNo       = xT("No");
    std::ctstring_t btnAbort    = xT("Abort");
    std::ctstring_t btnCancel   = xT("Cancel");
    std::ctstring_t btnContinue = xT("Continue");
    std::ctstring_t btnIgnore   = xT("Ignore");
    std::ctstring_t btnRetry    = xT("Retry");
    std::ctstring_t btnTryAgain = xT("Try Again");


    std::ctstring_t wmDeleteWindow = xT("WM_DELETE_WINDOW");

    // Open a display
    Display *display = ::XOpenDisplay(NULL);
    xTEST_PTR(display);

    // handle errors is on
    ::XSynchronize(display, False);
    ::XSetErrorHandler(xlib_errorHandler);

    // Get us a white and black color
    culong_t black = BlackPixel(display, DefaultScreen(display));
    culong_t white = WhitePixel(display, DefaultScreen(display));

    // Create a window with the specified title
    Window wnd = ::XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 100, 100, 0,
        black, black);

    iRv = ::XSelectInput(display, wnd, ExposureMask | StructureNotifyMask | KeyReleaseMask |
        PointerMotionMask | ButtonPressMask | ButtonReleaseMask);
    // xTEST_DIFF(iRv, 0);

    iRv = ::XMapWindow(display, wnd);
    // xTEST_DIFF(iRv, 0);

    iRv = ::XStoreName(display, wnd, a_title.c_str());
    // xTEST_DIFF(iRv, 0);

    Atom wmDelete = ::XInternAtom(display, wmDeleteWindow.c_str(), True);
    ::XSetWMProtocols(display, wnd, &wmDelete, 1);

    // Create a graphics context for the window
    const GC gc = ::XCreateGC(display, wnd, 0, 0);

    iRv = ::XSetForeground(display, gc, white);
    // xTEST_DIFF(iRv, 0);

    iRv = ::XSetBackground(display, gc, black);
    // xTEST_DIFF(iRv, 0);

    // Split the text down into a list of lines
    std::vec_tstring_t lines;
    CxString::split(a_text, CxConst::eol(), &lines);
    cint_t lines_size = static_cast<int_t>( lines.size() );

    // Compute the printed length and height of the longest and the tallest line
    XFontStruct *font = ::XQueryFont(display, ::XGContextFromGC(gc));
    xTEST_PTR(font);

    XCharStruct overall;

    int_t direction = 0, ascent = 0, descent = 0;
    int_t length = 0, height = 0;

    for (std::size_t i = 0; i < lines.size(); ++ i) {
        iRv = ::XTextExtents(font, lines[i].c_str(), (int)lines[i].size(), &direction, &ascent,
            &descent, &overall);
        // xTEST_DIFF(iRv, 0);

        length = (overall.width > length) ? overall.width : length;
        height = ((ascent + descent) > height) ? (ascent + descent) : height;
    }

    // Compute the shape of the window, needed to display the text and adjust the window accordingly
    cint_t  X = DisplayWidth (display, DefaultScreen(display)) / 2 - length / 2 - 10;
    cint_t  Y = DisplayHeight(display, DefaultScreen(display)) / 2 - lines_size * height / 2 -
        height - 10;
    cuint_t W = length + 20;
    cuint_t H = lines_size * height + height + 40;

    iRv = ::XMoveResizeWindow(display, wnd, X, Y, W, H);
    // xTEST_DIFF(iRv, 0);

    // Compute the shape of the OK button
    iRv = ::XTextExtents(font, btnOk.c_str(), 2, &direction, &ascent, &descent, &overall);
    // xTEST_DIFF(iRv, 0);

    iRv = ::XFreeFontInfo(NULL, font, 1);
    // xTEST_DIFF(iRv, 0);

    cint_t okWidth  = overall.width;
    cint_t okHeight = ascent + descent;
    cint_t okX1     = W / 2 - okWidth / 2 - 15;
    cint_t okY1     = (lines_size * height + 20) + 5;
    cint_t okX2     = W / 2 + okWidth / 2 + 15;
    cint_t okY2     = okY1 + 4 + okHeight;
    cint_t okBaseX  = okX1 + 15;
    cint_t okBaseY  = okY1 + 2 + okHeight;

    // Make the window non resizeable
    iRv = ::XUnmapWindow(display, wnd);
    // xTEST_DIFF(iRv, 0);

    XSizeHints *hints = ::XAllocSizeHints();
    xTEST_PTR(hints);

    hints->flags      = PSize | PMinSize | PMaxSize;
    hints->min_width  = hints->max_width  = hints->base_width  = W;
    hints->min_height = hints->max_height = hints->base_height = H;

    (void_t)::XSetWMNormalHints(display, wnd, hints);
    iRv = ::XFree(hints); hints = NULL;
    // xTEST_DIFF(iRv, 0);

    iRv = ::XMapRaised(display, wnd);
    // xTEST_DIFF(iRv, 0);

    iRv = ::XFlush(display);
    // xTEST_DIFF(iRv, 0);

    // Event loop
    bool_t isRun         = true;
    bool_t isButtonFocus = false;

    xFOREVER {
        int_t  offset = 0;
        XEvent event;

        iRv = ::XNextEvent(display, &event);
        // xTEST_DIFF(iRv, 0);

        if (event.type == MotionNotify) {
            if (event.xmotion.x >= okX1 && event.xmotion.x <= okX2 &&
                event.xmotion.y >= okY1 && event.xmotion.y <= okY2)
            {
                xCHECK_DO(!isButtonFocus, event.type = Expose);
                isButtonFocus = true;
            } else {
                xCHECK_DO(isButtonFocus,  event.type = Expose);
                isButtonFocus = false;
                offset        = 0;
            }
        }

        switch (event.type) {
        case ButtonPress:
        case ButtonRelease:
            xCHECK_DO(event.xbutton.button != Button1, break);

            if (isButtonFocus) {
                offset = (event.type == ButtonPress) ? 1 : 0;
                if (!offset) {
                    isRun = false;
                }
            } else {
                offset = 0;
            }
            break;
        case Expose:
        case MapNotify:
            iRv = ::XClearWindow(display, wnd);
            // xTEST_DIFF(iRv, 0);

            // Draw text lines
            for (std::size_t i = 0; i < lines.size(); ++ i) {
                iRv = ::XDrawString(display, wnd, gc, 10, 10 + height + height * (int_t)i,
                    lines[i].c_str(), (int)lines[i].size());
                // xTEST_DIFF(iRv, 0);
            }

            // Draw OK button
            if (isButtonFocus) {
                iRv = ::XFillRectangle(display, wnd, gc, offset + okX1, offset + okY1, okX2 - okX1,
                    okY2 - okY1);
                // xTEST_DIFF(iRv, 0);

                iRv = ::XSetForeground(display, gc, black);
                // xTEST_DIFF(iRv, 0);
            } else {
                iRv = ::XDrawLine(display, wnd, gc, okX1, okY1, okX2, okY1);
                // xTEST_DIFF(iRv, 0);

                iRv = ::XDrawLine(display, wnd, gc, okX1, okY2, okX2, okY2);
                // xTEST_DIFF(iRv, 0);

                iRv = ::XDrawLine(display, wnd, gc, okX1, okY1, okX1, okY2);
                // xTEST_DIFF(iRv, 0);

                iRv = ::XDrawLine(display, wnd, gc, okX2, okY1, okX2, okY2);
                // xTEST_DIFF(iRv, 0);
            }

            iRv = ::XDrawString(display, wnd, gc, offset + okBaseX, offset + okBaseY, btnOk.c_str(), 2);
            // xTEST_DIFF(iRv, 0);

            if (isButtonFocus) {
                iRv = ::XSetForeground(display, gc, white);
                // xTEST_DIFF(iRv, 0);
            }

            iRv = ::XFlush(display);
            // xTEST_DIFF(iRv, 0);

            break;
        case KeyRelease:
            {
                KeySym sym = ::XLookupKeysym(&event.xkey, 0);
                switch (sym) {
                case XK_Escape:
                case XK_space:
                    isRun = false;
                    break;
                default:
                    ;
                    break;
                }
            }
            break;
        case ClientMessage:
            char *atom = ::XGetAtomName(display, event.xclient.message_type);
            xTEST_PTR(atom);

            xCHECK_DO(std::tstring_t(atom) == wmDeleteWindow, isRun = false);

            iRv = ::XFree(atom);  atom = NULL;
            // xTEST_DIFF(iRv, 0);

            break;
        };

        xCHECK_DO(!isRun, break);
    }

    // Clean up
    {
        iRv = ::XFreeGC(display, gc);
        // xTEST_DIFF(iRv, 0);

        iRv = ::XDestroyWindow(display, wnd);
        // xTEST_DIFF(iRv, 0);

        iRv = ::XCloseDisplay(display);   display = NULL;
        // xTEST_DIFF(iRv, 0);
    }

    xUNUSED(NxInternal::NxEnum::modalResults);
#else
    #pragma message("xLib: CxMsgBox::show_impl() - n/a")
#endif

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
