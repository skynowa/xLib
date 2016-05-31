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
                    "Region to be redrawn at location ({},{}), with dimension ({},{})",
                    expose->window, expose->x, expose->y, expose->width, expose->height );

            #if 0
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
            #else
                #define WIDTH 300
                #define HEIGHT 150

                _textDraw(screen, mainWindowId, 10, HEIGHT - 10, xT2A(a_text).c_str());
            #endif
            }
            break;
        case XCB_BUTTON_PRESS: {
                xcb_button_press_event_t *button_press = (xcb_button_press_event_t *)event;
                _traceModifiers(button_press->state);

                switch (button_press->detail) {
                case 4:
                    Trace() << Format::str("Wheel Button up in window {}, at coordinates ({},{})",
                            button_press->event, button_press->event_x, button_press->event_y );
                    break;
                case 5:
                    Trace() << Format::str("Wheel Button down in window {}, at coordinates ({},{})",
                            button_press->event, button_press->event_x, button_press->event_y );
                    break;
                default:
                    Trace() << Format::str("Button {} pressed in window {}, at coordinates ({},{})",
                        button_press->detail, button_press->event, button_press->event_x,
                        button_press->event_y );
                    break;
                }
            }
            break;
        case XCB_BUTTON_RELEASE: {
                xcb_button_release_event_t *button_release = (xcb_button_release_event_t *)event;
                _traceModifiers(button_release->state);

                Trace() << Format::str("Button {} released in window {}, at coordinates ({},{})",
                    button_release->detail, button_release->event, button_release->event_x,
                    button_release->event_y );
            }
            break;
        case XCB_MOTION_NOTIFY: {
                xcb_motion_notify_event_t *motion = (xcb_motion_notify_event_t *)event;

                Trace() << Format::str("Mouse moved in window {}, at coordinates ({},{})",
                        motion->event, motion->event_x, motion->event_y );
            }
            break;
        case XCB_ENTER_NOTIFY: {
                xcb_enter_notify_event_t *enter = (xcb_enter_notify_event_t *)event;

                Trace() << Format::str("Mouse entered window {}, at coordinates ({},{})",
                    enter->event, enter->event_x, enter->event_y );
            }
            break;
        case XCB_LEAVE_NOTIFY: {
                xcb_leave_notify_event_t *leave_notify = (xcb_leave_notify_event_t *)event;

                Trace() << Format::str("Mouse left window {}, at coordinates ({},{})",
                    leave_notify->event, leave_notify->event_x, leave_notify->event_y );
            }
            break;
        case XCB_KEY_PRESS: {
                xcb_key_press_event_t *key_press = (xcb_key_press_event_t *)event;
                _traceModifiers(key_press->state);

                Trace() << Format::str("Key pressed in window {}", key_press->event);
            }
            break;
        case XCB_KEY_RELEASE: {
                xcb_key_release_event_t *key_release = (xcb_key_release_event_t *)event;
                _traceModifiers(key_release->state);

                Trace() << Format::str("Key released in window {}", key_release->event);
            }
            break;
        default: {
                Trace() << Format::str("Unknown event: {}", (uint_t)event->response_type);
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

xINLINE xcb_gc_t
XcbMsgBox::_gc_font_get (
    const xcb_screen_t     *screen,
    xcb_window_t      window,
    const char       *font_name
)
{
  uint32_t             value_list[3];
  xcb_void_cookie_t    cookie_font;
  xcb_void_cookie_t    cookie_gc;
  xcb_generic_error_t *error;
  xcb_font_t           font;
  xcb_gcontext_t       gc;
  uint32_t             mask;

  font = xcb_generate_id (_connection);
  cookie_font = xcb_open_font_checked (_connection, font,
                                       strlen (font_name),
                                       font_name);

  error = xcb_request_check (_connection, cookie_font);
  if (error) {
    fprintf (stderr, "ERROR: can't open font : %d\n", error->error_code);
    xcb_disconnect (_connection);
    return (xcb_gc_t)- 1;
  }

  gc = xcb_generate_id (_connection);
  mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT;
  value_list[0] = screen->black_pixel;
  value_list[1] = screen->white_pixel;
  value_list[2] = font;
  cookie_gc = xcb_create_gc_checked (_connection, gc, window, mask, value_list);
  error = xcb_request_check (_connection, cookie_gc);
  if (error) {
    fprintf (stderr, "ERROR: can't create gc : %d\n", error->error_code);
    xcb_disconnect (_connection);
    exit (-1);
  }

  cookie_font = xcb_close_font_checked (_connection, font);
  error = xcb_request_check (_connection, cookie_font);
  if (error) {
    fprintf (stderr, "ERROR: can't close font : %d\n", error->error_code);
    xcb_disconnect (_connection);
    exit (-1);
  }

  return static_cast<xcb_gc_t>(gc);
}
//-------------------------------------------------------------------------------------------------
xINLINE void
XcbMsgBox::_textDraw(
    const xcb_screen_t     *screen,
    xcb_window_t      window,
    int16_t           x1,
    int16_t           y1,
    const char       *label
)
{
  xcb_void_cookie_t    cookie_gc;
  xcb_void_cookie_t    cookie_text;
  xcb_generic_error_t *error;
  xcb_gcontext_t       gc;
  uint8_t              length;

  length = strlen (label);

  gc = _gc_font_get(screen, window, "7x13");

  cookie_text = ::xcb_image_text_8_checked (_connection, length, window, gc,
                                          x1,
                                          y1, label);
  error = ::xcb_request_check (_connection, cookie_text);
  if (error) {
    fprintf (stderr, "ERROR: can't paste text : %d\n", error->error_code);
    ::xcb_disconnect (_connection);
    exit (-1);
  }

  cookie_gc = ::xcb_free_gc (_connection, gc);
  error = ::xcb_request_check (_connection, cookie_gc);
  if (error) {
    fprintf (stderr, "ERROR: can't free gc : %d\n", error->error_code);
    ::xcb_disconnect (_connection);
    exit (-1);
  }
}
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

    Trace trace;
    trace << xT("Modifier mask: ");

    for (const char **modifier = modifiers; valueMask; valueMask >>= 1, ++ modifier) {
        if (valueMask & 1) {
            trace << *modifier;
        }
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, ui)
