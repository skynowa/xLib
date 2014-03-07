/**
 * \file  CxMsgBox.inl
 * \brief message box
 */


#include <xLib/Core/CxString.h>

#if xHAVE_X11 && 0
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/keysym.h>

    #undef Status
    #undef Unsorted
    #undef None
    #undef Bool
#endif

#if xHAVE_XCB
    #include <xcb/xcb.h>
#endif

xNAMESPACE2_BEGIN(xlib, gui)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

#if 0

std::ctstring_t
xlib_errorFormat
(
    Display *a_display,
    cint_t  &a_code
)
{
    std::tstring_t sRv;
    tchar_t        buff[1024 + 1] = {0};

    int_t iRv = ::XGetErrorText(a_display, a_code, buff, static_cast<int_t>( sizeof(buff) ) - 1);
    xTEST_DIFF(iRv, 0);

    sRv.assign(buff);

    return sRv;
}

int
xlib_errorHandler(
    Display     *a_display,
    XErrorEvent *a_errorEvent
)
{
    std::ctstring_t errorStr = ::xlib_errorFormat(a_display, a_errorEvent->error_code);

    CxTrace() << xT("xLib: XLIB error - ") << xTRACE_VAR7(a_errorEvent->type,
        a_errorEvent->resourceid, a_errorEvent->serial, a_errorEvent->error_code, errorStr,
        a_errorEvent->request_code, a_errorEvent->minor_code);

    return 0;
}

#endif

xNAMESPACE_ANONYM_END
//-------------------------------------------------------------------------------------------------
inline CxMsgBox::ExModalResult
CxMsgBox::_show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
    ExModalResult mrRv = mrUnknown;

#if xHAVE_X11 && 0
    xUNUSED(a_type);

    xUNUSED(internal::enums::types);
    xUNUSED(internal::enums::modalResults);

    int_t iRv = - 1;

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

    std::ctstring_t wmProtocols = xT("WM_PROTOCOLS");
    std::ctstring_t wmDeleteWindow = xT("WM_DELETE_WINDOW");

    // Open a display
    Display *display = ::XOpenDisplay(NULL);
    xTEST_PTR(display);

    // handle errors is on
    ::XSynchronize(display, True);
    ::XSetErrorHandler(::xlib_errorHandler);

    // Get us a white and black color
    culong_t black = BlackPixel(display, DefaultScreen(display));
    culong_t white = WhitePixel(display, DefaultScreen(display));

    // Create a window with the specified title
    Window wnd = ::XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 100, 100, 0,
        black, black);

    iRv = ::XSelectInput(display, wnd, ExposureMask | StructureNotifyMask | KeyReleaseMask |
        PointerMotionMask | ButtonPressMask | ButtonReleaseMask);
    xTEST_DIFF(iRv, 0);

    iRv = ::XMapWindow(display, wnd);
    xTEST_DIFF(iRv, 0);

    iRv = ::XStoreName(display, wnd, a_title.c_str());
    xTEST_DIFF(iRv, 0);

    Atom wmDelete = ::XInternAtom(display, wmDeleteWindow.c_str(), True);
    ::XSetWMProtocols(display, wnd, &wmDelete, 1);

    // Create a graphics context for the window
    const GC gc = ::XCreateGC(display, wnd, 0, 0);

    iRv = ::XSetForeground(display, gc, white);
    xTEST_DIFF(iRv, 0);

    iRv = ::XSetBackground(display, gc, black);
    xTEST_DIFF(iRv, 0);

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
    xTEST_DIFF(iRv, 0);

    // Compute the shape of the OK button
    iRv = ::XTextExtents(font, btnOk.c_str(), 2, &direction, &ascent, &descent, &overall);
    // xTEST_DIFF(iRv, 0);

    iRv = ::XFreeFontInfo(NULL, font, 1);
    xTEST_DIFF(iRv, 0);

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
    xTEST_DIFF(iRv, 0);

    XSizeHints *hints = ::XAllocSizeHints();
    xTEST_PTR(hints);

    hints->flags      = PSize | PMinSize | PMaxSize;
    hints->min_width  = hints->max_width  = hints->base_width  = W;
    hints->min_height = hints->max_height = hints->base_height = H;

    (void_t)::XSetWMNormalHints(display, wnd, hints);
    iRv = ::XFree(hints); hints = NULL;
    xTEST_DIFF(iRv, 0);

    iRv = ::XMapRaised(display, wnd);
    xTEST_DIFF(iRv, 0);

    iRv = ::XFlush(display);
    xTEST_DIFF(iRv, 0);

    // Event loop
    bool_t isRunning     = true;
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
                    isRunning = false;
                }
            } else {
                offset = 0;
            }
            break;
        case Expose:
        case MapNotify:
            iRv = ::XClearWindow(display, wnd);
            xTEST_DIFF(iRv, 0);

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
                xTEST_DIFF(iRv, 0);

                iRv = ::XSetForeground(display, gc, black);
                xTEST_DIFF(iRv, 0);
            } else {
                iRv = ::XDrawLine(display, wnd, gc, okX1, okY1, okX2, okY1);
                xTEST_DIFF(iRv, 0);

                iRv = ::XDrawLine(display, wnd, gc, okX1, okY2, okX2, okY2);
                xTEST_DIFF(iRv, 0);

                iRv = ::XDrawLine(display, wnd, gc, okX1, okY1, okX1, okY2);
                xTEST_DIFF(iRv, 0);

                iRv = ::XDrawLine(display, wnd, gc, okX2, okY1, okX2, okY2);
                xTEST_DIFF(iRv, 0);
            }

            iRv = ::XDrawString(display, wnd, gc, offset + okBaseX, offset + okBaseY, btnOk.c_str(), 2);
            // xTEST_DIFF(iRv, 0);

            if (isButtonFocus) {
                iRv = ::XSetForeground(display, gc, white);
                xTEST_DIFF(iRv, 0);
            }

            iRv = ::XFlush(display);
            xTEST_DIFF(iRv, 0);

            break;
        case KeyRelease:
            {
                KeySym sym = ::XLookupKeysym(&event.xkey, 0);
                switch (sym) {
                case XK_Escape:
                case XK_space:
                    isRunning = false;
                    break;
                default:
                    ;
                    break;
                }
            }
            break;
        case ClientMessage:
            {
                char *atom = ::XGetAtomName(display, event.xclient.message_type);
                xTEST_PTR(atom);

                xCHECK_DO(std::tstring_t(atom) == wmDeleteWindow, isRunning = false);
                xCHECK_DO(std::tstring_t(atom) == wmProtocols,    isRunning = false);

                iRv = ::XFree(atom);  atom = NULL;
                xTEST_DIFF(iRv, 0);
            }
            break;
        case ConfigureNotify:
            {
                // CxTrace() << xT("Window moved or resized!\n");
            }
            break;
        case DestroyNotify:
            {
                // CxTrace() << xT("Window killed!\n");
            }
            break;
        };

        xCHECK_DO(!isRunning, break);
    }

    // Clean up
    {
        iRv = ::XFreeGC(display, gc);
        xTEST_DIFF(iRv, 0);

        iRv = ::XDestroyWindow(display, wnd);
        xTEST_DIFF(iRv, 0);

        iRv = ::XCloseDisplay(display);   display = NULL;
        // xTEST_DIFF(iRv, 0);
    }
#else
#if xHAVE_XCB
    xcb_connection_t    *connection = NULL;
    xcb_screen_t        *screen     = NULL;
    xcb_drawable_t       windowId   = 0U;
    xcb_gcontext_t       foreground = 0U;
    xcb_gcontext_t       background = 0U;
    xcb_generic_event_t *event      = NULL;
    uint32_t             mask       = 0U;
    uint32_t             values[2]  = {0U, 0U};

    xcb_rectangle_t rectangles[] = {
        {40, 40, 20, 20},
    };

    connection = ::xcb_connect(NULL, NULL);

    // get the first screen
    screen = ::xcb_setup_roots_iterator( ::xcb_get_setup(connection) ).data;

    // root window
    windowId = screen->root;

    // create black(foreground) graphic context
    foreground = ::xcb_generate_id(connection);
    mask       = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
    values[0]  = screen->black_pixel;
    values[1]  = 0;

    ::xcb_create_gc(connection, foreground, windowId, mask, values);

    // create white(background) graphic context
    background = xcb_generate_id(connection);
    mask       = XCB_GC_BACKGROUND | XCB_GC_GRAPHICS_EXPOSURES;
    values[0]  = screen->white_pixel;
    values[1]  = 0;

    ::xcb_create_gc(connection, background, windowId, mask, values);

    // create the window
    windowId   = ::xcb_generate_id(connection);
    mask       = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    values[0]  = screen->white_pixel;
    values[1]  = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;

    ::xcb_create_window(
        connection,                    // connection
        XCB_COPY_FROM_PARENT,          // depth
        windowId,                      // window ID
        screen->root,                  // parent window
        0, 0,                          // x, y
        150, 150,                      // width, height
        10,                            // border_width
        XCB_WINDOW_CLASS_INPUT_OUTPUT, // class
        screen->root_visual,           // visual
        mask, values);                 // masks

    // map the window on the screen
    ::xcb_map_window(connection, windowId);
    ::xcb_flush(connection);

    while ( (event = ::xcb_wait_for_event(connection)) ) {
        switch (event->response_type & ~0x80) {
        case XCB_EXPOSE:
            ::xcb_poly_rectangle(connection, windowId, foreground, 1, rectangles);
            ::xcb_image_text_8(connection, static_cast<uint8_t>( a_text.size() ), windowId,
                background, 20, 20, a_text.c_str());
            ::xcb_flush(connection);
            break;
        case XCB_KEY_PRESS:
            goto breakLoop;
        }

        ::free(event);
    }

    breakLoop:
#endif
    xUNUSED(a_text);
    xUNUSED(a_title);
    xUNUSED(a_type);

    xUNUSED(internal::enums::types);
    xUNUSED(internal::enums::modalResults);

    // TODO: CxMsgBox::_show_impl() - Unix
    // #pragma message("xLib: CxMsgBox::_show_impl() - n/a")
#endif

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, gui)
