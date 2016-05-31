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

    Trace() << "Modifier mask: ";

    for (const char **modifier = MODIFIERS; mask; mask >>= 1, ++ modifier) {
        if (mask & 1) {
            Trace() << *modifier;
        }
    }

    Trace() << "\n";
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
    xcb_connection_t *connection = xPTR_NULL;
    xcb_screen_t     *screen     = xPTR_NULL;
    xcb_void_cookie_t cookie     = {};
    xcb_gcontext_t    foreground = 0U;
    xcb_gcontext_t    background = 0U;

    xcb_rectangle_t rectangles[] =
    {
        {40, 40, 20, 20}
    };

#if 1
    connection = ::xcb_connect(xPTR_NULL, xPTR_NULL);
    xTEST_PTR(connection);

    // get the first screen
    screen = ::xcb_setup_roots_iterator( ::xcb_get_setup(connection) ).data;
    xTEST_PTR(screen);

    // root window

    // create black(foreground) graphic context
	{
		xcb_gcontext_t foreground    = ::xcb_generate_id(connection);
		xcb_drawable_t drawable      = screen->root;
		uint32_t       value_mask    = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
		uint32_t       value_list[2] = {screen->black_pixel, XCB_EVENT_MASK_NO_EVENT};

		cookie = ::xcb_create_gc(connection, foreground, drawable, value_mask, value_list);
		xTEST_GR(cookie.sequence, 0U);
	}

    // create white(background) graphic context
	{
		xcb_gcontext_t background    = ::xcb_generate_id(connection);
		xcb_drawable_t drawable      = screen->root;
		uint32_t       value_mask    = XCB_GC_BACKGROUND | XCB_GC_GRAPHICS_EXPOSURES;
		uint32_t       value_list[2] = {screen->white_pixel, XCB_EVENT_MASK_NO_EVENT};

		cookie = ::xcb_create_gc(connection, background, drawable, value_mask, value_list);
		xTEST_GR(cookie.sequence, 0U);
	}

    // create the window
    uint32_t mainWindowId = 0;
	{
	    mainWindowId           = ::xcb_generate_id(connection);
		uint32_t value_mask    = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
		uint32_t value_list[2] = {screen->white_pixel, XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS};

		cookie = ::xcb_create_window(
			connection,                    // connection
			XCB_COPY_FROM_PARENT,          // depth
			mainWindowId,                  // window ID
			screen->root,                  // parent window
			0, 0,                          // x, y
			150, 150,                      // width, height
			10,                            // border_width
			XCB_WINDOW_CLASS_INPUT_OUTPUT, // class
			screen->root_visual,           // visual
			value_mask, value_list);                 // masks
		xTEST_GR(cookie.sequence, 0U);

		// map the window on the screen
		cookie = ::xcb_map_window(connection, mainWindowId);
		xTEST_GR(cookie.sequence, 0U);
	}

    iRv = ::xcb_flush(connection);
    xTEST_GR(iRv, 0);

    for ( ; ; ) {
        xcb_generic_event_t *event = ::xcb_wait_for_event(connection);
        xCHECK_DO(event == xPTR_NULL, break);

        switch (event->response_type & ~0x80) {
        case XCB_EXPOSE:
            cookie = ::xcb_poly_rectangle(connection, mainWindowId, foreground, 1, rectangles);
            xTEST_GR(cookie.sequence, 0U);

            cookie = ::xcb_image_text_8(connection, static_cast<uint8_t>( a_text.size() ), mainWindowId,
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
    connection = ::xcb_connect(xPTR_NULL, xPTR_NULL);
    xTEST_PTR(connection);

    // Get the first screen
    screen = ::xcb_setup_roots_iterator( ::xcb_get_setup(connection) ).data;
    xTEST_PTR(screen);

    // Create the window
    windowId = ::xcb_generate_id(connection);

    uint32_t mask      = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t values[2] = {screen->white_pixel,
                          XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
                          XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
                          XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
                          XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE};

    cookie = ::xcb_create_window(
        connection,                    // connection
        XCB_COPY_FROM_PARENT,          // depth
        windowId,                      // window ID
        screen->root,                  // parent window
        0, 0,                          // x, y
        150 * 2, 150,                  // width, height
        10,                            // border_width
        XCB_WINDOW_CLASS_INPUT_OUTPUT, // class
        screen->root_visual,           // visual
        mask, values);                 // masks
    xTEST_GR(cookie.sequence, 0U);

    // Map the window on the screen
    cookie = ::xcb_map_window(connection, windowId);
    xTEST_GR(cookie.sequence, 0U);

    iRv = ::xcb_flush(connection);
    xTEST_GR(iRv, 0);

    for ( ; ; ) {
        xcb_generic_event_t *event = ::xcb_wait_for_event(connection);
        xCHECK_DO(event == xPTR_NULL, break);

        switch (event->response_type & ~0x80) {
        case XCB_EXPOSE: {
                xcb_expose_event_t *expose = (xcb_expose_event_t *)event;

                Trace() << Format::str("Window {} exposed. Region to be redrawn at location ({},{}), with dimension ({},{})\n",
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
                    Trace() << Format::str("Wheel Button up in window {}, at coordinates ({},{})\n",
                            bp->event, bp->event_x, bp->event_y );
                    break;
                case 5:
                    Trace() << Format::str("Wheel Button down in window {}, at coordinates ({},{})\n",
                            bp->event, bp->event_x, bp->event_y );
                    break;
                default:
                    Trace() << Format::str("Button {} pressed in window {}, at coordinates ({},{})\n",
                            bp->detail, bp->event, bp->event_x, bp->event_y );
                    break;
                }
            }
            break;
        case XCB_BUTTON_RELEASE: {
                xcb_button_release_event_t *br = (xcb_button_release_event_t *)event;
                modifiersPrint(br->state);

                Trace() << Format::str("Button {} released in window {}, at coordinates ({},{})\n",
                        br->detail, br->event, br->event_x, br->event_y );
            }
            break;
        case XCB_MOTION_NOTIFY: {
                xcb_motion_notify_event_t *motion = (xcb_motion_notify_event_t *)event;

                Trace() << Format::str("Mouse moved in window {}, at coordinates ({},{})\n",
                        motion->event, motion->event_x, motion->event_y );
            }
            break;
        case XCB_ENTER_NOTIFY: {
                xcb_enter_notify_event_t *enter = (xcb_enter_notify_event_t *)event;

                Trace() << Format::str("Mouse entered window {}, at coordinates ({},{})\n",
                        enter->event, enter->event_x, enter->event_y );
            }
            break;
        case XCB_LEAVE_NOTIFY: {
                xcb_leave_notify_event_t *leave = (xcb_leave_notify_event_t *)event;

                Trace() << Format::str("Mouse left window {}, at coordinates ({},{})\n",
                        leave->event, leave->event_x, leave->event_y );
            }
            break;
        case XCB_KEY_PRESS: {
                xcb_key_press_event_t *kp = (xcb_key_press_event_t *)event;
                modifiersPrint(kp->state);

                Trace() << Format::str("Key pressed in window {}\n",
                        kp->event);
            }
            break;
        case XCB_KEY_RELEASE: {
                xcb_key_release_event_t *kr = (xcb_key_release_event_t *)event;
                modifiersPrint(kr->state);

                Trace() << Format::str("Key released in window {}\n",
                        kr->event);
            }
            break;
        default:
            /* Unknown event type, ignore it */
            Trace() << Format::str("Unknown event: {}\n", (uint_t)event->response_type);
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
