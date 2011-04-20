/**********************************************************************
*	Класс CXImageList (CXImageList.h)
*
***********************************************************************/


#ifndef CXImageListH
#define CXImageListH       
//---------------------------------------------------------------------------
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <assert.h>
//---------------------------------------------------------------------------
class CXImageList {
	public:
		HIMAGELIST         m_hImageList;

            		       CXImageList         (HIMAGELIST hImageList);
		CXImageList&       operator =          (HIMAGELIST hImageList);
		                   operator HIMAGELIST () const;
		VOID               Attach              (HIMAGELIST hImageList);
		HIMAGELIST         Detach              ();
		bool               IsNull              () const;
		INT                GetImageCount       () const;
		COLORREF           GetBkColor          () const;
		COLORREF           SetBkColor          (COLORREF cr);
		BOOL               GetImageInfo        (INT nImage, IMAGEINFO* pImageInfo) const;
		HICON              GetIcon             (INT nIndex, UINT uFlags) const;
		BOOL               GetIconSize         (INT& cx, INT& cy) const;
		BOOL               GetIconSize         (SIZE& size) const;
		BOOL               SetIconSize         (INT cx, INT cy);
		BOOL               SetIconSize         (SIZE size);
		BOOL               SetImageCount       (UINT uNewCount);
		BOOL               SetOverlayImage     (INT nImage, INT nOverlay);
		BOOL               Create              (INT cx, INT cy, UINT nFlags, INT nInitial, INT nGrow);
		BOOL               Create              (UINT nBitmapID, INT cx, INT nGrow, COLORREF crMask);
		BOOL               CreateFromImage     (UINT nBitmapID, INT cx, INT nGrow, COLORREF crMask, UINT uType, UINT uFlags);		//&&&HBITMAP
		BOOL               Merge               (HIMAGELIST hImageList1, INT nImage1, HIMAGELIST hImageList2, INT nImage2, INT dx, INT dy);
		BOOL               Destroy             ();
		INT                Add                 (HBITMAP hBitmap, HBITMAP hBitmapMask);
		INT                Add                 (HBITMAP hBitmap, COLORREF crMask);
		BOOL               Remove              (INT nImage);
		BOOL               RemoveAll           ();
		BOOL               Replace             (INT nImage, HBITMAP hBitmap, HBITMAP hBitmapMask);
		INT                AddIcon             (HICON hIcon);
		INT                ReplaceIcon         (INT nImage, HICON hIcon);
		HICON              ExtractIcon         (INT nImage);
		BOOL               Draw                (HDC hDC, INT nImage, INT x, INT y, UINT nStyle);
		BOOL               Draw                (HDC hDC, INT nImage, POINT pt, UINT nStyle);
		BOOL               DrawEx              (INT nImage, HDC hDC, INT x, INT y, INT dx, INT dy, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle);
		BOOL               DrawEx              (INT nImage, HDC hDC, RECT& rect, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle);
		static BOOL        DrawIndirect        (IMAGELISTDRAWPARAMS* pimldp)             {return ImageList_DrawIndirect(pimldp);}
		BOOL			   Copy                (INT nSrc, INT nDst, UINT uFlags);
#if (_WIN32_WINNT >= 0x0501)
		////static HRESULT     ReadEx              (DWORD dwFlags, LPSTREAM lpStream, REFIID riid, PVOID* ppv) {return ImageList_ReadEx(dwFlags, lpStream, riid, ppv);}
		////HRESULT            WriteEx             (DWORD dwFlags, LPSTREAM lpStream);
#endif // (_WIN32_WINNT >= 0x0501)
		BOOL               BeginDrag           (INT nImage, POINT ptHotSpot);
		BOOL               BeginDrag           (INT nImage, INT xHotSpot, INT yHotSpot);
		static void        EndDrag             ()                                        {ImageList_EndDrag();}
		static BOOL        DragMove            (POINT pt)                                {return ImageList_DragMove(pt.x, pt.y);}
		static BOOL        DragMove            (INT x, INT y)                            {return ImageList_DragMove(x, y);}
		BOOL               SetDragCursorImage  (INT nDrag, POINT ptHotSpot);
		BOOL               SetDragCursorImage  (INT nDrag, INT xHotSpot, INT yHotSpot);
		static BOOL        DragShowNolock      (BOOL bShow = TRUE)                       {return ImageList_DragShowNolock(bShow);}
		static CXImageList GetDragImage        (LPPOINT lpPoint, LPPOINT lpPointHotSpot) {return CXImageList(ImageList_GetDragImage(lpPoint, lpPointHotSpot));}
		static BOOL        DragEnter           (HWND hWnd, POINT point)                  {return ImageList_DragEnter(hWnd, point.x, point.y);}
		static BOOL        DragEnter           (HWND hWnd, INT x, INT y)                 {return ImageList_DragEnter(hWnd, x, y);}
		static BOOL        DragLeave           (HWND hWnd)                               {return ImageList_DragLeave(hWnd);}
#if (_WIN32_IE >= 0x0400)
		CXImageList        Duplicate           () const;
		static CXImageList Duplicate           (HIMAGELIST hImageList)                   {assert(NULL != hImageList);	return CXImageList(ImageList_Duplicate(hImageList));}
#endif // (_WIN32_IE >= 0x0400)
};
//---------------------------------------------------------------------------
#endif