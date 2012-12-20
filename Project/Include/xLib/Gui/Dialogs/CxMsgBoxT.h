/**
 * \file  CxMsgBoxT.h
 * \brief message box
 */


#ifndef xLib_Gui_CxMsgBoxTH
#define xLib_Gui_CxMsgBoxTH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMsgBoxT :
    private CxNonCopyable
    /// message box
{
    public:
        enum ExModalResult
            /// modal result
        {
            #if   xOS_ENV_WIN
                mrAbort  = IDABORT,
                mrIgnore = IDIGNORE,
                mrRetry  = IDRETRY
            #elif xOS_ENV_UNIX
                mrAbort  = 25856,
                mrIgnore = 26112,
                mrRetry  = 26368
            #endif
        };

    #if xOS_ENV_WIN
        template <typename TextT, typename TitleT>
        static ExModalResult iShow   (const HWND &chWnd, const TextT &cText, const TitleT &cTitle, const uint_t &cuiType);
            ///< message box has parent window, with custom text, custom title, custom type
    #endif

        template <typename TextT, typename TitleT>
        static ExModalResult iShow   (const TextT &cText, const TitleT &cTitle, const uint_t &cuiType);
            ///< message box with custom text, custom title, custom type

        template <typename TextT, typename TitleT>
        static ExModalResult iShow   (const TextT &cText, const TitleT &cTitle);
            ///< message box with custom text, custom title, default type

        template <typename TextT>
        static ExModalResult iShow   (const TextT &cText);
            ///< message box with custom text, default title, default type

    private:
                            CxMsgBoxT();
            ///< constructor
        virtual            ~CxMsgBoxT();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxMsgBoxT.inl"
//---------------------------------------------------------------------------
#endif    //xLib_Gui_CxMsgBoxTH
