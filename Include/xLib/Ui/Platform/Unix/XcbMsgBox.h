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
    virtual       ~XcbMsgBox();

    ExModalResult  show(std::ctstring_t &text, std::ctstring_t &title, cExType &type) xWARN_UNUSED_RV;
		///< message box with custom text, custom title, custom type

private:
    xcb_connection_t    *_conn;		///< connection
    xcb_screen_t        *_screen;	///< screen
    xcb_window_t         _windowId;	///< window ID
    xcb_generic_error_t *_error;	///< error

    void           _setTitle(std::ctstring_t &text);
        ///< set title
    void           _setText(const int16_t &x, const int16_t &y, std::cvec_tstring_t &text);
        ///< set text
    void           _autoResize(std::cvec_tstring_t &text);
        ///< auto resize
    void           _traceModifiers(const uint32_t &valueMask) const;
        ///< trace names of modifiers present in mask

private:
    xcb_gcontext_t _fontGContext(std::ctstring_t &fontName) xWARN_UNUSED_RV;
		///<
    void           _resize(const int16_t &width, const int16_t &height);
        ///< resize
    void           _setTextLine(const int16_t &x, const int16_t &y, std::ctstring_t &text);
        ///< set text
};

xNAMESPACE_END2(xlib, ui)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "XcbMsgBox.cpp"
#endif
