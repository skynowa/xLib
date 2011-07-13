/****************************************************************************
*	bTest_CxImageList.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: bTest_CxImageList ()
BOOL CWndMain::bTest_CxImageList(CxImageList &xObj, INT iID, CxWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

	
	//CxImageList::lpCoCreateInstance
	{
		#if (xWINVER >= xWIN32_VISTA)
		//Syntax: HRESULT lpCoCreateInstance(const IUnknown *pcunkOuter, REFIID riId, VOID **ppvParam);
		//TODO: _m_lpRes = m_Object.lpCoCreateInstance(const IUnknown *pcunkOuter, REFIID riId, VOID **ppvParam);
		//TODO: xASSERT(!S_OK != _m_lpRes);
		#endif //xWIN32_VISTA
	}
	
	//CxImageList::lpQueryInterface 
	{
		#if (xWINVER >= xWIN32_VISTA)
		//Syntax: HRESULT lpQueryInterface (REFIID riId, VOID **ppvParam);
		//TODO: _m_lpRes = m_Object.lpQueryInterface (REFIID riId, VOID **ppvParam);
		//TODO: xASSERT(!S_OK != _m_lpRes);
		#endif //xWIN32_VISTA
	}	
	
	//CxImageList::hCreate
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: HIMAGELIST hCreate(INT iWidth, INT iHeight, UINT uiFlags, INT iSize, INT iGrow);
		//TODO: _m_hRes = m_Object.hCreate(INT iWidth, INT iHeight, UINT uiFlags, INT iSize, INT iGrow);
		//TODO: xASSERT(NULL != _m_hRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::hDuplicate
	{
		#if (xWINVER >= xWIN32_95)
		//Syntax: HIMAGELIST hDuplicate();
		//TODO: _m_hRes = m_Object.hDuplicate();
		//TODO: xASSERT(NULL != _m_hRes);
		#endif //xWIN32_95
	}
	
	//CxImageList::bDestroy
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bDestroy();
		//TODO: _m_bRes = m_Object.bDestroy();
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::iAdd
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iAdd(HBITMAP hBitmap, HBITMAP hBitmapMask);
		//TODO: _m_iRes = m_Object.iAdd(HBITMAP hBitmap, HBITMAP hBitmapMask);
		//TODO: xASSERT(- 1 != _m_iRes);
		#endif //xWIN32_31
	}

	//CxImageList::iAddMasked
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iAddMasked(HBITMAP hBitmap, COLORREF crColor);
		//TODO: _m_iRes = m_Object.iAddMasked(HBITMAP hBitmap, COLORREF crColor);
		//TODO: xASSERT(- 1 != _m_iRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::bCopy
	{
		#if (xWINVER >= xWIN32_95)
		//Syntax: BOOL bCopy(INT iIndexDest, HIMAGELIST hImageListSrc, INT iIndexSrc, UINT uiFlags);
		//TODO: _m_bRes = m_Object.bCopy(INT iIndexDest, HIMAGELIST hImageListSrc, INT iIndexSrc, UINT uiFlags);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_95
	}
	
	//CxImageList::bRemove
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bRemove(INT iIndex);
		//TODO: _m_bRes = m_Object.bRemove(INT iIndex);
		//TODO: xASSERT(- 1 != _m_bRes);
		#endif //xWIN32_31
	}

	//CxImageList::bReplace
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bReplace(INT iIndex, HBITMAP hBitmap, HBITMAP hBitmapMask);
		//TODO: _m_bRes = m_Object.bReplace(INT iIndex, HBITMAP hBitmap, HBITMAP hBitmapMask);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::hMerge
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: HIMAGELIST hMerge(INT iIndex1, HIMAGELIST hImageList2, INT iIndex2, INT iLeft, INT iTop);
		//TODO: _m_hRes = m_Object.hMerge(INT iIndex1, HIMAGELIST hImageList2, INT iIndex2, INT iLeft, INT iTop);
		//TODO: xASSERT(NULL != _m_hRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::hRead
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: HIMAGELIST hRead();
		//TODO: _m_hRes = m_Object.hRead();
		//TODO: xASSERT(NULL != _m_hRes);
		#endif //xWIN32_31
	}

	//CxImageList::lpReadEx
	{
		#if (xWINVER >= xWIN32_XP)
		//Syntax: HRESULT lpReadEx(STREAM *pStream, REFIID riId, VOID **ppvParam);
		//TODO: _m_lpRes = m_Object.lpReadEx(STREAM *pStream, REFIID riId, VOID **ppvParam);
		//TODO: xASSERT(!S_OK != _m_lpRes);
		#endif //xWIN32_XP
	}

	//CxImageList::bWrite
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bWrite(STREAM *pStream);
		//TODO: _m_bRes = m_Object.bWrite(STREAM *pStream);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}

	//CxImageList::lpWriteEx
	{
		#if (xWINVER >= xWIN32_XP)
		//Syntax: HRESULT lpWriteEx(ULONG ulFlags, STREAM *pStream);
		//TODO: _m_lpRes = m_Object.lpWriteEx(ULONG ulFlags, STREAM *pStream);
		//TODO: xASSERT(!S_OK != _m_lpRes);
		#endif //xWIN32_XP
	}
	
	//CxImageList::bBeginDrag
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bBeginDrag(INT iIndex, INT iLeft, INT iTop);
		//TODO: _m_bRes = m_Object.bBeginDrag(INT iIndex, INT iLeft, INT iTop);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::bDragEnter
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bDragEnter(INT iLeft, INT iTop);
		//TODO: _m_bRes = m_Object.bDragEnter(INT iLeft, INT iTop);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}

	//CxImageList::bDragMove
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bDragMove(INT iTop);
		//TODO: _m_bRes = m_Object.bDragMove(INT iTop);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}	
	
	//CxImageList::bDragShowNolock
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bDragShowNolock();
		//TODO: _m_bRes = m_Object.bDragShowNolock();
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}	
	
	//CxImageList::bSetDragCursorImage
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bSetDragCursorImage(INT iDrag, INT iDxHotspot, INT iDyHotspot);
		//TODO: _m_bRes = m_Object.bSetDragCursorImage(INT iDrag, INT iDxHotspot, INT iDyHotspot);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::hGetDragImage
	{
		#if (xWINVER >= xWIN32_95)
		//Syntax: HIMAGELIST hGetDragImage(POINT *pptHotspot);
		//TODO: _m_hRes = m_Object.hGetDragImage(POINT *pptHotspot);
		//TODO: xASSERT(NULL != _m_hRes);
		#endif //xWIN32_95
	}
	
	//CxImageList::bDragLeave
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bDragLeave();
		//TODO: _m_bRes = m_Object.bDragLeave();
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}	
	
	//CxImageList::bEndDrag
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bEndDrag();
		//TODO: _m_bRes = m_Object.bEndDrag();
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxImageList::bDraw
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bDraw(INT iIndex, HDC hDC, INT iLeft, INT iTop, UINT uiStyle);
		//TODO: _m_bRes = m_Object.bDraw(INT iIndex, HDC hDC, INT iLeft, INT iTop, UINT uiStyle);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}

	//CxImageList::bDrawEx
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bDrawEx(INT iIndex, HDC hDC, INT iLeft, INT iTop, INT iWidth, INT iHeight, COLORREF crBkColor, COLORREF crFrgColor, UINT uiStyle);
		//TODO: _m_bRes = m_Object.bDrawEx(INT iIndex, HDC hDC, INT iLeft, INT iTop, INT iWidth, INT iHeight, COLORREF crBkColor, COLORREF crFrgColor, UINT uiStyle);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}

	//CxImageList::bDrawIndirect
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bDrawIndirect();
		//TODO: _m_bRes = m_Object.bDrawIndirect();
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::hLoadImage
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: HIMAGELIST hLoadImage(LPCTSTR pcszImage, INT iWidth, INT iGrow, COLORREF crMask, UINT uiType, UINT uiFlags);
		//TODO: _m_hRes = m_Object.hLoadImage(LPCTSTR pcszImage, INT iWidth, INT iGrow, COLORREF crMask, UINT uiType, UINT uiFlags);
		//TODO: xASSERT(NULL != _m_hRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::iGetImageCount
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iGetImageCount();
		//TODO: _m_iRes = m_Object.iGetImageCount();
		//TODO: xASSERT(not need != _m_iRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::bSetImageCount
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bSetImageCount(UINT uiCount);
		//TODO: _m_bRes = m_Object.bSetImageCount(UINT uiCount);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::bGetImageInfo
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bGetImageInfo(INT iIndex, IMAGEINFO *pImageInfo);
		//TODO: _m_bRes = m_Object.bGetImageInfo(INT iIndex, IMAGEINFO *pImageInfo);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::bSetOverlayImage
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bSetOverlayImage(INT iIndex, INT iOverlay);
		//TODO: _m_bRes = m_Object.bSetOverlayImage(INT iIndex, INT iOverlay);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::hGetIcon
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: HICON hGetIcon(INT iIndex, UINT uiFlags);
		//TODO: _m_hRes = m_Object.hGetIcon(INT iIndex, UINT uiFlags);
		//TODO: xASSERT(not need != _m_hRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::iReplaceIcon
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iReplaceIcon(INT iIndex, HICON hIcon);
		//TODO: _m_iRes = m_Object.iReplaceIcon(INT iIndex, HICON hIcon);
		//TODO: xASSERT(- 1 != _m_iRes);
		#endif //xWIN32_31
	}

	//CxImageList::bGetIconSize
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bGetIconSize(INT *piWidth, INT *piHeight);
		//TODO: _m_bRes = m_Object.bGetIconSize(INT *piWidth, INT *piHeight);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}
	
	//CxImageList::bSetIconSize
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bSetIconSize(INT iWidth, INT iHeight);
		//TODO: _m_bRes = m_Object.bSetIconSize(INT iWidth, INT iHeight);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}

	//CxImageList::crGetBkColor
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: COLORREF crGetBkColor();
		//TODO: _m_crRes = m_Object.crGetBkColor();
		//TODO: xASSERT(not need != _m_crRes);
		#endif //xWIN32_31
	}

	//CxImageList::crSetBkColor
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: COLORREF crSetBkColor(COLORREF clrColor);
		//TODO: _m_crRes = m_Object.crSetBkColor(COLORREF clrColor);
		//TODO: xASSERT(CLR_NONE != _m_crRes);
		#endif //xWIN32_31
	}

	//CxImageList::iSetColorTable
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iSetColorTable(INT iStart, INT iSize, RGBQUAD *pColor);
		//TODO: _m_iRes = m_Object.iSetColorTable(INT iStart, INT iSize, RGBQUAD *pColor);
		//TODO: xASSERT(? != _m_iRes);
		#endif //xWIN32_31
	}

	return TRUE;
}
//---------------------------------------------------------------------------