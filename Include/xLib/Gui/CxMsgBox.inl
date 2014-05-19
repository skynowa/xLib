/**
 * \file   CxMsgBox.inl
 * \brief  message box
 */


#include <xLib/Filesystem/CxPath.h>

#include "Platform/CxMsgBox_internal.inl"

#if   xENV_WIN
    #include "Platform/Win/CxMsgBox_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxMsgBox.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxMsgBox.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/CxMsgBox.inl"
    #endif
#endif

xNAMESPACE_BEGIN2(xlib, gui)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxMsgBox::ExModalResult
CxMsgBox::show(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
    return _show_impl(a_text, a_title, a_type);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, gui)
