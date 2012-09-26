/**
 * \file  bDownloadURL.cpp
 * \brief download file using  ftp, http, https
 */


#include <xLib/Units/Win/bDownloadURL.h>

#if xOS_ENV_WIN

#include <wininet.h>

#if xCOMPILER_MS
    #pragma comment(lib,"wininet")
#endif


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
bool
bDownloadURL(
    LPCTSTR a_pszUrl,
    LPCTSTR a_pszFilePath
)
{
    /*DEBUG*/xASSERT_RET(NULL != a_pszUrl,      false);
    /*DEBUG*/xASSERT_RET(NULL != a_pszFilePath, false);

    HINTERNET     hSession                = NULL;
    HINTERNET     hService                = NULL;
    const ulong_t culBuffSize             = 1024;
    tchar_t       szBuff[culBuffSize + 1] = {0};
    ulong_t       ulBytesRead             = 0;

    //hSession = ::InternetOpen(xT("Microsoft FireFox"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    hSession = ::InternetOpen(xT("Microsoft FireFox"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    /*DEBUG*/xASSERT_RET(NULL != hSession, false);

    hService = ::InternetOpenUrl(hSession, a_pszUrl, NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE, 0);
    /*DEBUG*/xASSERT_RET(NULL != hService, false);

    FILE *pFile = xTFOPEN(a_pszFilePath, xT("wb"));
    /*DEBUG*/xASSERT_RET(NULL != pFile, false);

    while (::InternetReadFile(hService, szBuff, culBuffSize, &ulBytesRead) && ulBytesRead) {
        fwrite(szBuff, 1, ulBytesRead, pFile);
    }

    fclose(pFile);    pFile = NULL;

    BOOL bRv = ::InternetCloseHandle(hService);
    /*DEBUG*/xASSERT_RET(FALSE != bRv, false);

    bRv = ::InternetCloseHandle(hSession);
    /*DEBUG*/xASSERT_RET(FALSE != bRv, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
