/**
 * \file  CxMsgBox.inl
 * \brief message box
 */


#include <xLib/Filesystem/CxPath.h>
#include "Platform/CxMsgBox_internal.inl"

#if   xOS_ENV_WIN
    #include "Platform/CxMsgBox_win.inl"
#elif xOS_ENV_UNIX
    #include "Platform/CxMsgBox_unix.inl"
#elif xOS_ENV_APPLE
    #include "Platform/CxMsgBox_mac.inl"
#endif

xNAMESPACE2_BEGIN(xlib, gui)

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
    ExModalResult mrRes = mrAbort;
    std::string   title = a_title;

    // title
    if ( title.empty() ) {
        title = CxPath(CxPath::exe()).fileName();
    }

    mrRes = _show_impl(a_text, a_title, a_type);

    return mrRes;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, gui)
