/**
 * \file  CxShell.cpp
 * \brief shell
 */


#include <xLib/System/CxShell.h>

#include <xLib/Core/CxString.h>
#include <xLib/Core/Win/CxCom.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTracer.h>

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
CxShell::isAvailable()
{
    xTESTS_NA;

    int_t iRv = ::xTSYSTEM(NULL);

#if xOS_ENV_WIN
    xCHECK_RET(0 == iRv && ENOENT == CxStdError::get(), false);
#else
    xCHECK_RET(0 == iRv, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
/* static */
void_t
CxShell::execute(
    std::ctstring_t &a_filePath,   ///< file path to binary file
    std::ctstring_t &a_params      ///< command line params for binary file
)
{
    xTEST_NA(a_filePath);
    xTEST_NA(a_params);

    xCHECK_DO(true  == a_filePath.empty(), return);
    xCHECK_DO(!isAvailable(),        return);

    // REVIEW: security bug - xT("%s \"%s\"") or xT("\"%s\" \"%s\"") ??
    std::tstring_t sCommand = CxString::format(xT("%s \"%s\""), a_filePath.c_str(), a_params.c_str());

    int_t iRv = ::xTSYSTEM(sCommand.c_str());
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------


#if xOS_ENV_WIN

//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxShell::findExecutable(
    std::ctstring_t &a_fileName,
    std::ctstring_t &a_findDirPath
)
{
    xTEST_EQ(false, a_fileName.empty());
    // findDirPath - n/a

    int_t            iRv             = SE_ERR_FNF;
    tchar_t        szRes[MAX_PATH] = {0};
    ctchar_t *cpszFindDirPath = a_findDirPath.empty() ? NULL : a_findDirPath.c_str();

    iRv = reinterpret_cast<int_t>( ::FindExecutable(a_fileName.c_str(), cpszFindDirPath, szRes) );
    xTEST_LESS(32, iRv);

    return std::tstring_t(szRes);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxShell::execute(
    const HWND        &a_owner,
    const ExOperation &a_operation,
    std::ctstring_t   &a_filePath,
    std::ctstring_t   &a_params,
    std::ctstring_t   &a_dirPath,
    const EShowFlag   &a_showCmd
)
{
    // owner      - n/a
    // ccsOperation - n/a
    // filePath   - n/a
    // params     - n/a
    // dirPath        - n/a
    // showCmd   - n/a

    std::tstring_t sFilePath  = CxString::trimSpace(a_filePath);
    std::tstring_t sParams    = CxString::trimSpace(a_params);
    std::tstring_t sDir       = CxString::trimSpace(a_dirPath);

    std::tstring_t sOperation;
    switch (a_operation) {
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

    int_t iRv = reinterpret_cast<int_t>( ::ShellExecute(a_owner, sOperation.c_str(), sFilePath.c_str(), sParams.c_str(), sDir.c_str(), a_showCmd) );
    xTEST_LESS(32, iRv);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxShell::executeEx(
    SHELLEXECUTEINFO *a_info
)
{
    xTEST_PTR(a_info);

    BOOL bRv = ::ShellExecuteEx(a_info);
    xTEST_DIFF(FALSE, bRv);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxShell::executeHttp(
    std::ctstring_t &a_url
)
{
    // url - n/a

    std::tstring_t sUrl = CxString::trimSpace(a_url);

    xTEST_EQ(false, sUrl.empty());

    execute(NULL, opOpen, xT("IEXPLORE.EXE"), sUrl, xT(""), sfShowNormal);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxShell::executeFtp(
    std::ctstring_t &a_url
)
{
    // url - n/a

    std::tstring_t sUrl = CxString::trimSpace(a_url);

    xTEST_EQ(false, sUrl.empty());

    execute(NULL, opOpen, xT("explorer.exe"), xT("/e, ") + sUrl, xT(""), sfShowNormal);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxShell::executeEmail(
    std::ctstring_t &a_toEmail,
    std::ctstring_t &a_subject,
    std::ctstring_t &a_body
)
{
    // toEmail - n/a
    // subject - n/a
    // body    - n/a

    std::tstring_t sToEmail = CxString::trimSpace(a_toEmail);
    std::tstring_t sSubject = CxString::trimSpace(a_subject);
    std::tstring_t sBody    = CxString::trimSpace(a_body);

    xTEST_EQ(false, a_toEmail.empty());

    //mailto:sAddress[sHeaders]
    //mailto:user@example.com?subject=Message Title&body=Message Content

    std::tstring_t sCmd;

    sCmd.append(xT("mailto:")  + sToEmail);

    xCHECK_DO(!sSubject.empty() || !sBody.empty(), sCmd.append(xT("?")                  ));
    xCHECK_DO(!sSubject.empty(),                           sCmd.append(xT("subject=") + sSubject));
    xCHECK_DO(!sBody.empty(),                              sCmd.append(xT("&body=")    + sBody  ));

    //iMsgBox(sCmd);

    execute(NULL, opOpen, sCmd, xT(""), xT(""), sfShowNormal);
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxShell::specialDirPath(
    const ESpecialDir &a_dir,
    const HANDLE      &a_token
)
{
    // dir  - n/a
    // token - n/a

    HRESULT      hRv     = S_FALSE;
    LPITEMIDLIST pidlList = {0};

    ////hRv = ::SHGetFolderLocation(NULL, sfDir, token, 0, &pidlList);    //FIXME: SHGetFolderLocation
    hRv = ::SHGetSpecialFolderLocation(NULL, a_dir, &pidlList);
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
void_t
CxShell::createShortcut(
    std::ctstring_t &a_shortCutFilePath, ///< путь и имя ярлыка, например, "C:\\Блокнот.lnk"
                                           ///< Если не указан путь, ярлык будет создан в папке, указанной в следующем параметре.
                                           ///< Прим.: Windows сама НЕ добавляет к имени расширение .lnk
    std::ctstring_t &a_filePath,         ///< путь и имя программы/файла, например, "C:\\Windows\\NotePad.Exe" или "C:\\Мои документы\\Файл.doc"
    std::ctstring_t &a_workingDirectory, ///< рабочий каталог, например, "C:\\Windows"
    std::ctstring_t &a_args,        ///< аргументы командной строки, например, "C:\\Doc\\Text.txt"
    const WORD      &a_hotKey,           ///< горячая клавиша, например, для Ctrl+Alt+A HOTKEY(HOTKEYF_ALT|HOTKEYF_CONTROL,'A')
    cint_t          &a_cmdShow,          ///< начальный вид, например, SW_SHOWNORMAL (см. параметр nCmdShow функции ShowWindow)
    std::ctstring_t &a_iconFilePath,     ///< путь и имя файла, содержащего иконку, например, "C:\\Windows\\NotePad.Exe"
    cint_t          &a_iconIndex,        ///< индекс иконки в файле, нумеруется с 0
    std::ctstring_t &a_description       ///< description
)
{


    CxCom cmCom(COINIT_MULTITHREADED);

    IShellLink *pslSL = NULL;
    HRESULT     hRv  = 0;

    hRv = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void_t **)&pslSL);
    xTEST_EQ(true, SUCCEEDED(hRv));

    {
        hRv = pslSL->SetPath(a_filePath.c_str());
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetArguments(a_args.c_str());
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetWorkingDirectory(a_workingDirectory.c_str());
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetIconLocation(a_iconFilePath.c_str(), a_iconIndex);
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetHotkey(a_hotKey);
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetShowCmd(a_cmdShow);
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = pslSL->SetDescription(a_description.c_str());
        xTEST_EQ(true, SUCCEEDED(hRv));
    }


    IPersistFile *ppfPF = NULL;

    hRv = pslSL->QueryInterface(IID_IPersistFile, CxUtils::reinterpretCastT<void_t **>( &ppfPF ));
    xTEST_EQ(true, SUCCEEDED(hRv));

#if xUNICODE
    hRv = ppfPF->Save(a_shortCutFilePath.c_str(), true);
#else
    wchar_t wszBuff[MAX_PATH + 1] = {0};

    ::MultiByteToWideChar(CP_ACP, 0, a_shortCutFilePath.c_str(), - 1, wszBuff, MAX_PATH);
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
CxShell::CxShell()
{
}
//------------------------------------------------------------------------------
/* virtual */
CxShell::~CxShell()
{
}
//------------------------------------------------------------------------------

#endif

xNAMESPACE_END(NxLib)
