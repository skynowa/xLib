/**
 * \file  CxIcon.cpp
 * \brief icon
 */


#include <xLib/Gui/Win/CxIcon.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxIcon (comment)
CxIcon::CxIcon() :
    _m_hHandle(NULL)
{
}
//---------------------------------------------------------------------------
//TODO: - ~CxIcon (comment)
CxIcon::~CxIcon() {
    //code
}


//---------------------------------------------------------------------------
//TODO: - hCopyIcon (The CopyIcon function copies the specified icon from another module to the current module)
#if (xWINVER >= xWIN32_XP)
HICON CxIcon::hCopyIcon(HICON hIcon) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, NULL);
    /*DEBUG*///hIcon

    HICON hRes = NULL;

    hRes = static_cast<HICON>( ::CopyIcon(hIcon) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);

    return hRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - hCreateIcon (The CreateIcon function creates an icon that has the specified size, colors, and bit patterns)
#if (xWINVER >= xWIN32_XP)
HICON CxIcon::hCreateIcon(HINSTANCE hInstance, INT iWidth, INT iHeight, BYTE ucPlanes, BYTE ucBitsPixel, const BYTE *pcucANDBits, const BYTE *pcucXORBits) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, NULL);
    /*DEBUG*///hInstance
    /*DEBUG*///iWidth
    /*DEBUG*///iHeight
    /*DEBUG*///ucPlanes
    /*DEBUG*///ucBitsPixel
    /*DEBUG*///BYTE
    /*DEBUG*///BYTE

    HICON hRes = NULL;

    hRes = static_cast<HICON>( ::CreateIcon(hInstance, iWidth, iHeight, ucPlanes, ucBitsPixel, pcucANDBits, pcucXORBits) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);

    return hRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - hCreateIconFromResource (The CreateIconFromResource function creates an icon or cursor from resource bits describing the icon)
#if (xWINVER >= xWIN32_XP)
HICON CxIcon::hCreateIconFromResource(PBYTE pucResBits, ULONG ulResSize, BOOL bIcon, ULONG ulVersion) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, NULL);
    /*DEBUG*///pucResBits
    /*DEBUG*///ulResSize
    /*DEBUG*///bIcon
    /*DEBUG*///ulVersion

    HICON hRes = NULL;

    hRes = static_cast<HICON>( ::CreateIconFromResource(pucResBits, ulResSize, bIcon, ulVersion) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);

    return hRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - hCreateIconFromResourceEx (The CreateIconFromResourceEx function creates an icon or cursor from resource bits describing the icon)
#if (xWINVER >= xWIN32_XP)
HICON CxIcon::hCreateIconFromResourceEx(PBYTE pucIconBits, ULONG ulIconBits, BOOL bIcon, ULONG ulVersion, INT ciDesiredX, INT ciDesiredY, UINT uiFlags) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, NULL);
    /*DEBUG*///pucIconBits
    /*DEBUG*///ulIconBits
    /*DEBUG*///bIcon
    /*DEBUG*///ulVersion
    /*DEBUG*///ciDesiredX
    /*DEBUG*///ciDesiredY
    /*DEBUG*///uiFlags

    HICON hRes = NULL;

    hRes = static_cast<HICON>( ::CreateIconFromResourceEx(pucIconBits, ulIconBits, bIcon, ulVersion, ciDesiredX, ciDesiredY, uiFlags) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);

    return hRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - hCreateIconIndirect (The CreateIconIndirect function creates an icon or cursor from an ICONINFO structure)
#if (xWINVER >= xWIN32_XP)
HICON CxIcon::hCreateIconIndirect(ICONINFO *pIconInfo) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, NULL);
    /*DEBUG*///pIconInfo

    HICON hRes = NULL;

    hRes = static_cast<HICON>( ::CreateIconIndirect(pIconInfo) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);

    return hRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - bDestroyIcon (Destroys an icon and frees any memory the icon occupied)
#if (xWINVER >= xWIN32_XP)
BOOL CxIcon::bDestroyIcon(HICON hIcon) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, FALSE);
    /*DEBUG*///hIcon

    BOOL bRes = FALSE;

    bRes = static_cast<BOOL>( ::DestroyIcon(hIcon) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return bRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - bDrawIcon (The DrawIcon function draws an icon or cursor into the specified device context)
#if (xWINVER >= xWIN32_XP)
BOOL CxIcon::bDrawIcon(HDC hDC, INT iX, INT iY, HICON hIcon) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, FALSE);
    /*DEBUG*///hDC
    /*DEBUG*///iX
    /*DEBUG*///iY
    /*DEBUG*///hIcon

    BOOL bRes = FALSE;

    bRes = static_cast<BOOL>( ::DrawIcon(hDC, iX, iY, hIcon) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return bRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - bDrawIconEx (The DrawIconEx function draws an icon or cursor into the specified device context, performing the specified raster operations, and stretching or compressing the icon or cursor as specified)
#if (xWINVER >= xWIN32_XP)
BOOL CxIcon::bDrawIconEx(HDC hdc, INT iLeft, INT iTop, HICON hIcon, INT iWidth, INT iHeight, UINT uiStepIfAniCur, HBRUSH hBrFlickerFreeDraw, UINT uiFlags) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, FALSE);
    /*DEBUG*///hdc
    /*DEBUG*///iLeft
    /*DEBUG*///iTop
    /*DEBUG*///hIcon
    /*DEBUG*///iWidth
    /*DEBUG*///iHeight
    /*DEBUG*///uiStepIfAniCur
    /*DEBUG*///hBrFlickerFreeDraw
    /*DEBUG*///uiFlags

    BOOL bRes = FALSE;

    bRes = static_cast<BOOL>( ::DrawIconEx(hdc, iLeft, iTop, hIcon, iWidth, iHeight, uiStepIfAniCur, hBrFlickerFreeDraw, uiFlags) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return bRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - hDuplicateIcon (The DuplicateIcon function creates a duplicate of a specified icon)
#if (xWINVER >= xWIN32_XP)
HICON CxIcon::hDuplicateIcon(HINSTANCE hInstance, HICON hIcon) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, NULL);
    /*DEBUG*///hInstance
    /*DEBUG*///hIcon

    HICON hRes = NULL;

    hRes = static_cast<HICON>( ::DuplicateIcon(hInstance, hIcon) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);

    return hRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - hExtractAssociatedIcon (The ExtractAssociatedIcon function returns a handle to an indexed icon found in a file or an icon found in an associated executable file)
#if (xWINVER >= xWIN32_XP)
HICON CxIcon::hExtractAssociatedIcon(HINSTANCE hInstance, LPTSTR pszIconPath, LPWORD pusIcon) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, NULL);
    /*DEBUG*///hInstance
    /*DEBUG*///pszIconPath
    /*DEBUG*///pusIcon

    HICON hRes = NULL;

    hRes = static_cast<HICON>( ::ExtractAssociatedIcon(hInstance, pszIconPath, pusIcon) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);

    return hRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - hExtractIcon (The ExtractIcon function retrieves a handle to an icon from the specified executable file, DLL, or icon file)
#if (xWINVER >= xWIN32_XP)
HICON CxIcon::hExtractIcon(HINSTANCE hInstance, LPCTSTR pcszExeFileName, UINT uiIconIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, NULL);
    /*DEBUG*///hInstance
    /*DEBUG*///pcszExeFileName
    /*DEBUG*///uiIconIndex

    HICON hRes = NULL;

    hRes = static_cast<HICON>( ::ExtractIcon(hInstance, pcszExeFileName, uiIconIndex) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);

    return hRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - uiExtractIconEx (The ExtractIconEx function creates an array of handles to large or small icons extracted from the specified executable file, DLL, or icon file)
#if (xWINVER >= xWIN32_XP)
UINT CxIcon::uiExtractIconEx(LPCTSTR pcszFile, INT iIconIndex, HICON *phIconLarge, HICON *phIconSmall, UINT uiIcons) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, 0);
    /*DEBUG*///pcszFile
    /*DEBUG*///iIconIndex
    /*DEBUG*///phIconLarge
    /*DEBUG*///phIconSmall
    /*DEBUG*///uiIcons

    UINT uiRes = 0;

    uiRes = static_cast<UINT>( ::ExtractIconEx(pcszFile, iIconIndex, phIconLarge, phIconSmall, uiIcons) );
    /*DEBUG*/xASSERT_RET(0 != uiRes, 0);

    return uiRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - bGetIconInfo (The GetIconInfo function retrieves information about the specified icon or cursor)
#if (xWINVER >= xWIN32_XP)
BOOL CxIcon::bGetIconInfo(HICON hIcon, ICONINFO *pIconInfo) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, FALSE);
    /*DEBUG*///hIcon
    /*DEBUG*///pIconInfo

    BOOL bRes = FALSE;

    bRes = static_cast<BOOL>( ::GetIconInfo(hIcon, pIconInfo) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return bRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - bGetIconInfoEx (Retrieves information about the specified icon or cursor)
#if (xWINVER >= xWIN32_VISTA)
BOOL CxIcon::bGetIconInfoEx(HICON hIcon, ICONINFOEX *pIconInfoEx) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, FALSE);
    /*DEBUG*///hIcon
    /*DEBUG*///pIconInfoEx

    BOOL bRes = FALSE;

    bRes = static_cast<BOOL>( ::GetIconInfoEx(hIcon, pIconInfoEx) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return bRes;
}
#endif //xWIN32_VISTA
//---------------------------------------------------------------------------
//TODO: - hLoadIcon (This function has been superseded by the LoadImage function)
#if (xWINVER >= xWIN32_XP)
HICON CxIcon::hLoadIcon(HINSTANCE hInstance, LPCTSTR pcszIconName) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, NULL);
    /*DEBUG*///hInstance
    /*DEBUG*///pcszIconName

    HICON hRes = NULL;

    hRes = static_cast<HICON>( ::LoadIcon(hInstance, pcszIconName) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);

    return hRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - iLookupIconIdFromDirectory (The LookupIconIdFromDirectory function searches through icon or cursor data for the icon or cursor that best fits the current display device)
#if (xWINVER >= xWIN32_XP)
INT CxIcon::iLookupIconIdFromDirectory(PBYTE pucResBits, BOOL bIcon) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, 0);
    /*DEBUG*///pucResBits
    /*DEBUG*///bIcon

    INT iRes = 0;

    iRes = static_cast<INT>( ::LookupIconIdFromDirectory(pucResBits, bIcon) );
    /*DEBUG*/xASSERT_RET(0 != iRes, 0);

    return iRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - iLookupIconIdFromDirectoryEx (The LookupIconIdFromDirectoryEx function searches through icon or cursor data for the icon or cursor that best fits the current display device)
#if (xWINVER >= xWIN32_XP)
INT CxIcon::iLookupIconIdFromDirectoryEx(PBYTE pucResBits, BOOL bIcon, INT cixDesired, INT ciyDesired, UINT uiFlags) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, 0);
    /*DEBUG*///pucResBits
    /*DEBUG*///bIcon
    /*DEBUG*///cixDesired
    /*DEBUG*///ciyDesired
    /*DEBUG*///uiFlags

    INT iRes = 0;

    iRes = static_cast<INT>( ::LookupIconIdFromDirectoryEx(pucResBits, bIcon, cixDesired, ciyDesired, uiFlags) );
    /*DEBUG*/xASSERT_RET(0 != iRes, 0);

    return iRes;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - uiPrivateExtractIcons (Creates an array of handles to icons that are extracted from a specified file)
#if (xWINVER >= xWIN32_2K)
UINT CxIcon::uiPrivateExtractIcons(LPCTSTR pcszFile, INT iIconIndex, INT ciIconX, INT ciIconY, HICON *phIcon, UINT *pIconId, UINT uiIcons, UINT uiFlags) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hHandle, 0);
    /*DEBUG*///pcszFile
    /*DEBUG*///iIconIndex
    /*DEBUG*///ciIconX
    /*DEBUG*///ciIconY
    /*DEBUG*///phIcon
    /*DEBUG*///pIconId
    /*DEBUG*///uiIcons
    /*DEBUG*///uiFlags

    UINT uiRes = 0;

    uiRes = static_cast<UINT>( ::PrivateExtractIcons(pcszFile, iIconIndex, ciIconX, ciIconY, phIcon, pIconId, uiIcons, uiFlags) );
    /*DEBUG*/xASSERT_RET(0 != uiRes, 0);

    return uiRes;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
#endif
