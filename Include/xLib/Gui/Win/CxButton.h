/****************************************************************************
* Class name:  CxButton
* Description: работа с кнопкой
* File name:   CxButton.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     23.07.2009 13:11:14
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLib_Gui_CxButtonH
#define XLib_Gui_CxButtonH
//---------------------------------------------------------------------------
#include <XLib/Gui/xCommon.h>
#include <XLib/Gui/CxWindow.h>
#include <XLib/GUI/CxButtonBase.h>
//---------------------------------------------------------------------------
class CxButton : public CxButtonBase {
	public:
		//-------------------------------------
		//константы

		//стиль (изображение/текст)
		enum EViewStyle {
			vsText     = BS_TEXT,
			vsBitmap   = BS_BITMAP,
			vsIcon     = BS_ICON
		};
		
		//тип изображения
		enum EImageType {
			itBitmap   = IMAGE_BITMAP,
			itIcon	   = IMAGE_ICON,
			itCursor   = IMAGE_CURSOR,
			itMetaFile = IMAGE_ENHMETAFILE
		};	
				
			     CxButton        ();
		virtual ~CxButton        ();

		BOOL     bCreateRes      (INT iID, CxWindow *pwndParent);

		//-------------------------------------
		//сообщения
		BOOL     bSetViewStyle   (EViewStyle vsViewStyle);	
		BOOL     bSetImage       (EImageType itImageType, HANDLE hImage);

		//-------------------------------------
		//события
		VOID     vSet_OnClick    (SClosureT<VOID(CxButton *pbtnSender)> vCallback);
		VOID     vSet_OnDbClick  (SClosureT<VOID(CxButton *pbtnSender)> vCallback);
		VOID     vSet_OnKillFocus(SClosureT<VOID(CxButton *pbtnSender)> vCallback);
		VOID     vSet_OnSetFocus (SClosureT<VOID(CxButton *pbtnSender)> vCallback);

	private:
		EViewStyle _m_vsViewStyle;

		virtual void vOnClick    () { _vHandler_OnClick    (this); }
		virtual void vOnDbClick  () { _vHandler_OnDbClick  (this); }
		virtual void vOnKillFocus() { _vHandler_OnKillFocus(this); }
		virtual void vOnSetFocus () { _vHandler_OnSetFocus (this); }


		//callback методы
		SClosureT<VOID(CxButton *pthSender)> _m_vCallback_OnClick;
		VOID                                 _vHandler_OnClick(CxButton *pthSender);

		SClosureT<VOID(CxButton *pthSender)> _m_vCallback_OnDbClick;
		VOID                                 _vHandler_OnDbClick(CxButton *pthSender);

		SClosureT<VOID(CxButton *pthSender)> _m_vCallback_OnKillFocus;
		VOID                                 _vHandler_OnKillFocus(CxButton *pthSender);

		SClosureT<VOID(CxButton *pthSender)> _m_vCallback_OnSetFocus;
		VOID                                 _vHandler_OnSetFocus(CxButton *pthSender);
};
//---------------------------------------------------------------------------
#endif	//XLib_Gui_CxButtonH












//GetParent()->PostMessage (WM_COMMAND, MAKELONG (GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);,