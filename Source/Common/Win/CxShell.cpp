/**
 * \file  CxShell.cpp
 * \brief shell
 */


#include <xLib/Common/Win/CxShell.h>

#include <xLib/Common/Win/CxCom.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxShell::bFindExecutable(
    const std::tstring_t &csFileName,
    const std::tstring_t &csFindDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(), std::tstring_t());
    /*DEBUG*/// csFindDirPath - n/a

    int   iRes            = SE_ERR_FNF;
    tchar_t szRes[MAX_PATH] = {0};

    iRes = reinterpret_cast<int>( ::FindExecutable(csFileName.c_str(), csFindDirPath.c_str(), szRes) );
    /*DEBUG*/xASSERT_RET(32 < iRes, std::tstring_t());

    return std::tstring_t(szRes);
}
//---------------------------------------------------------------------------
/*static*/
bool
CxShell::bExecute(
    const HWND          chOwner,
    const EOperation    copOperation,
    const std::tstring_t &csFilePath,
    const std::tstring_t &csParams,
    const std::tstring_t &csDir,
    const EShowFlag     csfShowCmd
)
{
    /*DEBUG*/// chOwner      - n/a
    /*DEBUG*/// ccsOperation - n/a
    /*DEBUG*/// csFilePath   - n/a
    /*DEBUG*/// csParams     - n/a
    /*DEBUG*/// csDir        - n/a
    /*DEBUG*/// csfShowCmd   - n/a

    std::tstring_t sFilePath  = CxString::sTrimSpace(csFilePath);
    std::tstring_t sParams    = CxString::sTrimSpace(csParams);
    std::tstring_t sDir       = CxString::sTrimSpace(csDir);

    std::tstring_t sOperation;
    switch (copOperation) {
        case opEdit:    { sOperation = xT("edit");    } break;
        case opExplore: { sOperation = xT("explore"); } break;
        case opFind:    { sOperation = xT("find");    } break;
        case opOpen:    { sOperation = xT("open");    } break;
        case opPrint:   { sOperation = xT("print");   } break;
        case opNull:    { sOperation = xT("");        } break;

        default:        { sOperation = xT("");        } break;
    }

    int iRes = reinterpret_cast<int>( ::ShellExecute(chOwner, sOperation.c_str(), sFilePath.c_str(), sParams.c_str(), sDir.c_str(), csfShowCmd) );
    /*DEBUG*/xASSERT_RET(32 < iRes, false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxShell::bExecuteEx(
    SHELLEXECUTEINFO *peiInfo
)
{
    /*DEBUG*/xASSERT_RET(false != peiInfo, false);

    BOOL bRes = ::ShellExecuteEx(peiInfo);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxShell::bExecuteHttp(
    const std::tstring_t &csUrl
)
{
    /*DEBUG*/// csUrl - n/a

    std::tstring_t sUrl = CxString::sTrimSpace(csUrl);

    xCHECK_RET(true == sUrl.empty(), false);

    bool bRes = bExecute(NULL, opOpen, xT("IEXPLORE.EXE"), sUrl, xT(""), sfShowNormal);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxShell::bExecuteFtp(
    const std::tstring_t &csUrl
)
{
    /*DEBUG*/// csUrl - n/a

    std::tstring_t sUrl = CxString::sTrimSpace(csUrl);

    xCHECK_RET(true == sUrl.empty(), false);

    bool bRes = bExecute(NULL, opOpen, xT("explorer.exe"), xT("/e, ") + sUrl, xT(""), sfShowNormal);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxShell::bExecuteEmail(
    const std::tstring_t &csToEmail,
    const std::tstring_t &csSubject,
    const std::tstring_t &csBody
)
{
    /*DEBUG*/// csToEmail - n/a
    /*DEBUG*/// csSubject - n/a
    /*DEBUG*/// csBody    - n/a

    std::tstring_t sToEmail = CxString::sTrimSpace(csToEmail);
    std::tstring_t sSubject = CxString::sTrimSpace(csSubject);
    std::tstring_t sBody    = CxString::sTrimSpace(csBody);

    xCHECK_RET(true == csToEmail.empty(), false);

    //mailto:sAddress[sHeaders]
    //mailto:user@example.com?subject=Message Title&body=Message Content

    std::tstring_t sCmd;

    sCmd.append(xT("mailto:")  + sToEmail);

    xCHECK_DO(false == sSubject.empty() || false == sBody.empty(), sCmd.append(xT("?")                  ));
    xCHECK_DO(false == sSubject.empty(),                           sCmd.append(xT("subject=") + sSubject));
    xCHECK_DO(false == sBody.empty(),                              sCmd.append(xT("&body=")    + sBody  ));

    //iMsgBox(sCmd);

    bool bRes = bExecute(NULL, opOpen, sCmd, xT(""), xT(""), sfShowNormal);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxShell::sGetSpecialDirPath(
    const ESpecialDir csfDir,
    const HANDLE      chToken
)
{
    /*DEBUG*/// csfDir  - n/a
    /*DEBUG*/// chToken - n/a

    HRESULT      hRes     = S_FALSE;
    LPITEMIDLIST pidlList = {0};

    ////hRes = ::SHGetFolderLocation(NULL, sfDir, chToken, 0, &pidlList);    //FIXME: SHGetFolderLocation
    hRes = ::SHGetSpecialFolderLocation(NULL, csfDir, &pidlList);
    /*DEBUG*/xASSERT_DO(SUCCEEDED(hRes), ::CoTaskMemFree(pidlList); return std::tstring_t());

    tchar_t szRes[MAX_PATH + sizeof(tchar_t)] = {0};

    BOOL bRes = ::SHGetPathFromIDList(pidlList, &szRes[0]);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, ::CoTaskMemFree(pidlList); return std::tstring_t());

    ::CoTaskMemFree(pidlList);
    /*DEBUG*/// n/a

    return std::tstring_t(szRes);
}
//---------------------------------------------------------------------------
#define xHOTKEY(modifier, key) ((((modifier) & 0xff) << 8) | ((key)&0xff))

/*static*/
bool
CxShell::bCreateShortcut(
    const std::tstring_t &csShortCutFilePath, ///< путь и имя ярлыка, например, "C:\\Блокнот.lnk"
                                            ///< Если не указан путь, ярлык будет создан в папке, указанной в следующем параметре.
                                            ///< Прим.: Windows сама НЕ добавляет к имени расширение .lnk
    const std::tstring_t &csFilePath,         ///< путь и имя программы/файла, например, "C:\\Windows\\NotePad.Exe" или "C:\\Мои документы\\Файл.doc"
    const std::tstring_t &csWorkingDirectory, ///< рабочий каталог, например, "C:\\Windows"
    const std::tstring_t &csArguments,        ///< аргументы командной строки, например, "C:\\Doc\\Text.Txt"
    const WORD          cwHotKey,           ///< горячая клавиша, например, для Ctrl+Alt+A HOTKEY(HOTKEYF_ALT|HOTKEYF_CONTROL,'A')
    const int           ciCmdShow,          ///< начальный вид, например, SW_SHOWNORMAL (см. параметр nCmdShow функции ShowWindow)
    const std::tstring_t &csIconFilePath,     ///< путь и имя файла, содержащего иконку, например, "C:\\Windows\\NotePad.Exe"
    const int           ciIconIndex,        ///< индекс иконки в файле, нумеруется с 0
    const std::tstring_t &csDescription       ///< description
)
{
    /*DEBUG*/

    CxCom cmCom(CxCom::cmMultiThreaded);

    IShellLink *pslSL = NULL;
    HRESULT     hRes  = 0;

    hRes = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&pslSL);
    /*DEBUG*/xASSERT_RET(SUCCEEDED(hRes), false);

    {
        hRes = pslSL->SetPath(csFilePath.c_str());
        /*DEBUG*/xASSERT_RET(SUCCEEDED(hRes), false);

        hRes = pslSL->SetArguments(csArguments.c_str());
        /*DEBUG*/xASSERT_RET(SUCCEEDED(hRes), false);

        hRes = pslSL->SetWorkingDirectory(csWorkingDirectory.c_str());
        /*DEBUG*/xASSERT_RET(SUCCEEDED(hRes), false);

        hRes = pslSL->SetIconLocation(csIconFilePath.c_str(), ciIconIndex);
        /*DEBUG*/xASSERT_RET(SUCCEEDED(hRes), false);

        hRes = pslSL->SetHotkey(cwHotKey);
        /*DEBUG*/xASSERT_RET(SUCCEEDED(hRes), false);

        hRes = pslSL->SetShowCmd(ciCmdShow);
        /*DEBUG*/xASSERT_RET(SUCCEEDED(hRes), false);

        hRes = pslSL->SetDescription(csDescription.c_str());
        /*DEBUG*/xASSERT_RET(SUCCEEDED(hRes), false);
    }


    IPersistFile *ppfPF = NULL;

    hRes = pslSL->QueryInterface(IID_IPersistFile, CxMacros::xreinterpret_cast<void **>( &ppfPF ));
    /*DEBUG*/xASSERT_RET(SUCCEEDED(hRes), false);

#if xUNICODE
    hRes = ppfPF->Save(csShortCutFilePath.c_str(), true);
#else
    wchar_t wszBuff[MAX_PATH + 1] = {0};

    ::MultiByteToWideChar(CP_ACP, 0, csShortCutFilePath.c_str(), - 1, wszBuff, MAX_PATH);
    hRes = ppfPF->Save(wszBuff, true);
#endif

    ppfPF->Release();
    pslSL->Release();

    return true;
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
/*virtual*/
CxShell::~CxShell() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif


#if xTODO
    How to find the application associated with particular file extension.

    May 30th

    Posted by Jijo Raj in Codeproject

    No comments



    Did you ever noticed that, While starting up some media player applications, they says that - �Some of its proprietary file formats are not associated with it and do you want to associate now?�. How these application are checking the associated application of particular filetype?


    For a given file extension, you can find the executable associated with it by calling the api � AssocQueryString(). See the sample code snippet below.
    #include "Shlwapi.h"
    ...
    DWORD dwSize = MAX_PATH;
    tchar_t tchApplicationPath[ MAX_PATH ] = { 0 };
    HRESULT hr = AssocQueryString( 0,
    ASSOCSTR_EXECUTABLE,
    xT( ".mp3" ),
    xT( "open" ),
    tchApplicationPath,
    &dwSize );

    if( FAILED( hr ))
    {
    // Failed to get the associated application.
    }
#endif
