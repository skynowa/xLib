/****************************************************************************
* Class name:  CxMsgBoxT
* Description: message box
* File name:   CxMsgBoxT.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     27.04.2009 10:24:49
*
*****************************************************************************/


#ifndef xLib_Gui_CxMsgBoxTH
#define xLib_Gui_CxMsgBoxTH
//---------------------------------------------------------------------------
#include <xLib/Gui/Win/xCommon.h>
//---------------------------------------------------------------------------
class CxMsgBoxT : 
    public CxNonCopyable 
{
    public:
        enum EModalResult {
            mrAbort  = IDABORT,
            mrRetry  = IDRETRY,
            mrIgnore = IDIGNORE,
        };

        template <typename TextT, typename TitleT>
        static EModalResult iShow(const HWND chWnd, const TextT &cText, const TitleT &cTitle, const UINT cuiType);

        template <typename TextT, typename TitleT>
        static EModalResult iShow(const TextT &cText, const TitleT &cTitle, const UINT cuiType);

        template <typename TextT, typename TitleT>
        static EModalResult iShow(const TextT &cText, const TitleT &cTitle);

        template <typename TextT>
        static EModalResult iShow(const TextT &cText);

     private:
                 CxMsgBoxT() {};
        virtual ~CxMsgBoxT() {};
};
//---------------------------------------------------------------------------
#include <Gui/Win/Dialogs/CxMsgBoxT.inl>
//---------------------------------------------------------------------------
#endif    //xLib_Gui_CxMsgBoxTH
