/**
 * \file  CxShell.cpp
 * \brief shell
 */


#include <xLib/Common/Win/CxShell.h>

#include <xLib/Common/Win/CxCom.h>

#if defined(xOS_WIN)
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
/*static*/
std::tstring
CxShell::bFindExecutable(
    const std::tstring &csFileName,
    const std::tstring &csFindDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(), std::tstring());
    /*DEBUG*/// csFindDirPath - n/a

    INT   iRes            = SE_ERR_FNF;
    TCHAR szRes[MAX_PATH] = {0};

    iRes = reinterpret_cast<INT>( ::FindExecutable(csFileName.c_str(), csFindDirPath.c_str(), szRes) );
    /*DEBUG*/xASSERT_RET(32 < iRes, std::tstring());

    return std::tstring(szRes);
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxShell::bExecute(
    const HWND          chOwner,
    const EOperation    copOperation,
    const std::tstring &csFilePath,
    const std::tstring &csParams,
    const std::tstring &csDir,
    const EShowFlag     csfShowCmd
)
{
    /*DEBUG*/// chOwner      - n/a
    /*DEBUG*/// ccsOperation - n/a
    /*DEBUG*/// csFilePath   - n/a
    /*DEBUG*/// csParams     - n/a
    /*DEBUG*/// csDir        - n/a
    /*DEBUG*/// csfShowCmd   - n/a

    std::tstring sFilePath  = CxString::sTrimSpace(csFilePath);
    std::tstring sParams    = CxString::sTrimSpace(csParams);
    std::tstring sDir       = CxString::sTrimSpace(csDir);

    std::tstring sOperation;
    switch (copOperation) {
        case opEdit:    { sOperation = xT("edit");    } break;
        case opExplore: { sOperation = xT("explore"); } break;
        case opFind:    { sOperation = xT("find");    } break;
        case opOpen:    { sOperation = xT("open");    } break;
        case opPrint:   { sOperation = xT("print");   } break;
        case opNull:    { sOperation = xT("");        } break;

        default:        { sOperation = xT("");        } break;
    }

    INT iRes = reinterpret_cast<INT>( ::ShellExecute(chOwner, sOperation.c_str(), sFilePath.c_str(), sParams.c_str(), sDir.c_str(), csfShowCmd) );
    /*DEBUG*/xASSERT_RET(32 < iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxShell::bExecuteEx(
    SHELLEXECUTEINFO *peiInfo
)
{
    /*DEBUG*/xASSERT_RET(FALSE != peiInfo, FALSE);

    _ms_bRes = ::ShellExecuteEx(peiInfo);
    /*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxShell::bExecuteHttp(
    const std::tstring &csUrl
)
{
    /*DEBUG*/// csUrl - n/a

    std::tstring sUrl = CxString::sTrimSpace(csUrl);

    xCHECK_RET(true == sUrl.empty(), FALSE);

    _ms_bRes = bExecute(NULL, opOpen, xT("IEXPLORE.EXE"), sUrl, xT(""), sfShowNormal);
    /*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxShell::bExecuteFtp(
    const std::tstring &csUrl
)
{
    /*DEBUG*/// csUrl - n/a

    std::tstring sUrl = CxString::sTrimSpace(csUrl);

    xCHECK_RET(true == sUrl.empty(), FALSE);

    _ms_bRes = bExecute(NULL, opOpen, xT("explorer.exe"), xT("/e, ") + sUrl, xT(""), sfShowNormal);
    /*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxShell::bExecuteEmail(
    const std::tstring &csToEmail,
    const std::tstring &csSubject,
    const std::tstring &csBody
)
{
    /*DEBUG*/// csToEmail - n/a
    /*DEBUG*/// csSubject - n/a
    /*DEBUG*/// csBody    - n/a

    std::tstring sToEmail = CxString::sTrimSpace(csToEmail);
    std::tstring sSubject = CxString::sTrimSpace(csSubject);
    std::tstring sBody    = CxString::sTrimSpace(csBody);

    xCHECK_RET(true == csToEmail.empty(), FALSE);

    //mailto:sAddress[sHeaders]
    //mailto:user@example.com?subject=Message Title&body=Message Content

    std::tstring sCmd;

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
/*static*/
std::tstring
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
    /*DEBUG*/xASSERT_DO(SUCCEEDED(hRes), ::CoTaskMemFree(pidlList); return std::tstring());

    TCHAR szRes[MAX_PATH + sizeof(TCHAR)] = {0};

    _ms_bRes = ::SHGetPathFromIDList(pidlList, &szRes[0]);
    /*DEBUG*/xASSERT_DO(FALSE != _ms_bRes, ::CoTaskMemFree(pidlList); return std::tstring());

    ::CoTaskMemFree(pidlList);
    /*DEBUG*/// n/a

    return std::tstring(szRes);
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxShell::bCreateShortcut(
    const std::tstring &csFilePath,
    const std::tstring &csShortCutPath,
    const std::tstring &csDescription
)
{
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
CxShell::CxShell() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxShell::~CxShell() {

}
//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

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
#endif
