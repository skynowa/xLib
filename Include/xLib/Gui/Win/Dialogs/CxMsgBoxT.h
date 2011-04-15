/****************************************************************************
* Class name:  CxMsgBoxT
* Description: message box
* File name:   CxMsgBoxT.h
* Compilers:   Visual C++ 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     27.04.2009 10:24:49
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Gui_CxMsgBoxTH
#define xLib_Gui_CxMsgBoxTH
//---------------------------------------------------------------------------
#include <xLib/Gui/Win/xCommon.h>
#include <xLib/Common/CxString.h>
//---------------------------------------------------------------------------
class CxMsgBoxT : public CxNonCopyable  {
    public:
        //EModalResult -
        enum EModalResult {
            mrAbort  = IDABORT,
            mrRetry  = IDRETRY,
            mrIgnore = IDIGNORE,
        };

        //---------------------------------------------------------------------------
        //DONE: iShow
        template <typename TextT, typename TitleT>
        static
        EModalResult
        iShow(HWND hWnd, TextT Text, TitleT Title, UINT uiType) {
            return static_cast<EModalResult>( ::MessageBox(hWnd, CxString::lexical_cast(Text).c_str(), CxString::lexical_cast(Title).c_str(), uiType) );
        }

        //---------------------------------------------------------------------------
        //DONE: iShow
        template <typename TextT, typename TitleT>
        static
        EModalResult
        iShow(TextT Text, TitleT Title, UINT uiType) {
            return static_cast<EModalResult>( ::MessageBox(NULL, CxString::lexical_cast(Text).c_str(), CxString::lexical_cast(Title).c_str(), uiType) );
        }

        //---------------------------------------------------------------------------
        //DONE: iShow
        template <typename TextT, typename TitleT>
        static
        EModalResult
        iShow(TextT Text, TitleT Title) {
            return static_cast<EModalResult>( ::MessageBox(NULL, CxString::lexical_cast(Text).c_str(), CxString::lexical_cast(Title).c_str(), MB_OK) );
        }

        //---------------------------------------------------------------------------
        //DONE: iShow
        template <typename TextT>
        static
        EModalResult
        iShow(TextT Text) {
            return static_cast<EModalResult>( ::MessageBox(NULL, CxString::lexical_cast(Text).c_str(), xT(""), MB_OK) );
        }

    private:
                 CxMsgBoxT();
        virtual ~CxMsgBoxT();
};
//---------------------------------------------------------------------------
#endif	//xLib_Gui_CxMsgBoxTH
