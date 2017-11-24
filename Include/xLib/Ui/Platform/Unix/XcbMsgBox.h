/**
 * \file   XcbMsgBox.h
 * \brief  XCB message box
 */


#pragma once


#include <xLib/Core/Core.h>

#if cmXCB_FOUND

#include <xcb/xcb.h>
//-------------------------------------------------------------------------------------------------
#define xLIB_XCB_MSGBOX_DEBUG 0

xNAMESPACE_BEGIN2(xl, ui)

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
    xcb_void_cookie_t    _cookie;	///< cookie
    xcb_generic_error_t *_error;	///< error

    void_t         _setTitle(std::ctstring_t &text);
        ///< set title
    void_t         _setText(std::cvec_tstring_t &text);
        ///< set text
    void_t         _autoResize(std::ctstring_t &title, std::cvec_tstring_t &text);
        ///< auto resize
    void_t         _setOnTop();
        ///< move the window on the top of the stack
	ExModalResult  _execute(std::cvec_tstring_t &text);
		///< execute

private:
    xcb_gcontext_t _fontGContext(std::ctstring_t &fontName) xWARN_UNUSED_RV;
		///< get font gcontext
    void_t         _resize(const uint32_t &width, const uint32_t &height);
        ///< resize
    void_t         _setTextLine(const int16_t &left, const int16_t &top, std::ctstring_t &text);
        ///< set text
    std::tstring_t _modifiersStr(const uint32_t &valueMask) const;
        ///< trace names of modifiers present in mask
};

xNAMESPACE_END2(xl, ui)
//-------------------------------------------------------------------------------------------------
#endif // cmXCB_FOUND
