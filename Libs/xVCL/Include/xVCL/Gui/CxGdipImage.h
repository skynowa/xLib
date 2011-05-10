/****************************************************************************
* Class name:  CxGdipImage
* Description: GDI+ картинка
* File name:   CxGdipImage.h
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     17.05.2010 13:55:40
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxGdiPlusImageH
#define CxGdiPlusImageH
//---------------------------------------------------------------------------
#include <xVCL/xCommon.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Gui/Win/GDI+/CxGdiplus.h>
#include <xLib/Gui/Win/GDI+/CxImage.h>
//---------------------------------------------------------------------------
class CxGdipImage : public TGraphicControl {
	__published:
		__property              PopupMenu;
		__property              Visible              = {default = true};

		__property              OnClick;
		__property              OnDblClick;
		__property              OnMouseDown;

	public:
		//encoder type
		enum EEncoderType {
			etBmp  = 0, 
			etJpeg = 1, 
			etGif  = 2, 
			etTiff = 3, 
			etPng  = 4
		};

		__fastcall              CxGdipImage            (Classes::TComponent *pAOwner);
		__fastcall virtual     ~CxGdipImage            ();

		BOOL                    bSetMargin             (LONG liMargin);
		BOOL                    bSetText               (const String &csText);

		BOOL                    bLoadFromFile          (const String &csFilePath);
		BOOL                    bLoadFromStream        (TMemoryStream *pmsStream);
		BOOL                    bSaveToFile            (const String &csFilePath, EEncoderType etType);
		BOOL                    bSaveToStream          (TMemoryStream *pmsStream, EEncoderType etType);

		BOOL                    bAssign                (CxGdipImage *pgdipImage);
		BOOL                    bRedraw                (BOOL bErase);
		BOOL                    bClear                 ();
		BOOL                    bDestroy               ();

	protected:
		virtual void __fastcall Paint                  ();
		virtual void __fastcall OnResize               ();

	private:
		BOOL                    _m_bRes;
		CxImage                 _m_imgImage;
		LONG                    _m_liMargin;
		String                  _m_sText;

		BOOL                    _m_bClear;

		BOOL                    _bMemoryStreamToIStream(TMemoryStream *pmsStream, IStream **ppisStream);
		BOOL                    _bIStreamToMemoryStream(IStream *ppisStream, TMemoryStream **pmsStream);
		void __fastcall         _vOnResize             (TObject *Sender);
};
//---------------------------------------------------------------------------
#endif //CxGdiPlusImageH
