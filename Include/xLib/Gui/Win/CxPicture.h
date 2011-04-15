/****************************************************************************
* Class name:  CxPicture
* Description: картинка
* File name:   CxPicture.h
* Compilers:   Visual C++ 2008
* String type: Unicode, Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     20.07.2010 20:40:41
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLib_Gui_CxPictureH
#define XLib_Gui_CxPictureH
//---------------------------------------------------------------------------
#include <XLib/GUI/CxWindow.h>
//---------------------------------------------------------------------------
class CxPicture : public CxWindow {
	public:
		//-------------------------------------
		//константы

		//стиль изображения
		enum EViewStyle {
			vsUknown       = 0,
			vsBitmap       = SS_BITMAP,
			vsIcon         = SS_ICON,
			vsCursor       = SS_ICON,
			vsEnhMetaFile  = SS_ENHMETAFILE,
			vsOwnerDraw    = SS_OWNERDRAW
    	};

		//тип изображения
		enum EImageType {
			itUknown      = - 1,
			itBitmap      = IMAGE_BITMAP,
			itIcon	      = IMAGE_ICON,
			itCursor      = IMAGE_CURSOR,
			itEnhMetaFile = IMAGE_ENHMETAFILE
		};
			
		           CxPicture    ();
		virtual   ~CxPicture    ();

		BOOL       bCreateRes   (INT iID, CxWindow *pwndParent);
		
		//-------------------------------------
		//сообщения
		BOOL       bSetViewStyle(EViewStyle vsViewStyle);
		BOOL       bSetImage    (EImageType itImageType, HANDLE hImage);
		
		//-------------------------------------
		//события

	private:
		EViewStyle _m_vsViewStyle;
};
//---------------------------------------------------------------------------
#endif	//XLib_Gui_CxPictureH
