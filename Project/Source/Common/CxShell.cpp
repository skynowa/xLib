/**
 * \file  CxShell.cpp
 * \brief shell
 */


#include <xLib/Common/CxShell.h>

#include <xLib/Common/CxString.h>
#include <xLib/Common/Win/CxCom.h>

#if xCOMPILER_MINGW
    //  lib: -luuid (for IID_IPersistFile)
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
bool_t
CxShell::isAvailable() {
    xTESTS_NA;

    int_t iRv = ::xTSYSTEM(NULL);

#if   xOS_ENV_WIN
    xCHECK_RET(0 == iRv && ENOENT == CxStdError::get(), false);
#elif xOS_ENV_UNIX
    xCHECK_RET(0 == iRv, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
/* static */
void
CxShell::execute(
    std::ctstring_t &a_csFilePath,   ///< file path to binary file
    std::ctstring_t &a_csParams      ///< command line params for binary file
)
{
    xTEST_NA(a_csFilePath);
    xTEST_NA(a_csParams);

    xCHECK_DO(true  == a_csFilePath.empty(), return);
    xCHECK_DO(false == isAvailable(),        return);

    // REVIEW: security bug - xT("%s \"%s\"") or xT("\"%s\" \"%s\"") ??
    std::tstring_t sCommand = CxString::format(xT("%s \"%s\""), a_csFilePath.c_str(), a_csParams.c_str());

    int_t iRv = ::xTSYSTEM(sCommand.c_str());
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------


#if   xOS_ENV_WIN

//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxShell::findExecutable(
    std::ctstring_t &a_csFileName,
    std::ctstring_t &a_csFindDirPath
)
{
    xTEST_EQ(false, a_csFileName.empty());
    // csFindDirPath - n/a

    int_t            iRv             = SE_ERR_FNF;
    tchar_t        szRes[MAX_PATH] = {0};
    ctchar_t *cpszFindDirPath = a_csFindDirPath.empty() ? NULL : a_csFindDirPath.c_str();

    iRv = reinterpret_cast<int_t>( ::FindExecutable(a_csFileName.c_str(), cpszFindDirPath, szRes) );
    xTEST_LESS(32, iRv);

    return std::tstring_t(szRes);
}
//------------------------------------------------------------------------------
/* static */
void
CxShell::execute(
    const HWND           &a_chOwner,
    const ExOperation    &a_copOperation,
    std::ctstring_t &a_csFilePath,
    std::ctstring_t &a_csParams,
    std::ctstring_t &a_csDir,
    const EShowFlag      &a_csfShowCmd
)
{
    // chOwner      - n/a
    // ccsOperation - n/a
    // csFilePath   - n/a
    // csParams     - n/a
    // csDir        - n/a
    // csfShowCmd   - n/a

    std::tstring_t sFilePath  = CxString::trimSpace(a_csFilePath);
    std::tstring_t sParams    = CxString::trimSpace(a_csParams);
    std::tstring_t sDir       = CxString::trimSpace(a_csDir);

    std::tstring_t sOperation;
    switch (a_copOperation) {
        case opEdit:
            sOperation = xT("edit");
            break;
        case opExplore:
            sOperation = xT("explore");
            break;
        case opFind:
            sOperation = xT("find");
            break;
        case opOpen:
            sOperation = xT("open");
            break;
        case opPrint:
            sOperation = xT("print");
            break;
        case opNull:
            sOperation = xT("");
            break;
        default:
            sOperation = xT("");
            break;
    }

    int_t iRv = reinterpret_cast<int_t>( ::ShellExecute(a_chOwner, sOperation.c_str(), sFilePath.c_str(), sParams.c_str(), sDir.c_str(), a_csfShowCmd) );
    xTEST_LESS(32, iRv);
}
//------------------------------------------------------------------------------
/* static */
void
CxShell::executeEx(
    SHELLEXECUTEINFO *a_peiInfo
)
{
    xTEST_PTR(a_peiInfo);

    BOOL bRv = ::ShellExecuteEx(a_peiInfo);
    xTEST_DIFF(FALSE, bRv);
}
//------------------------------------------------------------------------------
/* static */
void
CxShell::executeHttp(
    std::ctstring_t &a_csUrl
)
{
    // csUrl - n/a

    std::tstring_t sUrl = CxString::trimSpace(a_csUrl);

    xTEST_EQ(false, sUrl.empty());

    execute(NULL, opOpen, xT("IEXPLORE.EXE"), sUrl, xT(""), sfShowNormal);
}
//------------------------------------------------------------------------------
/* static */
void
CxShell::executeFtp(
    std::ctstring_t &a_csUrl
)
{
    // csUrl - n/a

    std::tstring_t sUrl = CxString::trimSpace(a_csUrl);

    xTEST_EQ(false, sUrl.empty());

    execute(NULL, opOpen, xT("explorer.exe"), xT("/e, ") + sUrl, xT(""), sfShowNormal);
}
//------------------------------------------------------------------------------
/* static */
void
CxShell::executeEmail(
    std::ctstring_t &a_csToEmail,
    std::ctstring_t &a_csSubject,
    std::ctstring_t &a_csBody
)
{
    // csToEmail - n/a
    // csSubject - n/a
    // csBody    - n/a

    std::tstring_t sToEmail = CxString::trimSpace(a_csToEmail);
    std::tstring_t sSubject = CxString::trimSpace(a_csSubject);
    std::tstring_t sBody    = CxString::trimSpace(a_csBody);

    xTEST_EQ(false, a_csToEmail.empty());

    //mailto:sAddress[sHeaders]
    //mailto:user@example.com?subject=Message Title&body=Message Content

    std::tstring_t sCmd;

    sCmd.append(xT("mailto:")  + sToEmail);

    xCHECK_DO(false == sSubject.empty() || false == sBody.empty(), sCmd.append(xT("?")                  ));
    xCHECK_DO(false == sSubject.empty(),                           sCmd.append(xT("subject=") + sSubject));
    xCHECK_DO(false == sBody.empty(),                              sCmd.append(xT("&body=")    + sBody  ));

    //iMsgBox(sCmd);

    execute(NULL, opOpen, sCmd, xT(""), xT(""), sfShowNormal);
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxShell::specialDirPath(
    const ESpecialDir &a_csfDir,
    const HANDLE      &a_chToken
)
{
    // csfDir  - n/a
    // chToken - n/a

    HRESULT      hRv     = S_FALSE;
    LPITEMIDLIST pidlList = {0};

    ////hRv = ::SHGetFolderLocation(NULL, sfDir, chToken, 0, &pidlList);    //FIXME: SHGetFolderLocation
    hRv = ::SHGetSpecialFolderLocation(NULL, a_csfDir, &pidlList);
    xTEST_EQ(true, SUCCEEDED(hRv));

    tchar_t szRes[MAX_PATH + sizeof(tchar_t)] = {0};

    BOOL bRv = ::SHGetPathFromIDList(pidlList, &szRes[0]);
    xTEST_DIFF(FALSE, bRv);

    ::CoTaskMemFree(pidlList);
    // n/a

    return std::tstring_t(szRes);
}
//------------------------------------------------------------------------------
#define xHOTKEY(modifier, key) ((((modifier) & 0xff) << 8) | ((key)&0xff))

/* static */
void
CxShell::createShortcut(
    std::ctstring_t &a_csShortCutFilePath, ///< путь и имя ярлыка, например, "C:\\Блокнот.lnk"
                                                ///< Если не указан путь, ярлык будет создан в папке, указанной в следующем параметре.
                                                ///< Прим.: Windows сама НЕ добавляет к имени расширение .lnk
    std::ctstring_t &a_csFilePath,         ///< путь и имя программы/файла, например, "C:\\Windows\\NotePad.Exe" или "C:\\Мои документы\\Файл.doc"
    std::ctstring_t &a_csWorkingDirectory, ///< рабочий каталог, например, "C:\\Windows"
    std::ctstring_t &a_csArguments,        ///< аргументы командной строки, например, "C:\\Doc\\Text.txt"
    const WORD           &a_cwHotKey,           ///< горячая клавиша, например, для Ctrl+Alt+A HOTKEY(HOTKEYF_ALT|HOTKEYF_CONTROL,'A')
    cint_t            &a_ciCmdShow,          ///< начальный вид, например, SW_SHOWNORMAL (см. параметр nCmdShow функции ShowWindow)
    std::ctstring_t &a_csIconFilePath,     ///< путь и имя файла, содержащего иконку, например, "C:\\Windows\\NotePad.Exe"
    cint_t            &a_ciIconIndex,        ///< индекс иконки в файле, нумеруется с 0
    std::ctstring_t &a_csDescription       ///< description
)
{


    CxCom cmCom(COINIT_MULTITHREADED);

    IShellLink *pslSL = NULL;
    HRESULT     hRv  = 0;

    hRv = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&pslSL);
    xTEST_EQ(true, SUCCEEDED(hRv));

    {
        hRv = pslSL->SetPath(a_csFilePath.c_str());
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetArguments(a_csArguments.c_str());
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetWorkingDirectory(a_csWorkingDirectory.c_str());
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetIconLocation(a_csIconFilePath.c_str(), a_ciIconIndex);
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetHotkey(a_cwHotKey);
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetShowCmd(a_ciCmdShow);
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetDescription(a_csDescription.c_str());
        xTEST_EQ(true, SUCCEEDED(hRv));
    }


    IPersistFile *ppfPF = NULL;

    hRv = pslSL->QueryInterface(IID_IPersistFile, CxUtils::reinterpretCastT<void **>( &ppfPF ));
    xTEST_EQ(true, SUCCEEDED(hRv));

#if xUNICODE
    hRv = ppfPF->Save(a_csShortCutFilePath.c_str(), true);
#else
    wchar_t wszBuff[MAX_PATH + 1] = {0};

    ::MultiByteToWideChar(CP_ACP, 0, a_csShortCutFilePath.c_str(), - 1, wszBuff, MAX_PATH);
    hRv = ppfPF->Save(wszBuff, true);
#endif

    ppfPF->Release();
    pslSL->Release();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxShell::CxShell() {

}
//------------------------------------------------------------------------------
/* virtual */
CxShell::~CxShell() {

}
//------------------------------------------------------------------------------

#endif

xNAMESPACE_END(NxLib)
