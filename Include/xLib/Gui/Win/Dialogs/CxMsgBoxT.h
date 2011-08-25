/**
 * \file  CxMsgBoxT.h
 * \brief message box
 */


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
            #if defined(xOS_WIN)
                mrAbort  = IDABORT,
                mrIgnore = IDIGNORE,
                mrRetry  = IDRETRY
            #elif defined(xOS_LINUX)
                mrAbort  = 3,
                mrIgnore = 5,
                mrRetry  = 4
            #endif
        };

    #if defined(xOS_WIN)
        template <typename TextT, typename TitleT>
        static EModalResult iShow       (const HWND chWnd, const TextT &cText, const TitleT &cTitle, const UINT cuiType);
    #endif

        template <typename TextT, typename TitleT>
        static EModalResult iShow       (const TextT &cText, const TitleT &cTitle, const UINT cuiType);

        template <typename TextT, typename TitleT>
        static EModalResult iShow       (const TextT &cText, const TitleT &cTitle);

        template <typename TextT>
        static EModalResult iShow       (const TextT &cText);

    private:

                            CxMsgBoxT   ();
        virtual            ~CxMsgBoxT   ();
};
//---------------------------------------------------------------------------
#include <Gui/Win/Dialogs/CxMsgBoxT.inl>
//---------------------------------------------------------------------------
#endif    //xLib_Gui_CxMsgBoxTH
