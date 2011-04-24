/**********************************************************************
*	vShowNoImage.cpp	
*
***********************************************************************/


#include <vcl.h>
#pragma hdrstop

#include "uMain.h"
//---------------------------------------------------------------------------
void __fastcall vShowNoImage(TImage *pImage) {
	/*DEBUG*/xASSERT(NULL != pImage);

	//-------------------------------------
	//удаляем старую картинку   (BC++ 6.0 - RAD2009: работает, RAD2010 - ошибка)
	pImage->Picture->Assign(NULL);
	pImage->Repaint();

	//-------------------------------------
	//рисуем на канве
	const String cusNoPhotoText = _T("Нет");    //oaeno

	pImage->Canvas->Brush->Color = clWhite;
	pImage->Canvas->Font->Color  = clBlack;
	pImage->Canvas->Font->Size   = 18;
	pImage->Canvas->Font->Style  = TFontStyles() << fsBold;
	pImage->Canvas->TextOut(
		pImage->Width  / 2 - pImage->Canvas->TextWidth(cusNoPhotoText)  / 2,
		pImage->Height / 2 - pImage->Canvas->TextHeight(cusNoPhotoText) / 2,
		cusNoPhotoText
	);
	//
	pImage->Canvas->Brush->Color = clBlack;
	pImage->Canvas->Brush->Style = bsDiagCross;
	pImage->Canvas->Rectangle(0, 0, pImage->Width, pImage->Height);
	//X
	////pImage->Canvas->MoveTo(pImage->Width, 0);
	////pImage->Canvas->LineTo(0, pImage->Height);

	////pImage->Canvas->MoveTo(0, 0);
	////pImage->Canvas->LineTo(pImage->Width, pImage->Height);
}
//---------------------------------------------------------------------------
