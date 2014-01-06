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

    ExModalResult mrRv = mrAbort;

#if xHAVE_X11
    std::ctstring_t buttonOk       = xT("OK");
    std::ctstring_t wmDeleteWindow = xT("WM_DELETE_WINDOW");

    // Open a display
    Display *display = ::XOpenDisplay(NULL);
    xTEST_PTR(display);

    // Get us a white and black color
    culong_t black = BlackPixel(display, DefaultScreen(display));
    culong_t white = WhitePixel(display, DefaultScreen(display));

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
    const GC gc = ::XCreateGC(display, wnd, 0, 0);

    ::XSetForeground(display, gc, white);
    ::XSetBackground(display, gc, black);

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
        ::XTextExtents(font, lines[i].c_str(), (int)lines[i].size(), &direction, &ascent,
            &descent, &overall);

        length = (overall.width > length) ? overall.width : length;
        height = ((ascent + descent) > height) ? (ascent + descent) : height;
    }

    // Compute the shape of the window, needed to display the text and adjust the window accordingly
    cint_t  X = DisplayWidth (display, DefaultScreen(display)) / 2 - length / 2 - 10;
    cint_t  Y = DisplayHeight(display, DefaultScreen(display)) / 2 - lines_size * height / 2 -
        height - 10;
    cuint_t W = length + 20;
    cuint_t H = lines_size * height + height + 40;

    ::XMoveResizeWindow(display, wnd, X, Y, W, H);

    // Compute the shape of the OK button
    ::XTextExtents(font, buttonOk.c_str(), 2, &direction, &ascent, &descent, &overall);
    ::XFreeFontInfo(NULL, font, 1);

    cint_t okWidth  = overall.width;
    cint_t okHeight = ascent + descent;
    cint_t okX1     = W / 2 - okWidth / 2 - 15;
    cint_t okY1     = (lines_size * height + 20) + 5;
    cint_t okX2     = W / 2 + okWidth / 2 + 15;
    cint_t okY2     = okY1 + 4 + okHeight;
    cint_t okBaseX  = okX1 + 15;
    cint_t okBaseY  = okY1 + 2 + okHeight;

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

    xFOREVER {
        int_t  offset = 0;
        XEvent event;

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
            ::XClearWindow(display, wnd);

            // Draw text lines
            for (std::size_t i = 0; i < lines.size(); ++ i) {
                ::XDrawString(display, wnd, gc, 10, 10 + height + height * (int_t)i,
                    lines[i].c_str(), (int)lines[i].size());
            }

            // Draw OK button
            if (isButtonFocus) {
                ::XFillRectangle(display, wnd, gc, offset + okX1, offset + okY1, okX2 - okX1,
                    okY2 - okY1);
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

        xCHECK_DO(!isRun, break);
    }

    // Clean up
    {
        ::XFreeGC(display, gc);
        ::XDestroyWindow(display, wnd);
        ::XCloseDisplay(display);   display = NULL;
    }
#else
    #pragma message("xLib: CxMsgBox::show_impl() - n/a")
#endif

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
