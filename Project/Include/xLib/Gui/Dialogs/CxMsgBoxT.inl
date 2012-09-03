/**
 * \file  CxMsgBoxT.inl
 * \brief message box
 */


#include <xLib/Common/CxString.h>
#include <xLib/Common/CxConsole.h>
#include <xLib/Filesystem/CxPath.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
#if xOS_ENV_WIN

template <class TextT, class TitleT>
/*static*/
CxMsgBoxT::ExModalResult
CxMsgBoxT::iShow(
    const HWND    chWnd,
    const TextT  &cText,
    const TitleT &cTitle,
    const uint_t  cuiType
)
{
    ExModalResult mrRes = mrAbort;

    mrRes = static_cast<ExModalResult>( ::MessageBox(
                            chWnd,
                            CxString::lexical_cast(cText).c_str(),
                            CxString::lexical_cast(cTitle).c_str(),
                            cuiType) );

    return mrRes;
}

#endif
//---------------------------------------------------------------------------
template <class TextT, class TitleT>
/*static*/
CxMsgBoxT::ExModalResult
CxMsgBoxT::iShow(
    const TextT  &cText,
    const TitleT &cTitle,
    const uint_t    cuiType
)
{
    ExModalResult mrRes = mrAbort;

#if xOS_ENV_WIN
    mrRes = static_cast<ExModalResult>( ::MessageBox(
                            NULL,
                            CxString::lexical_cast(cText).c_str(),
                            CxString::lexical_cast(cTitle).c_str(),
                            cuiType) );
#elif xOS_ENV_UNIX
    std::tstring_t sMsg = CxString::sFormat(
                            xT("xmessage -center \"%s\" -title \"%s\" -buttons \"%s\""),
                            CxString::lexical_cast(cText).c_str(),
                            CxString::lexical_cast(cTitle).c_str(),
                            xT("Abort, Ignore, Retry"));

    mrRes = static_cast<ExModalResult>( std::xTSYSTEM(sMsg.c_str()) );
#endif

    return mrRes;
}
//---------------------------------------------------------------------------
template <class TextT, class TitleT>
/*static*/
CxMsgBoxT::ExModalResult
CxMsgBoxT::iShow(
    const TextT  &cText,
    const TitleT &cTitle
)
{
    ExModalResult mrRes = mrAbort;

#if xOS_ENV_WIN
    mrRes = static_cast<ExModalResult>( ::MessageBox(
                            NULL,
                            CxString::lexical_cast(cText).c_str(),
                            CxString::lexical_cast(cTitle).c_str(),
                            MB_OK) );
#elif xOS_ENV_UNIX
    std::tstring_t sMsg = CxString::sFormat(
                            xT("xmessage -center \"%s\" -title \"%s\" -buttons \"%s\""),
                            CxString::lexical_cast(cText).c_str(),
                            CxString::lexical_cast(cTitle).c_str(),
                            xT("Ok"));

    mrRes = static_cast<ExModalResult>( std::xTSYSTEM(sMsg.c_str()) );
#endif

    return mrRes;
}
//---------------------------------------------------------------------------
template <class TextT>
/*static*/
CxMsgBoxT::ExModalResult
CxMsgBoxT::iShow(
    const TextT &cText
)
{
    ExModalResult mrRes = mrAbort;

#if xOS_ENV_WIN
    mrRes = static_cast<ExModalResult>( ::MessageBox(
                            NULL,
                            CxString::lexical_cast(cText).c_str(),
                            CxPath::sGetFileName( CxPath::sGetExe() ).c_str(),
                            MB_OK) );
#elif xOS_ENV_UNIX
    std::tstring_t sMsg = CxString::sFormat(
                            xT("xmessage -center \"%s\" -title \"%s\" -buttons \"%s\""),
                            CxString::lexical_cast(cText).c_str(),
                            xT("Message box"),
                            xT("Ok"));

    mrRes = static_cast<ExModalResult>( std::xTSYSTEM(sMsg.c_str()) );
#endif

    return mrRes;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
