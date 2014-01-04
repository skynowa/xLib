/**
 * \file  CxMsgBox.inl
 * \brief message box
 */


#include <xLib/Filesystem/CxPath.h>

#if   xOS_ENV_WIN
    #include "Platform/CxMsgBox_win.inl"
#elif xOS_ENV_UNIX
    #include "Platform/CxMsgBox_unix.inl"
#elif xOS_ENV_MAC
    #include "Platform/CxMsgBox_mac.inl"
#endif

xNAMESPACE_BEGIN(NxLib)

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

    mrRes = show_impl(a_text, a_title, a_type);

    return mrRes;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
