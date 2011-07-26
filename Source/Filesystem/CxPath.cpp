/****************************************************************************
* Class name:  CxPath
* Description: file system path
* File name:   CxPath.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.06.2009 9:27:28
*
*****************************************************************************/


#include <xLib/Filesystem/CxPath.h>

#include <xLib/Common/CxChar.h>
#include <xLib/Filesystem/CxStdioFile.h>
#include <xLib/Filesystem/CxEnvironment.h>
#include <xLib/Sync/CxProcess.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: sGetExe (full path to exe)
//NOTE: http://www.cplusplus.com/forum/general/11104/
//      http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
//      http://libsylph.sourceforge.net/wiki/Full_path_to_binary
//      http://h21007.www2.hp.com/portal/site/dspp/menuitem.863c3e4cbcdc3f3515b49c108973a801?ciid=88086d6e1de021106d6e1de02110275d6e10RCRD

/*static*/
tString
CxPath::sGetExe() {
    tString sRes;

    #if defined(xOS_WIN)
        sRes.resize(xPATH_MAX);

        ULONG ulStored = ::GetModuleFileName(NULL, &sRes.at(0), sRes.size());
        /*DEBUG*/xASSERT_RET(0 != ulStored, tString());

        sRes.resize(ulStored);
    #elif defined(xOS_LINUX)
        #if xDEPRECIATE
            #if defined(xOS_FREEBSD)
                #if defined(KERN_PROC_PATHNAME)
                    sRes.resize(xPATH_MAX);

                    INT aiMib[] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, - 1};

                    size_t uiResSize = sRes.size() * sizeof(tString::value_type);

                    INT iRes = sysctl(aiMib, static_cast<u_int>( xARRAY_SIZE(aiMib) ), &sRes.at(0), &uiResSize, NULL, 0);
                    /*DEBUG*/xASSERT_RET(- 1 != iRes, tString());

                    sRes.resize(uiResSize);
                #else
                    BOOL bRes                = FALSE;
                    const tString csProcFile = xT("/proc/curproc/file");

                    bRes = CxStdioFile::bIsExists(csProcFile);
                    if (TRUE == bRes) {
                        sRes.resize(xPATH_MAX);

                        INT iReaded = - 1;

                        for ( ; ; ) {
                            iReaded = readlink(csProcFile.c_str(), &sRes.at(0), sRes.size() * sizeof(tString::value_type));
                            /*DEBUG*/xASSERT_RET(- 1 != iReaded, tString());

                            xCHECK_DO(sRes.size() * sizeof(tString::value_type) > static_cast<size_t>( iReaded ), break);

                            sRes.resize(sRes.size() * 2);
                        }

                        sRes.resize(iReaded);

                    } else {
                        sRes = tString();
                    }
                #endif

                #if 1

                #endif
            #else
                BOOL          bRes       = FALSE;
                const tString csProcFile = CxString::sFormat(xT("/proc/%ld/exe"), CxProcess::ulGetCurrId());

                bRes = CxStdioFile::bIsExists(csProcFile);
                if (TRUE == bRes) {
                    sRes.resize(xPATH_MAX);

                    INT iReaded = - 1;

                    for ( ; ; ) {
                        iReaded = readlink(csProcFile.c_str(), &sRes.at(0), sRes.size() * sizeof(tString::value_type));
                        /*DEBUG*/xASSERT_RET(- 1 != iReaded, tString());

                        xCHECK_DO(sRes.size() * sizeof(tString::value_type) > static_cast<size_t>( iReaded ), break);

                        sRes.resize(sRes.size() * 2);
                    }

                    sRes.resize(iReaded);
                }
            #endif
        #else   //xDEPRECIATE
            std::vector<tString> vsArgs;

            BOOL bRes = CxEnvironment::bGetCommandLineArgs(&vsArgs);
            /*DEBUG*/xASSERT_RET(FALSE != bRes,                              tString());
            /*DEBUG*/xASSERT_RET(FALSE == CxPath::bIsAbsolute(vsArgs.at(0)), tString())

            tString sAbsolutePath;

            sAbsolutePath.resize(xPATH_MAX);

            char *pszRes = realpath(&vsArgs.at(0).at(0), &sAbsolutePath.at(0));
            /*DEBUG*/xASSERT_RET(NULL != pszRes, tString());

            sRes.assign(pszRes);
        #endif
    #endif

    /*DEBUG*/xASSERT_RET(false == sRes.empty(),                 tString());
    /*DEBUG*/xASSERT_RET(FALSE != CxStdioFile::bIsExists(sRes), tString());

    return sRes;
}
//---------------------------------------------------------------------------
//TODO: sGetDll (full path to Dll)
/*static*/
tString
CxPath::sGetDll() {
    /*DEBUG*/

    tString sRes;

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
//DONE: sGetExeDir (dir path to exe)
/*static*/
tString
CxPath::sGetExeDir() {
    return sGetDir(sGetExe());
}
//---------------------------------------------------------------------------
//DONE: sGetDrive (get drive)
#if defined(xOS_WIN)
/*static*/
tString
CxPath::sGetDrive(
    const tString &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());

    size_t uiDriveDelimPos = csFilePath.find(CxConst::xDRIVE_SEP);
    /*DEBUG*/xASSERT_RET(tString::npos != uiDriveDelimPos, tString());
    /*DEBUG*/xASSERT_RET(1             == uiDriveDelimPos, tString());

    return csFilePath.substr(0, uiDriveDelimPos + CxConst::xDRIVE_SEP.size());
}
#endif
//--------------------------------------------------------------------------
//DONE: sGetDir (dir path, without a trailing backslash '\')
/*static*/
tString
CxPath::sGetDir(
    const tString &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    /*DEBUG*/// n/a
    xCHECK_RET(tString::npos == uiSlashPos, tString());

    return csFilePath.substr(0, uiSlashPos);
}
//--------------------------------------------------------------------------
//DONE: sGetDirName (dir name)
/*static*/
tString
CxPath::sGetDirName(
    const tString &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());

    size_t uiSlashPos2 = csFilePath.rfind(CxConst::xSLASH);
    /*DEBUG*/// n/a
    xCHECK_RET(tString::npos == uiSlashPos2, tString());

    size_t uiSlashPos1 = csFilePath.rfind(CxConst::xSLASH, uiSlashPos2 - 1);
    /*DEBUG*/// n/a
    if (tString::npos == uiSlashPos1) {
        return csFilePath.substr(0, uiSlashPos2);
    } else {
        return csFilePath.substr(uiSlashPos1 + 1, uiSlashPos2 - uiSlashPos1 - 1);
    }
}
//---------------------------------------------------------------------------
//DONE: sGetFullName (get name.extension)
/*static*/
tString
CxPath::sGetFullName(
    const tString &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    /*DEBUG*/// n/a
    xCHECK_RET(tString::npos == uiSlashPos, csFilePath);

    return csFilePath.substr(uiSlashPos + CxConst::xSLASH.size(), csFilePath.size());
}
//--------------------------------------------------------------------------
//DONE: sGetName (get name without extension)
/*static*/
tString
CxPath::sGetName(
    const tString &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    /*DEBUG*/// n/a

    size_t uiDotPos = csFilePath.rfind(CxConst::xDOT, csFilePath.size());
    /*DEBUG*/// n/a

    return CxString::sCut(csFilePath, uiSlashPos + CxConst::xSLASH.size(), uiDotPos);
}
//--------------------------------------------------------------------------
//DONE: sGetExt (get extension)
/*static*/
tString
CxPath::sGetExt(
    const tString &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());

    size_t uiDotPos = csFilePath.rfind(CxConst::xDOT, csFilePath.size());
    /*DEBUG*/// n/a
    xCHECK_RET(tString::npos == uiDotPos, tString());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    /*DEBUG*/// n/a

    //if dot after slash - extension not exists
    xCHECK_RET(uiDotPos < uiSlashPos && tString::npos != uiSlashPos, tString());

    return csFilePath.substr(uiDotPos + CxConst::xDOT.size());
}
//--------------------------------------------------------------------------
//DONE: sGetStandartExt (get standart extension)
/*static*/
tString
CxPath::sGetStandartExt(
    const EStandartExt cseFileExt
)
{
    tString sRes;

	switch (cseFileExt) {
    #if defined(xOS_WIN)
        case seExe:	{ sRes = xT("exe");    }   break;
	    case seDll:	{ sRes = xT("dll");    }   break;
	    case seLib:	{ sRes = xT("lib");    }   break;
    #elif defined(xOS_LINUX)
        case seExe:	{ sRes = xT("");       }   break;
	    case seDll:	{ sRes = xT("so");     }   break;
	    case seLib:	{ sRes = xT("a");      }   break;
    #endif
    	default:    { sRes = xT("");       }   break;
    }

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sSetDrive ()
#if defined(xOS_WIN)
/*static*/
tString
CxPath::sSetDrive(
    const tString &csFilePath,
    const tString &csDrivePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
    /*DEBUG*/// csDrivePath

    tString sRes;
    sRes.assign(csFilePath);

    tString sDrive = sGetDrive(sRes);
    /*DEBUG*/xASSERT_RET(false == sDrive.empty(), tString());

    size_t uiPos = sRes.find(sDrive);
    /*DEBUG*/xASSERT_RET(tString::npos != uiPos, tString());

    return sRes.replace(uiPos, sDrive.size(), csDrivePath);
}
#endif
//---------------------------------------------------------------------------
//DONE: sSetDir ()
/*static*/
tString
CxPath::sSetDir(
    const tString &csFilePath,
    const tString &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
    /*DEBUG*/// csDirPath

    tString sRes;
    sRes.assign(csFilePath);

    tString sDir = sGetDir(sRes);
    /*DEBUG*/xASSERT_RET(false == sDir.empty(), tString());

    size_t uiPos = sRes.find(sDir);
    /*DEBUG*/xASSERT_RET(tString::npos != uiPos, tString());

    return sRes.replace(uiPos, sDir.size(), sSlashRemove(csDirPath));
}
//---------------------------------------------------------------------------
//DONE: sSetFullName ()
/*static*/
tString
CxPath::sSetFullName(
    const tString &csFilePath,
    const tString &csFullName
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
    /*DEBUG*/// csFullName

    tString sRes;
    sRes.assign(csFilePath);

    tString sFullName = sGetFullName(sRes);
    /*DEBUG*/xASSERT_RET(false == sFullName.empty(), tString());

    size_t uiPos = sRes.rfind(sFullName);
    /*DEBUG*/xASSERT_RET(tString::npos != uiPos, tString());

    return sRes.replace(uiPos, sFullName.size(), csFullName);
}
//---------------------------------------------------------------------------
//DONE: sSetName ()
/*static*/
tString
CxPath::sSetName(
    const tString &csFilePath,
    const tString &csName
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
    /*DEBUG*/// csName

    tString sRes;
    sRes.assign(csFilePath);

    tString sName = sGetName(sRes);
    /*DEBUG*/xASSERT_RET(false == sName.empty(), tString());

    size_t uiPos = sRes.rfind(sName);
    /*DEBUG*/xASSERT_RET(tString::npos != uiPos, tString());

    return sRes.replace(uiPos, sName.size(), csName);
}
//---------------------------------------------------------------------------
//DONE: sSetExt
/*static*/
tString
CxPath::sSetExt(
    const tString &csFilePath,
    const tString &csExt
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
    /*DEBUG*/// csExt - n/a

    return sRemoveExt(csFilePath) + CxConst::xDOT + csExt;
}
//---------------------------------------------------------------------------


//--------------------------------------------------------------------------
//DONE: sRemoveExt
/*static*/
tString
CxPath::sRemoveExt(
    const tString &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());

    size_t uiDotPos = csFilePath.rfind(CxConst::xDOT);
    /*DEBUG*/// n/a

    return csFilePath.substr(0, uiDotPos);
}
//--------------------------------------------------------------------------
//DONE: sRemoveExtIf
/*static*/
tString
CxPath::sRemoveExtIf(
    const tString &csFilePath,
    const tString &csExt
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());

    size_t uiExtPos = csFilePath.rfind(CxConst::xDOT + csExt);
    xCHECK_RET(tString::npos == uiExtPos, csFilePath);

    size_t uiDotPos = csFilePath.rfind(CxConst::xDOT);
    /*DEBUG*/xASSERT_RET(tString::npos != uiDotPos, tString());

    return csFilePath.substr(0, uiDotPos);
}
//---------------------------------------------------------------------------
//TODO: bIsValid ()
/*static*/
BOOL
CxPath::bIsValid(
    const tString &csFilePath
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
//TODO: bIsNameValid (file name validation)
/*static*/
BOOL
CxPath::bIsNameValid(
    const tString &csFilePath
)
{
    /*DEBUG*/// csFileName - n/a

    BOOL bRes = FALSE;

    const tString csFileName = CxPath::sGetFullName(csFilePath);

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
//DONE: bIsAbsolute (is absolute)
/*static*/
BOOL
CxPath::bIsAbsolute(
    const tString &csFilePath
)
{
    xCHECK_RET(true                  == csFilePath.empty(), FALSE);
    xCHECK_RET(CxConst::xSLASH.at(0) == csFilePath.at(0),   TRUE);

#if defined(xOS_WIN)
    xCHECK_RET(1 == csFilePath.size(),                                                          FALSE);
    xCHECK_RET(CxChar::bIsAlpha(csFilePath.at(0)) && CxConst::xCOLON.at(0) == csFilePath.at(1), TRUE);
#else

#endif

    return FALSE;
}
//---------------------------------------------------------------------------
//DONE: sSetValidName
/*static*/
tString
CxPath::sSetValidName(
    const tString &csFileName
)
{
    /*DEBUG*/// n/a

    tString sRes;
    sRes.assign(csFileName);

    //-------------------------------------
    //is empty
    xCHECK_RET(true == sRes.empty(), tString());

    //-------------------------------------
    //check for name size
    xCHECK_RET(xNAME_MAX <= sRes.size(), tString());

#if defined(xOS_WIN)
    //-------------------------------------
    //if only dots
    size_t uiDotPos = sRes.find_first_not_of(CxConst::xDOT);
    xCHECK_RET(tString::npos == uiDotPos, tString());

    //-------------------------------------
    //if the first character is a dot, the filename is okay or space
    xCHECK_RET(CxConst::xDOT.at(0) == sRes.at(0), tString());

    //-------------------------------------
    //A device name was used. You can pass this value to GetIsValidFileNameErrStr to obtain a pointer to the name of this device.


    //-------------------------------------
    //All characters greater than ASCII 31 to be used except for the following:    "/*:<>?\|
    const tString csFatalChars = xT("\\/:*<>|?\"\t\n\r");

    size_t uiFound = sRes.find_first_of(csFatalChars);
    while (tString::npos != uiFound) {
        sRes.erase(uiFound, 1);
        uiFound = sRes.find_first_of(csFatalChars, uiFound);
    }

    //-------------------------------------
    //The following device names cannot be used for a file name nor may they
    //be used for the first segment of a file name (that part which precedes the  first dot):
    //CLOCK$, AUX, CON, NUL, PRN, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8,
    //COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, LPT9
    //Device names are case insensitve. aux, AUX, Aux, etc. are identical.

    const tString csReservedNames[] = {
        xT("CON"),  xT("PRN"),  xT("AUX"),  xT("CLOCK$"), xT("NUL"),
        xT("COM0"), xT("COM1"), xT("COM2"), xT("COM3"),   xT("COM4"),
        xT("COM5"), xT("COM6"), xT("COM7"), xT("COM8"),   xT("COM9"),
        xT("LPT0"), xT("LPT1"), xT("LPT2"), xT("LPT3"),   xT("LPT4"),
        xT("LPT5"), xT("LPT6"), xT("LPT7"), xT("LPT8"),   xT("LPT9")
    };

    tString sFileName = sRemoveExt(sRes);

    for (size_t i = 0; i < xARRAY_SIZE(csReservedNames); ++ i) {
        xCHECK_RET(TRUE == CxString::bCompareNoCase(sFileName, csReservedNames[i]), tString());
    }
#elif defined(xOS_LINUX)
    //TODO: sSetValidName
#endif

    return sRes;
}
//--------------------------------------------------------------------------
//DONE: sToWin (convert slashes to Windows-like)
/*static*/
tString
CxPath::sToWin(
    const tString &csFilePath,
    const BOOL     cbIsSlashAtEnd
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    tString sRes;

    if (TRUE == cbIsSlashAtEnd) {
        sRes = sSlashAppend(csFilePath);
    } else {
        sRes = sSlashRemove(csFilePath);
    }

    sRes = CxString::sReplaceAll(sRes, CxConst::xNIX_SLASH, CxConst::xWIN_SLASH);

    return sRes;
}
//--------------------------------------------------------------------------
//DONE: sToNix (convert slashes to Nix-like)
/*static*/
tString
CxPath::sToNix(
    const tString &csFilePath,
    const BOOL     cbIsSlashAtEnd
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    tString sRes;

    if (TRUE == cbIsSlashAtEnd) {
        sRes = sSlashAppend(csFilePath);
    } else {
        sRes = sSlashRemove(csFilePath);
    }

    sRes = CxString::sReplaceAll(sRes, CxConst::xWIN_SLASH, CxConst::xNIX_SLASH);

    return sRes;
}
//--------------------------------------------------------------------------
//DONE: sToCurrentOs (convert slashes to current OS-like)
/*static*/
tString
CxPath::sToCurrentOs(
    const tString &csFilePath,
    const BOOL     cbIsSlashAtEnd
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    tString sRes;

    if (TRUE == cbIsSlashAtEnd) {
        sRes = sSlashAppend(csFilePath);
    } else {
        sRes = sSlashRemove(csFilePath);
    }

    sRes = CxString::sReplaceAll(sRes, CxConst::xWIN_SLASH, CxConst::xSLASH);

    return sRes;
}
//--------------------------------------------------------------------------
//DONE: sGetFull (get full path of the specified file)
/*static*/
tString 
CxPath::sGetFull(
    const tString &csFilePath
)
{
    /*DEBUG*/  

    tString sRes;

#if defined(xOS_WIN)
    ULONG   ulRes = 0;
    tString sBuff;

    ulRes = ::GetFullPathName(&csFilePath.at(0), 0, NULL, NULL);
    /*DEBUG*/xASSERT_RET(0 != ulRes, tString());

    sBuff.resize(ulRes);

    ulRes = ::GetFullPathName(&csFilePath.at(0), sBuff.size(), &sBuff.at(0), NULL);
    /*DEBUG*/xASSERT_RET(0 != ulRes, tString());

    sBuff.resize(ulRes);

    sRes.assign(sBuff);
#elif defined(xOS_LINUX)
    tString sBuff;

    sBuff.resize(xPATH_MAX);

    char *pszRes = realpath(&csFilePath.at(0), &sBuff.at(0));
    /*DEBUG*/xASSERT_RET(NULL != pszRes, tString());

    sRes.assign(pszRes);
#endif

    /*DEBUG*/xASSERT_RET(FALSE != bIsAbsolute(sRes), tString());

    return sRes;        
}
//--------------------------------------------------------------------------
//DONE: sMinimizeName
/*static*/
tString
CxPath::sMinimizeName(
    const tString &csFileName,
    const size_t   cuiMaxSize
)
{
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(),          tString());
    /*DEBUG*///xASSERT_RET(false == sGetExt(csFileName).empty(), tString());
    /*DEBUG*/xASSERT_RET(0 < cuiMaxSize,                       tString());

    tString sRes;

    tString sTildaDotExt;

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
tString
CxPath::sMinimize(
    const tString &csFilePath,
    const size_t   cuiMaxSize
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
    /*DEBUG*/xASSERT_RET(0 < cuiMaxSize,              tString());

    tString sRes;

#if defined(xOS_WIN)
    sRes.assign(csFilePath);

    tString sDrive = sGetDrive(sRes);                                            //D:
    tString sDir   = sGetDir(sRes).erase(0, sDrive.size()) + CxConst::xSLASH;    /* \xLib\Test\CxString\Project\Debug\ */
    tString sName  = sGetFullName(sRes);                                        //Test.exe

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
            size_t uiPos = tString::npos;

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
                if (tString::npos == uiPos) {
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
//DONE: sSlashAppend (append slash)
/*static*/
tString
CxPath::sSlashAppend(
    const tString &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), tString());

    return CxString::sTrimRightChars(csDirPath, CxConst::xSLASH).append(CxConst::xSLASH);
}
//--------------------------------------------------------------------------
//DONE: sSlashRemove (remove slash)
/*static*/
tString
CxPath::sSlashRemove(
    const tString &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), tString());

    return CxString::sTrimRightChars(csDirPath, CxConst::xSLASH);
}
//--------------------------------------------------------------------------
//DONE: uiGetMaxSize (get max path length in symbols)
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
//DONE: uiGetNameMaxSize (get max name length in symbols)
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
//DONE: CxPath
CxPath::CxPath() {

}
//---------------------------------------------------------------------------
//DONE: ~CxPath
/*virtual*/
CxPath::~CxPath() {

}
//---------------------------------------------------------------------------
