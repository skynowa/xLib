/****************************************************************************
* Class name:  CxMsgBoxT
* Description: message box
* File name:   CxMsgBoxT.inl
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     27.04.2009 10:24:49
*
*****************************************************************************/


#include <xLib/Common/CxString.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: iShow
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
    return static_cast<EModalResult>( ::MessageBox(chWnd, CxString::lexical_cast(cText).c_str(), CxString::lexical_cast(cTitle).c_str(), cuiType) );
}
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
    return static_cast<EModalResult>( ::MessageBox(NULL, CxString::lexical_cast(cText).c_str(), CxString::lexical_cast(cTitle).c_str(), cuiType) );
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
    return static_cast<EModalResult>( ::MessageBox(NULL, CxString::lexical_cast(cText).c_str(), CxString::lexical_cast(cTitle).c_str(), MB_OK) );
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
	return static_cast<EModalResult>( ::MessageBox(NULL, CxString::lexical_cast(cText).c_str(), tString().c_str(), MB_OK) );
}
//---------------------------------------------------------------------------
