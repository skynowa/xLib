/**
 * \file  CxMsgBoxT.inl
 * \brief message box
 */


#include <xLib/Common/CxString.h>
#include <xLib/Common/CxConsole.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: iShow
#if defined(xOS_WIN)
template <class TextT, class TitleT>
/*static*/
CxMsgBoxT::EModalResult
CxMsgBoxT::iShow(
    const HWND    chWnd,
    const TextT  &cText,
    const TitleT &cTitle,
    const UINT    cuiType
)
{
    EModalResult mrRes = mrAbort;

    mrRes = static_cast<EModalResult>( ::MessageBox(chWnd, CxString::lexical_cast(cText).c_str(), CxString::lexical_cast(cTitle).c_str(), cuiType) );

    return mrRes;
}
#endif
//---------------------------------------------------------------------------
//DONE: iShow
template <class TextT, class TitleT>
/*static*/
CxMsgBoxT::EModalResult
CxMsgBoxT::iShow(
    const TextT  &cText,
    const TitleT &cTitle,
    const UINT    cuiType
)
{
    EModalResult mrRes = mrAbort;

#if defined(xOS_WIN)
    mrRes = static_cast<EModalResult>( ::MessageBox(NULL, CxString::lexical_cast(cText).c_str(), CxString::lexical_cast(cTitle).c_str(), cuiType) );
#elif defined(xOS_LINUX)
    mrRes = CxConsole::iMsgBox(CxString::lexical_cast(cText), CxString::lexical_cast(cTitle), cuiType);
#endif

    return mrRes;
}
//---------------------------------------------------------------------------
//DONE: iShow
template <class TextT, class TitleT>
/*static*/
CxMsgBoxT::EModalResult
CxMsgBoxT::iShow(
    const TextT  &cText,
    const TitleT &cTitle
)
{
    EModalResult mrRes = mrAbort;

#if defined(xOS_WIN)
    mrRes = static_cast<EModalResult>( ::MessageBox(NULL, CxString::lexical_cast(cText).c_str(), CxString::lexical_cast(cTitle).c_str(), MB_OK) );
#elif defined(xOS_LINUX)
    mrRes = CxConsole::iMsgBox((CxString::lexical_cast(cText), CxString::lexical_cast(cTitle), 0U);
#endif

    return mrRes;
}
//---------------------------------------------------------------------------
//DONE: iShow
template <class TextT>
/*static*/
CxMsgBoxT::EModalResult
CxMsgBoxT::iShow(
    const TextT &cText
)
{
    EModalResult mrRes = mrAbort;

#if defined(xOS_WIN)
	mrRes = static_cast<EModalResult>( ::MessageBox(NULL, CxString::lexical_cast(cText).c_str(), std::tstring().c_str(), MB_OK) );
#elif defined(xOS_LINUX)
    mrRes = CxConsole::iMsgBox((CxString::lexical_cast(cText), CxConst::xSTR_EMPTY, 0U);
#endif

    return mrRes;
}
//---------------------------------------------------------------------------
