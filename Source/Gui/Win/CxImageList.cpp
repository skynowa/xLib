/****************************************************************************
* Class name:  CxImageList
* Description: список картинок
* File name:   CxImageList.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     27.07.2009 12:58:27
* Version:     1.0.0.0 Debug
*
*****************************************************************************/



#include <XLib/Gui/CxImageList.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxImageList
CxImageList::CxImageList() : 
	_m_hImglst(NULL)
{
}
//---------------------------------------------------------------------------
//TODO: - ~CxImageList
CxImageList::~CxImageList() {

}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: COM
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - lpCoCreateInstance (Creates a single instance of an imagelist and returns an interface pointer to it)
#if (xWINVER >= xWIN32_VISTA)
HRESULT CxImageList::lpCoCreateInstance(const IUnknown *pcunkOuter, REFIID riId, VOID **ppvParam) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, !S_OK);
    /*DEBUG*///IUnknown
    /*DEBUG*///riId
    /*DEBUG*///*ppvParam
    
    HRESULT lpRes = !S_OK;
    
    ////////////lpRes = static_cast<HRESULT>( ImageList_CoCreateInstance(_m_hImglst, pcunkOuter, riId, *ppvParam) );
    /////////////*DEBUG*/xASSERT_RET(!S_OK != lpRes, !S_OK);
    
    return lpRes;
}
#endif //xWIN32_VISTA
//---------------------------------------------------------------------------
//TODO: - lpQueryInterface  (Retrieves a pointer to an IImageList or IImageList2 object that corresponds to the image list's HIMAGELIST handle)
#if (xWINVER >= xWIN32_VISTA)
HRESULT CxImageList::lpQueryInterface (REFIID riId, VOID **ppvParam) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, !S_OK);
    /*DEBUG*///riId
    /*DEBUG*///*ppvParam
    
    HRESULT lpRes = !S_OK;
    
    ////////lpRes = static_cast<HRESULT>( HIMAGELIST_QueryInterface (_m_hImglst, riId, *ppvParam) );
    /////////*DEBUG*/xASSERT_RET(!S_OK != lpRes, !S_OK);
    
    return lpRes;
}
#endif //xWIN32_VISTA
//---------------------------------------------------------------------------


/****************************************************************************
*	public: создание/разрушение
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - hCreate (Creates a new image list)
#if (xWINVER >= xWIN32_31)
HIMAGELIST CxImageList::hCreate(INT iWidth, INT iHeight, UINT uiFlags, INT iSize, INT iGrow) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, NULL);
    /*DEBUG*///iWidth
    /*DEBUG*///iHeight
    /*DEBUG*///uiFlags
    /*DEBUG*///iSize
    /*DEBUG*///iGrow
    
    HIMAGELIST hRes = NULL;
    
    hRes = static_cast<HIMAGELIST>( ImageList_Create(iWidth, iHeight, uiFlags, iSize, iGrow) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);
    
    return hRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - hDuplicate (Creates a duplicate of an existing image list)
#if (xWINVER >= xWIN32_95)
HIMAGELIST CxImageList::hDuplicate() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, NULL);
    
    HIMAGELIST hRes = NULL;
    
    hRes = static_cast<HIMAGELIST>( ImageList_Duplicate(_m_hImglst) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);
    
    return hRes;
}
#endif //xWIN32_95
//---------------------------------------------------------------------------
//TODO: - bDestroy (Destroys an image list)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bDestroy() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_Destroy(_m_hImglst) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------


/****************************************************************************
*	public: действия
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - iAdd (Adds an image or images to an image list)
#if (xWINVER >= xWIN32_31)
INT CxImageList::iAdd(HBITMAP hBitmap, HBITMAP hBitmapMask) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, - 1);
    /*DEBUG*///hBitmap
    /*DEBUG*///hBitmapMask
    
    INT iRes = - 1;
    
    iRes = static_cast<INT>( ImageList_Add(_m_hImglst, hBitmap, hBitmapMask) );
    /*DEBUG*/xASSERT_RET(- 1 != iRes, - 1);
    
    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iAddMasked (Adds an image or images to an image list, generating a mask from the specified bitmap)
#if (xWINVER >= xWIN32_31)
INT CxImageList::iAddMasked(HBITMAP hBitmap, COLORREF crColor) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, - 1);
    /*DEBUG*///hBitmap
    /*DEBUG*///crColor
    
    INT iRes = - 1;
    
    iRes = static_cast<INT>( ImageList_AddMasked(_m_hImglst, hBitmap, crColor) );
    /*DEBUG*/xASSERT_RET(- 1 != iRes, - 1);
    
    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bCopy (Copies images within a given image list)
#if (xWINVER >= xWIN32_95)
BOOL CxImageList::bCopy(INT iIndexDest, HIMAGELIST hImageListSrc, INT iIndexSrc, UINT uiFlags) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    /*DEBUG*///iIndexDest
    /*DEBUG*///hImageListSrc
    /*DEBUG*///iIndexSrc
    /*DEBUG*///uiFlags
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_Copy(_m_hImglst, iIndexDest, hImageListSrc, iIndexSrc, uiFlags) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_95
//---------------------------------------------------------------------------
//TODO: - bRemove (Removes an image from an image list)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bRemove(INT iIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, - 1);
    /*DEBUG*///iIndex
    
    BOOL bRes = - 1;
    
    bRes = static_cast<BOOL>( ImageList_Remove(_m_hImglst, iIndex) );
    /*DEBUG*/xASSERT_RET(- 1 != bRes, - 1);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bReplace (Replaces an image in an image list with a new image)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bReplace(INT iIndex, HBITMAP hBitmap, HBITMAP hBitmapMask) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    /*DEBUG*///iIndex
    /*DEBUG*///hBitmap
    /*DEBUG*///hBitmapMask
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_Replace(_m_hImglst, iIndex, hBitmap, hBitmapMask) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - hMerge (Creates a new image by combining two existing images)
#if (xWINVER >= xWIN32_31)
HIMAGELIST CxImageList::hMerge(INT iIndex1, HIMAGELIST hImageList2, INT iIndex2, INT iLeft, INT iTop) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, NULL);
    /*DEBUG*///iIndex1
    /*DEBUG*///hImageList2
    /*DEBUG*///iIndex2
    /*DEBUG*///iLeft
    /*DEBUG*///iTop
    
    HIMAGELIST hRes = NULL;
    
    hRes = static_cast<HIMAGELIST>( ImageList_Merge(_m_hImglst, iIndex1, hImageList2, iIndex2, iLeft, iTop) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);
    
    return hRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------


/****************************************************************************
*	public: чтение/запись
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - hRead (Reads an image list from a stream)
#if (xWINVER >= xWIN32_31)
HIMAGELIST CxImageList::hRead(LPSTREAM pStream) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, NULL);
	/*DEBUG*///pStream

    HIMAGELIST hRes = NULL;
    
    hRes = static_cast<HIMAGELIST>( ImageList_Read(pStream) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);
    
    return hRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - lpReadEx (Reads an image list from a stream, and returns an interface to the image list)
#if (xWINVER >= xWIN32_VISTA)
HRESULT CxImageList::lpReadEx(ULONG ulFlags, LPSTREAM pStream, REFIID riId, VOID **ppvParam) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, S_FALSE);
	/*DEBUG*///ulFlags
	/*DEBUG*///pStream
    /*DEBUG*///riId
    /*DEBUG*///*ppvParam
    
    HRESULT lpRes = S_FALSE;
    
    lpRes = static_cast<HRESULT>( ImageList_ReadEx(ulFlags, pStream, riId, ppvParam) );
    /*DEBUG*/xASSERT_RET(SUCCEEDED(lpRes), S_FALSE);
    
    return lpRes;
}
#endif //xWIN32_VISTA
//---------------------------------------------------------------------------
//TODO: - bWrite (Writes an image list to a stream)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bWrite(LPSTREAM pStream) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    /*DEBUG*///pStream
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_Write(_m_hImglst, pStream) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - lpWriteEx (Writes an image list to a stream)
#if (xWINVER >= xWIN32_VISTA)
HRESULT CxImageList::lpWriteEx(ULONG ulFlags, LPSTREAM pStream) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, !S_OK);
    /*DEBUG*///ulFlags
    /*DEBUG*///pStream
    
    HRESULT lpRes = S_FALSE; 
    
    lpRes = static_cast<HRESULT>( ImageList_WriteEx(_m_hImglst, ulFlags, pStream) );
    /*DEBUG*/xASSERT_RET(SUCCEEDED(lpRes), S_FALSE);
    
    return lpRes;
}
#endif //xWIN32_VISTA
//---------------------------------------------------------------------------


/****************************************************************************
*	public: перетаскивание
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bBeginDrag (Begins dragging an image)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bBeginDrag(INT iIndex, INT iLeft, INT iTop) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    /*DEBUG*///iIndex
    /*DEBUG*///iLeft
    /*DEBUG*///iTop
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_BeginDrag(_m_hImglst, iIndex, iLeft, iTop) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bDragEnter (Displays the drag image at the specified position within the window)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bDragEnter(HWND hwndLock, INT iLeft, INT iTop) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
	/*DEBUG*///hwndLock
	/*DEBUG*///iLeft
    /*DEBUG*///iTop
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_DragEnter(hwndLock, iLeft, iTop) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bDragMove (Moves the image that is being dragged during a drag-and-drop operation)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bDragMove(INT iLeft, INT iTop) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    /*DEBUG*///iTop
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_DragMove(iLeft, iTop) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bDragShowNolock (Shows or hides the image being dragged)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bDragShowNolock(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_DragShowNolock(bFlag) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetDragCursorImage (Creates a new drag image by combining the specified image (typically a mouse cursor image) with the current drag image)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bSetDragCursorImage(INT iDrag, INT iDxHotspot, INT iDyHotspot) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    /*DEBUG*///iDrag
    /*DEBUG*///iDxHotspot
    /*DEBUG*///iDyHotspot
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_SetDragCursorImage(_m_hImglst, iDrag, iDxHotspot, iDyHotspot) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - hGetDragImage (Retrieves the temporary image list that is used for the drag image)
#if (xWINVER >= xWIN32_95)
HIMAGELIST CxImageList::hGetDragImage(POINT *pptReciever, POINT *pptHotspot) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, NULL);
    /*DEBUG*///pptHotspot
    
    HIMAGELIST hRes = NULL;
    
    hRes = static_cast<HIMAGELIST>( ImageList_GetDragImage(pptReciever, pptHotspot) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);
    
    return hRes;
}
#endif //xWIN32_95
//---------------------------------------------------------------------------
//TODO: - bDragLeave (Unlocks the specified window and hides the drag image, allowing the window to be updated)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bDragLeave(HWND hwndLock) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
	/*DEBUG*///hwndLock

    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_DragLeave(hwndLock) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bEndDrag (Ends a drag operation)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bEndDrag() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    
    static_cast<VOID>( ImageList_EndDrag() );
    /*DEBUG*/// n/a
    
    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------


/****************************************************************************
*	public: рисование
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bDraw (Draws an image list item in the specified device context)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bDraw(INT iIndex, HDC hDC, INT iLeft, INT iTop, UINT uiStyle) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    /*DEBUG*///iIndex
    /*DEBUG*///hDC
    /*DEBUG*///iLeft
    /*DEBUG*///iTop
    /*DEBUG*///uiStyle
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_Draw(_m_hImglst, iIndex, hDC, iLeft, iTop, uiStyle) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bDrawEx (Draws an image list item in the specified device context)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bDrawEx(INT iIndex, HDC hDC, INT iLeft, INT iTop, INT iWidth, INT iHeight, COLORREF crBkColor, COLORREF crFrgColor, UINT uiStyle) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    /*DEBUG*///iIndex
    /*DEBUG*///hDC
    /*DEBUG*///iLeft
    /*DEBUG*///iTop
    /*DEBUG*///iWidth
    /*DEBUG*///iHeight
    /*DEBUG*///crBkColor
    /*DEBUG*///crFrgColor
    /*DEBUG*///uiStyle
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_DrawEx(_m_hImglst, iIndex, hDC, iLeft, iTop, iWidth, iHeight, crBkColor, crFrgColor, uiStyle) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bDrawIndirect (Draws an image list image based on an IMAGELISTDRAWPARAMS structure)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bDrawIndirect(IMAGELISTDRAWPARAMS *pimldpImageListDrawParams) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
	/*DEBUG*///pimldpImageListDrawParams

    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_DrawIndirect(pimldpImageListDrawParams) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------


/****************************************************************************
*	public: Bitmap/Icon
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - hLoadImage (Creates an image list from the specified bitmap)
#if (xWINVER >= xWIN32_31)
HIMAGELIST CxImageList::hLoadImage(HINSTANCE hInstance, LPCTSTR pcszImage, INT iWidth, INT iGrow, COLORREF crMask, UINT uiType, UINT uiFlags) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, NULL);
	/*DEBUG*///hInstance
	/*DEBUG*///pcszImage
    /*DEBUG*///iWidth
    /*DEBUG*///iGrow
    /*DEBUG*///crMask
    /*DEBUG*///uiType
    /*DEBUG*///uiFlags
    
    HIMAGELIST hRes = NULL;
    
    hRes = static_cast<HIMAGELIST>( ImageList_LoadImage(hInstance, pcszImage, iWidth, iGrow, crMask, uiType, uiFlags) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);
    
    return hRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iGetImageCount (Retrieves the number of images in an image list)
#if (xWINVER >= xWIN32_31)
INT CxImageList::iGetImageCount() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, - 1);
    
    INT iRes = - 1;
    
    iRes = static_cast<INT>( ImageList_GetImageCount(_m_hImglst) );
    /*DEBUG*/xASSERT_RET(-1 < iRes, - 1);
    
    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetImageCount (Resizes an existing image list)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bSetImageCount(UINT uiCount) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    /*DEBUG*///uiCount
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_SetImageCount(_m_hImglst, uiCount) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetImageInfo (Retrieves information about an image)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bGetImageInfo(INT iIndex, IMAGEINFO *pImageInfo) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    /*DEBUG*///iIndex
    /*DEBUG*///pImageInfo
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_GetImageInfo(_m_hImglst, iIndex, pImageInfo) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetOverlayImage (dds a specified image to the list of images to be used as overlay masks)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bSetOverlayImage(INT iIndex, INT iOverlay) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    /*DEBUG*///iIndex
    /*DEBUG*///iOverlay
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_SetOverlayImage(_m_hImglst, iIndex, iOverlay) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - hGetIcon (Creates an icon from an image and mask in an image list)
#if (xWINVER >= xWIN32_31)
HICON CxImageList::hGetIcon(INT iIndex, UINT uiFlags) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, NULL);
    /*DEBUG*///iIndex
    /*DEBUG*///uiFlags
    
    HICON hRes = NULL;
    
    hRes = static_cast<HICON>( ImageList_GetIcon(_m_hImglst, iIndex, uiFlags) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);
    
    return hRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iReplaceIcon (Replaces an image with an icon or cursor)
#if (xWINVER >= xWIN32_31)
INT CxImageList::iReplaceIcon(INT iIndex, HICON hIcon) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, - 1);
    /*DEBUG*///iIndex
    /*DEBUG*///hIcon
    
    INT iRes = - 1;
    
    iRes = static_cast<INT>( ImageList_ReplaceIcon(_m_hImglst, iIndex, hIcon) );
    /*DEBUG*/xASSERT_RET(- 1 != iRes, - 1);
    
    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetIconSize (Retrieves the dimensions of images in an image list)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bGetIconSize(INT *piWidth, INT *piHeight) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    /*DEBUG*///piWidth
    /*DEBUG*///piHeight
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_GetIconSize(_m_hImglst, piWidth, piHeight) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetIconSize (Sets the dimensions of images in an image list and removes all images from the list)
#if (xWINVER >= xWIN32_31)
BOOL CxImageList::bSetIconSize(INT iWidth, INT iHeight) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, FALSE);
    /*DEBUG*///iWidth
    /*DEBUG*///iHeight
    
    BOOL bRes = FALSE;
    
    bRes = static_cast<BOOL>( ImageList_SetIconSize(_m_hImglst, iWidth, iHeight) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------


/****************************************************************************
*	public: цвет
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - crGetBkColor (Retrieves the current background color for an image list)
#if (xWINVER >= xWIN32_31)
COLORREF CxImageList::crGetBkColor() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, RGB(0, 0, 0));
    
	return static_cast<COLORREF>( ImageList_GetBkColor(_m_hImglst) );
	/*DEBUG*/// n/a
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - crSetBkColor (Sets the background color for an image list)
#if (xWINVER >= xWIN32_31)
COLORREF CxImageList::crSetBkColor(COLORREF clrColor) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, CLR_NONE);
    /*DEBUG*///clrColor
    
    COLORREF crRes = CLR_NONE;
    
    crRes = static_cast<COLORREF>( ImageList_SetBkColor(_m_hImglst, clrColor) );
    /*DEBUG*/xASSERT_RET(CLR_NONE != crRes, CLR_NONE);
    
    return crRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSetColorTable (Sets the color table for an image list)
#if (xWINVER >= xWIN32_31)
INT CxImageList::iSetColorTable(INT iStart, INT iSize, RGBQUAD *pColor) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hImglst, - 1);
    /*DEBUG*///iStart
    /*DEBUG*///iSize
    /*DEBUG*///pColor
    
    INT iRes = - 1;
    
	//FIX: ImageList_SetColorTable
    ////iRes = static_cast<INT>( ImageList_SetColorTable(_m_hImglst, iStart, iSize, pColor) );
    /////*DEBUG*/xASSERT_RET(0 < iRes, ?);
    
    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------

































////////---------------------------------------------------------------------------
//////CxImageList::CxImageList(HIMAGELIST hImageList = NULL) : 
//////	m_hImageList(hImageList) 
//////{ 
//////   	//LOG();
//////	//
//////}
////////---------------------------------------------------------------------------
//////CxImageList& CxImageList::operator = (HIMAGELIST hImageList) {
//////	m_hImageList = hImageList;
//////	
//////	return *this;
//////}
////////---------------------------------------------------------------------------
//////CxImageList::operator HIMAGELIST() const { 
//////	return m_hImageList;
//////}
////////---------------------------------------------------------------------------
//////void CxImageList::Attach(HIMAGELIST hImageList) {
//////	/*DEBUG*/xASSERT(NULL == m_hImageList);
//////	/*DEBUG*/xASSERT(NULL != hImageList);
//////	
//////	m_hImageList = hImageList;
//////}
////////---------------------------------------------------------------------------
//////HIMAGELIST CxImageList::Detach() {
//////	HIMAGELIST hImageList = m_hImageList;
//////	m_hImageList = NULL;
//////	
//////	return hImageList;
//////}
////////---------------------------------------------------------------------------
//////bool CxImageList::IsNull() const { 
//////	return (NULL == m_hImageList); 
//////}
////////---------------------------------------------------------------------------
//////INT CxImageList::GetImageCount() const {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_GetImageCount(m_hImageList);
//////}
////////---------------------------------------------------------------------------
//////COLORREF CxImageList::GetBkColor() const {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_GetBkColor(m_hImageList);
//////}
////////---------------------------------------------------------------------------
//////COLORREF CxImageList::SetBkColor(COLORREF cr) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_SetBkColor(m_hImageList, cr);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::GetImageInfo(INT nImage, IMAGEINFO* pImageInfo) const {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_GetImageInfo(m_hImageList, nImage, pImageInfo);
//////}
////////---------------------------------------------------------------------------
//////HICON CxImageList::GetIcon(INT nIndex, UINT uFlags = ILD_NORMAL) const {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_GetIcon(m_hImageList, nIndex, uFlags);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::GetIconSize(INT& cx, INT& cy) const {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_GetIconSize(m_hImageList, &cx, &cy);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::GetIconSize(SIZE& size) const {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_GetIconSize(m_hImageList, (INT*)&size.cx, (INT*)&size.cy);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::SetIconSize(INT cx, INT cy) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_SetIconSize(m_hImageList, cx, cy);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::SetIconSize(SIZE size) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_SetIconSize(m_hImageList, size.cx, size.cy);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::SetImageCount(UINT uNewCount) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_SetImageCount(m_hImageList, uNewCount);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::SetOverlayImage(INT nImage, INT nOverlay) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_SetOverlayImage(m_hImageList, nImage, nOverlay);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::Create(INT cx, INT cy, UINT nFlags, INT nInitial, INT nGrow) {
//////	/*DEBUG*/xASSERT(NULL == m_hImageList);
//////	
//////	m_hImageList = ImageList_Create(cx, cy, nFlags, nInitial, nGrow);
//////	
//////	return (NULL != m_hImageList) ? TRUE : FALSE;
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::Create(UINT nBitmapID, INT cx, INT nGrow, COLORREF crMask) {
//////	/*DEBUG*/xASSERT(NULL == m_hImageList);
//////	/* Создание ImageList’a для иконок, отображаемых перед ветками в TreeView. 
//////	Загружаются 3 картинки из ресурсов текущего проекта (предварительно надо 
//////	создать их в разделе Bitmap закладки Resource View, причем все три рисунка 
//////	должны располагаться последовательно в одном BMP ресурсе, а высота и ширина
//////	каждого должна быть cx_x_cx (16x16) точек).*/ 
//////	/*cx     - высота и ширина битмапа
//////	nGrow  - кол-во битмапов
//////	crMask - цвет прозрачности*/
//////	m_hImageList = ImageList_LoadBitmap(GetModuleHandle(NULL)/*g_hInst*/, MAKEINTRESOURCE(nBitmapID), cx, nGrow, crMask);
//////
//////	return (NULL != m_hImageList) ? TRUE : FALSE; 
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::CreateFromImage(UINT nBitmapID, INT cx, INT nGrow, COLORREF crMask, UINT uType, UINT uFlags = LR_DEFAULTCOLOR | LR_DEFAULTSIZE) {
//////	/*DEBUG*/xASSERT(NULL == m_hImageList);
//////
//////	m_hImageList = ImageList_LoadImage(GetModuleHandle(NULL)/*g_hInst*/, MAKEINTRESOURCE(nBitmapID), cx, nGrow, crMask, uType, uFlags);
//////
//////	return (NULL != m_hImageList) ? TRUE : FALSE;
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::Merge(HIMAGELIST hImageList1, INT nImage1, HIMAGELIST hImageList2, INT nImage2, INT dx, INT dy) {
//////	/*DEBUG*/xASSERT(NULL == m_hImageList);
//////	
//////	m_hImageList = ImageList_Merge(hImageList1, nImage1, hImageList2, nImage2, dx, dy);
//////	
//////	return (NULL != m_hImageList) ? TRUE : FALSE;
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::Destroy() {
//////	if (NULL == m_hImageList) {
//////		return FALSE;
//////	}
//////	BOOL bRet = ImageList_Destroy(m_hImageList);
//////	if (bRet) {
//////		m_hImageList = NULL;
//////	}
//////	
//////	return bRet;
//////}
////////---------------------------------------------------------------------------
//////INT CxImageList::Add(HBITMAP hBitmap, HBITMAP hBitmapMask = NULL) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_Add(m_hImageList, hBitmap, hBitmapMask);
//////}
////////---------------------------------------------------------------------------
//////INT CxImageList::Add(HBITMAP hBitmap, COLORREF crMask) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_AddMasked(m_hImageList, hBitmap, crMask);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::Remove(INT nImage) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_Remove(m_hImageList, nImage);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::RemoveAll() {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////
//////	return ImageList_RemoveAll(m_hImageList);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::Replace(INT nImage, HBITMAP hBitmap, HBITMAP hBitmapMask) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_Replace(m_hImageList, nImage, hBitmap, hBitmapMask);
//////}
////////---------------------------------------------------------------------------
//////INT CxImageList::AddIcon(HICON hIcon) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_AddIcon(m_hImageList, hIcon);
//////}
////////---------------------------------------------------------------------------
//////INT CxImageList::ReplaceIcon(INT nImage, HICON hIcon) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_ReplaceIcon(m_hImageList, nImage, hIcon);
//////}
////////---------------------------------------------------------------------------
//////HICON CxImageList::ExtractIcon(INT nImage) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_ExtractIcon(NULL, m_hImageList, nImage);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::Draw(HDC hDC, INT nImage, INT x, INT y, UINT nStyle) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	/*DEBUG*/xASSERT(NULL != hDC);
//////	
//////	return ImageList_Draw(m_hImageList, nImage, hDC, x, y, nStyle);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::Draw(HDC hDC, INT nImage, POINT pt, UINT nStyle) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	/*DEBUG*/xASSERT(NULL != hDC);
//////	
//////	return ImageList_Draw(m_hImageList, nImage, hDC, pt.x, pt.y, nStyle);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::DrawEx(INT nImage, HDC hDC, INT x, INT y, INT dx, INT dy, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	/*DEBUG*/xASSERT(NULL != hDC);
//////	
//////	return ImageList_DrawEx(m_hImageList, nImage, hDC, x, y, dx, dy, rgbBk, rgbFg, fStyle);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::DrawEx(INT nImage, HDC hDC, RECT& rect, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	/*DEBUG*/xASSERT(NULL != hDC);
//////	
//////	return ImageList_DrawEx(m_hImageList, nImage, hDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, rgbBk, rgbFg, fStyle);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::Copy(INT nSrc, INT nDst, UINT uFlags = ILCF_MOVE) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_Copy(m_hImageList, nDst, m_hImageList, nSrc, uFlags);
//////}
////////---------------------------------------------------------------------------
//////#if (_WIN32_WINNT >= 0x0501)
////// ////HRESULT CxImageList::WriteEx(DWORD dwFlags, LPSTREAM lpStream) {
//////	/////*DEBUG*/xASSERT(NULL != m_hImageList);
//////
//////	////return ImageList_WriteEx(m_hImageList, dwFlags, lpStream);
////// ////}
//////#endif // (_WIN32_WINNT >= 0x0501)
////////---------------------------------------------------------------------------
//////BOOL CxImageList::BeginDrag(INT nImage, POINT ptHotSpot) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_BeginDrag(m_hImageList, nImage, ptHotSpot.x, ptHotSpot.y);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::BeginDrag(INT nImage, INT xHotSpot, INT yHotSpot) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_BeginDrag(m_hImageList, nImage, xHotSpot, yHotSpot);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::SetDragCursorImage(INT nDrag, POINT ptHotSpot){
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_SetDragCursorImage(m_hImageList, nDrag, ptHotSpot.x, ptHotSpot.y);
//////}
////////---------------------------------------------------------------------------
//////BOOL CxImageList::SetDragCursorImage(INT nDrag, INT xHotSpot, INT yHotSpot) {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return ImageList_SetDragCursorImage(m_hImageList, nDrag, xHotSpot, yHotSpot);
//////}
////////---------------------------------------------------------------------------
//////#if (_WIN32_IE >= 0x0400)
//////CxImageList CxImageList::Duplicate() const {
//////	/*DEBUG*/xASSERT(NULL != m_hImageList);
//////	
//////	return CxImageList(ImageList_Duplicate(m_hImageList));
//////}
//////#endif // (_WIN32_IE >= 0x0400)
////////---------------------------------------------------------------------------