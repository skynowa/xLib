/****************************************************************************
* Unit name:   bDownloadURL
* Description: скачка файла с инета в файл по протоколам ftp, http, https
* File name:   bDownloadURL.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.11.2009 11:50:17
*
*****************************************************************************/

#ifndef XLib_Units_bDownloadURLH
#define XLib_Units_bDownloadURLH
//---------------------------------------------------------------------------
#include <wininet.h>
#pragma comment(lib,"wininet")
//---------------------------------------------------------------------------
/*ftp:, http:, https:*/
BOOL bDownloadURL(LPCTSTR pszUrl, LPCTSTR pszFilePath) {
	/*DEBUG*/XASSERT_RET(NULL != pszUrl, FALSE);
	/*DEBUG*/XASSERT_RET(NULL != pszFilePath, FALSE);

	BOOL        bRes                    = FALSE;
	HINTERNET   hSession                = NULL;
	HINTERNET   hService                = NULL ;
	const ULONG culBuffSize             = 8192 * 4;
	TCHAR       szBuff[culBuffSize + 1] = {0};
	ULONG       ulBytesRead             = 0;

	//hSession = ::InternetOpen(xT("Microsoft FireFox"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	hSession = ::InternetOpen(xT("Microsoft FireFox"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	/*DEBUG*/XASSERT_RET(NULL != hSession, FALSE);

	hService = ::InternetOpenUrl(hSession, pszUrl, NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE, 0);
	/*DEBUG*/XASSERT_RET(NULL != hService, FALSE);


	FILE *pFile = _tfopen(pszFilePath, xT("wb"));
	/*DEBUG*/XASSERT_RET(NULL != pFile, FALSE);

	while (::InternetReadFile(hService, szBuff, culBuffSize, &ulBytesRead) && ulBytesRead){
		fwrite(szBuff, 1, ulBytesRead, pFile);
	}

	fflush(pFile);
	fclose(pFile);

	bRes = ::InternetCloseHandle(hService);
	/*DEBUG*/XASSERT_RET(FALSE != bRes, FALSE);

	bRes = ::InternetCloseHandle(hSession);
	/*DEBUG*/XASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
#endif //XLib_Units_bDownloadURLH

//---------------------------------------------------------------------------
/*int main(int argc, char* argv[]) {
	BOOL        bRes         = FALSE;
	std::string sUrl         = xT("http://dn0.berloga.net/78938/Uraliskaya_rybalka_v.02.rar"); //xT("http://forum.vingrad.ru/forum/borland-c++builder.html");
	std::string sFileContent = xT("");
	std::string sFilePath    = xT("C:/test.rar");


	bRes = bDownloadURL(sUrl.c_str(), sFilePath.c_str());
	if (TRUE == bRes) {
		std::cout << "Yes" << std::endl;
	} else {
		std::cout << "No" << std::endl;
	}


	system("pause");
	return 0;
}*/
//---------------------------------------------------------------------------
