/**
 * \file  CxShell.cpp
 * \brief shell
 */


#include <xLib/Common/CxShell.h>

#include <xLib/Common/CxString.h>
#include <xLib/Common/Win/CxCom.h>

#if xCOMPILER_MINGW32
    //  lib: -luuid (for IID_IPersistFile)
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
bool
CxShell::bIsAvailable() {
    xDEBUG_VARS_NA;

    int iRv = ::xTSYSTEM(NULL);

#if   xOS_ENV_WIN
    xCHECK_RET(0 == iRv && ENOENT == CxStdError::iGet(), false);
#elif xOS_ENV_UNIX
    xCHECK_RET(0 == iRv, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/* static */
void
CxShell::vExecute(
    const std::tstring_t &a_csFilePath,   ///< file path to binary file
    const std::tstring_t &a_csParams      ///< command line params for binary file
)
{
    xDEBUG_VAR_NA(a_csFilePath);
    xDEBUG_VAR_NA(a_csParams);

    xCHECK_DO(true  == a_csFilePath.empty(), return);
    xCHECK_DO(false == bIsAvailable(),       return);

    // REVIEW: security bug - xT("%s \"%s\"") or xT("\"%s\" \"%s\"") ??
    std::tstring_t sCommand = CxString::sFormat(xT("%s \"%s\""), a_csFilePath.c_str(), a_csParams.c_str());

    int iRv = ::xTSYSTEM(sCommand.c_str());
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
}
//---------------------------------------------------------------------------


#if   xOS_ENV_WIN

//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxShell::sFindExecutable(
    const std::tstring_t &a_csFileName,
    const std::tstring_t &a_csFindDirPath
)
{
    /*DEBUG*/xTEST_EQ(false, a_csFileName.empty());
    /*DEBUG*/// csFindDirPath - n/a

    int     iRv             = SE_ERR_FNF;
    tchar_t szRes[MAX_PATH] = {0};

    iRv = reinterpret_cast<int>( ::FindExecutable(a_csFileName.c_str(), a_csFindDirPath.c_str(), szRes) );
    /*DEBUG*/xTEST_LESS(32, iRv);

    return std::tstring_t(szRes);
}
//---------------------------------------------------------------------------
/* static */
void
CxShell::vExecute(
    const HWND           &a_chOwner,
    const ExOperation    &a_copOperation,
    const std::tstring_t &a_csFilePath,
    const std::tstring_t &a_csParams,
    const std::tstring_t &a_csDir,
    const EShowFlag      &a_csfShowCmd
)
{
    /*DEBUG*/// chOwner      - n/a
    /*DEBUG*/// ccsOperation - n/a
    /*DEBUG*/// csFilePath   - n/a
    /*DEBUG*/// csParams     - n/a
    /*DEBUG*/// csDir        - n/a
    /*DEBUG*/// csfShowCmd   - n/a

    std::tstring_t sFilePath  = CxString::sTrimSpace(a_csFilePath);
    std::tstring_t sParams    = CxString::sTrimSpace(a_csParams);
    std::tstring_t sDir       = CxString::sTrimSpace(a_csDir);

    std::tstring_t sOperation;
    switch (a_copOperation) {
        case opEdit:    { sOperation = xT("edit");    } break;
        case opExplore: { sOperation = xT("explore"); } break;
        case opFind:    { sOperation = xT("find");    } break;
        case opOpen:    { sOperation = xT("open");    } break;
        case opPrint:   { sOperation = xT("print");   } break;
        case opNull:    { sOperation = xT("");        } break;

        default:        { sOperation = xT("");        } break;
    }

    int iRv = reinterpret_cast<int>( ::ShellExecute(a_chOwner, sOperation.c_str(), sFilePath.c_str(), sParams.c_str(), sDir.c_str(), a_csfShowCmd) );
    /*DEBUG*/xTEST_LESS(32, iRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxShell::vExecuteEx(
    SHELLEXECUTEINFO *a_peiInfo
)
{
    /*DEBUG*/xTEST_PTR(a_peiInfo);

    BOOL bRv = ::ShellExecuteEx(a_peiInfo);
    /*DEBUG*/xTEST_DIFF(FALSE, bRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxShell::vExecuteHttp(
    const std::tstring_t &a_csUrl
)
{
    /*DEBUG*/// csUrl - n/a

    std::tstring_t sUrl = CxString::sTrimSpace(a_csUrl);

    xTEST_EQ(false, sUrl.empty());

    vExecute(NULL, opOpen, xT("IEXPLORE.EXE"), sUrl, xT(""), sfShowNormal);
}
//---------------------------------------------------------------------------
/* static */
void
CxShell::vExecuteFtp(
    const std::tstring_t &a_csUrl
)
{
    /*DEBUG*/// csUrl - n/a

    std::tstring_t sUrl = CxString::sTrimSpace(a_csUrl);

    xTEST_EQ(false, sUrl.empty());

    vExecute(NULL, opOpen, xT("explorer.exe"), xT("/e, ") + sUrl, xT(""), sfShowNormal);
}
//---------------------------------------------------------------------------
/* static */
void
CxShell::vExecuteEmail(
    const std::tstring_t &a_csToEmail,
    const std::tstring_t &a_csSubject,
    const std::tstring_t &a_csBody
)
{
    /*DEBUG*/// csToEmail - n/a
    /*DEBUG*/// csSubject - n/a
    /*DEBUG*/// csBody    - n/a

    std::tstring_t sToEmail = CxString::sTrimSpace(a_csToEmail);
    std::tstring_t sSubject = CxString::sTrimSpace(a_csSubject);
    std::tstring_t sBody    = CxString::sTrimSpace(a_csBody);

    xTEST_EQ(false, a_csToEmail.empty());

    //mailto:sAddress[sHeaders]
    //mailto:user@example.com?subject=Message Title&body=Message Content

    std::tstring_t sCmd;

    sCmd.append(xT("mailto:")  + sToEmail);

    xCHECK_DO(false == sSubject.empty() || false == sBody.empty(), sCmd.append(xT("?")                  ));
    xCHECK_DO(false == sSubject.empty(),                           sCmd.append(xT("subject=") + sSubject));
    xCHECK_DO(false == sBody.empty(),                              sCmd.append(xT("&body=")    + sBody  ));

    //iMsgBox(sCmd);

    vExecute(NULL, opOpen, sCmd, xT(""), xT(""), sfShowNormal);
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxShell::sGetSpecialDirPath(
    const ESpecialDir &a_csfDir,
    const HANDLE      &a_chToken
)
{
    /*DEBUG*/// csfDir  - n/a
    /*DEBUG*/// chToken - n/a

    HRESULT      hRv     = S_FALSE;
    LPITEMIDLIST pidlList = {0};

    ////hRv = ::SHGetFolderLocation(NULL, sfDir, chToken, 0, &pidlList);    //FIXME: SHGetFolderLocation
    hRv = ::SHGetSpecialFolderLocation(NULL, a_csfDir, &pidlList);
    /*DEBUG*/xTEST_EQ(true, SUCCEEDED(hRv));

    tchar_t szRes[MAX_PATH + sizeof(tchar_t)] = {0};

    BOOL bRv = ::SHGetPathFromIDList(pidlList, &szRes[0]);
    /*DEBUG*/xTEST_DIFF(FALSE, bRv);

    ::CoTaskMemFree(pidlList);
    /*DEBUG*/// n/a

    return std::tstring_t(szRes);
}
//---------------------------------------------------------------------------
#define xHOTKEY(modifier, key) ((((modifier) & 0xff) << 8) | ((key)&0xff))

/* static */
void
CxShell::vCreateShortcut(
    const std::tstring_t &a_csShortCutFilePath, ///< путь и имя ярлыка, например, "C:\\Блокнот.lnk"
                                                ///< Если не указан путь, ярлык будет создан в папке, указанной в следующем параметре.
                                                ///< Прим.: Windows сама НЕ добавляет к имени расширение .lnk
    const std::tstring_t &a_csFilePath,         ///< путь и имя программы/файла, например, "C:\\Windows\\NotePad.Exe" или "C:\\Мои документы\\Файл.doc"
    const std::tstring_t &a_csWorkingDirectory, ///< рабочий каталог, например, "C:\\Windows"
    const std::tstring_t &a_csArguments,        ///< аргументы командной строки, например, "C:\\Doc\\Text.txt"
    const WORD           &a_cwHotKey,           ///< горячая клавиша, например, для Ctrl+Alt+A HOTKEY(HOTKEYF_ALT|HOTKEYF_CONTROL,'A')
    const int            &a_ciCmdShow,          ///< начальный вид, например, SW_SHOWNORMAL (см. параметр nCmdShow функции ShowWindow)
    const std::tstring_t &a_csIconFilePath,     ///< путь и имя файла, содержащего иконку, например, "C:\\Windows\\NotePad.Exe"
    const int            &a_ciIconIndex,        ///< индекс иконки в файле, нумеруется с 0
    const std::tstring_t &a_csDescription       ///< description
)
{
    /*DEBUG*/

    CxCom cmCom(CxCom::cmMultiThreaded);

    IShellLink *pslSL = NULL;
    HRESULT     hRv  = 0;

    hRv = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&pslSL);
    /*DEBUG*/xTEST_EQ(true, SUCCEEDED(hRv));

    {
        hRv = pslSL->SetPath(a_csFilePath.c_str());
        /*DEBUG*/xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetArguments(a_csArguments.c_str());
        /*DEBUG*/xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetWorkingDirectory(a_csWorkingDirectory.c_str());
        /*DEBUG*/xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetIconLocation(a_csIconFilePath.c_str(), a_ciIconIndex);
        /*DEBUG*/xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetHotkey(a_cwHotKey);
        /*DEBUG*/xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetShowCmd(a_ciCmdShow);
        /*DEBUG*/xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetDescription(a_csDescription.c_str());
        /*DEBUG*/xTEST_EQ(true, SUCCEEDED(hRv));
    }


    IPersistFile *ppfPF = NULL;

    hRv = pslSL->QueryInterface(IID_IPersistFile, CxUtils::reinterpretCastT<void **>( &ppfPF ));
    /*DEBUG*/xTEST_EQ(true, SUCCEEDED(hRv));

#if xUNICODE
    hRv = ppfPF->Save(csShortCutFilePath.c_str(), true);
#else
    wchar_t wszBuff[MAX_PATH + 1] = {0};

    ::MultiByteToWideChar(CP_ACP, 0, a_csShortCutFilePath.c_str(), - 1, wszBuff, MAX_PATH);
    hRv = ppfPF->Save(wszBuff, true);
#endif

    ppfPF->Release();
    pslSL->Release();
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxShell::CxShell() {

}
//---------------------------------------------------------------------------
/* virtual */
CxShell::~CxShell() {

}
//---------------------------------------------------------------------------

#endif

xNAMESPACE_END(NxLib)
