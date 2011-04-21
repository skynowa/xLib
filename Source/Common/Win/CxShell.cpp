/****************************************************************************
* Class name:  CxShell
* Description: shell
* File name:   CxShell.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     26.04.2010 22:05:23
*
*****************************************************************************/


#include <xLib/Common/Win/CxShell.h>

#include <xLib/Common/Win/CxCom.h>

/****************************************************************************
*    Static
*
*****************************************************************************/

/*static*/ BOOL CxShell::_ms_bRes = FALSE;


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: -  bFindExecutable ()
/*static*/
tString CxShell::bFindExecutable(const tString csFileName, const tString csFindDirPath) {
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(), tString());
    /*DEBUG*/// csFindDirPath - n/a

    INT   iRes            = SE_ERR_FNF;
    TCHAR szRes[MAX_PATH] = {0};

    iRes = reinterpret_cast<INT>( ::FindExecutable(csFileName.c_str(), csFindDirPath.c_str(), szRes) );
    /*DEBUG*/xASSERT_RET(32 < iRes, tString());

    return tString(szRes);
}
//---------------------------------------------------------------------------
//TODO: -  bExecute ()
/*static*/
BOOL CxShell::bExecute(HWND hOwner, EOperation opOperation, const tString &csFilePath, const tString &csParams, const tString &csDir, EShowFlag sfShowCmd) {
    /*DEBUG*/// hOwner      - n/a
    /*DEBUG*/// csOperation - n/a
    /*DEBUG*/// csFilePath  - n/a
    /*DEBUG*/// csParams    - n/a
    /*DEBUG*/// csDir       - n/a
    /*DEBUG*/// iShowCmd    - n/a

    tString sFilePath  = CxString::sTrimSpace(csFilePath);
    tString sParams    = CxString::sTrimSpace(csParams);
    tString sDir       = CxString::sTrimSpace(csDir);

    tString sOperation;
    switch (opOperation) {
        case opEdit:    { sOperation = xT("edit");    } break;
        case opExplore: { sOperation = xT("explore"); } break;
        case opFind:    { sOperation = xT("find");    } break;
        case opOpen:    { sOperation = xT("open");    } break;
        case opPrint:   { sOperation = xT("print");   } break;
        case opNull:    { sOperation = xT("");        } break;

        default:        { sOperation = xT("");        } break;
    }

    INT iRes = reinterpret_cast<INT>( ::ShellExecute(hOwner, sOperation.c_str(), sFilePath.c_str(), sParams.c_str(), sDir.c_str(), sfShowCmd) );
    /*DEBUG*/xASSERT_RET(32 < iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: -  bExecuteEx ()
/*static*/
BOOL CxShell::bExecuteEx(SHELLEXECUTEINFO *peiInfo) {
    /*DEBUG*/xASSERT_RET(FALSE != peiInfo, FALSE);

    _ms_bRes = ::ShellExecuteEx(peiInfo);
    /*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bExecuteHttp ()
/*static*/
BOOL CxShell::bExecuteHttp(const tString &csUrl) {
    /*DEBUG*/// csUrl - n/a

    tString sUrl = CxString::sTrimSpace(csUrl);

    xCHECK_RET(true == sUrl.empty(), FALSE);

    _ms_bRes = bExecute(NULL, opOpen, xT("IEXPLORE.EXE"), sUrl, xT(""), sfShowNormal);
    /*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bExecuteFtp ()
/*static*/
BOOL CxShell::bExecuteFtp(const tString &csUrl) {
    /*DEBUG*/// csUrl - n/a

    tString sUrl = CxString::sTrimSpace(csUrl);

    xCHECK_RET(true == sUrl.empty(), FALSE);

    _ms_bRes = bExecute(NULL, opOpen, xT("explorer.exe"), xT("/e, ") + sUrl, xT(""), sfShowNormal);
    /*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bExecuteEmail ()
/*static*/
BOOL CxShell::bExecuteEmail(const tString &csToEmail, const tString &csSubject, const tString &csBody) {
    /*DEBUG*/// csToEmail - n/a
    /*DEBUG*/// csSubject - n/a
    /*DEBUG*/// csBody    - n/a

    tString sToEmail = CxString::sTrimSpace(csToEmail);
    tString sSubject = CxString::sTrimSpace(csSubject);
    tString sBody    = CxString::sTrimSpace(csBody);

    xCHECK_RET(true == csToEmail.empty(), FALSE);

    //mailto:sAddress[sHeaders]
    //mailto:user@example.com?subject=Message Title&body=Message Content

    tString sCmd;

    sCmd.append(xT("mailto:")  + sToEmail);

    xCHECK_DO(false == sSubject.empty() || false == sBody.empty(), sCmd.append(xT("?")                  ));
    xCHECK_DO(false == sSubject.empty(),                           sCmd.append(xT("subject=") + sSubject));
    xCHECK_DO(false == sBody.empty(),                              sCmd.append(xT("&body=")    + sBody  ));

    //iMsgBox(sCmd);

    _ms_bRes = bExecute(NULL, opOpen, sCmd, xT(""), xT(""), sfShowNormal);
    /*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - sGetSpecialFolderLocation ()
/*static*/
tString CxShell::sGetSpecialDirPath(ESpecialDir sfDir, HANDLE hToken) {
    /*DEBUG*/// sfDir  - n/a
    /*DEBUG*/// hToken - n/a

    HRESULT      hRes     = S_FALSE;
    LPITEMIDLIST pidlList = {0};

    ////hRes = ::SHGetFolderLocation(NULL, sfDir, hToken, 0, &pidlList);    //FIXME: SHGetFolderLocation
    hRes = ::SHGetSpecialFolderLocation(NULL, sfDir, &pidlList);
    /*DEBUG*/xASSERT_DO(SUCCEEDED(hRes), ::CoTaskMemFree(pidlList); return tString());

    TCHAR szRes[MAX_PATH + sizeof(TCHAR)] = {0};

    _ms_bRes = ::SHGetPathFromIDList(pidlList, &szRes[0]);
    /*DEBUG*/xASSERT_DO(FALSE != _ms_bRes, ::CoTaskMemFree(pidlList); return tString());

    ::CoTaskMemFree(pidlList);
    /*DEBUG*/// n/a

    return tString(szRes);
}
//---------------------------------------------------------------------------
//DONE: bCreateShortcut
/*static*/
BOOL
CxShell::bCreateShortcut(const tString &csFilePath, const tString &csShortCutPath, const tString &csDescription) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),     FALSE);
    /*DEBUG*/xASSERT_RET(false == csShortCutPath.empty(), FALSE);
    /*DEBUG*/// csDescription - n/a

    CxCom comCom(CxCom::cmMultiThreaded);

    IShellLink *pslSL = NULL;
    HRESULT     hRes  = 0;

    hRes = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&pslSL);
    /*DEBUG*/xASSERT_RET(SUCCEEDED(hRes), FALSE);

    pslSL->SetPath(csFilePath.c_str());
    pslSL->SetDescription(csDescription.c_str());


    IPersistFile *pPF = NULL;

    hRes = pslSL->QueryInterface(IID_IPersistFile, CxMacros::xreinterpret_cast<VOID **>( &pPF ));
    /*DEBUG*/xASSERT_RET(SUCCEEDED(hRes), FALSE);

    #if defined(UNICODE) || defined(_UNICODE)
        hRes = pPF->Save(csShortCutPath.c_str(), TRUE);
        pPF->Release();
    #else
        wchar_t wszBuff[MAX_PATH + 1] = {0};

        ::MultiByteToWideChar(CP_ACP, 0, csShortCutPath.c_str(), - 1, wszBuff, MAX_PATH);
        hRes = pPF->Save(wszBuff, TRUE);
        pPF->Release();
    #endif  /*_UNICODE*/

    pslSL->Release();

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxShell (comment)
CxShell::CxShell() {
    //code
}
//---------------------------------------------------------------------------
//TODO: - ~CxShell (comment)
CxShell::~CxShell() {
    //code
}
//---------------------------------------------------------------------------






/*
How to find the application associated with particular file extension.

May 30th

Posted by Jijo Raj in Codeproject

No comments



Did you ever noticed that, While starting up some media player applications, they says that - �Some of its proprietary file formats are not associated with it and do you want to associate now?�. How these application are checking the associated application of particular filetype?


For a given file extension, you can find the executable associated with it by calling the api � AssocQueryString(). See the sample code snippet below.
#include "Shlwapi.h"
...
DWORD dwSize = MAX_PATH;
TCHAR tchApplicationPath[ MAX_PATH ] = { 0 };
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
*/
