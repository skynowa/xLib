/**
 * \file  CxMsgBox.inl
 * \brief message box
 */


#include <xLib/Core/CxString.h>
#include <xLib/System/CxConsole.h>
#include <xLib/Filesystem/CxPath.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>


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
    xUNUSED(a_type);

    ExModalResult mrRes = mrAbort;

#if xHAVE_X11
    std::ctstring_t buttonOk       = xT("OK");
    std::ctstring_t wmDeleteWindow = xT("WM_DELETE_WINDOW");

    int_t   i = 0;
    ulong_t black = 0;
    ulong_t white = 0;
    int_t   length = 0;
    int_t   height = 0;
    int_t   direction = 0;
    int_t   ascent = 0;
    int_t   descent = 0;
    int_t   X = 0;
    int_t   Y = 0;
    uint_t  W = 0;
    uint_t  H = 0;
    int_t   okX1 = 0;
    int_t   okY1 = 0;
    int_t   okX2 = 0;
    int_t   okY2 = 0;
    int_t   okBaseX = 0;
    int_t   okBaseY = 0;
    int_t   okWidth = 0;
    int_t   okHeight = 0;

    // Open a display
    Display *display = ::XOpenDisplay(NULL);
    xTEST_PTR(display);

    // Get us a white and black color
    black = BlackPixel(display, DefaultScreen(display));
    white = WhitePixel(display, DefaultScreen(display));

    // Create a window with the specified title
    Window wnd = ::XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 100, 100, 0,
        black, black);

    ::XSelectInput(display, wnd, ExposureMask | StructureNotifyMask | KeyReleaseMask |
        PointerMotionMask | ButtonPressMask | ButtonReleaseMask);

    ::XMapWindow(display, wnd);
    ::XStoreName(display, wnd, a_title.c_str());

    Atom wmDelete = ::XInternAtom(display, wmDeleteWindow.c_str(), True);
    ::XSetWMProtocols(display, wnd, &wmDelete, 1);

    // Create a graphics context for the window
    GC gc = ::XCreateGC(display, wnd, 0, 0);

    ::XSetForeground(display, gc, white);
    ::XSetBackground(display, gc, black);

    // Split the text down into a list of lines
    char  **strvec      = NULL;
    int_t   strvec_size = 0;

    char *temp = (char *)std::malloc( std::strlen(a_text.c_str()) + 1);
    std::strcpy(temp, a_text.c_str());

    char *pch = std::strtok(temp, "\n");
    while (pch != NULL) {
        strvec = (char **)std::realloc(strvec, (strvec_size + 1) * sizeof(char **));

        strvec[strvec_size] = (char *)std::malloc(std::strlen(pch) + 1);
        std::strcpy(strvec[strvec_size], pch);

        ++ strvec_size;

        pch = std::strtok(NULL, "\n");
    }

    xBUFF_FREE(temp);

    // Compute the printed length and height of the longest and the tallest line
    XFontStruct *font = ::XQueryFont(display, ::XGContextFromGC(gc));
    xTEST_PTR(font);

    XCharStruct overall;
    for (i = 0, length = 0, height = 0; i < strvec_size; ++ i) {
        ::XTextExtents(font, strvec[i], (int)std::strlen(strvec[i]), &direction, &ascent, &descent, &overall);

        length = (overall.width > length) ? overall.width : length;
        height = ((ascent + descent) > height) ? (ascent + descent) : height;
    }

    // Compute the shape of the window, needed to display the text and adjust the window accordingly
    X = DisplayWidth (display, DefaultScreen(display)) / 2 - length / 2 - 10;
    Y = DisplayHeight(display, DefaultScreen(display)) / 2 - strvec_size * height / 2 - height - 10;
    W = length + 20;
    H = strvec_size * height + height + 40;

    ::XMoveResizeWindow(display, wnd, X, Y, W, H);

    // Compute the shape of the OK button
    ::XTextExtents(font, buttonOk.c_str(), 2, &direction, &ascent, &descent, &overall);

    okWidth  = overall.width;
    okHeight = ascent + descent;
    okX1     = W / 2 - okWidth / 2 - 15;
    okY1     = (strvec_size * height + 20) + 5;
    okX2     = W/2 + okWidth / 2 + 15;
    okY2     = okY1 + 4 + okHeight;
    okBaseX  = okX1 + 15;
    okBaseY  = okY1 + 2 + okHeight;

    ::XFreeFontInfo(NULL, font, 1);

    // Make the window non resizeable
    ::XUnmapWindow(display, wnd);
    XSizeHints *hints = ::XAllocSizeHints();
    xTEST_PTR(hints);

    hints->flags      = PSize | PMinSize | PMaxSize;
    hints->min_width  = hints->max_width  = hints->base_width  = W;
    hints->min_height = hints->max_height = hints->base_height = H;

    ::XSetWMNormalHints(display, wnd, hints);
    ::XFree(hints); hints = NULL;

    ::XMapRaised(display, wnd);
    ::XFlush(display);

    // Event loop
    bool_t isRun         = true;
    bool_t isButtonFocus = false;
    XEvent event;

    do {
        int_t offset = 0;

        ::XNextEvent(display, &event);

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
            if (event.xbutton.button != Button1) {
                break;
            }
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
            ::XClearWindow(display, wnd);

            // Draw text lines
            for (i = 0; i < strvec_size; ++ i) {
                ::XDrawString(display, wnd, gc, 10, 10 + height + height * i, strvec[i],
                    (int)std::strlen(strvec[i]));
            }

            // Draw OK button
            if (isButtonFocus) {
                ::XFillRectangle(display, wnd, gc, offset + okX1, offset + okY1, okX2 - okX1, okY2 - okY1);
                ::XSetForeground(display, gc, black);
            } else {
                ::XDrawLine(display, wnd, gc, okX1, okY1, okX2, okY1);
                ::XDrawLine(display, wnd, gc, okX1, okY2, okX2, okY2);
                ::XDrawLine(display, wnd, gc, okX1, okY1, okX1, okY2);
                ::XDrawLine(display, wnd, gc, okX2, okY1, okX2, okY2);
            }

            ::XDrawString(display, wnd, gc, offset + okBaseX, offset + okBaseY, buttonOk.c_str(), 2);

            if (isButtonFocus) {
                ::XSetForeground(display, gc, white);
            }

            ::XFlush(display);
            break;
        case KeyRelease:
            if (::XLookupKeysym(&event.xkey, 0) == XK_Escape) {
                isRun = false;
            }
            break;
        case ClientMessage:
            char *atom = ::XGetAtomName(display, event.xclient.message_type);
            xTEST_PTR(atom);

            xCHECK_DO(std::tstring_t(atom) == wmDeleteWindow, isRun = false);

            ::XFree(atom);  atom = NULL;
            break;
        };
    }
    while (isRun);

    // Clean up
    {
        for (i = 0; i < strvec_size; ++ i) {
            xBUFF_FREE(strvec[i]);
        }
        xBUFF_FREE(strvec);

        ::XFreeGC(display, gc); gc = NULL;
        ::XDestroyWindow(display, wnd);
        ::XCloseDisplay(display);   display = NULL;
    }
#else
    #pragma message("xLib: CxMsgBox::show_impl() - n/a")
#endif

    return mrRes;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
