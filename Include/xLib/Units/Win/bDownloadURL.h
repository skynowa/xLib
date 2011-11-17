/**
 * \file  bDownloadURL.h
 * \brief download file using  ftp, http, https
 */


#ifndef xLib_Units_bDownloadURLH
#define xLib_Units_bDownloadURLH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

    xNAMESPACE_BEGIN(NxLib)

        BOOL bDownloadURL(LPCTSTR pszUrl, LPCTSTR pszFilePath);
            ///< download file using ftp, http, https

    xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif //xLib_Units_bDownloadURLH


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
