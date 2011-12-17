/**
 * \file  CxClipboard.h
 * \brief clipboard
 */


#ifndef xLib_Common_Win_CxClipboardH
#define xLib_Common_Win_CxClipboardH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxClipboard :
    private CxNonCopyable
    /// clipboard
{
    public:
        enum EFormat
            /// format
        {
            fmBITMAP          = CF_BITMAP,
            fmdib             = CF_DIB,
        #if xCOMPILER_MS || xCOMPILER_CODEGEAR
            fmDibv5           = CF_DIBV5,
        #endif
            fmDif             = CF_DIF,
            fmDspBitmap       = CF_DSPBITMAP,
            fmDsPenhMetaFile  = CF_DSPENHMETAFILE,
            fmDspMetaFilePict = CF_DSPMETAFILEPICT,
            fmDspText         = CF_DSPTEXT,
            fmEnhMetaFile     = CF_ENHMETAFILE,
            fmGdiObjFirst     = CF_GDIOBJFIRST,
            fmGdiObjLast      = CF_GDIOBJLAST,
            fmHdrop           = CF_HDROP,
            fmLocale          = CF_LOCALE,
            fmMetaFilePict    = CF_METAFILEPICT,
            fmOemText         = CF_OEMTEXT,
            fmOwnerDisplay    = CF_OWNERDISPLAY,
            fmPalette         = CF_PALETTE,
            fmPenData         = CF_PENDATA,
            fmPrivateFirst    = CF_PRIVATEFIRST,
            fmPrivateLast     = CF_PRIVATELAST,
            fmRiff            = CF_RIFF,
            fmSylk            = CF_SYLK,
            fmText            = CF_TEXT,
            fmTiff            = CF_TIFF,
            fmUnicodeText     = CF_UNICODETEXT,
            fmWave            = CF_WAVE
        };

                 CxClipboard    ();
            ///< constructor
        virtual ~CxClipboard    ();
            ///< destructor

        bool     bSetOwner      (const HWND chWndOwner);
            ///< set owner
        bool     bGetText       (std::tstring_t *psText);
            ///< get text
        bool     bSetText       (const std::tstring_t &csText);
            ///< set text
        bool     bIsHasFormat   (const EFormat cfmFormat);
            ///<  is has format
        bool     bRegisterFormat(const std::tstring_t &csText, EFormat *pfmFormat);
            ///< register format
        bool     bClear         ();
            ///< clear

    private:
        HANDLE  _m_hObject;     ///< handle
        HWND    _m_hWndOwner;   ///< owner handle

        bool    bOpen           ();
            ///< open
        bool    bClose          ();
            ///< close

        bool    bGetData        (const EFormat cfmFormat);
            ///< get data
        bool    bSetData        (const EFormat cfmFormat, const HANDLE chData);
            ///< set data
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif //xLib_Common_Win_CxClipboardH


#if xTODO
    static HGLOBAL   hglb;

    void __fastcall
    TfrmMainServer::LockClipboard(bool bLockFlag) {
        if (bLockFlag == true) {
            OpenClipboard(NULL);
            //hglb = GetClipboardData(CF_TEXT);
            //GlobalLock(hglb);
            EmptyClipboard();
        } else {
            //GlobalUnlock(hglb);
            //GlobalFree(hglb);
            CloseClipboard();
        }
    }
#endif
