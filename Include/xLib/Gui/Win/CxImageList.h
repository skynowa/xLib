/**
 * \file  CxImageList.h
 * \brief image list
 */


#ifndef XLib_Gui_CxImageListH
#define XLib_Gui_CxImageListH
//---------------------------------------------------------------------------
#include <xLib/Gui/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxImageList :
    public CxNonCopyable
    /// image list
{
    public:
        //-------------------------------------
        //���������

        CxImageList();
        ~CxImageList();

        //COM
        #if (xWINVER >= xWIN32_VISTA)
            HRESULT    lpCoCreateInstance (const IUnknown *pcunkOuter, REFIID riId, VOID **ppvParam);
        #endif //xWIN32_VISTA

        #if (xWINVER >= xWIN32_VISTA)
            HRESULT    lpQueryInterface   (REFIID riId, VOID **ppvParam);
        #endif //xWIN32_VISTA


        //��������/����������
        #if (xWINVER >= xWIN32_31)
            HIMAGELIST hCreate            (INT iWidth, INT iHeight, UINT uiFlags, INT iSize, INT iGrow);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_95)
            HIMAGELIST hDuplicate         ();
        #endif //xWIN32_95
        #if (xWINVER >= xWIN32_31)
            BOOL       bDestroy           ();
        #endif //xWIN32_31


        //��������
        #if (xWINVER >= xWIN32_31)
            INT        iAdd               (HBITMAP hBitmap, HBITMAP hBitmapMask);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT        iAddMasked         (HBITMAP hBitmap, COLORREF crColor);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_95)
            BOOL       bCopy              (INT iIndexDest, HIMAGELIST hImageListSrc, INT iIndexSrc, UINT uiFlags);
        #endif //xWIN32_95
        #if (xWINVER >= xWIN32_31)
            BOOL       bRemove            (INT iIndex);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL       bReplace           (INT iIndex, HBITMAP hBitmap, HBITMAP hBitmapMask);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            HIMAGELIST hMerge             (INT iIndex1, HIMAGELIST hImageList2, INT iIndex2, INT iLeft, INT iTop);
        #endif //xWIN32_31


        //������/������
        #if (xWINVER >= xWIN32_31)
            HIMAGELIST hRead              (LPSTREAM pStream);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_VISTA)
            HRESULT    lpReadEx           (ULONG ulFlags, LPSTREAM pStream, REFIID riId, VOID **ppvParam);
        #endif //xWIN32_VISTA
        #if (xWINVER >= xWIN32_31)
            BOOL       bWrite             (LPSTREAM pStream);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_VISTA)
            HRESULT    lpWriteEx          (ULONG ulFlags, LPSTREAM pStream);
        #endif //xWIN32_VISTA


        //��������������
        #if (xWINVER >= xWIN32_31)
            BOOL       bBeginDrag         (INT iIndex, INT iLeft, INT iTop);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL       bDragEnter         (HWND hwndLock, INT iLeft, INT iTop);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL       bDragMove          (INT iLeft, INT iTop);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL       bDragShowNolock    (BOOL bFlag);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL       bSetDragCursorImage(INT iDrag, INT iDxHotspot, INT iDyHotspot);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_95)
            HIMAGELIST hGetDragImage      (POINT *pptReciever, POINT *pptHotspot);
        #endif //xWIN32_95
        #if (xWINVER >= xWIN32_31)
            BOOL       bDragLeave         (HWND hwndLock);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL       bEndDrag           ();
        #endif //xWIN32_31


        //���������
        #if (xWINVER >= xWIN32_31)
            BOOL       bDraw              (INT iIndex, HDC hDC, INT iLeft, INT iTop, UINT uiStyle);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL       bDrawEx            (INT iIndex, HDC hDC, INT iLeft, INT iTop, INT iWidth, INT iHeight, COLORREF crBkColor, COLORREF crFrgColor, UINT uiStyle);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL       bDrawIndirect      (IMAGELISTDRAWPARAMS *pimldpImageListDrawParams);
        #endif //xWIN32_31


        //Bitmap/Icon
        #if (xWINVER >= xWIN32_31)
            HIMAGELIST hLoadImage         (HINSTANCE hInstance, LPCTSTR pcszImage, INT iWidth, INT iGrow, COLORREF crMask, UINT uiType, UINT uiFlags);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT        iGetImageCount     ();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL       bSetImageCount     (UINT uiCount);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL       bGetImageInfo      (INT iIndex, IMAGEINFO *pImageInfo);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL       bSetOverlayImage   (INT iIndex, INT iOverlay);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            HICON      hGetIcon           (INT iIndex, UINT uiFlags);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT        iReplaceIcon       (INT iIndex, HICON hIcon);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL       bGetIconSize       (INT *piWidth, INT *piHeight);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL       bSetIconSize       (INT iWidth, INT iHeight);
        #endif //xWIN32_31


        //����
        #if (xWINVER >= xWIN32_31)
            COLORREF   crGetBkColor       ();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            COLORREF   crSetBkColor       (COLORREF clrColor);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT        iSetColorTable     (INT iStart, INT iSize, RGBQUAD *pColor);
        #endif //xWIN32_31

    private:
        HIMAGELIST  _m_hImglst;
};
#endif
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxImageListH


//////HIMAGELIST         m_hImageList;
//////
//////CxImageList         (HIMAGELIST hImageList);
//////CxImageList&       operator =          (HIMAGELIST hImageList);
//////operator HIMAGELIST () const;
//////VOID               Attach              (HIMAGELIST hImageList);
//////HIMAGELIST         Detach              ();
//////bool               IsNull              () const;
//////INT                GetImageCount       () const;
//////COLORREF           GetBkColor          () const;
//////COLORREF           SetBkColor          (COLORREF cr);
//////BOOL               GetImageInfo        (INT nImage, IMAGEINFO* pImageInfo) const;
//////HICON              GetIcon             (INT nIndex, UINT uFlags) const;
//////BOOL               GetIconSize         (INT& cx, INT& cy) const;
//////BOOL               GetIconSize         (SIZE& size) const;
//////BOOL               SetIconSize         (INT cx, INT cy);
//////BOOL               SetIconSize         (SIZE size);
//////BOOL               SetImageCount       (UINT uNewCount);
//////BOOL               SetOverlayImage     (INT nImage, INT nOverlay);
//////BOOL               Create              (INT cx, INT cy, UINT nFlags, INT nInitial, INT nGrow);
//////BOOL               Create              (UINT nBitmapID, INT cx, INT nGrow, COLORREF crMask);
//////BOOL               CreateFromImage     (UINT nBitmapID, INT cx, INT nGrow, COLORREF crMask, UINT uType, UINT uFlags);        //&&&HBITMAP
//////BOOL               Merge               (HIMAGELIST hImageList1, INT nImage1, HIMAGELIST hImageList2, INT nImage2, INT dx, INT dy);
//////BOOL               Destroy             ();
//////INT                Add                 (HBITMAP hBitmap, HBITMAP hBitmapMask);
//////INT                Add                 (HBITMAP hBitmap, COLORREF crMask);
//////BOOL               Remove              (INT nImage);
//////BOOL               RemoveAll           ();
//////BOOL               Replace             (INT nImage, HBITMAP hBitmap, HBITMAP hBitmapMask);
//////INT                AddIcon             (HICON hIcon);
//////INT                ReplaceIcon         (INT nImage, HICON hIcon);
//////HICON              ExtractIcon         (INT nImage);
//////BOOL               Draw                (HDC hDC, INT nImage, INT x, INT y, UINT nStyle);
//////BOOL               Draw                (HDC hDC, INT nImage, POINT pt, UINT nStyle);
//////BOOL               DrawEx              (INT nImage, HDC hDC, INT x, INT y, INT dx, INT dy, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle);
//////BOOL               DrawEx              (INT nImage, HDC hDC, RECT& rect, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle);
//////static BOOL        DrawIndirect        (IMAGELISTDRAWPARAMS* pimldp)             {return ImageList_DrawIndirect(pimldp);}
//////BOOL               Copy                (INT nSrc, INT nDst, UINT uFlags);
//////#if (_WIN32_WINNT >= 0x0501)
//////////static HRESULT     ReadEx              (DWORD dwFlags, LPSTREAM lpStream, REFIID riid, PVOID* ppv) {return ImageList_ReadEx(dwFlags, lpStream, riid, ppv);}
//////////HRESULT            WriteEx             (DWORD dwFlags, LPSTREAM lpStream);
//////#endif // (_WIN32_WINNT >= 0x0501)
//////BOOL               BeginDrag           (INT nImage, POINT ptHotSpot);
//////BOOL               BeginDrag           (INT nImage, INT xHotSpot, INT yHotSpot);
//////static void        EndDrag             ()                                        {ImageList_EndDrag();}
//////static BOOL        DragMove            (POINT pt)                                {return ImageList_DragMove(pt.x, pt.y);}
//////static BOOL        DragMove            (INT x, INT y)                            {return ImageList_DragMove(x, y);}
//////BOOL               SetDragCursorImage  (INT nDrag, POINT ptHotSpot);
//////BOOL               SetDragCursorImage  (INT nDrag, INT xHotSpot, INT yHotSpot);
//////static BOOL        DragShowNolock      (BOOL bShow = TRUE)                       {return ImageList_DragShowNolock(bShow);}
//////static CxImageList GetDragImage        (LPPOINT lpPoint, LPPOINT lpPointHotSpot) {return CxImageList(ImageList_GetDragImage(lpPoint, lpPointHotSpot));}
//////static BOOL        DragEnter           (HWND hWnd, POINT point)                  {return ImageList_DragEnter(hWnd, point.x, point.y);}
//////static BOOL        DragEnter           (HWND hWnd, INT x, INT y)                 {return ImageList_DragEnter(hWnd, x, y);}
//////static BOOL        DragLeave           (HWND hWnd)                               {return ImageList_DragLeave(hWnd);}
//////#if (_WIN32_IE >= 0x0400)
//////CxImageList        Duplicate           () const;
//////static CxImageList Duplicate           (HIMAGELIST hImageList)                   {xASSERT(NULL != hImageList);    return CxImageList(ImageList_Duplicate(hImageList));}
//////#endif // (_WIN32_IE >= 0x0400)
