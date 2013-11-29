/**
 * \file  CxShell.cpp
 * \brief shell
 */


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

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxShell::isAvailable() const
{
    xTESTS_NA;

    int_t iRv = std::xTSYSTEM(NULL);

#if xOS_ENV_WIN
    xCHECK_RET(0 == iRv && ENOENT == CxStdError::get(), false);
#else
    xCHECK_RET(0 == iRv, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxShell::execute(
    std::ctstring_t &a_filePath,   ///< file path to binary file
    std::ctstring_t &a_params      ///< command line params for binary file
) const
{
    xTEST_NA(a_filePath);
    xTEST_NA(a_params);

    xCHECK_DO(true  == a_filePath.empty(), return);
    xCHECK_DO(!isAvailable(),              return);

    // REVIEW: security bug - xT("%s \"%s\"") or xT("\"%s\" \"%s\"") ??
    std::tstring_t cmd = CxString::format(xT("%s \"%s\""), a_filePath.c_str(), a_params.c_str());

    int_t iRv = std::xTSYSTEM(cmd.c_str());
    xTEST_DIFF(- 1, iRv);
}
//-------------------------------------------------------------------------------------------------


#if xOS_ENV_WIN

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxShell::findExecutable(
    std::ctstring_t &a_fileName,
    std::ctstring_t &a_findDirPath
) const
{
    xTEST_EQ(false, a_fileName.empty());
    // findDirPath - n/a

    int_t     iRv            = SE_ERR_FNF;
    tchar_t   buff[MAX_PATH] = {0};
    ctchar_t *findDirPath    = a_findDirPath.empty() ? NULL : a_findDirPath.c_str();

    iRv = reinterpret_cast<int_t>( ::FindExecutable(a_fileName.c_str(), findDirPath, buff) );
    xTEST_LESS(32, iRv);

    return std::tstring_t(buff);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxShell::execute(
    const HWND        &a_owner,
    const ExOperation &a_operation,
    std::ctstring_t   &a_filePath,
    std::ctstring_t   &a_params,
    std::ctstring_t   &a_dirPath,
    const EShowFlag   &a_showCmd
) const
{
    // owner      - n/a
    // ccsOperation - n/a
    // filePath   - n/a
    // params     - n/a
    // dirPath        - n/a
    // showCmd   - n/a

    std::tstring_t filePath = CxString::trimSpace(a_filePath);
    std::tstring_t params   = CxString::trimSpace(a_params);
    std::tstring_t dirPath  = CxString::trimSpace(a_dirPath);

    std::tstring_t operation;
    switch (a_operation) {
    case opEdit:
        operation = xT("edit");
        break;
    case opExplore:
        operation = xT("explore");
        break;
    case opFind:
        operation = xT("find");
        break;
    case opOpen:
        operation = xT("open");
        break;
    case opPrint:
        operation = xT("print");
        break;
    case opNull:
        operation = xT("");
        break;
    default:
        operation = xT("");
        break;
    }

    int_t iRv = reinterpret_cast<int_t>( ::ShellExecute(a_owner, operation.c_str(),
        filePath.c_str(), params.c_str(), dirPath.c_str(), a_showCmd) );
    xTEST_LESS(32, iRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxShell::executeEx(
    SHELLEXECUTEINFO &a_info
) const
{
    xTEST_NA(a_info);

    BOOL bRv = ::ShellExecuteEx(&a_info);
    xTEST_DIFF(FALSE, bRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxShell::executeHttp(
    std::ctstring_t &a_url
) const
{
    xTEST_NA(a_url);

    std::tstring_t url = CxString::trimSpace(a_url);

    xTEST_EQ(false, url.empty());

    execute(NULL, opOpen, xT("IEXPLORE.EXE"), url, xT(""), sfShowNormal);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxShell::executeFtp(
    std::ctstring_t &a_url
) const
{
    xTEST_NA(a_url);

    std::ctstring_t url = CxString::trimSpace(a_url);

    xTEST_EQ(false, url.empty());

    execute(NULL, opOpen, xT("explorer.exe"), xT("/e, ") + url, xT(""), sfShowNormal);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxShell::executeEmail(
    std::ctstring_t &a_toEmail,
    std::ctstring_t &a_subject,
    std::ctstring_t &a_body
) const
{
    // toEmail - n/a
    // subject - n/a
    // body    - n/a

    std::tstring_t toEmail = CxString::trimSpace(a_toEmail);
    std::tstring_t subject = CxString::trimSpace(a_subject);
    std::tstring_t body    = CxString::trimSpace(a_body);

    xTEST_EQ(false, toEmail.empty());

    // mailto:sAddress[sHeaders]
    // mailto:user@example.com?subject=Message Title&body=Message Content

    std::tstring_t cmd;

    cmd.append(xT("mailto:")  + toEmail);

    xCHECK_DO(!subject.empty() || !body.empty(), cmd.append(xT("?")                 ));
    xCHECK_DO(!subject.empty(),                  cmd.append(xT("subject=") + subject));
    xCHECK_DO(!body.empty(),                     cmd.append(xT("&body=")   + body   ));

    //iMsgBox(cmd);

    execute(NULL, opOpen, cmd, xT(""), xT(""), sfShowNormal);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxShell::specialDirPath(
    const ESpecialDir &a_dir,
    const HANDLE      &a_token
) const
{
    // dir  - n/a
    // token - n/a

    HRESULT      hRv    = S_FALSE;
    LPITEMIDLIST idList = {0};

    // FIXME: SHGetFolderLocation
    ////hRv = ::SHGetFolderLocation(NULL, sfDir, token, 0, &idList);
    hRv = ::SHGetSpecialFolderLocation(NULL, a_dir, &idList);
    xTEST_EQ(true, SUCCEEDED(hRv));

    tchar_t buff[MAX_PATH + sizeof(tchar_t)] = {0};

    BOOL bRv = ::SHGetPathFromIDList(idList, &buff[0]);
    xTEST_DIFF(FALSE, bRv);

    (void_t)::CoTaskMemFree(idList);

    return std::tstring_t(buff);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxShell::createShortcut(
    std::ctstring_t &a_shortCutFilePath, ///< путь и имя ярлыка, например, "C:\\Блокнот.lnk"
                                         ///< Если не указан путь, ярлык будет создан в папке,
                                         ///< указанной в следующем параметре.
                                         ///< Прим.: Windows сама НЕ добавляет
                                         ///< к имени расширение .lnk
    std::ctstring_t &a_filePath,         ///< путь и имя программы/файла, например,
                                         ///< "C:\\Windows\\NotePad.Exe" или
                                         ///< "C:\\Мои документы\\Файл.doc"
    std::ctstring_t &a_workingDirectory, ///< рабочий каталог, например, "C:\\Windows"
    std::ctstring_t &a_args,             ///< аргументы командной строки, например,
                                         ///< "C:\\Doc\\Text.txt"
    const WORD      &a_hotKey,           ///< горячая клавиша, например,
                                         ///< для Ctrl+Alt+A HOTKEY(HOTKEYF_ALT|HOTKEYF_CONTROL,'A')
    cint_t          &a_cmdShow,          ///< начальный вид, например, SW_SHOWNORMAL
    std::ctstring_t &a_iconFilePath,     ///< путь и имя файла, содержащего иконку,
                                         ///< например, "C:\\Windows\\NotePad.Exe"
    cint_t          &a_iconIndex,        ///< индекс иконки в файле, нумеруется с 0
    std::ctstring_t &a_description       ///< description
) const
{


    CxCom cmCom(COINIT_MULTITHREADED);

    HRESULT     hRv  = 0;
    IShellLink *link = NULL;

    hRv = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink,
        (void_t **)&link);
    xTEST_EQ(true, SUCCEEDED(hRv));

    {
        hRv = link->SetPath(a_filePath.c_str());
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = link->SetArguments(a_args.c_str());
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = link->SetWorkingDirectory(a_workingDirectory.c_str());
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = link->SetIconLocation(a_iconFilePath.c_str(), a_iconIndex);
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = link->SetHotkey(a_hotKey);
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = link->SetShowCmd(a_cmdShow);
        xTEST_EQ(true, SUCCEEDED(hRv));

        hRv = link->SetDescription(a_description.c_str());
        xTEST_EQ(true, SUCCEEDED(hRv));
    }

    IPersistFile *file = NULL;

    hRv = link->QueryInterface(IID_IPersistFile, CxUtils::reinterpretCastT<void_t **>( &file ));
    xTEST_EQ(true, SUCCEEDED(hRv));

#if xUNICODE
    hRv = file->Save(a_shortCutFilePath.c_str(), true);
#else
    wchar_t buff[MAX_PATH + 1] = {0};

    ::MultiByteToWideChar(CP_ACP, 0, a_shortCutFilePath.c_str(), - 1, buff, MAX_PATH);
    hRv = file->Save(buff, true);
#endif

    file->Release();    file = NULL;
    link->Release();    link = NULL;
}
//-------------------------------------------------------------------------------------------------

#endif

xNAMESPACE_END(NxLib)
