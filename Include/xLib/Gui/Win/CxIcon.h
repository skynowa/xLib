/**
 * \file  CxIcon.h
 * \brief icon
 */


#ifndef XLib_Gui_CxIconH
#define XLib_Gui_CxIconH
//---------------------------------------------------------------------------
#include <xLib/Gui/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
#define STRINGIZE2(x) #x

class CxIcon :
    public CxNonCopyable
    /// icon
{
    public:
               CxIcon();
    virtual   ~CxIcon();

    #if (xWINVER >= xWIN32_XP)
        HICON  hCopyIcon                   (HICON hIcon);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        HICON  hCreateIcon                 (HINSTANCE hInstance, INT iWidth, INT iHeight, BYTE ucPlanes, BYTE ucBitsPixel, const BYTE *pcucANDBits, const BYTE *pcucXORBits);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        HICON  hCreateIconFromResource     (PBYTE pucResBits, ULONG ulResSize, BOOL bIcon, ULONG ulVersion);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        HICON  hCreateIconFromResourceEx   (PBYTE pucIconBits, ULONG ulIconBits, BOOL bIcon, ULONG ulVersion, INT ciDesiredX, INT ciDesiredY, UINT uiFlags);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        HICON  hCreateIconIndirect         (ICONINFO *pIconInfo);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        BOOL   bDestroyIcon                (HICON hIcon);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        BOOL   bDrawIcon                   (HDC hDC, INT iX, INT iY, HICON hIcon);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        BOOL   bDrawIconEx                 (HDC hdc, INT iLeft, INT iTop, HICON hIcon, INT iWidth, INT iHeight, UINT uiStepIfAniCur, HBRUSH hBrFlickerFreeDraw, UINT uiFlags);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        HICON  hDuplicateIcon              (HINSTANCE hInstance, HICON hIcon);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        HICON  hExtractAssociatedIcon      (HINSTANCE hInstance, LPTSTR pszIconPath, LPWORD pusIcon);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        HICON  hExtractIcon                (HINSTANCE hInstance, LPCTSTR pcszExeFileName, UINT uiIconIndex);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        UINT   uiExtractIconEx             (LPCTSTR pcszFile, INT iIconIndex, HICON *phIconLarge, HICON *phIconSmall, UINT uiIcons);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        BOOL   bGetIconInfo                (HICON hIcon, ICONINFO *pIconInfo);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_VISTA)
        BOOL   bGetIconInfoEx              (HICON hIcon, ICONINFOEX *pIconInfoEx);
    #endif //xWIN32_VISTA
    #if (xWINVER >= xWIN32_XP)
        HICON  hLoadIcon                   (HINSTANCE hInstance, LPCTSTR pcszIconName);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        INT    iLookupIconIdFromDirectory  (PBYTE pucResBits, BOOL bIcon);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_XP)
        INT    iLookupIconIdFromDirectoryEx(PBYTE pucResBits, BOOL bIcon, INT cixDesired, INT ciyDesired, UINT uiFlags);
    #endif //xWIN32_XP
    #if (xWINVER >= xWIN32_2K)
        UINT   uiPrivateExtractIcons       (LPCTSTR pcszFile, INT iIconIndex, INT ciIconX, INT ciIconY, HICON *phIcon, UINT *pIconId, UINT uiIcons, UINT uiFlags);
    #endif //xWIN32_2K

    private:
        HICON _m_hHandle;
};
#endif
//---------------------------------------------------------------------------
#endif //XLib_Gui_CxIconH
