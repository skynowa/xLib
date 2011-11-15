/**
 * \file  CxPath.cpp
 * \brief file system path
 */


#include <xLib/Filesystem/CxPath.h>

#include <xLib/Common/CxChar.h>
#include <xLib/Common/CxCommandLine.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxCurrentProcess.h>


xNAMESPACE_BEGIN(NxLib)

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
std::string_t
CxPath::sGetExe() {
    std::string_t sRes;

#if defined(xOS_ENV_WIN)
    sRes.resize(xPATH_MAX);

    ULONG ulStored = ::GetModuleFileName(NULL, &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0 != ulStored, std::string_t());

    sRes.resize(ulStored);
#elif defined(xOS_ENV_UNIX)
    #if defined(xOS_FREEBSD)
        #if defined(KERN_PROC_PATHNAME)
            sRes.resize(xPATH_MAX);

            int aiMib[] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, - 1};

            size_t uiResSize = sRes.size() * sizeof(std::string_t::value_type);

            int iRes = sysctl(aiMib, static_cast<u_int>( xARRAY_SIZE(aiMib) ), &sRes.at(0), &uiResSize, NULL, 0);
            /*DEBUG*/xASSERT_RET(- 1 != iRes, std::string_t());

            sRes.resize(uiResSize);
        #else
            std::vector<std::string_t> vsArgs;

            BOOL bRes = CxCommandLine::bGetArgs(&vsArgs);
            /*DEBUG*/xASSERT_RET(FALSE != bRes,                      std::string_t());
            /*DEBUG*/xASSERT_RET(false == vsArgs.empty(),            std::string_t());
            /*DEBUG*/xASSERT_RET(FALSE == bIsAbsolute(vsArgs.at(0)), std::string_t());

            sRes.assign( sGetAbsolute(vsArgs.at(0)) );
        #endif
    #else
        const std::string_t csProcFile = CxString::sFormat(xT("/proc/%ld/exe"), CxCurrentProcess::ulGetId());

        BOOL bRes = CxFile::bIsExists(csProcFile);
        if (TRUE == bRes) {
            sRes.resize(xPATH_MAX);

            int iReaded = - 1;

            for ( ; ; ) {
                iReaded = readlink(csProcFile.c_str(), &sRes.at(0), sRes.size() * sizeof(std::string_t::value_type));
                /*DEBUG*/xASSERT_RET(- 1 != iReaded, std::string_t());

                xCHECK_DO(sRes.size() * sizeof(std::string_t::value_type) > static_cast<size_t>( iReaded ), break);

                sRes.resize(sRes.size() * 2);
            }

            sRes.resize(iReaded);
        }
    #endif
#endif

    /*DEBUG*/xASSERT_RET(FALSE != CxFile::bIsExists(sRes), std::string_t());

    return sRes;
}
//---------------------------------------------------------------------------
//TODO: sGetDll
/*static*/
std::string_t
CxPath::sGetDll() {
    /*DEBUG*/

    std::string_t sRes;

#if defined(xOS_ENV_WIN)
    #if xTODO
        MEMORY_BASIC_INFORMATION mbi;
        VirtualQuery(&symbol,&mbi,sizeof(mbi));
        HMODULE mod = mbi.AllocationBase;

        LPTSTR buf = new char_t[255];
        GetModuleFileName(mod,buf,255);
        Array<uchar> arr(strlen(buf));
        for(idx_t i = 0; i < strlen(buf);i++) {
            arr[i] = buf[i];
        }
        String fullpath = arr;
    #endif
#elif defined(xOS_ENV_UNIX)
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
std::string_t
CxPath::sGetExeDir() {
    return sGetDir(sGetExe());
}
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

/*static*/
std::string_t
CxPath::sGetDrive(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());

    size_t uiDriveDelimPos = csFilePath.find(CxConst::xDRIVE_SEP);
    /*DEBUG*/xASSERT_RET(std::string_t::npos != uiDriveDelimPos, std::string_t());
    /*DEBUG*/xASSERT_RET(1                  == uiDriveDelimPos, std::string_t());

    return csFilePath.substr(0, uiDriveDelimPos + CxConst::xDRIVE_SEP.size());
}

#endif
//--------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sGetDir(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    xCHECK_RET(std::string_t::npos == uiSlashPos, std::string_t());

    return csFilePath.substr(0, uiSlashPos);
}
//--------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sGetDirName(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());

    size_t uiSlashPos2 = csFilePath.rfind(CxConst::xSLASH);
    xCHECK_RET(std::string_t::npos == uiSlashPos2, std::string_t());

    size_t uiSlashPos1 = csFilePath.rfind(CxConst::xSLASH, uiSlashPos2 - 1);
    if (std::string_t::npos == uiSlashPos1) {
        return csFilePath.substr(0, uiSlashPos2);
    } else {
        return csFilePath.substr(uiSlashPos1 + 1, uiSlashPos2 - uiSlashPos1 - 1);
    }
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sGetFullName(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    xCHECK_RET(std::string_t::npos == uiSlashPos, csFilePath);

    return csFilePath.substr(uiSlashPos + CxConst::xSLASH.size(), csFilePath.size());
}
//--------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sGetName(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    size_t uiDotPos   = csFilePath.rfind(CxConst::xDOT,   csFilePath.size());

    return CxString::sCut(csFilePath, uiSlashPos + CxConst::xSLASH.size(), uiDotPos);
}
//--------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sGetExt(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());

    size_t uiDotPos   = csFilePath.rfind(CxConst::xDOT,   csFilePath.size());
    xCHECK_RET(std::string_t::npos == uiDotPos, std::string_t());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    //if dot after slash - extension not exists
    xCHECK_RET(uiDotPos < uiSlashPos && std::string_t::npos != uiSlashPos, std::string_t());

    return csFilePath.substr(uiDotPos + CxConst::xDOT.size());
}
//--------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sGetStandartExt(
    const EStandartExt cseFileExt
)
{
    std::string_t sRes;

    switch (cseFileExt) {
    #if defined(xOS_ENV_WIN)
        case seExe: { sRes = xT("exe"); }   break;
        case seDll: { sRes = xT("dll"); }   break;
        case seLib: { sRes = xT("lib"); }   break;
        case seObj: { sRes = xT("obj"); }   break;
    #elif defined(xOS_ENV_UNIX)
        case seExe: { sRes = xT("");    }   break;
        case seDll: { sRes = xT("so");  }   break;
        case seLib: { sRes = xT("a");   }   break;
        case seObj: { sRes = xT("o");   }   break;
    #endif
        default:    { sRes = xT("");    }   break;
    }

    return sRes;
}
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

/*static*/
std::string_t
CxPath::sSetDrive(
    const std::string_t &csFilePath,
    const std::string_t &csDrivePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());
    /*DEBUG*/// csDrivePath

    std::string_t sRes;
    sRes.assign(csFilePath);

    std::string_t sDrive = sGetDrive(sRes);
    /*DEBUG*/xASSERT_RET(false == sDrive.empty(), std::string_t());

    size_t uiPos = sRes.find(sDrive);
    /*DEBUG*/xASSERT_RET(std::string_t::npos != uiPos, std::string_t());

    return sRes.replace(uiPos, sDrive.size(), csDrivePath);
}

#endif
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sSetDir(
    const std::string_t &csFilePath,
    const std::string_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());
    /*DEBUG*/// csDirPath

    std::string_t sRes;
    sRes.assign(csFilePath);

    std::string_t sDir = sGetDir(sRes);
    /*DEBUG*/xASSERT_RET(false == sDir.empty(), std::string_t());

    size_t uiPos = sRes.find(sDir);
    /*DEBUG*/xASSERT_RET(std::string_t::npos != uiPos, std::string_t());

    return sRes.replace(uiPos, sDir.size(), sSlashRemove(csDirPath));
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sSetFullName(
    const std::string_t &csFilePath,
    const std::string_t &csFullName
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());
    /*DEBUG*/// csFullName

    std::string_t sRes;
    sRes.assign(csFilePath);

    std::string_t sFullName = sGetFullName(sRes);
    /*DEBUG*/xASSERT_RET(false == sFullName.empty(), std::string_t());

    size_t uiPos = sRes.rfind(sFullName);
    /*DEBUG*/xASSERT_RET(std::string_t::npos != uiPos, std::string_t());

    return sRes.replace(uiPos, sFullName.size(), csFullName);
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sSetName(
    const std::string_t &csFilePath,
    const std::string_t &csName
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());
    /*DEBUG*/// csName

    std::string_t sRes;
    sRes.assign(csFilePath);

    std::string_t sName = sGetName(sRes);
    /*DEBUG*/xASSERT_RET(false == sName.empty(), std::string_t());

    size_t uiPos = sRes.rfind(sName);
    /*DEBUG*/xASSERT_RET(std::string_t::npos != uiPos, std::string_t());

    return sRes.replace(uiPos, sName.size(), csName);
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sSetExt(
    const std::string_t &csFilePath,
    const std::string_t &csExt
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());
    /*DEBUG*/// csExt - n/a

    return sRemoveExt(csFilePath) + CxConst::xDOT + csExt;
}
//---------------------------------------------------------------------------


//--------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sRemoveExt(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());

    size_t uiDotPos = csFilePath.rfind(CxConst::xDOT);

    return csFilePath.substr(0, uiDotPos);
}
//--------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sRemoveExtIf(
    const std::string_t &csFilePath,
    const std::string_t &csExt
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());

    size_t uiExtPos = csFilePath.rfind(CxConst::xDOT + csExt);
    xCHECK_RET(std::string_t::npos == uiExtPos, csFilePath);

    size_t uiDotPos = csFilePath.rfind(CxConst::xDOT);
    /*DEBUG*/xASSERT_RET(std::string_t::npos != uiDotPos, std::string_t());

    return csFilePath.substr(0, uiDotPos);
}
//---------------------------------------------------------------------------
//TODO: bIsValid
/*static*/
BOOL
CxPath::bIsValid(
    const std::string_t &csFilePath
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
    const std::string_t &csFilePath
)
{
    /*DEBUG*/// csFileName - n/a

    BOOL bRes = FALSE;

    const std::string_t csFileName = CxPath::sGetFullName(csFilePath);

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
    const std::string_t &csFilePath
)
{
    xCHECK_RET(true                  == csFilePath.empty(), FALSE);
    xCHECK_RET(CxConst::xSLASH.at(0) == csFilePath.at(0),   TRUE);

#if defined(xOS_ENV_WIN)
    xCHECK_RET(1 == csFilePath.size(),                                                          FALSE);
    xCHECK_RET(CxChar::bIsAlpha(csFilePath.at(0)) && CxConst::xCOLON.at(0) == csFilePath.at(1), TRUE);
#else
    // n/a
#endif

    return FALSE;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sSetValidName(
    const std::string_t &csFileName
)
{
    /*DEBUG*/// n/a

    std::string_t sRes;
    sRes.assign(csFileName);

    //-------------------------------------
    //is empty
    xCHECK_RET(true == sRes.empty(), std::string_t());

    //-------------------------------------
    //check for name size
    xCHECK_RET(xNAME_MAX <= sRes.size(), std::string_t());

#if defined(xOS_ENV_WIN)
    //-------------------------------------
    //if only dots
    size_t uiDotPos = sRes.find_first_not_of(CxConst::xDOT);
    xCHECK_RET(std::string_t::npos == uiDotPos, std::string_t());

    //-------------------------------------
    //if the first character is a dot, the filename is okay or space
    xCHECK_RET(CxConst::xDOT.at(0) == sRes.at(0), std::string_t());

    //-------------------------------------
    //A device name was used. You can pass this value to GetIsValidFileNameErrStr to obtain a pointer to the name of this device.


    //-------------------------------------
    //All characters greater than ASCII 31 to be used except for the following:    "/*:<>?\|
    const std::string_t csFatalChars = xT("\\/:*<>|?\"\t\n\r");

    size_t uiFound = sRes.find_first_of(csFatalChars);
    while (std::string_t::npos != uiFound) {
        sRes.erase(uiFound, 1);
        uiFound = sRes.find_first_of(csFatalChars, uiFound);
    }

    //-------------------------------------
    //The following device names cannot be used for a file name nor may they
    //be used for the first segment of a file name (that part which precedes the  first dot):
    //CLOCK$, AUX, CON, NUL, PRN, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8,
    //COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, LPT9
    //Device names are case insensitve. aux, AUX, Aux, etc. are identical.

    const std::string_t csReservedNames[] = {
        xT("CON"),  xT("PRN"),  xT("AUX"),  xT("CLOCK$"), xT("NUL"),
        xT("COM0"), xT("COM1"), xT("COM2"), xT("COM3"),   xT("COM4"),
        xT("COM5"), xT("COM6"), xT("COM7"), xT("COM8"),   xT("COM9"),
        xT("LPT0"), xT("LPT1"), xT("LPT2"), xT("LPT3"),   xT("LPT4"),
        xT("LPT5"), xT("LPT6"), xT("LPT7"), xT("LPT8"),   xT("LPT9")
    };

    std::string_t sFileName = sRemoveExt(sRes);

    for (size_t i = 0; i < xARRAY_SIZE(csReservedNames); ++ i) {
        xCHECK_RET(TRUE == CxString::bCompareNoCase(sFileName, csReservedNames[i]), std::string_t());
    }
#elif defined(xOS_ENV_UNIX)
    //TODO: sSetValidName
#endif

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sToWin(
    const std::string_t &csFilePath,
    const BOOL          cbIsSlashAtEnd
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    std::string_t sRes;

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
std::string_t
CxPath::sToNix(
    const std::string_t &csFilePath,
    const BOOL          cbIsSlashAtEnd
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    std::string_t sRes;

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
std::string_t
CxPath::sToCurrentOs(
    const std::string_t &csFilePath,
    const BOOL          cbIsSlashAtEnd
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    std::string_t sRes;

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
std::string_t
CxPath::sGetAbsolute(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/

    std::string_t sRes;

#if defined(xOS_ENV_WIN)
    ULONG   ulRes = 0UL;
    std::string_t sBuff;

    ulRes = ::GetFullPathName(&csFilePath.at(0), 0, NULL, NULL);
    /*DEBUG*/xASSERT_RET(0UL != ulRes, std::string_t());

    sBuff.resize(ulRes);

    ulRes = ::GetFullPathName(&csFilePath.at(0), sBuff.size(), &sBuff.at(0), NULL);
    /*DEBUG*/xASSERT_RET(0UL != ulRes, std::string_t());

    sBuff.resize(ulRes);

    sRes.assign(sBuff);
#elif defined(xOS_ENV_UNIX)
    std::string_t sBuff;

    sBuff.resize(xPATH_MAX);

    char_t *pszRes = realpath(&csFilePath.at(0), &sBuff.at(0));
    /*DEBUG*/xASSERT_RET(NULL != pszRes, std::string_t());

    sRes.assign(pszRes);
#endif

    /*DEBUG*/xASSERT_RET(FALSE != bIsAbsolute(sRes), std::string_t());

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sMinimizeName(
    const std::string_t &csFileName,
    const size_t        cuiMaxSize
)
{
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(), std::string_t());
    /*DEBUG*/xASSERT_RET(0 < cuiMaxSize,              std::string_t());

    std::string_t sRes;

    std::string_t sTildaDotExt;

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
std::string_t
CxPath::sMinimize(
    const std::string_t &csFilePath,
    const size_t        cuiMaxSize
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::string_t());
    /*DEBUG*/xASSERT_RET(0     <  cuiMaxSize,         std::string_t());

    std::string_t sRes;

#if defined(xOS_ENV_WIN)
    sRes.assign(csFilePath);

    std::string_t sDrive = sGetDrive(sRes);                                          /* D: */
    std::string_t sDir   = sGetDir(sRes).erase(0, sDrive.size()) + CxConst::xSLASH;  /* \xLib\Test\CxString\Project\Debug */
    std::string_t sName  = sGetFullName(sRes);                                       /* Test.exe */

    while (((false == sDir.empty()) || (false == sDrive.empty())) && (sRes.size() > cuiMaxSize)) {
        if ((CxConst::xSLASH + xT("...") + CxConst::xSLASH) == sDir ) {
            sDrive.clear();
            sDir = xT("...") + CxConst::xSLASH;
        }
        else if (true == sDir.empty()) {
            sDrive.clear();
        }
        else {
            BOOL   bRoot = FALSE;
            size_t uiPos = std::string_t::npos;

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
                uiPos = sDir.find_first_of(CxConst::xSLASH);
                if (std::string_t::npos == uiPos) {
                    sDir.clear();
                } else {
                    //Delete(S, 1, uiPos); - c ������� 1(0) uiPos ��������
                    sDir.erase(0, uiPos + CxConst::xSLASH.size());
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
#elif defined(xOS_ENV_UNIX)
    sRes.assign(csFilePath);
#endif

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sSlashAppend(
    const std::string_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), std::string_t());

    return CxString::sTrimRightChars(csDirPath, CxConst::xSLASH).append(CxConst::xSLASH);
}
//--------------------------------------------------------------------------
/*static*/
std::string_t
CxPath::sSlashRemove(
    const std::string_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), std::string_t());

    return CxString::sTrimRightChars(csDirPath, CxConst::xSLASH);
}
//--------------------------------------------------------------------------
/*static*/
size_t
CxPath::uiGetMaxSize() {
    /*DEBUG*/

    size_t uiRes = 0;

#if defined(xOS_ENV_WIN)
    #if defined(MAX_PATH)
        uiRes = MAX_PATH;
    #else
        const size_t cuiDefaultSize = 260;

        uiRes = cuiDefaultSize;
    #endif
#elif defined(xOS_ENV_UNIX)
    #if defined(PATH_MAX)
        uiRes = PATH_MAX;
    #else
        const ULONG culSavedError = 0UL;
        LONG        liRes         = - 1L;
        ULONG       ulLastError   = 0UL;

        (void)CxLastError::bSet(culSavedError);

        liRes       = ::pathconf("/", _PC_PATH_MAX);
        ulLastError = CxLastError::ulGet();
        /*DEBUG*/xASSERT_RET(- 1L == liRes && 0UL != culSavedError, 0);

        if (- 1L == liRes && culSavedError == ulLastError) {
            //system does not have a limit for the requested resource
            const size_t cuiDefaultSize = 1024;

            uiRes = cuiDefaultSize;
        } else {
            //relative root
            uiRes = static_cast<size_t>( liRes + 1 );
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

#if defined(xOS_ENV_WIN)
    #if defined(FILENAME_MAX)
        uiRes = FILENAME_MAX;
    #else
        const size_t cuiDefaultSize = 260;

        uiRes = cuiDefaultSize;
    #endif
#elif defined(xOS_ENV_UNIX)
    #if defined(NAME_MAX)
        uiRes = NAME_MAX;
    #else
        const ULONG culSavedError = 0UL;
        LONG        liRes         = - 1L;
        ULONG       ulLastError   = 0UL;

        (void)CxLastError::bSet(culSavedError);

        liRes       = ::pathconf("/", _PC_NAME_MAX);
        ulLastError = CxLastError::ulGet();
        /*DEBUG*/xASSERT_RET(- 1L == liRes && 0UL != culSavedError, 0);

        if (- 1 == liRes && culSavedError == ulLastError) {
            //system does not have a limit for the requested resource
            const size_t cuiDefaultSize = 1024;

            uiRes = cuiDefaultSize;
        } else {
            uiRes = static_cast<size_t>( liRes );
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

xNAMESPACE_END(NxLib)
