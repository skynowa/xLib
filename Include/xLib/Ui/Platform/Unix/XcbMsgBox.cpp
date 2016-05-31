/**
 * \file   XcbMsgBox.inl
 * \brief  XCB message box
 */


#include <xLib/Core/Format.h>

#if xHAVE_XCB
    #include <xcb/xcb.h>
#endif


xNAMESPACE_BEGIN2(xlib, ui)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
XcbMsgBox::XcbMsgBox() :
    _connection(xPTR_NULL)
{
    // Open the connection to the X server
    _connection = ::xcb_connect(xPTR_NULL, xPTR_NULL);
    xTEST_PTR(_connection);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
XcbMsgBox::~XcbMsgBox()
{
    if (_connection != xPTR_NULL) {
        (void_t)::xcb_disconnect(_connection);
        _connection = xPTR_NULL;
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE XcbMsgBox::ExModalResult
XcbMsgBox::show(
    std::ctstring_t &a_text,    ///< text
    std::ctstring_t &a_title,   ///< title
    cExType         &a_type     ///< type
)
{
    xUNUSED(a_type);
    xUNUSED(a_title);

    int_t iRv = 0;

    xcb_void_cookie_t cookie = {};

    // Get the first screen
    const xcb_screen_t *screen = ::xcb_setup_roots_iterator( ::xcb_get_setup(_connection) ).data;
    xTEST_PTR(screen);

    // create black (foreground) graphic context
    xcb_gcontext_t foreground = 0;
    {
        foreground                   = ::xcb_generate_id(_connection);
        xcb_drawable_t drawable      = screen->root;
        uint32_t       value_mask    = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
        uint32_t       value_list[2] = {screen->black_pixel, XCB_EVENT_MASK_NO_EVENT};

        cookie = ::xcb_create_gc(_connection, foreground, drawable, value_mask, value_list);
        xTEST_GR(cookie.sequence, 0U);
    }

    // create white (background) graphic context
    xcb_gcontext_t background = 0;
    {
        background                   = ::xcb_generate_id(_connection);
        xcb_drawable_t drawable      = screen->root;
        uint32_t       value_mask    = XCB_GC_BACKGROUND | XCB_GC_GRAPHICS_EXPOSURES;
        uint32_t       value_list[2] = {screen->white_pixel, XCB_EVENT_MASK_NO_EVENT};

        cookie = ::xcb_create_gc(_connection, background, drawable, value_mask, value_list);
        xTEST_GR(cookie.sequence, 0U);
    }

    // Create the window
    xcb_window_t mainWindowId = 0;
    {
        mainWindowId          = ::xcb_generate_id(_connection);
        uint32_t valueMask    = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        uint32_t valueList[2] = {screen->white_pixel,
                                  XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
                                  XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
                                  XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
                                  XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE};

        cookie = ::xcb_create_window(
            _connection,                   // connection
            XCB_COPY_FROM_PARENT,          // depth
            mainWindowId,                  // window ID
            screen->root,                  // parent window
            0, 0,                          // x, y
            150 * 2, 150,                  // width, height
            10,                            // border_width
            XCB_WINDOW_CLASS_INPUT_OUTPUT, // class
            screen->root_visual,           // visual
            valueMask, valueList);         // masks
        xTEST_GR(cookie.sequence, 0U);

        // Map the window on the screen
        cookie = ::xcb_map_window(_connection, mainWindowId);
        xTEST_GR(cookie.sequence, 0U);
    }

    iRv = ::xcb_flush(_connection);
    xTEST_GR(iRv, 0);

    for ( ; ; ) {
        xcb_generic_event_t *event = ::xcb_wait_for_event(_connection);
        xCHECK_DO(event == xPTR_NULL, break);

        switch (event->response_type & ~0x80) {
        case XCB_EXPOSE: {
                xcb_expose_event_t *expose = (xcb_expose_event_t *)event;

                Trace() << Format::str("Window {} exposed. "
                    "Region to be redrawn at location ({},{}), with dimension ({},{})\n",
                    expose->window, expose->x, expose->y, expose->width, expose->height );

                const xcb_rectangle_t rectangles[] =
                {
                    {40, 40, 20, 20}
                };

                cookie = ::xcb_poly_rectangle(_connection, mainWindowId, foreground, 1, rectangles);
                xTEST_GR(cookie.sequence, 0U);

                cookie = ::xcb_image_text_8(_connection, static_cast<uint8_t>( a_text.size() ),
                    mainWindowId, background, 20, 20, xT2A(a_text).c_str());
                xTEST_GR(cookie.sequence, 0U);

                iRv = ::xcb_flush(_connection);
                xTEST_GR(iRv, 0);
            }
            break;
        case XCB_BUTTON_PRESS: {
                xcb_button_press_event_t *button_press = (xcb_button_press_event_t *)event;
                _traceModifiers(button_press->state);

                switch (button_press->detail) {
                case 4:
                    Trace() << Format::str("Wheel Button up in window {}, at coordinates ({},{})\n",
                            button_press->event, button_press->event_x, button_press->event_y );
                    break;
                case 5:
                    Trace() << Format::str("Wheel Button down in window {}, at coordinates ({},{})\n",
                            button_press->event, button_press->event_x, button_press->event_y );
                    break;
                default:
                    Trace() << Format::str("Button {} pressed in window {}, at coordinates ({},{})\n",
                        button_press->detail, button_press->event, button_press->event_x,
                        button_press->event_y );
                    break;
                }
            }
            break;
        case XCB_BUTTON_RELEASE: {
                xcb_button_release_event_t *button_release = (xcb_button_release_event_t *)event;
                _traceModifiers(button_release->state);

                Trace() << Format::str("Button {} released in window {}, at coordinates ({},{})\n",
                    button_release->detail, button_release->event, button_release->event_x,
                    button_release->event_y );
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
                xcb_leave_notify_event_t *leave_notify = (xcb_leave_notify_event_t *)event;

                Trace() << Format::str("Mouse left window {}, at coordinates ({},{})\n",
                    leave_notify->event, leave_notify->event_x, leave_notify->event_y );
            }
            break;
        case XCB_KEY_PRESS: {
                xcb_key_press_event_t *key_press = (xcb_key_press_event_t *)event;
                _traceModifiers(key_press->state);

                Trace() << Format::str("Key pressed in window {}\n", key_press->event);
            }
            break;
        case XCB_KEY_RELEASE: {
                xcb_key_release_event_t *key_release = (xcb_key_release_event_t *)event;
                _traceModifiers(key_release->state);

                Trace() << Format::str("Key released in window {}\n", key_release->event);
            }
            break;
        default: {
                Trace() << Format::str("Unknown event: {}\n", (uint_t)event->response_type);
            }
            break;
        }

        xBUFF_FREE(event);
    } // switch

}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void
XcbMsgBox::_traceModifiers(
    const uint32_t a_valueMask
) const
{
    uint32_t valueMask = a_valueMask;

    ctchar_t *modifiers[] =
    {
        xT("Shift"),   xT("Lock"),    xT("Ctrl"),    xT("Alt"),
        xT("Mod2"),    xT("Mod3"),    xT("Mod4"),    xT("Mod5"),
        xT("Button1"), xT("Button2"), xT("Button3"), xT("Button4"), xT("Button5")
    };

    Trace() << xT("Modifier mask: ");

    for (const char **modifier = modifiers; valueMask; valueMask >>= 1, ++ modifier) {
        if (valueMask & 1) {
            Trace() << *modifier;
        }
    }

    Trace() << xT("\n");
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, ui)
