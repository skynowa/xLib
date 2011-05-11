/****************************************************************************
* Class name:  CxGdipImage
* Description: GDI+ картинка
* File name:   CxGdipImage.cpp
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     17.05.2010 13:55:40
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xVCL/Gui/CxGdipImage.h>

#include <Ole2.h>
#include <xVCL/Units/Graphics/TColorConverter.cpp>


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxGdipImage (конструктор)
__fastcall CxGdipImage::CxGdipImage(Classes::TComponent *pAOwner) :
	TGraphicControl(pAOwner),
	_m_bRes        (FALSE),
	_m_imgImage    (),
	_m_liMargin    (2),
	_m_sText       (),
	_m_bClear      (TRUE)
{

}
//---------------------------------------------------------------------------
//TODO: ~CxGdipImage (деструктор)
/*virtual*/
__fastcall CxGdipImage::~CxGdipImage() {

}
//---------------------------------------------------------------------------
//TODO: - bSetMargin (отступы) 
BOOL CxGdipImage::bSetMargin(LONG liMargin) {
	/*DEBUG*/// _m_imgImage - n/a
	/*DEBUG*/// liMargin    - n/a

	xCHECK_DO(0 > liMargin, liMargin = 0);

	_m_liMargin = liMargin + 2;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSetText (текст) 
BOOL CxGdipImage::bSetText(const String &csText) {
	/*DEBUG*/// _m_imgImage - n/a
	/*DEBUG*/// csText    - n/a

	_m_sText = csText;

	_m_bRes = bRedraw(TRUE);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bLoadFromFile (загрузка из файла)
BOOL CxGdipImage::bLoadFromFile(const String &csFilePath) {
	/*DEBUG*/// _m_imgImage 
	/*DEBUG*/xASSERT_RET(false == csFilePath.IsEmpty(), FALSE);

	_m_bRes = _m_imgImage.bLoad(xD2S(csFilePath));
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	_m_bRes = bRedraw(TRUE);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	_m_bClear = FALSE;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bLoadFromStream (загрузка из потока)
BOOL CxGdipImage::bLoadFromStream(TMemoryStream *pmsStream) {
	/*DEBUG*/// _m_imgImage
	/*DEBUG*/xASSERT_RET(NULL != pmsStream, FALSE);

	IStream *pisStream = NULL;
	
	//TMemoryStream -> IStream
	_m_bRes = _bMemoryStreamToIStream(pmsStream, &pisStream);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes,   FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pisStream, FALSE);

	_m_bRes = _m_imgImage.bLoad(pisStream);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	xRELEASE(pisStream);

	_m_bRes = bRedraw(TRUE);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	_m_bClear = FALSE;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSaveToFile
BOOL CxGdipImage::bSaveToFile(const String &csFilePath, EEncoderType etType) {
	/*DEBUG*/// _m_imgImage
	/*DEBUG*/xASSERT_RET(false == csFilePath.IsEmpty(), FALSE);

	_m_bRes = _m_imgImage.bSave(xD2S(csFilePath), static_cast<CxImage::EEncoderType>(etType)); 	//FIXME: CxImage::etPng
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSaveToStream
BOOL CxGdipImage::bSaveToStream(TMemoryStream *pmsStream, EEncoderType etType) {
	/*DEBUG*/// _m_imgImage
	/*DEBUG*/xASSERT_RET(NULL != pmsStream, FALSE);

	IStream *pisStream = NULL;
	HRESULT  hrRes     = NULL;
	HGLOBAL  hGlobal   = NULL;

	hGlobal = ::GlobalAlloc(GMEM_MOVEABLE, 0);
	/*DEBUG*/xASSERT_RET(NULL != hGlobal, FALSE);

	//create IStream* from global memory
	hrRes = ::CreateStreamOnHGlobal(hGlobal, TRUE, &pisStream);
	/*DEBUG*/xASSERT_RET(SUCCEEDED(hrRes), FALSE);



	

	_m_bRes = _m_imgImage.bSave(pisStream, static_cast<CxImage::EEncoderType>(etType)); 	//FIXME: CxImage::etPng
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	_m_bRes = _bIStreamToMemoryStream(pisStream, &pmsStream);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	//TODO: GlobalFree(hGlobal); ???

	xRELEASE(pisStream);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bAssign ()
BOOL CxGdipImage::bAssign(CxGdipImage *pgdipImage) {
	/*DEBUG*/// _m_imgImage
	/*DEBUG*/xASSERT_RET(NULL !=  pgdipImage, FALSE);

//	std::auto_ptr<TMemoryStream> apmsMS(new TMemoryStream());
//    /*DEBUG*/xASSERT_RET(NULL != apmsMS.get(), FALSE);
//
//	apmsMS->Position = 0;
//	_m_bRes = pgdipImage->bSaveToStream(apmsMS.get());
//	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes,      FALSE);
//	/*DEBUG*/xASSERT_RET(0     < apmsMS->Size , FALSE);
//
//	apmsMS->Position = 0;
//	_m_bRes = this->bLoadFromStream(apmsMS.get());
//	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
//
//
////	_m_bRes = pgdipImage->bSaveToFile(xT("C:\\tmp.png"));
////	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
////
////	_m_bRes = bLoadFromFile(xT("C:\\tmp.png"));
////	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bRedraw ()
BOOL CxGdipImage::bRedraw(BOOL bErase) {
	/*DEBUG*/// _m_imgImage

	///Paint();
	/*DEBUG*/// n/a

    RECT rcClient = {0};

    _m_bRes = ::GetClientRect(Parent->Handle, &rcClient); 
    xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_bRes = ::InvalidateRect(Parent->Handle, &rcClient, bErase);
    xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bClear ()
BOOL CxGdipImage::bClear() {
	/*DEBUG*/// _m_imgImage

	xCHECK_DO(FALSE == _m_imgImage.bIsLoaded(), TRUE);

	////HDC hDc = ::GetDC(Parent->Handle);
	/////*DEBUG*/xASSERT_RET(NULL != hDc, FALSE);

	{
		////BYTE ucRed, ucGreen, ucBlue;

		////vTColorToRGB(clBtnFace, &ucRed, &ucGreen, &ucBlue);
		
		////_m_bRes = _m_imgImage.bClear(hDc, /*Gdiplus::Color(255, 0, 0, 255)*/ Gdiplus::Color(255, ucRed, ucGreen, ucBlue));
		/////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
	}

	////INT iRes = ::ReleaseDC(Parent->Handle, hDc);
	/////*DEBUG*/xASSERT_RET(0 != iRes, FALSE);

	_m_bClear = TRUE;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bDestroy ()
BOOL CxGdipImage::bDestroy() {
	/*DEBUG*/// _m_imgImage

	xCHECK_DO(FALSE == _m_imgImage.bIsLoaded(), TRUE);

	_m_bRes = _m_imgImage.bDestroy();
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	_m_bRes = bRedraw(TRUE);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	_m_bClear = TRUE;

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	protected
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: Paint (отрисовка CxImage)
/*virtual*/
void __fastcall CxGdipImage::Paint() {
	/*DEBUG*/// _m_imgImage - n/a


	//-------------------------------------
	//вывод текста
	if (TRUE == _m_bClear && false == _m_sText.IsEmpty()) {
		HDC hDc = ::GetDC(Parent->Handle);
		/*DEBUG*/xASSERT_DO(NULL != hDc, return);

		{
			Gdiplus::Status stRes;

			//Создаем контекст рисования и устанавливаем пиксельную систему координат
			Gdiplus::Graphics grfGraphics(hDc);
			grfGraphics.SetPageUnit(Gdiplus::UnitPixel);

			//шрифт
			Gdiplus::Font fntFont(Font->Name.c_str(), Font->Size + 10, Gdiplus::FontStyleBold);

			//rcBounds
			RECT rcParent = {0};
			_m_bRes = ::GetClientRect(Parent->Handle, &rcParent); 
			/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);

			Gdiplus::RectF rcBounds(rcParent.left, rcParent.top, rcParent.right, rcParent.bottom);

			//формат
			Gdiplus::StringFormat fmtFormat;
			fmtFormat.SetAlignment    (Gdiplus::StringAlignmentCenter);
			fmtFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);

			//Создаем кисть с градиентом на все окно и полупрозрачностью
			Gdiplus::LinearGradientBrush brsBrush(rcBounds,
											      Gdiplus::Color(255, 0, 0, 0),
											      Gdiplus::Color(255, 0, 0, 0),
											      Gdiplus::LinearGradientModeBackwardDiagonal);


			//Выводим текст приветствия, длина -1 означает, что строка заканчивается нулем
			//TCHAR -> wide
			stRes = grfGraphics.DrawString(_m_sText.c_str(), -1, &fntFont, rcBounds, &fmtFormat, &brsBrush);
			/*DEBUG*/xASSERT_DO(Gdiplus::Ok == stRes, return); 


			//Загружаем фоновое изображение и растягиваем его на все окно
			//--Image bg(L"BACKGRND.gif");
			//--grfGraphics.DrawImage(&bg, rcBounds);
		}
		
		INT iRes = ::ReleaseDC(Parent->Handle, hDc);
		/*DEBUG*/xASSERT_DO(0 != iRes, return);
	}



	
		

	//-------------------------------------
	//вывод картинки
	xCHECK_DO(FALSE == _m_imgImage.bIsLoaded(), return);
	xCHECK_DO(TRUE == _m_bClear,                return);

	HDC hDc = ::GetDC(Parent->Handle);
	/*DEBUG*/xASSERT_DO(NULL != hDc, return);

	{
		RECT rcParent = {0};
		_m_bRes = ::GetClientRect(Parent->Handle, &rcParent); 
		/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);

		const LONG  liParentWidth  = rcParent.right  - rcParent.left;
		const LONG  liParentHeight = rcParent.bottom - rcParent.top;
		const FLOAT fRatio         = static_cast<FLOAT>(liParentHeight)            / static_cast<FLOAT>(liParentWidth);
		const FLOAT fImgRatio      = static_cast<FLOAT>(_m_imgImage.uiGetHeight()) / static_cast<FLOAT>(_m_imgImage.uiGetWidth());

		LONG liLeft, liTop, liWidth, liHeight;	//[SPEED] - убрана инициализация переменных

		if (fImgRatio > fRatio) {
			liWidth  = liParentHeight / fImgRatio;
			liLeft   = (liParentWidth - liWidth) / 2;
			liTop    = 0;
			liHeight = liParentHeight;
		} else {
			liLeft   = 0;
			liWidth  = liParentWidth;
			liHeight = liParentWidth * fImgRatio;
			liTop    = (liParentHeight - liHeight) / 2;
		}		

		_m_imgImage.bDraw(hDc, 
			liLeft   + _m_liMargin, 
			liTop    + _m_liMargin, 
			liWidth  - _m_liMargin * 2, 
			liHeight - _m_liMargin * 2
		);
	}

	INT iRes = ::ReleaseDC(Parent->Handle, hDc);
	/*DEBUG*/xASSERT_DO(0 != iRes, return);
};
//---------------------------------------------------------------------------
//TODO: - OnResize ()
/*virtual*/
void __fastcall CxGdipImage::OnResize() {
	/*DEBUG*/// _m_imgImage - n/a
	//xCHECK_DO(FALSE == _m_imgImage.bIsLoaded(), return);
	
	ShowMessage(_T("xxxxx"));

}
//---------------------------------------------------------------------------


/****************************************************************************
*	private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: _bMemoryStreamToIStream (TMemoryStream -> IStream)
//INFO: сделать pisStream->Release(), когда pisStream уже не нужен
BOOL CxGdipImage::_bMemoryStreamToIStream(TMemoryStream *pmsStream, IStream **ppisStream) {
	/*DEBUG*/// _m_imgImage
	/*DEBUG*/xASSERT_RET(NULL != pmsStream,   FALSE);
	/*DEBUG*/xASSERT_RET(NULL == *ppisStream, FALSE); 

	HGLOBAL hGlobal = NULL;

	__int64 i64MemoryStreamSize = pmsStream->Size;

	hGlobal = ::GlobalAlloc(GMEM_MOVEABLE, i64MemoryStreamSize);
	/*DEBUG*/xASSERT_RET(NULL != hGlobal, FALSE);

	LPVOID pvData = ::GlobalLock(hGlobal);
	/*DEBUG*/xASSERT_RET(NULL != pvData, FALSE);

	__int64 i64BytesRead = 0;
	__try {
		//read TMemoryStream and store in global memory
		pmsStream->Position = 0;
		i64BytesRead        = pmsStream->Read(pvData, i64MemoryStreamSize);
	}
	__finally {
		_m_bRes = ::GlobalUnlock(hGlobal);
		/*DEBUG*///xASSERT(FALSE != _m_bRes);
	}

	if (i64MemoryStreamSize != i64BytesRead) {
		hGlobal = ::GlobalFree(hGlobal);
		/*DEBUG*/xASSERT_RET(NULL == hGlobal, FALSE);
		
		return FALSE;
	} 

	//create IStream* from global memory
	HRESULT hRes = ::CreateStreamOnHGlobal(hGlobal, TRUE, ppisStream);
	/*DEBUG*/xASSERT_RET(SUCCEEDED(hRes), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: _bIStreamToMemoryStream (IStream -> TMemoryStream)
//INFO: сделать pisStream->Release(), когда pisStream уже не нужен
BOOL CxGdipImage::_bIStreamToMemoryStream(IStream *pisStream, TMemoryStream **ppmsStream) {
	/*DEBUG*/// _m_imgImage
	/*DEBUG*/xASSERT_RET(NULL !=  pisStream,  FALSE); 
	/*DEBUG*/xASSERT_RET(NULL !=  ppmsStream, FALSE);
	/*DEBUG*/xASSERT_RET(NULL != *ppmsStream, FALSE);

	HRESULT hRes = 0;

	//-------------------------------------
	//устанока размера потока ppmsStream
	STATSTG   stStat = {0};
	ULONGLONG ulSize = 0;

	hRes = pisStream->Stat(&stStat, 0);
	/*DEBUG*/xASSERT_RET(S_OK == hRes, FALSE);
	
	ulSize = stStat.cbSize.QuadPart;
	
	(*ppmsStream)->SetSize((int)ulSize);
	/*DEBUG*/// n/a
	
	//-------------------------------------
	//чтение в поток
	hRes = pisStream->Seek(LARGE_INTEGER(), STREAM_SEEK_SET, NULL);
	/*DEBUG*/xASSERT_RET(S_OK   == hRes, FALSE);
	
	ULONG ulReaded = 0;
	hRes = pisStream->Read((*ppmsStream)->Memory, ulSize, &ulReaded);
	/*DEBUG*/xASSERT_RET(S_OK   == hRes,                FALSE);
	/*DEBUG*/xASSERT_RET(ulSize == ulReaded,            FALSE);
	/*DEBUG*/xASSERT_RET(ulSize == (*ppmsStream)->Size, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - _vOnResize ()
void __fastcall CxGdipImage::_vOnResize(TObject *Sender) {
	/*DEBUG*/

	_m_bRes = bRedraw(TRUE);
	/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------