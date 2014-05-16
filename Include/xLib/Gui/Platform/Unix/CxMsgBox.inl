/**
 * \file   CxMsgBox.inl
 * \brief  message box
 */


#include <xLib/Core/CxString.h>

#if xHAVE_XCB && 0
    #include <xcb/xcb.h>
#endif

xNAMESPACE2_BEGIN(xlib, gui)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxMsgBox::ExModalResult
CxMsgBox::_show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
    ExModalResult mrRv = mrUnknown;

#if xHAVE_XCB && 0
    xUNUSED(a_text);
    xUNUSED(a_title);
    xUNUSED(a_type);

    xUNUSED(internal::enums::types);
    xUNUSED(internal::enums::modalResults);

    int_t             iRv        = 0;
    xcb_connection_t *connection = xPTR_NULL;
    xcb_screen_t     *screen     = xPTR_NULL;
    xcb_drawable_t    windowId   = 0U;
    xcb_gcontext_t    foreground = 0U;
    xcb_gcontext_t    background = 0U;
    uint32_t          mask       = 0U;
    uint32_t          values[2]  = {0U, 0U};

    xcb_rectangle_t rectangles[] = {
        {40, 40, 20, 20},
    };

    connection = ::xcb_connect(xPTR_NULL, xPTR_NULL);

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
    iRv = ::xcb_flush(connection);
    xTEST_GR(iRv, 0);

    // while ( (event = ::xcb_wait_for_event(connection)) ) {
    for ( ; ; ) {
        xcb_generic_event_t *event = ::xcb_wait_for_event(connection);
        xTEST_PTR(event);

        switch (event->response_type & ~0x80) {
        case XCB_EXPOSE:
            ::xcb_poly_rectangle(connection, windowId, foreground, 1, rectangles);
            ::xcb_image_text_8(connection, static_cast<uint8_t>( a_text.size() ), windowId,
                background, 20, 20, a_text.c_str());
            iRv = ::xcb_flush(connection);
            xTEST_GR(iRv, 0);
            break;
        case XCB_KEY_PRESS:
            break;
        default:
            CxTrace() << xT("Unknown event: ") << event->response_type;
            break;
        }

        xBUFF_FREE(event);
    }

    if (connection != xPTR_NULL) {
        (void_t)::xcb_disconnect(connection);
        connection = xPTR_NULL;
    }
#else
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
