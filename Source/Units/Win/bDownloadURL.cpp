/**
 * \file  bDownloadURL.cpp
 * \brief download file using  ftp, http, https
 */


#include <xLib/Units/Win/bDownloadURL.h>

#if defined(xOS_ENV_WIN)
#include <wininet.h>

#if defined(xCOMPILER_MS)
    #pragma comment(lib,"wininet")
#endif


//---------------------------------------------------------------------------
BOOL
bDownloadURL(
    LPCTSTR pszUrl,
    LPCTSTR pszFilePath
)
{
    /*DEBUG*/xASSERT_RET(NULL != pszUrl,      FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pszFilePath, FALSE);

    BOOL        bRes                    = FALSE;
    HINTERNET   hSession                = NULL;
    HINTERNET   hService                = NULL ;
    const ULONG culBuffSize             = 1024;
    char_t       szBuff[culBuffSize + 1] = {0};
    ULONG       ulBytesRead             = 0;

    //hSession = ::InternetOpen(xT("Microsoft FireFox"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    hSession = ::InternetOpen(xT("Microsoft FireFox"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    /*DEBUG*/xASSERT_RET(NULL != hSession, FALSE);

    hService = ::InternetOpenUrl(hSession, pszUrl, NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE, 0);
    /*DEBUG*/xASSERT_RET(NULL != hService, FALSE);

    FILE *pFile = xTFOPEN(pszFilePath, xT("wb"));
    /*DEBUG*/xASSERT_RET(NULL != pFile, FALSE);

    while (::InternetReadFile(hService, szBuff, culBuffSize, &ulBytesRead) && ulBytesRead) {
        fwrite(szBuff, 1, ulBytesRead, pFile);
    }

    fclose(pFile);    pFile = NULL;

    bRes = ::InternetCloseHandle(hService);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = ::InternetCloseHandle(hSession);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
#endif
