/****************************************************************************
*	bTest_CxPicture.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: bTest_CxPicture ()
BOOL CWndMain::bTest_CxPicture(CxPicture &xObj, INT iID, CxWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

	//CxPicture::bCreateRes
	{
		_m_bRes = xObj.bCreateRes(iID, pwndParent);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}
	
	//CxPicture::bSetViewStyle (vsBitmap), CxPicture::bSetImage (itBitmap)
	{
		_m_bRes = m_picPicture1.bSetViewStyle(CxPicture::vsBitmap);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL, xT("Bitmap1.bmp"), IMAGE_BITMAP, 48, 48, LR_LOADFROMFILE);
		/*DEBUG*/xASSERT(NULL != hBitmap);

		_m_bRes = m_picPicture1.bSetImage(CxPicture::itBitmap, hBitmap);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxPicture::bSetViewStyle (vsIcon), CxPicture::bSetImage (itIcon)
	{
		_m_bRes = m_picPicture1.bSetViewStyle(CxPicture::vsIcon);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		HICON hIcon = (HICON)::LoadImage(NULL, xT("icon0.ico"), IMAGE_ICON, 32, 32, LR_LOADFROMFILE); /*::LoadIcon(NULL, IDI_EXCLAMATION);*/
		/*DEBUG*/xASSERT(NULL != hIcon);

		_m_bRes = m_picPicture1.bSetImage(CxPicture::itIcon, hIcon);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxPicture::bSetViewStyle (vsCursor), CxPicture::bSetImage (itCursor)
	{
		_m_bRes = m_picPicture1.bSetViewStyle(CxPicture::vsCursor);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		HICON hCursor = (HICON)::LoadImage(NULL, xT("cursor0.cur"), IMAGE_ICON, 32, 32, LR_LOADFROMFILE); /*::LoadIcon(NULL, IDI_EXCLAMATION);*/
		/*DEBUG*/xASSERT(NULL != hCursor);

		_m_bRes = m_picPicture1.bSetImage(CxPicture::itCursor, hCursor);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxPicture::bSetViewStyle (vsEnhMetaFile), CxPicture::bSetImage (itEnhMetaFile)
	{
		////_m_bRes = m_picPicture1.bSetViewStyle(CxPicture::vsEnhMetaFile);
		/////*DEBUG*/xASSERT(FALSE != _m_bRes);

		////HENHMETAFILE hEnhMetaFile = ::GetEnhMetaFile(xT("EnhMetaFile0.emf"));
		/////*DEBUG*/xASSERT(NULL != hEnhMetaFile);

		////_m_bRes = m_picPicture1.bSetImage(CxPicture::itEnhMetaFile, hEnhMetaFile);
		/////*DEBUG*/xASSERT(FALSE != _m_bRes);
	}


	return TRUE;
}
//---------------------------------------------------------------------------