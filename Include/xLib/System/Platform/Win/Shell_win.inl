/**
 * \file  Shell.inl
 * \brief shell
 */


#if xCOMPILER_MINGW
    //  lib: -luuid (for IID_IPersistFile)
#endif


xNAMESPACE_BEGIN2(xl, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Shell::_isAvailable_impl() const
{
    int_t iRv = xTSYSTEM(xPTR_NULL);
    xCHECK_RET(iRv == 0 && StdError::get() == ENOENT, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Shell::findExecutable(
    std::ctstring_t &a_fileName,
    std::ctstring_t &a_findDirPath
) const
{
    xTEST_EQ(a_fileName.empty(), false);
    xTEST_NA(a_findDirPath);

    int_t         iRv            = SE_ERR_FNF;
    tchar_t       buff[MAX_PATH] = {0};
    cptr_ctchar_t findDirPath    = a_findDirPath.empty() ? xPTR_NULL : a_findDirPath.c_str();

    iRv = reinterpret_cast<int_t>( ::FindExecutable(a_fileName.c_str(), findDirPath, buff) );
    xTEST_LESS(32, iRv);

    return std::tstring_t(buff);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Shell::execute(
    const HWND        &a_owner,
    const ExOperation &a_operation,
    std::ctstring_t   &a_filePath,
    std::ctstring_t   &a_params,
    std::ctstring_t   &a_dirPath,
    const EShowFlag   &a_showCmd
) const
{
    xTEST_NA(a_owner);
    xTEST_NA(a_operation);
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_NA(a_params);
    xTEST_EQ(a_dirPath.empty(), false);
    xTEST_NA(a_showCmd);

    std::ctstring_t filePath = String::trimSpace(a_filePath);
    std::ctstring_t params   = String::trimSpace(a_params);
    std::ctstring_t dirPath  = String::trimSpace(a_dirPath);

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
xINLINE void_t
Shell::executeEx(
    SHELLEXECUTEINFO &a_info
) const
{
    xTEST_EQ(a_info.empty(), false);

    BOOL blRv = ::ShellExecuteEx(&a_info);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Shell::executeHttp(
    std::ctstring_t &a_url
) const
{
    xTEST_EQ(a_url.empty(), false);

    std::ctstring_t url = String::trimSpace(a_url);
    xTEST_EQ(url.empty(), false);

    execute(xPTR_NULL, opOpen, xT("IEXPLORE.EXE"), url, xT(""), sfShowNormal);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Shell::executeFtp(
    std::ctstring_t &a_url
) const
{
    xTEST_EQ(a_url.empty(), false);

    std::ctstring_t url = String::trimSpace(a_url);
    xTEST_EQ(url.empty(), false);

    execute(xPTR_NULL, opOpen, xT("explorer.exe"), xT("/e, ") + url, xT(""), sfShowNormal);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Shell::executeEmail(
    std::ctstring_t &a_toEmail,
    std::ctstring_t &a_subject,
    std::ctstring_t &a_body
) const
{
    xTEST_NA(a_toEmail);
    xTEST_NA(a_subject);
    xTEST_NA(a_body);

    std::ctstring_t toEmail = String::trimSpace(a_toEmail);
    std::ctstring_t subject = String::trimSpace(a_subject);
    std::ctstring_t body    = String::trimSpace(a_body);

    xTEST_EQ(a_toEmail.empty(), false);

   /**
    * mailto:address[headers]
    *
    * mailto:user@example.com?subject=Message Title&body=Message Content
    */

    std::tstring_t cmd;

    cmd.append(xT("mailto:") + toEmail);

    xCHECK_DO(!subject.empty() || !body.empty(), cmd.append(xT("?")                 ));
    xCHECK_DO(!subject.empty(),                  cmd.append(xT("subject=") + subject));
    xCHECK_DO(!body.empty(),                     cmd.append(xT("&body=")   + body   ));

    execute(xPTR_NULL, opOpen, cmd, xT(""), xT(""), sfShowNormal);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Shell::specialDirPath(
    const ESpecialDir &a_dir,
    const HANDLE      &a_token
) const
{
    xTEST_NA(a_dir);
    xTEST_NA(a_token);

    HRESULT       hRv    = S_FALSE;
    LPITEMIDLIST *idList = xPTR_NULL;

    hRv = ::SHGetFolderLocation(xPTR_NULL, a_dir, a_token, 0UL, idList);
    xTEST_EQ(hRv, S_OK);
    xTEST_PTR(idList);

    tchar_t buff[MAX_PATH + sizeof(tchar_t)] = {0};

    BOOL bRv = ::SHGetPathFromIDList(idList, &buff[0]);
    (void_t)::ILFree(idList);   idList = xPTR_NULL;
    xTEST_DIFF(bRv, FALSE);

    return std::tstring_t(buff);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Shell::createShortcut(
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
    xTEST_EQ(a_shortCutFilePath.empty(), false);
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_EQ(a_workingDirectory.empty(), false);
    xTEST_NA(a_args);
    xTEST_NA(a_hotKey);
    xTEST_NA(a_cmdShow);
    xTEST_EQ(a_iconFilePath.empty(), false);
    xTEST_GR(a_iconIndex, - 1);
    xTEST_NA(a_description);

    Com com(COINIT_MULTITHREADED);

    HRESULT     hRv  = 0;
    IShellLink *link = xPTR_NULL;

    hRv = ::CoCreateInstance(CLSID_ShellLink, xPTR_NULL, CLSCTX_INPROC_SERVER, IID_IShellLink,
        (void_t **)&link);
    xTEST_EQ(SUCCEEDED(hRv), true);

    {
        hRv = link->SetPath(a_filePath.c_str());
        xTEST_EQ(SUCCEEDED(hRv), true);

        hRv = link->SetArguments(a_args.c_str());
        xTEST_EQ(SUCCEEDED(hRv), true);

        hRv = link->SetWorkingDirectory(a_workingDirectory.c_str());
        xTEST_EQ(SUCCEEDED(hRv), true);

        hRv = link->SetIconLocation(a_iconFilePath.c_str(), a_iconIndex);
        xTEST_EQ(SUCCEEDED(hRv), true);

        hRv = link->SetHotkey(a_hotKey);
        xTEST_EQ(SUCCEEDED(hRv), true);

        hRv = link->SetShowCmd(a_cmdShow);
        xTEST_EQ(SUCCEEDED(hRv), true);

        hRv = link->SetDescription(a_description.c_str());
        xTEST_EQ(SUCCEEDED(hRv), true);
    }

    IPersistFile *file = xPTR_NULL;

    hRv = link->QueryInterface(IID_IPersistFile, Utils::reinterpretCastT<void_t **>( &file ));
    xTEST_EQ(SUCCEEDED(hRv), true);

#if xUNICODE
    hRv = file->Save(a_shortCutFilePath.c_str(), true);
#else
    wchar_t buff[MAX_PATH + 1] = {0};

    ::MultiByteToWideChar(CP_ACP, 0, a_shortCutFilePath.c_str(), - 1, buff, MAX_PATH);
    hRv = file->Save(buff, true);
#endif

    file->Release();    file = xPTR_NULL;
    link->Release();    link = xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
