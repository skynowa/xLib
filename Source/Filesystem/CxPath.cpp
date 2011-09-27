/**
 * \file  CxPath.cpp
 * \brief file system path
 */


#include <xLib/Filesystem/CxPath.h>

#include <xLib/Common/CxChar.h>
#include <xLib/Common/CxCommandLine.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxProcess.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//NOTE: http://www.cplusplus.com/forum/general/11104/
//      http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
//      http://libsylph.sourceforge.net/wiki/Full_path_to_binary
//      http://h21007.www2.hp.com/portal/site/dspp/menuitem.863c3e4cbcdc3f3515b49c108973a801?ciid=88086d6e1de021106d6e1de02110275d6e10RCRD

/*static*/
std::tstring
CxPath::sGetExe() {
    std::tstring sRes;

    #if defined(xOS_WIN)
        sRes.resize(xPATH_MAX);

        ULONG ulStored = ::GetModuleFileName(NULL, &sRes.at(0), sRes.size());
        /*DEBUG*/xASSERT_RET(0 != ulStored, std::tstring());

        sRes.resize(ulStored);
    #elif defined(xOS_LINUX)
        #if xDEPRECIATE
            #if defined(xOS_FREEBSD)
                #if defined(KERN_PROC_PATHNAME)
                    sRes.resize(xPATH_MAX);

                    INT aiMib[] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, - 1};

                    size_t uiResSize = sRes.size() * sizeof(std::tstring::value_type);

                    INT iRes = sysctl(aiMib, static_cast<u_int>( xARRAY_SIZE(aiMib) ), &sRes.at(0), &uiResSize, NULL, 0);
                    /*DEBUG*/xASSERT_RET(- 1 != iRes, std::tstring());

                    sRes.resize(uiResSize);
                #else
                    BOOL bRes                = FALSE;
                    const std::tstring csProcFile = xT("/proc/curproc/file");

                    bRes = CxFile::bIsExists(csProcFile);
                    if (TRUE == bRes) {
                        sRes.resize(xPATH_MAX);

                        INT iReaded = - 1;

                        for ( ; ; ) {
                            iReaded = readlink(csProcFile.c_str(), &sRes.at(0), sRes.size() * sizeof(std::tstring::value_type));
                            /*DEBUG*/xASSERT_RET(- 1 != iReaded, std::tstring());

                            xCHECK_DO(sRes.size() * sizeof(std::tstring::value_type) > static_cast<size_t>( iReaded ), break);

                            sRes.resize(sRes.size() * 2);
                        }

                        sRes.resize(iReaded);

                    } else {
                        sRes = std::tstring();
                    }
                #endif
            #else
                BOOL          bRes       = FALSE;
                const std::tstring csProcFile = CxString::sFormat(xT("/proc/%ld/exe"), CxProcess::ulGetCurrId());

                bRes = CxFile::bIsExists(csProcFile);
                if (TRUE == bRes) {
                    sRes.resize(xPATH_MAX);

                    INT iReaded = - 1;

                    for ( ; ; ) {
                        iReaded = readlink(csProcFile.c_str(), &sRes.at(0), sRes.size() * sizeof(std::tstring::value_type));
                        /*DEBUG*/xASSERT_RET(- 1 != iReaded, std::tstring());

                        xCHECK_DO(sRes.size() * sizeof(std::tstring::value_type) > static_cast<size_t>( iReaded ), break);

                        sRes.resize(sRes.size() * 2);
                    }

                    sRes.resize(iReaded);
                }
            #endif
        #else   //xDEPRECIATE
            std::vector<std::tstring> vsArgs;

            BOOL bRes = CxCommandLine::bGetArgs(&vsArgs);
            /*DEBUG*/xASSERT_RET(FALSE != bRes,                      std::tstring());
            /*DEBUG*/xASSERT_RET(false == vsArgs.empty(),            std::tstring());
            /*DEBUG*/xASSERT_RET(FALSE == bIsAbsolute(vsArgs.at(0)), std::tstring());

            sRes.assign( sGetAbsolute(vsArgs.at(0)) );
        #endif
    #endif

    /*DEBUG*/xASSERT_RET(false == sRes.empty(),            std::tstring());
    /*DEBUG*/xASSERT_RET(FALSE != CxFile::bIsExists(sRes), std::tstring());

    return sRes;
}
//---------------------------------------------------------------------------
//TODO: sGetDll
/*static*/
std::tstring
CxPath::sGetDll() {
    /*DEBUG*/

    std::tstring sRes;

#if defined(xOS_WIN)
    #if xTODO
        MEMORY_BASIC_INFORMATION mbi;
        VirtualQuery(&symbol,&mbi,sizeof(mbi));
        HMODULE mod = mbi.AllocationBase;

        LPTSTR buf = new TCHAR[255];
        GetModuleFileName(mod,buf,255);
        Array<uchar> arr(strlen(buf));
        for(idx_t i = 0; i < strlen(buf);i++) {
            arr[i] = buf[i];
        }
        String fullpath = arr;
    #endif
#elif defined(xOS_LINUX)
    #if xTODO
        Dl_info info;
        dladdr(&symbol,&info);
        String fullpath = info.dli_filename;
    #endif
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sGetExeDir() {
    return sGetDir(sGetExe());
}
//---------------------------------------------------------------------------
#if defined(xOS_WIN)

/*static*/
std::tstring
CxPath::sGetDrive(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());

    size_t uiDriveDelimPos = csFilePath.find(CxConst::xDRIVE_SEP);
    /*DEBUG*/xASSERT_RET(std::tstring::npos != uiDriveDelimPos, std::tstring());
    /*DEBUG*/xASSERT_RET(1                  == uiDriveDelimPos, std::tstring());

    return csFilePath.substr(0, uiDriveDelimPos + CxConst::xDRIVE_SEP.size());
}

#endif
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sGetDir(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    xCHECK_RET(std::tstring::npos == uiSlashPos, std::tstring());

    return csFilePath.substr(0, uiSlashPos);
}
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sGetDirName(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());

    size_t uiSlashPos2 = csFilePath.rfind(CxConst::xSLASH);
    xCHECK_RET(std::tstring::npos == uiSlashPos2, std::tstring());

    size_t uiSlashPos1 = csFilePath.rfind(CxConst::xSLASH, uiSlashPos2 - 1);
    if (std::tstring::npos == uiSlashPos1) {
        return csFilePath.substr(0, uiSlashPos2);
    } else {
        return csFilePath.substr(uiSlashPos1 + 1, uiSlashPos2 - uiSlashPos1 - 1);
    }
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sGetFullName(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    xCHECK_RET(std::tstring::npos == uiSlashPos, csFilePath);

    return csFilePath.substr(uiSlashPos + CxConst::xSLASH.size(), csFilePath.size());
}
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sGetName(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    size_t uiDotPos   = csFilePath.rfind(CxConst::xDOT,   csFilePath.size());

    return CxString::sCut(csFilePath, uiSlashPos + CxConst::xSLASH.size(), uiDotPos);
}
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sGetExt(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());

    size_t uiDotPos   = csFilePath.rfind(CxConst::xDOT,   csFilePath.size());
    xCHECK_RET(std::tstring::npos == uiDotPos, std::tstring());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    //if dot after slash - extension not exists
    xCHECK_RET(uiDotPos < uiSlashPos && std::tstring::npos != uiSlashPos, std::tstring());

    return csFilePath.substr(uiDotPos + CxConst::xDOT.size());
}
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sGetStandartExt(
    const EStandartExt cseFileExt
)
{
    std::tstring sRes;

	switch (cseFileExt) {
    #if defined(xOS_WIN)
        case seExe:	{ sRes = xT("exe"); }   break;
	    case seDll:	{ sRes = xT("dll"); }   break;
	    case seLib:	{ sRes = xT("lib"); }   break;
    #elif defined(xOS_LINUX)
        case seExe:	{ sRes = xT("");    }   break;
	    case seDll:	{ sRes = xT("so");  }   break;
	    case seLib:	{ sRes = xT("a");   }   break;
    #endif
    	default:    { sRes = xT("");    }   break;
    }

    return sRes;
}
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
/*static*/
std::tstring
CxPath::sSetDrive(
    const std::tstring &csFilePath,
    const std::tstring &csDrivePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());
    /*DEBUG*/// csDrivePath

    std::tstring sRes;
    sRes.assign(csFilePath);

    std::tstring sDrive = sGetDrive(sRes);
    /*DEBUG*/xASSERT_RET(false == sDrive.empty(), std::tstring());

    size_t uiPos = sRes.find(sDrive);
    /*DEBUG*/xASSERT_RET(std::tstring::npos != uiPos, std::tstring());

    return sRes.replace(uiPos, sDrive.size(), csDrivePath);
}
#endif
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sSetDir(
    const std::tstring &csFilePath,
    const std::tstring &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());
    /*DEBUG*/// csDirPath

    std::tstring sRes;
    sRes.assign(csFilePath);

    std::tstring sDir = sGetDir(sRes);
    /*DEBUG*/xASSERT_RET(false == sDir.empty(), std::tstring());

    size_t uiPos = sRes.find(sDir);
    /*DEBUG*/xASSERT_RET(std::tstring::npos != uiPos, std::tstring());

    return sRes.replace(uiPos, sDir.size(), sSlashRemove(csDirPath));
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sSetFullName(
    const std::tstring &csFilePath,
    const std::tstring &csFullName
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());
    /*DEBUG*/// csFullName

    std::tstring sRes;
    sRes.assign(csFilePath);

    std::tstring sFullName = sGetFullName(sRes);
    /*DEBUG*/xASSERT_RET(false == sFullName.empty(), std::tstring());

    size_t uiPos = sRes.rfind(sFullName);
    /*DEBUG*/xASSERT_RET(std::tstring::npos != uiPos, std::tstring());

    return sRes.replace(uiPos, sFullName.size(), csFullName);
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sSetName(
    const std::tstring &csFilePath,
    const std::tstring &csName
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());
    /*DEBUG*/// csName

    std::tstring sRes;
    sRes.assign(csFilePath);

    std::tstring sName = sGetName(sRes);
    /*DEBUG*/xASSERT_RET(false == sName.empty(), std::tstring());

    size_t uiPos = sRes.rfind(sName);
    /*DEBUG*/xASSERT_RET(std::tstring::npos != uiPos, std::tstring());

    return sRes.replace(uiPos, sName.size(), csName);
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sSetExt(
    const std::tstring &csFilePath,
    const std::tstring &csExt
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());
    /*DEBUG*/// csExt - n/a

    return sRemoveExt(csFilePath) + CxConst::xDOT + csExt;
}
//---------------------------------------------------------------------------


//--------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sRemoveExt(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());

    size_t uiDotPos = csFilePath.rfind(CxConst::xDOT);

    return csFilePath.substr(0, uiDotPos);
}
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sRemoveExtIf(
    const std::tstring &csFilePath,
    const std::tstring &csExt
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());

    size_t uiExtPos = csFilePath.rfind(CxConst::xDOT + csExt);
    xCHECK_RET(std::tstring::npos == uiExtPos, csFilePath);

    size_t uiDotPos = csFilePath.rfind(CxConst::xDOT);
    /*DEBUG*/xASSERT_RET(std::tstring::npos != uiDotPos, std::tstring());

    return csFilePath.substr(0, uiDotPos);
}
//---------------------------------------------------------------------------
//TODO: bIsValid
/*static*/
BOOL
CxPath::bIsValid(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/// csFileName - n/a

    BOOL bRes = FALSE;

    //is empty
    bRes = static_cast<BOOL>( csFilePath.empty() );
    xCHECK_RET(TRUE == bRes, FALSE);

    //check for size
    bRes = static_cast<BOOL>( xPATH_MAX < csFilePath.size() );
    xCHECK_RET(TRUE == bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bIsNameValid
/*static*/
BOOL
CxPath::bIsNameValid(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/// csFileName - n/a

    BOOL bRes = FALSE;

    const std::tstring csFileName = CxPath::sGetFullName(csFilePath);

    //is empty
    bRes = static_cast<BOOL>( csFileName.empty() );
    xCHECK_RET(TRUE == bRes, FALSE);

    //check for name size
    bRes = static_cast<BOOL>( xNAME_MAX < csFileName.size() );
    xCHECK_RET(TRUE == bRes, FALSE);

    //cm. sSetValidName

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxPath::bIsAbsolute(
    const std::tstring &csFilePath
)
{
    xCHECK_RET(true                  == csFilePath.empty(), FALSE);
    xCHECK_RET(CxConst::xSLASH.at(0) == csFilePath.at(0),   TRUE);

#if defined(xOS_WIN)
    xCHECK_RET(1 == csFilePath.size(),                                                          FALSE);
    xCHECK_RET(CxChar::bIsAlpha(csFilePath.at(0)) && CxConst::xCOLON.at(0) == csFilePath.at(1), TRUE);
#else
    // n/a
#endif

    return FALSE;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sSetValidName(
    const std::tstring &csFileName
)
{
    /*DEBUG*/// n/a

    std::tstring sRes;
    sRes.assign(csFileName);

    //-------------------------------------
    //is empty
    xCHECK_RET(true == sRes.empty(), std::tstring());

    //-------------------------------------
    //check for name size
    xCHECK_RET(xNAME_MAX <= sRes.size(), std::tstring());

#if defined(xOS_WIN)
    //-------------------------------------
    //if only dots
    size_t uiDotPos = sRes.find_first_not_of(CxConst::xDOT);
    xCHECK_RET(std::tstring::npos == uiDotPos, std::tstring());

    //-------------------------------------
    //if the first character is a dot, the filename is okay or space
    xCHECK_RET(CxConst::xDOT.at(0) == sRes.at(0), std::tstring());

    //-------------------------------------
    //A device name was used. You can pass this value to GetIsValidFileNameErrStr to obtain a pointer to the name of this device.


    //-------------------------------------
    //All characters greater than ASCII 31 to be used except for the following:    "/*:<>?\|
    const std::tstring csFatalChars = xT("\\/:*<>|?\"\t\n\r");

    size_t uiFound = sRes.find_first_of(csFatalChars);
    while (std::tstring::npos != uiFound) {
        sRes.erase(uiFound, 1);
        uiFound = sRes.find_first_of(csFatalChars, uiFound);
    }

    //-------------------------------------
    //The following device names cannot be used for a file name nor may they
    //be used for the first segment of a file name (that part which precedes the  first dot):
    //CLOCK$, AUX, CON, NUL, PRN, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8,
    //COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, LPT9
    //Device names are case insensitve. aux, AUX, Aux, etc. are identical.

    const std::tstring csReservedNames[] = {
        xT("CON"),  xT("PRN"),  xT("AUX"),  xT("CLOCK$"), xT("NUL"),
        xT("COM0"), xT("COM1"), xT("COM2"), xT("COM3"),   xT("COM4"),
        xT("COM5"), xT("COM6"), xT("COM7"), xT("COM8"),   xT("COM9"),
        xT("LPT0"), xT("LPT1"), xT("LPT2"), xT("LPT3"),   xT("LPT4"),
        xT("LPT5"), xT("LPT6"), xT("LPT7"), xT("LPT8"),   xT("LPT9")
    };

    std::tstring sFileName = sRemoveExt(sRes);

    for (size_t i = 0; i < xARRAY_SIZE(csReservedNames); ++ i) {
        xCHECK_RET(TRUE == CxString::bCompareNoCase(sFileName, csReservedNames[i]), std::tstring());
    }
#elif defined(xOS_LINUX)
    //TODO: sSetValidName
#endif

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sToWin(
    const std::tstring &csFilePath,
    const BOOL          cbIsSlashAtEnd
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    std::tstring sRes;

    if (TRUE == cbIsSlashAtEnd) {
        sRes = sSlashAppend(csFilePath);
    } else {
        sRes = sSlashRemove(csFilePath);
    }

    sRes = CxString::sReplaceAll(sRes, CxConst::xNIX_SLASH, CxConst::xWIN_SLASH);

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sToNix(
    const std::tstring &csFilePath,
    const BOOL          cbIsSlashAtEnd
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    std::tstring sRes;

    if (TRUE == cbIsSlashAtEnd) {
        sRes = sSlashAppend(csFilePath);
    } else {
        sRes = sSlashRemove(csFilePath);
    }

    sRes = CxString::sReplaceAll(sRes, CxConst::xWIN_SLASH, CxConst::xNIX_SLASH);

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
//TODO: make test
std::tstring
CxPath::sToCurrentOs(
    const std::tstring &csFilePath,
    const BOOL          cbIsSlashAtEnd
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    std::tstring sRes;

    if (TRUE == cbIsSlashAtEnd) {
        sRes = sSlashAppend(csFilePath);
    } else {
        sRes = sSlashRemove(csFilePath);
    }

    sRes = CxString::sReplaceAll(sRes, CxConst::xWIN_SLASH, CxConst::xSLASH);

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sGetAbsolute(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/

    std::tstring sRes;

#if defined(xOS_WIN)
    ULONG   ulRes = 0;
    std::tstring sBuff;

    ulRes = ::GetFullPathName(&csFilePath.at(0), 0, NULL, NULL);
    /*DEBUG*/xASSERT_RET(0 != ulRes, std::tstring());

    sBuff.resize(ulRes);

    ulRes = ::GetFullPathName(&csFilePath.at(0), sBuff.size(), &sBuff.at(0), NULL);
    /*DEBUG*/xASSERT_RET(0 != ulRes, std::tstring());

    sBuff.resize(ulRes);

    sRes.assign(sBuff);
#elif defined(xOS_LINUX)
    std::tstring sBuff;

    sBuff.resize(xPATH_MAX);

    TCHAR *pszRes = realpath(&csFilePath.at(0), &sBuff.at(0));
    /*DEBUG*/xASSERT_RET(NULL != pszRes, std::tstring());

    sRes.assign(pszRes);
#endif

    /*DEBUG*/xASSERT_RET(FALSE != bIsAbsolute(sRes), std::tstring());

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sMinimizeName(
    const std::tstring &csFileName,
    const size_t        cuiMaxSize
)
{
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(), std::tstring());
    /*DEBUG*/xASSERT_RET(0 < cuiMaxSize,              std::tstring());

    std::tstring sRes;

    std::tstring sTildaDotExt;

    //if file extension exists or not
    if (true == sGetExt(csFileName).empty()) {
        sTildaDotExt = xT("~");
    } else {
        sTildaDotExt = xT("~") + CxConst::xDOT + sGetExt(csFileName);
    }

    if (csFileName.size() > cuiMaxSize) {
        if (cuiMaxSize < sTildaDotExt.size()) {
            sRes = csFileName.substr(0, cuiMaxSize);
        } else {
            sRes = csFileName.substr(0, cuiMaxSize - sTildaDotExt.size()) + sTildaDotExt;
        }
    } else {
        sRes = csFileName;
    }

    return sRes;
}
//---------------------------------------------------------------------------
//TODO: sMinimize
/*static*/
std::tstring
CxPath::sMinimize(
    const std::tstring &csFilePath,
    const size_t        cuiMaxSize
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring());
    /*DEBUG*/xASSERT_RET(0     <  cuiMaxSize,         std::tstring());

    std::tstring sRes;

#if defined(xOS_WIN)
    sRes.assign(csFilePath);

    std::tstring sDrive = sGetDrive(sRes);                                            //D:
    std::tstring sDir   = sGetDir(sRes).erase(0, sDrive.size()) + CxConst::xSLASH;    /* \xLib\Test\CxString\Project\Debug\ */
    std::tstring sName  = sGetFullName(sRes);                                        //Test.exe

    while (((false == sDir.empty()) || (false == sDrive.empty())) && (sRes.size() > cuiMaxSize)) {
        if ((CxConst::xSLASH + xT("...") + CxConst::xSLASH) == sDir ) {
            sDrive.clear();
            sDir = xT("...") + CxConst::xSLASH;
        }
        else if (true == sDir.empty()) {
            sDrive.clear();
        }
        else {
            BOOL        bRoot = FALSE;
            size_t uiPos = std::tstring::npos;

            if (CxConst::xSLASH == sDir) {
                sDir.clear();
            }
            else {
                if (sDir.at(0) == CxConst::xSLASH.at(0)) {
                    bRoot = TRUE;
                    //������� � 1(0) ������� 1 ������
                    //Delete(S, 1, 1);
                    sDir.erase(0, 1);
                } else {
                    bRoot = FALSE;
                }

                if (CxConst::xDOT.at(0) == sDir.at(0)) {
                    //Delete(S, 1, 4);
                    sDir.erase(0, 4);
                }

                //uiPos = AnsiPos("\\", S);
                uiPos = sDir.find_first_of(CxConst::xSLASH);        //-- uiPos = sDir.find_first_of(xWIN_SLASH) + 1;
                if (std::tstring::npos == uiPos) {
                    sDir.clear();
                } else {
                    //Delete(S, 1, uiPos); - c ������� 1(0) uiPos ��������
                    sDir.erase(0, uiPos + CxConst::xSLASH.size());                //-- sDir.erase(0, uiPos);
                    sDir = xT("...") + CxConst::xSLASH + sDir;
                }

                if (TRUE == bRoot) {
                    sDir = CxConst::xSLASH + sDir;
                }
            }
            //-------------------------------

        }

        sRes = sDrive + sDir + sName;
    }
#elif defined(xOS_LINUX)
    sRes.assign(csFilePath);
#endif

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sSlashAppend(
    const std::tstring &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), std::tstring());

    return CxString::sTrimRightChars(csDirPath, CxConst::xSLASH).append(CxConst::xSLASH);
}
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxPath::sSlashRemove(
    const std::tstring &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), std::tstring());

    return CxString::sTrimRightChars(csDirPath, CxConst::xSLASH);
}
//--------------------------------------------------------------------------
/*static*/
size_t
CxPath::uiGetMaxSize() {
    /*DEBUG*/

    size_t uiRes = 0;

    #if defined(xOS_WIN)
        #if defined(MAX_PATH)
            uiRes = MAX_PATH;
        #else
            const cuiDefaultSize = 260;

            uiRes = cuiDefaultSize;
        #endif
    #elif defined(xOS_LINUX)
        #if defined(PATH_MAX)
            uiRes = PATH_MAX;
        #else
            const ULONG culSavedError = 0;
            LONG        liRes         = - 1;
            ULONG       ulLastError   = 0;

            CxLastError::bSet(culSavedError);

            liRes       = ::pathconf("/", _PC_PATH_MAX);
            ulLastError = CxLastError::ulGet();
            /*DEBUG*/xASSERT_RET(- 1 == liRes && 0 != culSavedError, 0);

            if (- 1 == liRes && culSavedError == ulLastError) {
                //system does not have a limit for the requested resource
                const cuiDefaultSize = 1024;

                uiRes = cuiDefaultSize;
            } else {
                //relative root
                uiRes = static_cast<std::size_t>(liRes + 1);
            }
        #endif
    #endif

    return uiRes;
}
//---------------------------------------------------------------------------
/*static*/
size_t
CxPath::uiGetNameMaxSize() {
    /*DEBUG*/

    size_t uiRes = 0;

    #if defined(xOS_WIN)
        #if defined(FILENAME_MAX)
            uiRes = FILENAME_MAX;
        #else
            const cuiDefaultSize = 260;

            uiRes = cuiDefaultSize;
        #endif
    #elif defined(xOS_LINUX)
        #if defined(NAME_MAX)
            uiRes = NAME_MAX;
        #else
            const ULONG culSavedError = 0;
            LONG        liRes         = - 1;
            ULONG       ulLastError   = 0;

            CxLastError::bSet(culSavedError);

            liRes       = ::pathconf("/", _PC_NAME_MAX);
            ulLastError = CxLastError::ulGet();
            /*DEBUG*/xASSERT_RET(- 1 == liRes && 0 != culSavedError, 0);

            if (- 1 == liRes && culSavedError == ulLastError) {
                //system does not have a limit for the requested resource
                const cuiDefaultSize = 1024;

                uiRes = cuiDefaultSize;
            } else {
                uiRes = static_cast<std::size_t>(liRes);
            }
        #endif
    #endif

    return uiRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxPath::CxPath() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxPath::~CxPath() {

}
//---------------------------------------------------------------------------
