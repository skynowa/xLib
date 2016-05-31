/**
 * \file   XcbMsgBox.h
 * \brief  XCB message box
 */


#pragma once

#include <xLib/Core/Core.h>

#if xHAVE_XCB
    #include <xcb/xcb.h>
#endif
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, ui)

class XcbMsgBox
    ///< XCB message box
    ///< FAQ: https://xcb.freedesktop.org/tutorial/events/
    ///<      https://www.x.org/releases/X11R7.6/doc/libxcb/tutorial/index.html
{
public:
    enum ExType
        ///< windows type
    {
        tpUnknown,
        tpOk
    };
    xTYPEDEF_CONST(ExType);

    enum ExModalResult
        /// modal result
    {
        mrUnknown,
        mrOk
    };
    xTYPEDEF_CONST(ExModalResult);

                      XcbMsgBox();
    virtual          ~XcbMsgBox();

    ExModalResult     show(std::ctstring_t &text, std::ctstring_t &title, cExType &type)
                            xWARN_UNUSED_RV;

private:
    xcb_connection_t *_connection;

    xcb_gc_t
    _gc_font_get (
                 const xcb_screen_t     *screen,
                 xcb_window_t      window,
                 const char       *font_name);
    void              _textDraw(const xcb_screen_t *screen, xcb_window_t window, int16_t x1, int16_t y1,
                            const char *label);
        ///<
    void              _traceModifiers(const uint32_t valueMask) const;
        ///< trace names of modifiers present in mask
};

xNAMESPACE_END2(xlib, ui)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "XcbMsgBox.cpp"
#endif
