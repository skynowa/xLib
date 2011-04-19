/****************************************************************************
* Class name:  CxClipboard
* Description: clipboard
* File name:   CxClipboard.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     12.07.2010 12:43:35
*
*****************************************************************************/


#ifndef xLib_Common_Win_CxClipboardH
#define xLib_Common_Win_CxClipboardH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxClipboard : public CxNonCopyable {
	public:
		enum EFormat {
			fmBITMAP 			= CF_BITMAP,
			fmdib 				= CF_DIB,
			////TODO: g++ fmDibv5 			= CF_DIBV5,
			fmDif 				= CF_DIF,
			fmDspBitmap       	= CF_DSPBITMAP,
			fmDsPenhMetaFile  	= CF_DSPENHMETAFILE,
			fmDspMetaFilePict 	= CF_DSPMETAFILEPICT,
			fmDspText         	= CF_DSPTEXT,
			fmEnhMetaFile 		= CF_ENHMETAFILE,
			fmGdiObjFirst 		= CF_GDIOBJFIRST,
			fmGdiObjLast 		= CF_GDIOBJLAST,
			fmHdrop 			= CF_HDROP,
			fmLocale 			= CF_LOCALE,
			fmMetaFilePict 		= CF_METAFILEPICT,
			fmOemText 			= CF_OEMTEXT,
			fmOwnerDisplay 		= CF_OWNERDISPLAY,
			fmPalette 			= CF_PALETTE,
			fmPenData 			= CF_PENDATA,
			fmPrivateFirst 		= CF_PRIVATEFIRST,
			fmPrivateLast 		= CF_PRIVATELAST,
			fmRiff				= CF_RIFF,
			fmSylk 				= CF_SYLK,
			fmText 				= CF_TEXT,
			fmTiff 				= CF_TIFF,
			fmUnicodeText 		= CF_UNICODETEXT,
			fmWave 				= CF_WAVE
		};

		         CxClipboard    ();
		virtual ~CxClipboard    ();

		BOOL     bSetOwner      (HWND hWndOwner);
		BOOL     bGetText       (tString *psText);
		BOOL     bSetText       (const tString csText);
		BOOL     bIsHasFormat   (EFormat fmFormat);
		BOOL     bRegisterFormat(const tString csText, EFormat *pfmFormat);
		BOOL     bClear         ();

	private:
		BOOL    _m_bRes;
		HANDLE  _m_hObject;
		HWND    _m_hWndOwner;

		BOOL    bOpen           ();
		BOOL    bClose          ();

		BOOL    bGetData        (EFormat fmFormat);
		BOOL    bSetData        (EFormat fmFormat, HANDLE hData);
};
//---------------------------------------------------------------------------
#endif //xLib_Common_Win_CxClipboardH



/*
//static HGLOBAL   hglb;
void __fastcall TfrmMainServer::LockClipboard(bool bLockFlag) {
    if (bLockFlag == true) {
        OpenClipboard(NULL);
//        hglb = GetClipboardData(CF_TEXT);
//        GlobalLock(hglb);
        EmptyClipboard();
    } else {
//        GlobalUnlock(hglb);
//        GlobalFree(hglb);
        CloseClipboard();
    }
}
*/





