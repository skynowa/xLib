/**********************************************************************
*	Класс CXImageList (CXImageList.cpp)
*
***********************************************************************/


#include <Xlib/WinControls/CXImageList.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXImageList::CXImageList(HIMAGELIST hImageList = NULL) : m_hImageList(hImageList) { 
	//
}
//---------------------------------------------------------------------------
CXImageList& CXImageList::operator = (HIMAGELIST hImageList) {
	m_hImageList = hImageList;
	
	return *this;
}
//---------------------------------------------------------------------------
CXImageList::operator HIMAGELIST() const { 
	return m_hImageList;
}
//---------------------------------------------------------------------------
void CXImageList::Attach(HIMAGELIST hImageList) {
	/*DEBUG*/XASSERT(NULL == m_hImageList);
	/*DEBUG*/XASSERT(NULL != hImageList);
	
	m_hImageList = hImageList;
}
//---------------------------------------------------------------------------
HIMAGELIST CXImageList::Detach() {
	HIMAGELIST hImageList = m_hImageList;
	m_hImageList = NULL;
	
	return hImageList;
}
//---------------------------------------------------------------------------
bool CXImageList::IsNull() const { 
	return (NULL == m_hImageList); 
}
//---------------------------------------------------------------------------
INT CXImageList::GetImageCount() const {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_GetImageCount(m_hImageList);
}
//---------------------------------------------------------------------------
COLORREF CXImageList::GetBkColor() const {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_GetBkColor(m_hImageList);
}
//---------------------------------------------------------------------------
COLORREF CXImageList::SetBkColor(COLORREF cr) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_SetBkColor(m_hImageList, cr);
}
//---------------------------------------------------------------------------
BOOL CXImageList::GetImageInfo(INT nImage, IMAGEINFO* pImageInfo) const {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_GetImageInfo(m_hImageList, nImage, pImageInfo);
}
//---------------------------------------------------------------------------
HICON CXImageList::GetIcon(INT nIndex, UINT uFlags = ILD_NORMAL) const {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_GetIcon(m_hImageList, nIndex, uFlags);
}
//---------------------------------------------------------------------------
BOOL CXImageList::GetIconSize(INT& cx, INT& cy) const {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_GetIconSize(m_hImageList, &cx, &cy);
}
//---------------------------------------------------------------------------
BOOL CXImageList::GetIconSize(SIZE& size) const {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_GetIconSize(m_hImageList, (INT*)&size.cx, (INT*)&size.cy);
}
//---------------------------------------------------------------------------
BOOL CXImageList::SetIconSize(INT cx, INT cy) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_SetIconSize(m_hImageList, cx, cy);
}
//---------------------------------------------------------------------------
BOOL CXImageList::SetIconSize(SIZE size) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_SetIconSize(m_hImageList, size.cx, size.cy);
}
//---------------------------------------------------------------------------
BOOL CXImageList::SetImageCount(UINT uNewCount) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_SetImageCount(m_hImageList, uNewCount);
}
//---------------------------------------------------------------------------
BOOL CXImageList::SetOverlayImage(INT nImage, INT nOverlay) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_SetOverlayImage(m_hImageList, nImage, nOverlay);
}
//---------------------------------------------------------------------------
BOOL CXImageList::Create(INT cx, INT cy, UINT nFlags, INT nInitial, INT nGrow) {
	/*DEBUG*/XASSERT(NULL == m_hImageList);
	
	m_hImageList = ImageList_Create(cx, cy, nFlags, nInitial, nGrow);
	
	return (NULL != m_hImageList) ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
BOOL CXImageList::Create(UINT nBitmapID, INT cx, INT nGrow, COLORREF crMask) {
	/*DEBUG*/XASSERT(NULL == m_hImageList);
	/* Создание ImageList’a для иконок, отображаемых перед ветками в TreeView. 
	Загружаются 3 картинки из ресурсов текущего проекта (предварительно надо 
	создать их в разделе Bitmap закладки Resource View, причем все три рисунка 
	должны располагаться последовательно в одном BMP ресурсе, а высота и ширина
	каждого должна быть cx_x_cx (16x16) точек).*/ 
	/*cx     - высота и ширина битмапа
	nGrow  - кол-во битмапов
	crMask - цвет прозрачности*/
	m_hImageList = ImageList_LoadBitmap(GetModuleHandle(NULL)/*g_hInst*/, MAKEINTRESOURCE(nBitmapID), cx, nGrow, crMask);

	return (NULL != m_hImageList) ? TRUE : FALSE; 
}
//---------------------------------------------------------------------------
BOOL CXImageList::CreateFromImage(UINT nBitmapID, INT cx, INT nGrow, COLORREF crMask, UINT uType, UINT uFlags = LR_DEFAULTCOLOR | LR_DEFAULTSIZE) {
	/*DEBUG*/XASSERT(NULL == m_hImageList);

	m_hImageList = ImageList_LoadImage(GetModuleHandle(NULL)/*g_hInst*/, MAKEINTRESOURCE(nBitmapID), cx, nGrow, crMask, uType, uFlags);

	return (NULL != m_hImageList) ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
BOOL CXImageList::Merge(HIMAGELIST hImageList1, INT nImage1, HIMAGELIST hImageList2, INT nImage2, INT dx, INT dy) {
	/*DEBUG*/XASSERT(NULL == m_hImageList);
	
	m_hImageList = ImageList_Merge(hImageList1, nImage1, hImageList2, nImage2, dx, dy);
	
	return (NULL != m_hImageList) ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
BOOL CXImageList::Destroy() {
	if (NULL == m_hImageList) {
		return FALSE;
	}
	BOOL bRet = ImageList_Destroy(m_hImageList);
	if (bRet) {
		m_hImageList = NULL;
	}
	
	return bRet;
}
//---------------------------------------------------------------------------
INT CXImageList::Add(HBITMAP hBitmap, HBITMAP hBitmapMask = NULL) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_Add(m_hImageList, hBitmap, hBitmapMask);
}
//---------------------------------------------------------------------------
INT CXImageList::Add(HBITMAP hBitmap, COLORREF crMask) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_AddMasked(m_hImageList, hBitmap, crMask);
}
//---------------------------------------------------------------------------
BOOL CXImageList::Remove(INT nImage) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_Remove(m_hImageList, nImage);
}
//---------------------------------------------------------------------------
BOOL CXImageList::RemoveAll() {
	/*DEBUG*/XASSERT(NULL != m_hImageList);

	return ImageList_RemoveAll(m_hImageList);
}
//---------------------------------------------------------------------------
BOOL CXImageList::Replace(INT nImage, HBITMAP hBitmap, HBITMAP hBitmapMask) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_Replace(m_hImageList, nImage, hBitmap, hBitmapMask);
}
//---------------------------------------------------------------------------
INT CXImageList::AddIcon(HICON hIcon) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_AddIcon(m_hImageList, hIcon);
}
//---------------------------------------------------------------------------
INT CXImageList::ReplaceIcon(INT nImage, HICON hIcon) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_ReplaceIcon(m_hImageList, nImage, hIcon);
}
//---------------------------------------------------------------------------
HICON CXImageList::ExtractIcon(INT nImage) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_ExtractIcon(NULL, m_hImageList, nImage);
}
//---------------------------------------------------------------------------
BOOL CXImageList::Draw(HDC hDC, INT nImage, INT x, INT y, UINT nStyle) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	/*DEBUG*/XASSERT(NULL != hDC);
	
	return ImageList_Draw(m_hImageList, nImage, hDC, x, y, nStyle);
}
//---------------------------------------------------------------------------
BOOL CXImageList::Draw(HDC hDC, INT nImage, POINT pt, UINT nStyle) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	/*DEBUG*/XASSERT(NULL != hDC);
	
	return ImageList_Draw(m_hImageList, nImage, hDC, pt.x, pt.y, nStyle);
}
//---------------------------------------------------------------------------
BOOL CXImageList::DrawEx(INT nImage, HDC hDC, INT x, INT y, INT dx, INT dy, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	/*DEBUG*/XASSERT(NULL != hDC);
	
	return ImageList_DrawEx(m_hImageList, nImage, hDC, x, y, dx, dy, rgbBk, rgbFg, fStyle);
}
//---------------------------------------------------------------------------
BOOL CXImageList::DrawEx(INT nImage, HDC hDC, RECT& rect, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	/*DEBUG*/XASSERT(NULL != hDC);
	
	return ImageList_DrawEx(m_hImageList, nImage, hDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, rgbBk, rgbFg, fStyle);
}
//---------------------------------------------------------------------------
BOOL CXImageList::Copy(INT nSrc, INT nDst, UINT uFlags = ILCF_MOVE) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_Copy(m_hImageList, nDst, m_hImageList, nSrc, uFlags);
}
//---------------------------------------------------------------------------
#if (_WIN32_WINNT >= 0x0501)
 ////HRESULT CXImageList::WriteEx(DWORD dwFlags, LPSTREAM lpStream) {
	/////*DEBUG*/XASSERT(NULL != m_hImageList);

	////return ImageList_WriteEx(m_hImageList, dwFlags, lpStream);
 ////}
#endif // (_WIN32_WINNT >= 0x0501)
//---------------------------------------------------------------------------
BOOL CXImageList::BeginDrag(INT nImage, POINT ptHotSpot) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_BeginDrag(m_hImageList, nImage, ptHotSpot.x, ptHotSpot.y);
}
//---------------------------------------------------------------------------
BOOL CXImageList::BeginDrag(INT nImage, INT xHotSpot, INT yHotSpot) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_BeginDrag(m_hImageList, nImage, xHotSpot, yHotSpot);
}
//---------------------------------------------------------------------------
BOOL CXImageList::SetDragCursorImage(INT nDrag, POINT ptHotSpot){
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_SetDragCursorImage(m_hImageList, nDrag, ptHotSpot.x, ptHotSpot.y);
}
//---------------------------------------------------------------------------
BOOL CXImageList::SetDragCursorImage(INT nDrag, INT xHotSpot, INT yHotSpot) {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return ImageList_SetDragCursorImage(m_hImageList, nDrag, xHotSpot, yHotSpot);
}
//---------------------------------------------------------------------------
#if (_WIN32_IE >= 0x0400)
CXImageList CXImageList::Duplicate() const {
	/*DEBUG*/XASSERT(NULL != m_hImageList);
	
	return CXImageList(ImageList_Duplicate(m_hImageList));
}
#endif // (_WIN32_IE >= 0x0400)
//---------------------------------------------------------------------------