/**
 * \file  CxMsgBoxT.inl
 * \brief message box
 */


#include <xLib/Common/CxString.h>
#include <xLib/Common/CxConsole.h>
#include <xLib/Filesystem/CxPath.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
#if xOS_ENV_WIN

template <typename TextT, class TitleT>
/* static */
CxMsgBoxT::ExModalResult
CxMsgBoxT::show(
    const HWND   &a_chWnd,
    const TextT  &a_cText,
    const TitleT &a_cTitle,
    const uint_t &a_cuiType
)
{
    ExModalResult mrRes = mrAbort;

    mrRes = static_cast<ExModalResult>( ::MessageBox(
                            a_chWnd,
                            CxString::cast(a_cText).c_str(),
                            CxString::cast(a_cTitle).c_str(),
                            a_cuiType) );

    return mrRes;
}

#endif
//------------------------------------------------------------------------------
template <typename TextT, class TitleT>
/* static */
CxMsgBoxT::ExModalResult
CxMsgBoxT::show(
    const TextT  &a_cText,
    const TitleT &a_cTitle,
    const uint_t &a_cuiType
)
{
    ExModalResult mrRes = mrAbort;

#if   xOS_ENV_WIN
    mrRes = static_cast<ExModalResult>( ::MessageBox(
                            NULL,
                            CxString::cast(a_cText).c_str(),
                            CxString::cast(a_cTitle).c_str(),
                            a_cuiType) );
#elif xOS_ENV_UNIX
    std::tstring_t sMsg = CxString::format(
                            xT("xmessage -center \"%s\" -title \"%s\" -buttons \"%s\""),
                            CxString::cast(a_cText).c_str(),
                            CxString::cast(a_cTitle).c_str(),
                            xT("Abort, Ignore, Retry"));

    mrRes = static_cast<ExModalResult>( std::xTSYSTEM(sMsg.c_str()) );
#endif

    return mrRes;
}
//------------------------------------------------------------------------------
template <typename TextT, class TitleT>
/* static */
CxMsgBoxT::ExModalResult
CxMsgBoxT::show(
    const TextT  &a_cText,
    const TitleT &a_cTitle
)
{
    ExModalResult mrRes = mrAbort;

#if   xOS_ENV_WIN
    mrRes = static_cast<ExModalResult>( ::MessageBox(
                            NULL,
                            CxString::cast(a_cText).c_str(),
                            CxString::cast(a_cTitle).c_str(),
                            MB_OK) );
#elif xOS_ENV_UNIX
    std::tstring_t sMsg = CxString::format(
                            xT("xmessage -center \"%s\" -title \"%s\" -buttons \"%s\""),
                            CxString::cast(a_cText).c_str(),
                            CxString::cast(a_cTitle).c_str(),
                            xT("Ok"));

    mrRes = static_cast<ExModalResult>( std::xTSYSTEM(sMsg.c_str()) );
#endif

    return mrRes;
}
//------------------------------------------------------------------------------
template <typename TextT>
/* static */
CxMsgBoxT::ExModalResult
CxMsgBoxT::show(
    const TextT &a_cText
)
{
    ExModalResult mrRes = mrAbort;

#if   xOS_ENV_WIN
    mrRes = static_cast<ExModalResult>( ::MessageBox(
                            NULL,
                            CxString::cast(a_cText).c_str(),
                            CxPath(CxPath::exe()).fileName().c_str(),
                            MB_OK) );
#elif xOS_ENV_UNIX
    std::tstring_t sMsg = CxString::format(
                            xT("xmessage -center \"%s\" -title \"%s\" -buttons \"%s\""),
                            CxString::cast(a_cText).c_str(),
                            xT("Message box"),
                            xT("Ok"));

    mrRes = static_cast<ExModalResult>( std::xTSYSTEM(sMsg.c_str()) );
#endif

    return mrRes;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
