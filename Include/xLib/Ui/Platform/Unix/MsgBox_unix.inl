/**
 * \file   MsgBox.inl
 * \brief  message box
 */


#include <xLib/Core/String.h>

#if xHAVE_XCB
    #include <xcb/xcb.h>
#endif

xNAMESPACE_BEGIN2(xlib, ui)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

/* print names of modifiers present in mask */
xINLINE void
modifiersPrint(uint32_t mask)
{
    const char *MODIFIERS[] =
    {
        "Shift", "Lock", "Ctrl", "Alt",
        "Mod2", "Mod3", "Mod4", "Mod5",
        "Button1", "Button2", "Button3", "Button4", "Button5"
    };

    printf("Modifier mask: ");

    for (const char **modifier = MODIFIERS; mask; mask >>= 1, ++ modifier) {
        if (mask & 1) {
            printf(*modifier);
        }
    }

    printf("\n");
}
//-------------------------------------------------------------------------------------------------
xINLINE MsgBox::ExModalResult
MsgBox::_show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
    ExModalResult mrRv = mrUnknown;

#if xHAVE_XCB
    xUNUSED(a_text);
    xUNUSED(a_title);
    xUNUSED(a_type);

    xUNUSED(internal::enums::types);
    xUNUSED(internal::enums::modalResults);

    int_t             iRv        = 0;
    xcb_gcontext_t    foreground = 0U;
    xcb_gcontext_t    background = 0U;

    xcb_rectangle_t rectangles[] =
    {
        {40, 40, 20, 20}
    };

#if 0
    xcb_connection_t *connection = xPTR_NULL;
    xcb_screen_t     *screen     = xPTR_NULL;
    xcb_drawable_t    windowId   = 0U;
    uint32_t          mask       = 0U;
    uint32_t          values[2]  = {0U, 0U};

    connection = ::xcb_connect(xPTR_NULL, xPTR_NULL);
    xTEST_PTR(connection);

    // get the first screen
    screen = ::xcb_setup_roots_iterator( ::xcb_get_setup(connection) ).data;
    xTEST_PTR(screen);

    // root window
    windowId = screen->root;

    // create black(foreground) graphic context
    foreground = ::xcb_generate_id(connection);
    mask       = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
    values[0]  = screen->black_pixel;
    values[1]  = 0;

    xcb_void_cookie_t cookie = ::xcb_create_gc(connection, foreground, windowId, mask, values);
    xTEST_GR(cookie.sequence, 0U);

    // create white(background) graphic context
    background = xcb_generate_id(connection);
    mask       = XCB_GC_BACKGROUND | XCB_GC_GRAPHICS_EXPOSURES;
    values[0]  = screen->white_pixel;
    values[1]  = 0;

    cookie = ::xcb_create_gc(connection, background, windowId, mask, values);
    xTEST_GR(cookie.sequence, 0U);

    // create the window
    windowId   = ::xcb_generate_id(connection);
    mask       = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    values[0]  = screen->white_pixel;
    values[1]  = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;

    cookie = ::xcb_create_window(
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
    xTEST_GR(cookie.sequence, 0U);

    // map the window on the screen
    cookie = ::xcb_map_window(connection, windowId);
    xTEST_GR(cookie.sequence, 0U);

    iRv = ::xcb_flush(connection);
    xTEST_GR(iRv, 0);

    for ( ; ; ) {
        xcb_generic_event_t *event = ::xcb_wait_for_event(connection);
        xCHECK_DO(event == xPTR_NULL, break);

        switch (event->response_type & ~0x80) {
        case XCB_EXPOSE:
            cookie = ::xcb_poly_rectangle(connection, windowId, foreground, 1, rectangles);
            xTEST_GR(cookie.sequence, 0U);

            cookie = ::xcb_image_text_8(connection, static_cast<uint8_t>( a_text.size() ), windowId,
                background, 20, 20, a_text.c_str());
            xTEST_GR(cookie.sequence, 0U);

            iRv = ::xcb_flush(connection);
            xTEST_GR(iRv, 0);

            break;
        case XCB_KEY_PRESS:
            break;
        default:
            Trace() << xT("Unknown event: ") << event->response_type;
            break;
        }

        xBUFF_FREE(event);
    }

    if (connection != xPTR_NULL) {
        (void_t)::xcb_disconnect(connection);
        connection = xPTR_NULL;
    }
#else
    // FAQ: https://xcb.freedesktop.org/tutorial/events/

    // Open the connection to the X server
    xcb_connection_t *connection = ::xcb_connect(xPTR_NULL, xPTR_NULL);
    xTEST_PTR(connection);

    // Get the first screen
    xcb_screen_t *screen = ::xcb_setup_roots_iterator( ::xcb_get_setup (connection) ).data;
    xTEST_PTR(screen);

    // Create the window
    xcb_window_t windowId  = ::xcb_generate_id(connection);
    uint32_t     mask      = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t     values[2] = {screen->white_pixel,
                              XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
                              XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
                              XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
                              XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE };

    xcb_void_cookie_t cookie = ::xcb_create_window(
        connection,                    // connection
        0,                             // depth
        windowId,                      // window ID
        screen->root,                  // parent window
        0, 0,                          // x, y
        150 * 2, 150,                  // width, height
        10,                            // border_width
        XCB_WINDOW_CLASS_INPUT_OUTPUT, // class
        screen->root_visual,           // visual
        mask, values );                // masks
    xTEST_GR(cookie.sequence, 0U);

    // Map the window on the screen
    cookie = ::xcb_map_window(connection, windowId);
    xTEST_GR(cookie.sequence, 0U);

    iRv = ::xcb_flush(connection);
    xTEST_GR(iRv, 0);

    xcb_generic_event_t *event = xPTR_NULL;
    while ( (event = ::xcb_wait_for_event(connection)) ) {
        switch (event->response_type & ~0x80) {
        case XCB_EXPOSE: {
                xcb_expose_event_t *expose = (xcb_expose_event_t *)event;

                printf("Window %ull exposed. Region to be redrawn at location (%ull,%ull), with dimension (%ull,%ull)\n",
                        expose->window, expose->x, expose->y, expose->width, expose->height );

                cookie = ::xcb_poly_rectangle(connection, windowId, foreground, 1, rectangles);
                xTEST_GR(cookie.sequence, 0U);

                cookie = ::xcb_image_text_8(connection, static_cast<uint8_t>( a_text.size() ), windowId,
                    background, 20, 20, a_text.c_str());
                xTEST_GR(cookie.sequence, 0U);

                iRv = ::xcb_flush(connection);
                xTEST_GR(iRv, 0);
            }
            break;
        case XCB_BUTTON_PRESS: {
                xcb_button_press_event_t *bp = (xcb_button_press_event_t *)event;
                modifiersPrint(bp->state);

                switch (bp->detail) {
                case 4:
                    printf("Wheel Button up in window %ull, at coordinates (%ull,%ull)\n",
                            bp->event, bp->event_x, bp->event_y );
                    break;
                case 5:
                    printf("Wheel Button down in window %ull, at coordinates (%ull,%ull)\n",
                            bp->event, bp->event_x, bp->event_y );
                    break;
                default:
                    printf("Button %ull pressed in window %ull, at coordinates (%ull,%ull)\n",
                            bp->detail, bp->event, bp->event_x, bp->event_y );
                    break;
                }
            }
            break;
        case XCB_BUTTON_RELEASE: {
                xcb_button_release_event_t *br = (xcb_button_release_event_t *)event;
                modifiersPrint(br->state);

                printf("Button %ull released in window %ull, at coordinates (%ull,%ull)\n",
                        br->detail, br->event, br->event_x, br->event_y );
            }
            break;
        case XCB_MOTION_NOTIFY: {
                xcb_motion_notify_event_t *motion = (xcb_motion_notify_event_t *)event;

                printf("Mouse moved in window %ull, at coordinates (%ull,%ull)\n",
                        motion->event, motion->event_x, motion->event_y );
            }
            break;
        case XCB_ENTER_NOTIFY: {
                xcb_enter_notify_event_t *enter = (xcb_enter_notify_event_t *)event;

                printf("Mouse entered window %ull, at coordinates (%ull,%ull)\n",
                        enter->event, enter->event_x, enter->event_y );
            }
            break;
        case XCB_LEAVE_NOTIFY: {
                xcb_leave_notify_event_t *leave = (xcb_leave_notify_event_t *)event;

                printf("Mouse left window %ull, at coordinates (%ull,%ull)\n",
                        leave->event, leave->event_x, leave->event_y );
            }
            break;
        case XCB_KEY_PRESS: {
                xcb_key_press_event_t *kp = (xcb_key_press_event_t *)event;
                modifiersPrint(kp->state);

                printf("Key pressed in window %ull\n",
                        kp->event);
            }
            break;
        case XCB_KEY_RELEASE: {
                xcb_key_release_event_t *kr = (xcb_key_release_event_t *)event;
                modifiersPrint(kr->state);

                printf("Key released in window %ull\n",
                        kr->event);
            }
            break;
        default:
            /* Unknown event type, ignore it */
            Format::cout("Unknown event: {}\n", event->response_type);
            break;
        }

        xBUFF_FREE(event);
    }

    if (connection != xPTR_NULL) {
        (void_t)::xcb_disconnect(connection);
        connection = xPTR_NULL;
    }
#endif
#else
    xUNUSED(a_text);
    xUNUSED(a_title);
    xUNUSED(a_type);

    xUNUSED(internal::enums::types);
    xUNUSED(internal::enums::modalResults);

    // TODO: MsgBox::_show_impl() - Unix
    // #pragma message("xLib: MsgBox::_show_impl() - n/a")
#endif

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, ui)
