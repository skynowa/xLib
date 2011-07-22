/****************************************************************************
* Unit name:   bDownloadURL
* Description: download file using  ftp, http, https
* File name:   bDownloadURL.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.11.2009 11:50:17
*
*****************************************************************************/


#include <xLib/Units/Win/bDownloadURL.h>

#if defined(xOS_WIN)
#include <wininet.h>

#if defined(xCOMPILER_MS)
	#pragma comment(lib,"wininet")
#endif


//---------------------------------------------------------------------------
//DONE: bDownloadURL (download file using  ftp, http, https)
BOOL
bDownloadURL(
    LPCTSTR pszUrl,
    LPCTSTR pszFilePath
)
{
    /*DEBUG*/xASSERT_RET(NULL != pszUrl, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pszFilePath, FALSE);

    BOOL        bRes                    = FALSE;
    HINTERNET   hSession                = NULL;
    HINTERNET   hService                = NULL ;
    const ULONG culBuffSize             = 8192 * 4;
    TCHAR       szBuff[culBuffSize + 1] = {0};
    ULONG       ulBytesRead             = 0;

    //hSession = ::InternetOpen(xT("Microsoft FireFox"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    hSession = ::InternetOpen(xT("Microsoft FireFox"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    /*DEBUG*/xASSERT_RET(NULL != hSession, FALSE);

    hService = ::InternetOpenUrl(hSession, pszUrl, NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE, 0);
    /*DEBUG*/xASSERT_RET(NULL != hService, FALSE);


    FILE *pFile = _tfopen(pszFilePath, xT("wb"));
    /*DEBUG*/xASSERT_RET(NULL != pFile, FALSE);

    while (::InternetReadFile(hService, szBuff, culBuffSize, &ulBytesRead) && ulBytesRead){
        fwrite(szBuff, 1, ulBytesRead, pFile);
    }

    fflush(pFile);
    fclose(pFile);

    bRes = ::InternetCloseHandle(hService);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = ::InternetCloseHandle(hSession);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif
