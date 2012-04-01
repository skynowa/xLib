/**
 * \file  CxPath.cpp
 * \brief file system path
 */


#include <xLib/Filesystem/CxPath.h>

#include <xLib/Common/CxChar.h>
#include <xLib/Common/CxCommandLine.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>
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
std::tstring_t
CxPath::sGetExe() {
    std::tstring_t sRes;

#if xOS_ENV_WIN
    sRes.resize(xPATH_MAX);

    DWORD ulStored = ::GetModuleFileName(NULL, &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0UL != ulStored, std::tstring_t());

    sRes.resize(ulStored);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        const std::tstring_t csProcFile = CxString::sFormat(xT("/proc/%ld/exe"), CxCurrentProcess::ulGetId());

        bool bRes = CxFile::bIsExists(csProcFile);
        xCHECK_RET(false == bRes, std::tstring_t());

        int iReaded = - 1;
        sRes.resize(xPATH_MAX);

        for ( ; ; ) {
            iReaded = ::readlink(csProcFile.c_str(), &sRes.at(0), sRes.size() * sizeof(std::tstring_t::value_type));
            /*DEBUG*/xASSERT_RET(- 1 != iReaded, std::tstring_t());

            xCHECK_DO(sRes.size() * sizeof(std::tstring_t::value_type) > static_cast<size_t>( iReaded ), break);

            sRes.resize(sRes.size() * 2);
        }

        sRes.resize(iReaded);
    #elif xOS_FREEBSD
        #if defined(KERN_PROC_PATHNAME)
            sRes.resize(xPATH_MAX);

            int aiMib[] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, - 1};

            size_t uiResSize = sRes.size() * sizeof(std::tstring_t::value_type);

            int iRes = ::sysctl(aiMib, xARRAY_SIZE(aiMib), &sRes.at(0), &uiResSize, NULL, 0);
            /*DEBUG*/xASSERT_RET(- 1 != iRes, std::tstring_t());

            sRes.resize(uiResSize);
        #else
            std::vector<std::tstring_t> vsArgs;

            bool bRes = CxCommandLine::bGetArgs(&vsArgs);
            /*DEBUG*/xASSERT_RET(true  == bRes,                      std::tstring_t());
            /*DEBUG*/xASSERT_RET(false == vsArgs.empty(),            std::tstring_t());
            /*DEBUG*/xASSERT_RET(false == bIsAbsolute(vsArgs.at(0)), std::tstring_t());

            sRes = sGetAbsolute(vsArgs.at(0));
        #endif
    #endif
#endif

    /*DEBUG*/xASSERT_RET(true == CxFile::bIsExists(sRes), std::tstring_t());

    return sRes;
}
//---------------------------------------------------------------------------
#if xOS_ENV_WIN
    extern "C" IMAGE_DOS_HEADER __ImageBase;
#elif xOS_ENV_UNIX
	static void vFunction() { ; }
#endif

/*static*/
std::tstring_t
CxPath::sGetDll() {
    /*DEBUG*/

    std::tstring_t sRes;

#if xOS_ENV_WIN
    sRes.resize(xPATH_MAX);

    DWORD ulStored = ::GetModuleFileName(reinterpret_cast<HINSTANCE>( &__ImageBase ), &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0UL != ulStored, std::tstring_t());

    sRes.resize(ulStored);
#elif xOS_ENV_UNIX
    Dl_info  diInfo        = {0};
    void    *fpProcAddress = (void *)vFunction;

    int iRes = ::dladdr(fpProcAddress, &diInfo);
    /*DEBUF*/xASSERT_RET(0 < iRes, CxConst::xSTR_EMPTY);

    sRes = sGetAbsolute(diInfo.dli_fname);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sGetExeDir() {
    return sGetDir(sGetExe());
}
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

/*static*/
std::tstring_t
CxPath::sGetDrive(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());

    size_t uiDriveDelimPos = csFilePath.find(CxConst::xDRIVE_SEP);
    /*DEBUG*/xASSERT_RET(std::tstring_t::npos != uiDriveDelimPos, std::tstring_t());
    /*DEBUG*/xASSERT_RET(1                    == uiDriveDelimPos, std::tstring_t());

    return csFilePath.substr(0, uiDriveDelimPos + CxConst::xDRIVE_SEP.size());
}

#endif
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sGetDir(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    xCHECK_RET(std::tstring_t::npos == uiSlashPos, std::tstring_t());

    return csFilePath.substr(0, uiSlashPos);
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sGetDirName(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());

    size_t uiSlashPos2 = csFilePath.rfind(CxConst::xSLASH);
    xCHECK_RET(std::tstring_t::npos == uiSlashPos2, std::tstring_t());

    size_t uiSlashPos1 = csFilePath.rfind(CxConst::xSLASH, uiSlashPos2 - 1);
    if (std::tstring_t::npos == uiSlashPos1) {
        return csFilePath.substr(0, uiSlashPos2);
    } else {
        return csFilePath.substr(uiSlashPos1 + 1, uiSlashPos2 - uiSlashPos1 - 1);
    }
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sGetFullName(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    xCHECK_RET(std::tstring_t::npos == uiSlashPos, csFilePath);

    return csFilePath.substr(uiSlashPos + CxConst::xSLASH.size(), csFilePath.size());
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sGetName(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    size_t uiDotPos   = csFilePath.rfind(CxConst::xDOT,   csFilePath.size());

    return CxString::sCut(csFilePath, uiSlashPos + CxConst::xSLASH.size(), uiDotPos);
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sGetExt(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());

    size_t uiDotPos   = csFilePath.rfind(CxConst::xDOT,   csFilePath.size());
    xCHECK_RET(std::tstring_t::npos == uiDotPos, std::tstring_t());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    //if dot after slash - extension not exists
    xCHECK_RET(uiDotPos < uiSlashPos && std::tstring_t::npos != uiSlashPos, std::tstring_t());

    return csFilePath.substr(uiDotPos + CxConst::xDOT.size());
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sGetStandartExt(
    const EStandartExt cseFileExt
)
{
    std::tstring_t sRes;

    switch (cseFileExt) {
    #if xOS_ENV_WIN
        case seExe: { sRes = xT("exe"); }   break;
        case seDll: { sRes = xT("dll"); }   break;
        case seLib: { sRes = xT("lib"); }   break;
        case seObj: { sRes = xT("obj"); }   break;
    #elif xOS_ENV_UNIX
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
#if xOS_ENV_WIN

/*static*/
std::tstring_t
CxPath::sSetDrive(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csDrivePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());
    /*DEBUG*/// csDrivePath

    std::tstring_t sRes(csFilePath);

    std::tstring_t sDrive = sGetDrive(sRes);
    /*DEBUG*/xASSERT_RET(false == sDrive.empty(), std::tstring_t());

    size_t uiPos = sRes.find(sDrive);
    /*DEBUG*/xASSERT_RET(std::tstring_t::npos != uiPos, std::tstring_t());

    return sRes.replace(uiPos, sDrive.size(), csDrivePath);
}

#endif
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sSetDir(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());
    /*DEBUG*/// csDirPath

    std::tstring_t sRes(csFilePath);

    std::tstring_t sDir = sGetDir(sRes);
    /*DEBUG*/xASSERT_RET(false == sDir.empty(), std::tstring_t());

    size_t uiPos = sRes.find(sDir);
    /*DEBUG*/xASSERT_RET(std::tstring_t::npos != uiPos, std::tstring_t());

    return sRes.replace(uiPos, sDir.size(), sSlashRemove(csDirPath));
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sSetFullName(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csFullName
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());
    /*DEBUG*/// csFullName

    std::tstring_t sRes(csFilePath);

    std::tstring_t sFullName = sGetFullName(sRes);
    /*DEBUG*/xASSERT_RET(false == sFullName.empty(), std::tstring_t());

    size_t uiPos = sRes.rfind(sFullName);
    /*DEBUG*/xASSERT_RET(std::tstring_t::npos != uiPos, std::tstring_t());

    return sRes.replace(uiPos, sFullName.size(), csFullName);
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sSetName(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csName
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());
    /*DEBUG*/// csName

    std::tstring_t sRes(csFilePath);

    std::tstring_t sName = sGetName(sRes);
    /*DEBUG*/xASSERT_RET(false == sName.empty(), std::tstring_t());

    size_t uiPos = sRes.rfind(sName);
    /*DEBUG*/xASSERT_RET(std::tstring_t::npos != uiPos, std::tstring_t());

    return sRes.replace(uiPos, sName.size(), csName);
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sSetExt(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csExt
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());
    /*DEBUG*/// csExt - n/a

    return sRemoveExt(csFilePath) + CxConst::xDOT + csExt;
}
//---------------------------------------------------------------------------


//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sRemoveExt(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());

    size_t uiDotPos = csFilePath.rfind(CxConst::xDOT);

    return csFilePath.substr(0, uiDotPos);
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sRemoveExtIf(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csExt
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());

    size_t uiExtPos = csFilePath.rfind(CxConst::xDOT + csExt);
    xCHECK_RET(std::tstring_t::npos == uiExtPos, csFilePath);

    size_t uiDotPos = csFilePath.rfind(CxConst::xDOT);
    /*DEBUG*/xASSERT_RET(std::tstring_t::npos != uiDotPos, std::tstring_t());

    return csFilePath.substr(0, uiDotPos);
}
//---------------------------------------------------------------------------
//TODO: bIsValid
/*static*/
bool
CxPath::bIsValid(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/// csFileName - n/a

    bool bRes = false;

    //is empty
    bRes = csFilePath.empty();
    xCHECK_RET(true == bRes, false);

    //check for size
    bRes = (xPATH_MAX < csFilePath.size());
    xCHECK_RET(true == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//TODO: bIsNameValid
/*static*/
bool
CxPath::bIsNameValid(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/// csFileName - n/a

    bool bRes = false;

    const std::tstring_t csFileName = CxPath::sGetFullName(csFilePath);

    //is empty
    bRes = csFileName.empty();
    xCHECK_RET(true == bRes, false);

    //check for name size
    bRes = (xNAME_MAX < csFileName.size());
    xCHECK_RET(true == bRes, false);

    //cm. sSetValidName

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxPath::bIsAbsolute(
    const std::tstring_t &csFilePath
)
{
    xCHECK_RET(true                  == csFilePath.empty(), false);
    xCHECK_RET(CxConst::xSLASH.at(0) == csFilePath.at(0),   true);

#if xOS_ENV_WIN
    xCHECK_RET(1 == csFilePath.size(),                                                          false);
    xCHECK_RET(CxChar::bIsAlpha(csFilePath.at(0)) && CxConst::xCOLON.at(0) == csFilePath.at(1), true);
#else
    // n/a
#endif

    return false;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sSetValidName(
    const std::tstring_t &csFileName
)
{
    /*DEBUG*/// n/a

    std::tstring_t sRes(csFileName);

    //-------------------------------------
    //is empty
    xCHECK_RET(true == sRes.empty(), std::tstring_t());

    //-------------------------------------
    //check for name size
    xCHECK_RET(xNAME_MAX <= sRes.size(), std::tstring_t());

#if xOS_ENV_WIN
    //-------------------------------------
    //if only dots
    size_t uiDotPos = sRes.find_first_not_of(CxConst::xDOT);
    xCHECK_RET(std::tstring_t::npos == uiDotPos, std::tstring_t());

    //-------------------------------------
    //if the first character is a dot, the filename is okay or space
    xCHECK_RET(CxConst::xDOT.at(0) == sRes.at(0), std::tstring_t());

    //-------------------------------------
    //A device name was used. You can pass this value to GetIsValidFileNameErrStr to obtain a pointer to the name of this device.


    //-------------------------------------
    //All characters greater than ASCII 31 to be used except for the following:    "/*:<>?\|
    const std::tstring_t csFatalChars = xT("\\/:*<>|?\"\t\n\r");

    size_t uiFound = sRes.find_first_of(csFatalChars);
    while (std::tstring_t::npos != uiFound) {
        sRes.erase(uiFound, 1);
        uiFound = sRes.find_first_of(csFatalChars, uiFound);
    }

    //-------------------------------------
    //The following device names cannot be used for a file name nor may they
    //be used for the first segment of a file name (that part which precedes the  first dot):
    //CLOCK$, AUX, CON, NUL, PRN, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8,
    //COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, LPT9
    //Device names are case insensitve. aux, AUX, Aux, etc. are identical.

    const std::tstring_t csReservedNames[] = {
        xT("CON"),  xT("PRN"),  xT("AUX"),  xT("CLOCK$"), xT("NUL"),
        xT("COM0"), xT("COM1"), xT("COM2"), xT("COM3"),   xT("COM4"),
        xT("COM5"), xT("COM6"), xT("COM7"), xT("COM8"),   xT("COM9"),
        xT("LPT0"), xT("LPT1"), xT("LPT2"), xT("LPT3"),   xT("LPT4"),
        xT("LPT5"), xT("LPT6"), xT("LPT7"), xT("LPT8"),   xT("LPT9")
    };

    std::tstring_t sFileName = sRemoveExt(sRes);

    for (size_t i = 0; i < xARRAY_SIZE(csReservedNames); ++ i) {
        xCHECK_RET(true == CxString::bCompareNoCase(sFileName, csReservedNames[i]), std::tstring_t());
    }
#elif xOS_ENV_UNIX
    //TODO: sSetValidName
#endif

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sToWin(
    const std::tstring_t &csFilePath,
    const bool           cbIsSlashAtEnd
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    std::tstring_t sRes;

    if (true == cbIsSlashAtEnd) {
        sRes = sSlashAppend(csFilePath);
    } else {
        sRes = sSlashRemove(csFilePath);
    }

    sRes = CxString::sReplaceAll(sRes, CxConst::xUNIX_SLASH, CxConst::xWIN_SLASH);

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sToUnix(
    const std::tstring_t &csFilePath,
    const bool            cbIsSlashAtEnd
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    std::tstring_t sRes;

    if (true == cbIsSlashAtEnd) {
        sRes = sSlashAppend(csFilePath);
    } else {
        sRes = sSlashRemove(csFilePath);
    }

    sRes = CxString::sReplaceAll(sRes, CxConst::xWIN_SLASH, CxConst::xUNIX_SLASH);

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sToCurrentOs(
    const std::tstring_t &csFilePath,
    const bool            cbIsSlashAtEnd
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    std::tstring_t sRes;

    if (true == cbIsSlashAtEnd) {
        sRes = sSlashAppend(csFilePath);
    } else {
        sRes = sSlashRemove(csFilePath);
    }

#if   xOS_ENV_WIN
    sRes = CxString::sReplaceAll(sRes, CxConst::xUNIX_SLASH, CxConst::xSLASH);
#elif xOS_ENV_UNIX
    sRes = CxString::sReplaceAll(sRes, CxConst::xWIN_SLASH,  CxConst::xSLASH);
#endif

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sGetAbsolute(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/

    std::tstring_t sRes;

#if xOS_ENV_WIN
    DWORD          ulRes = 0UL;
    std::tstring_t sBuff;

    ulRes = ::GetFullPathName(&csFilePath.at(0), 0, NULL, NULL);
    /*DEBUG*/xASSERT_RET(0UL != ulRes, std::tstring_t());

    sBuff.resize(ulRes);

    ulRes = ::GetFullPathName(&csFilePath.at(0), sBuff.size(), &sBuff.at(0), NULL);
    /*DEBUG*/xASSERT_RET(0UL != ulRes, std::tstring_t());

    sBuff.resize(ulRes);

    sRes = sBuff;
#elif xOS_ENV_UNIX
    std::tstring_t sBuff;

    sBuff.resize(xPATH_MAX);

    tchar_t *pszRes = ::realpath(&csFilePath.at(0), &sBuff.at(0));
    /*DEBUG*/xASSERT_RET(NULL != pszRes, std::tstring_t());

    sRes.assign(pszRes);
#endif

    /*DEBUG*/xASSERT_RET(false != bIsAbsolute(sRes), std::tstring_t());

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sGetShortName(
    const std::tstring_t &csFileName,
    const size_t          cuiMaxSize
)
{
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(), std::tstring_t());
    /*DEBUG*/xASSERT_RET(0 < cuiMaxSize,              std::tstring_t());

    std::tstring_t sRes;

    std::tstring_t sTildaDotExt;

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
/*static*/
std::tstring_t
CxPath::sGetShort(
    const std::tstring_t &csFilePath,
    const size_t          cuiMaxSize
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), std::tstring_t());
    /*DEBUG*/xASSERT_RET(0     <  cuiMaxSize,         std::tstring_t());

    // util fuction
    struct _SSlashes
    {
        static void
        vMake(std::tstring_t &cStr, size_t &uiNum) {
            size_t uiIndex = 0;

            for ( ; ; ) {
                size_t uiPos = cStr.find_first_of(CxConst::xWIN_SLASH + CxConst::xUNIX_SLASH);

                cStr.erase(0, uiPos + CxConst::xSLASH.size());

                xCHECK_DO(std::tstring_t::npos != uiPos,  ++ uiIndex);
                xCHECK_DO(uiIndex == uiNum && 0 != uiNum, break);
                xCHECK_DO(std::tstring_t::npos == uiPos,  break);
            }

            uiNum = uiIndex;
        }
    };


    std::tstring_t sRes  = csFilePath;
    std::tstring_t sPath = csFilePath;
    size_t         uiNum = 0;

    _SSlashes::vMake(sPath, uiNum);

    while (sRes.size() > cuiMaxSize && uiNum > 2) {
        sPath = sRes;

        size_t uiNumNew = uiNum / 2;

        _SSlashes::vMake(sPath, uiNumNew);

        sRes.erase(sRes.find(sPath), sPath.size());

        uiNumNew = 2;
        _SSlashes::vMake(sPath, uiNumNew);

        sRes.append(CxConst::x3DOT + CxConst::xSLASH + sPath);

        -- uiNum;
    }

    sRes = sToCurrentOs(sRes, false);

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sSlashAppend(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), std::tstring_t());

    return CxString::sTrimRightChars(csDirPath, CxConst::xSLASH).append(CxConst::xSLASH);
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxPath::sSlashRemove(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), std::tstring_t());

    return CxString::sTrimRightChars(csDirPath, CxConst::xSLASH);
}
//--------------------------------------------------------------------------
/*static*/
size_t
CxPath::uiGetMaxSize() {
    /*DEBUG*/

    size_t uiRes = 0;

#if xOS_ENV_WIN
    #if defined(MAX_PATH)
        uiRes = MAX_PATH;
    #else
        const size_t cuiDefaultSize = 260;

        uiRes = cuiDefaultSize;
    #endif
#elif xOS_ENV_UNIX
    #if defined(PATH_MAX)
        uiRes = PATH_MAX;
    #else
        const ulong_t culSavedError = 0UL;
        long_t        liRes         = - 1L;
        ulong_t       ulLastError   = 0UL;

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

#if xOS_ENV_WIN
    #if defined(FILENAME_MAX)
        uiRes = FILENAME_MAX;
    #else
        const size_t cuiDefaultSize = 260;

        uiRes = cuiDefaultSize;
    #endif
#elif xOS_ENV_UNIX
    #if defined(NAME_MAX)
        uiRes = NAME_MAX;
    #else
        const ulong_t culSavedError = 0UL;
        long_t        liRes         = - 1L;
        ulong_t       ulLastError   = 0UL;

        (void)CxLastError::bSet(culSavedError);

        liRes       = ::pathconf("/", _PC_NAME_MAX);
        ulLastError = CxLastError::ulGet();
        /*DEBUG*/xASSERT_RET(- 1L == liRes && 0UL != culSavedError, 0);

        if (- 1L == liRes && culSavedError == ulLastError) {
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
#if xOS_ENV_UNIX

/*static*/
std::tstring_t
CxPath::sGetProcValue(
    const std::tstring_t &csProcPath,   ///< file path to proc-file
    const std::tstring_t &csData        ///< target search data string
)
{
    // check for existance "/proc/" directory
    {
        bool bRes = false;

        bRes = CxDir::bIsExists(xT("/proc/"));
        xCHECK_MSG_RET(false == bRes, xT("Proc dir not mount"), std::tstring_t());

        bRes = CxDir::bIsEmpty(xT("/proc/"));
        xCHECK_MSG_RET(true == bRes, xT("Proc dir is empty"),  std::tstring_t());
    }


    std::tstring_t sRes;

    std::tifstream_t ifsStream(csProcPath.c_str());
    /*DEBUG*/xASSERT_RET(ifsStream,           std::tstring_t());
    /*DEBUG*/xASSERT_RET(!ifsStream.fail(),   std::tstring_t());
    /*DEBUG*/xASSERT_RET(ifsStream.good(),    std::tstring_t());
    /*DEBUG*/xASSERT_RET(ifsStream.is_open(), std::tstring_t());
    /*DEBUG*/xASSERT_RET(!ifsStream.eof(),    std::tstring_t());

    for ( ; !ifsStream.eof(); ) {
        std::tstring_t sLine;

        std::getline(ifsStream, sLine);

        // TODO: no case search
        size_t uiPos = sLine.find(csData);
        xCHECK_DO(std::tstring_t::npos == uiPos, continue);

        // parse value
        size_t uiDelimPos = sLine.find(xT(":"));
        /*DEBUG*/xASSERT_RET(std::string::npos != uiDelimPos, std::tstring_t());

        sRes = sLine.substr(uiDelimPos + 1);
        sRes = CxString::sTrimSpace(sRes);

        break;
    }

    return sRes;
}

#endif
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
