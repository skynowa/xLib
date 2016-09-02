/**
 * \file   XcbMsgBox.inl
 * \brief  XCB message box
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "XcbMsgBox.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>


xNAMESPACE_BEGIN2(xlib, ui)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

const int16_t title_padding  = 8;
const int16_t left_default   = 32;
const int16_t top_default    = 32;
const int16_t width_default  = 300;
const int16_t height_default = 150;
const int16_t border_width   = 10;
const int16_t lineIndent     = 24;

xNAMESPACE_ANONYM_END
//-------------------------------------------------------------------------------------------------
xINLINE
XcbMsgBox::XcbMsgBox() :
    _conn    (xPTR_NULL),
    _screen  (xPTR_NULL),
    _windowId(0),
    _error   (xPTR_NULL)
{
    // Open the connection to the X server
    int_t screenPreferredNum = 0;
    _conn = ::xcb_connect(xPTR_NULL, &screenPreferredNum);
    xTEST_PTR(_conn);

    xcb_screen_iterator_t it = ::xcb_setup_roots_iterator( ::xcb_get_setup(_conn) );
    for ( ; it.rem; -- screenPreferredNum, ::xcb_screen_next(&it)) {
        if (screenPreferredNum != 0) {
            continue;
        }

        _screen = it.data;
        xTEST_PTR(_screen);

        break;
    }
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
XcbMsgBox::~XcbMsgBox()
{
    _error    = xPTR_NULL;
    _windowId = 0;
    _screen   = xPTR_NULL;

    if (_conn != xPTR_NULL) {
        (void_t)::xcb_disconnect(_conn);
        _conn = xPTR_NULL;
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

    int_t iRv = 0;

    std::vec_tstring_t text;
    String::split(a_text, Const::nl(), &text);

    // Create the window
    {
        _windowId = ::xcb_generate_id(_conn);

        uint32_t valueMask    = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        uint32_t valueList[2] = {_screen->white_pixel,
                                  XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
                                  XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
                                  XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
                                  XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE};

        _cookie = ::xcb_create_window(
            _conn,                         // connection
            XCB_COPY_FROM_PARENT,          // depth
            _windowId,                     // window ID
            _screen->root,                 // parent window
            0, 0,                          // x, y
            width_default, height_default, // width, height
            border_width,                  // border_width
            XCB_WINDOW_CLASS_INPUT_OUTPUT, // class
            _screen->root_visual,          // visual
            valueMask, valueList);         // masks
        xTEST_GR(_cookie.sequence, 0U);

        _setTitle(a_title);
        _autoResize(a_title, text);
        _setOnTop();

        // Map the window on the screen
        _cookie = ::xcb_map_window(_conn, _windowId);
        xTEST_GR(_cookie.sequence, 0U);

        iRv = ::xcb_flush(_conn);
        xTEST_GR(iRv, 0);
    }

    return _execute(text);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
XcbMsgBox::_setTitle(
    std::ctstring_t &a_text
)
{
    _cookie = ::xcb_change_property(_conn, XCB_PROP_MODE_REPLACE, _windowId, XCB_ATOM_WM_NAME,
        XCB_ATOM_STRING, 8, a_text.size(), a_text.c_str());
    xTEST_GR(_cookie.sequence, 0U);

    int_t iRv = ::xcb_flush(_conn);
    xTEST_GR(iRv, 0);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
XcbMsgBox::_setText(
    std::cvec_tstring_t &a_text
)
{
    const int16_t left = left_default;
    int16_t       top  = top_default;

    xFOR_EACH_CONST(std::cvec_tstring_t, it, a_text) {
        _setTextLine(left, top, *it);

        top += lineIndent;
    }
}
//-------------------------------------------------------------------------------------------------
struct MaxElementComp
{
    bool_t operator () (std::ctstring_t &a_it1, std::ctstring_t &a_it2) const
    {
        return a_it1.size() < a_it2.size();
    }
};

xINLINE void_t
XcbMsgBox::_autoResize(
    std::ctstring_t     &a_title,
    std::cvec_tstring_t &a_text
)
{
    if (a_title.empty() && a_text.empty()) {
        _resize(width_default, height_default);

        return;
    }

    int16_t width = 0;
    {
        // TODO: XcbMsgBox - fontWidth, calc
        const int16_t fontWidth = 6;

        if ( a_text.empty() ) {
            if ( a_title.empty() ) {
                width = width_default;
            } else {
                width = a_title.size() + title_padding * 2;
                width = width * fontWidth + left_default * 2;
            }
        } else {
            std::csize_t widthMax = std::max_element(a_text.begin(), a_text.end(), MaxElementComp())->size();

            if (a_title.size() > widthMax) {
                width = a_title.size() + title_padding * 2;
            } else {
                width = widthMax;
            }

            width = width * fontWidth + left_default * 2;
        }

        // fix max screen width
        if (width > _screen->width_in_pixels) {
            width = _screen->width_in_pixels;
        }
    }

    int16_t height = 0;
    {
        height = a_text.size() * lineIndent + top_default * 2;

        // fix max screen height
        if (height > _screen->height_in_pixels) {
            height = _screen->height_in_pixels;
        }
    }

    _resize(width, height);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
XcbMsgBox::_setOnTop()
{
    const uint32_t values[] = {XCB_STACK_MODE_ABOVE};

    _cookie = ::xcb_configure_window(_conn, _windowId, XCB_CONFIG_WINDOW_STACK_MODE, values);
    xTEST_GR(_cookie.sequence, 0U);
}
//-------------------------------------------------------------------------------------------------
xINLINE XcbMsgBox::ExModalResult
XcbMsgBox::_execute(
    std::cvec_tstring_t &a_text
)
{
    for ( ; ; ) {
        xcb_generic_event_t *event = ::xcb_wait_for_event(_conn);
        xCHECK_DO(event == xPTR_NULL, break);

        switch (event->response_type & ~0x80) {
        case XCB_EXPOSE: {
                xcb_expose_event_t *expose = (xcb_expose_event_t *)event;
                xUNUSED(expose);

            #if xLIB_XCB_MSGBOX_DEBUG
                Trace() << Format::str("Window {} exposed. "
                    "Region to be redrawn at location ({},{}), with dimension ({},{})",
                    expose->window, expose->x, expose->y, expose->width, expose->height );
            #endif

                _setText(a_text);
            }
            break;
        case XCB_BUTTON_PRESS: {
                xcb_button_press_event_t *button_press = (xcb_button_press_event_t *)event;
                xUNUSED(button_press);

            #if xLIB_XCB_MSGBOX_DEBUG
                Trace() << Format::str("Modifier mask: {}", _modifiersStr(button_press->state));

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
            #endif
            }
            break;
        case XCB_BUTTON_RELEASE: {
                xcb_button_release_event_t *button_release = (xcb_button_release_event_t *)event;
                xUNUSED(button_release);

            #if xLIB_XCB_MSGBOX_DEBUG
                Trace() << Format::str("Modifier mask: {}", _modifiersStr(button_release->state));
                Trace() << Format::str("Button {} released in window {}, at coordinates ({},{})",
                    button_release->detail, button_release->event, button_release->event_x,
                    button_release->event_y );
            #endif
            }
            break;
        case XCB_MOTION_NOTIFY: {
                xcb_motion_notify_event_t *motion = (xcb_motion_notify_event_t *)event;
                xUNUSED(motion);

            #if xLIB_XCB_MSGBOX_DEBUG
                Trace() << Format::str("Mouse moved in window {}, at coordinates ({},{})",
                        motion->event, motion->event_x, motion->event_y );
            #endif
            }
            break;
        case XCB_ENTER_NOTIFY: {
                xcb_enter_notify_event_t *enter = (xcb_enter_notify_event_t *)event;
                xUNUSED(enter);

            #if xLIB_XCB_MSGBOX_DEBUG
                Trace() << Format::str("Mouse entered window {}, at coordinates ({},{})",
                    enter->event, enter->event_x, enter->event_y );
            #endif
            }
            break;
        case XCB_LEAVE_NOTIFY: {
                xcb_leave_notify_event_t *leave_notify = (xcb_leave_notify_event_t *)event;
                xUNUSED(leave_notify);

            #if xLIB_XCB_MSGBOX_DEBUG
                Trace() << Format::str("Mouse left window {}, at coordinates ({},{})",
                    leave_notify->event, leave_notify->event_x, leave_notify->event_y );
            #endif
            }
            break;
        case XCB_KEY_PRESS: {
                xcb_key_press_event_t *key_press = (xcb_key_press_event_t *)event;

            #if xLIB_XCB_MSGBOX_DEBUG
                Trace() << Format::str("Modifier mask: {}", _modifiersStr(key_press->state));
                Trace() << Format::str("Key {} pressed in window {}", (uint_t)key_press->detail, key_press->event);
            #endif

                const xcb_keycode_t keyCode_Esc         = 9;
                const xcb_keycode_t keyCode_Enter       = 36;
                const xcb_keycode_t keyCode_KeyPadEnter = 104;

                switch (key_press->detail) {
                case keyCode_Esc:
                case keyCode_Enter:
                case keyCode_KeyPadEnter:
                    xBUFF_FREE(event);
                    goto l_endFor;

                    break;
                default:
                    break;
                }
            }
            break;
        case XCB_KEY_RELEASE: {
                xcb_key_release_event_t *key_release = (xcb_key_release_event_t *)event;
                xUNUSED(key_release);

            #if xLIB_XCB_MSGBOX_DEBUG
                Trace() << Format::str("Modifier mask: {}", _modifiersStr(key_release->state));
                Trace() << Format::str("Key released in window {}", key_release->event);
            #endif
            }
            break;
        default: {
            #if xLIB_XCB_MSGBOX_DEBUG
                Trace() << Format::str("Unknown event: {}", (uint_t)event->response_type);
            #endif
            }
            break;
        } // switch

        xBUFF_FREE(event);
    } // switch

l_endFor:
    return XcbMsgBox::mrOk;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE xcb_gcontext_t
XcbMsgBox::_fontGContext(
    std::ctstring_t &a_fontName
)
{
    xcb_font_t        fontId     = 0;
    xcb_void_cookie_t cookieFont = {};
    {
        fontId     = ::xcb_generate_id(_conn);
        cookieFont = ::xcb_open_font_checked(_conn, fontId, a_fontName.size(), xT2A(a_fontName).c_str());

        _error = ::xcb_request_check(_conn, cookieFont);
        xTEST(_error == xPTR_NULL);
    }

    xcb_gcontext_t gcontextId = 0;
    {
        gcontextId = ::xcb_generate_id(_conn);

        uint32_t valueMask    = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT;
        uint32_t valueList[3] = {_screen->black_pixel, _screen->white_pixel, fontId};

        xcb_void_cookie_t cookie_gc = ::xcb_create_gc_checked(_conn, gcontextId, _windowId, valueMask,
            valueList);

        _error = ::xcb_request_check(_conn, cookie_gc);
        xTEST(_error == xPTR_NULL);
    }

    cookieFont = ::xcb_close_font_checked(_conn, fontId);

    _error = ::xcb_request_check(_conn, cookieFont);
    xTEST(_error == xPTR_NULL);

    return gcontextId;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
XcbMsgBox::_resize(
    const int16_t &a_width,
    const int16_t &a_height
)
{
    const uint32_t values[] = {static_cast<uint32_t>(a_width), static_cast<uint32_t>(a_height)};

    _cookie = ::xcb_configure_window(_conn, _windowId,
        XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, values);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
XcbMsgBox::_setTextLine(
    const int16_t   &a_left,
    const int16_t   &a_top,
    std::ctstring_t &a_text
)
{
    xcb_void_cookie_t cookie_gc   = {};
    xcb_void_cookie_t cookie_text = {};

    xcb_gcontext_t gcontext = _fontGContext(xT("fixed"));

    cookie_text = ::xcb_image_text_8_checked(_conn, a_text.size(), _windowId, gcontext,
        a_left, a_top, xT2A(a_text).c_str());

    _error = ::xcb_request_check(_conn, cookie_text);
    xTEST(_error == xPTR_NULL);

    cookie_gc = ::xcb_free_gc(_conn, gcontext);

    _error = ::xcb_request_check(_conn, cookie_gc);
    xTEST(_error == xPTR_NULL);

    int_t iRv = ::xcb_flush(_conn);
    xTEST_GR(iRv, 0);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
XcbMsgBox::_modifiersStr(
    const uint32_t &a_valueMask
) const
{
    std::tstring_t sRv;

    uint32_t valueMask = a_valueMask;

    cptr_ctchar_t modifiers[] =
    {
        xT("Shift"),   xT("Lock"),    xT("Ctrl"),    xT("Alt"),
        xT("Mod2"),    xT("Mod3"),    xT("Mod4"),    xT("Mod5"),
        xT("Button1"), xT("Button2"), xT("Button3"), xT("Button4"), xT("Button5")
    };

    for (cptr_ctchar_t *modifier = modifiers; valueMask; valueMask >>= 1, ++ modifier) {
        if (valueMask & 1) {
            sRv += *modifier;
        }
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, ui)
