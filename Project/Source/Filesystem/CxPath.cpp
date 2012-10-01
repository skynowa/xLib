/**
 * \file  CxPath.cpp
 * \brief file system path
 */


#include <xLib/Filesystem/CxPath.h>

#include <xLib/Common/CxChar.h>
#include <xLib/Common/CxString.h>
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

/* static */
std::tstring_t
CxPath::sGetExe() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    // REVIEW: QueryFullProcessImageName on xOS_WIN_VER > xOS_WIN_S03

    sRv.resize(xPATH_MAX);

    DWORD dwStored = ::GetModuleFileName(NULL, &sRv.at(0), sRv.size());
    /*DEBUG*/xTEST_DIFF(0UL, dwStored);

    sRv.resize(dwStored);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        const std::tstring_t csProcFile = CxString::sFormat(xT("/proc/%ld/exe"), CxCurrentProcess::ulGetId());

        bool bRv = CxFile::bIsExists(csProcFile);
        xCHECK_RET(false == bRv, std::tstring_t());

        int iReaded = - 1;
        sRv.resize(xPATH_MAX);

        for ( ; ; ) {
            iReaded = ::readlink(csProcFile.c_str(), &sRv.at(0), sRv.size() * sizeof(std::tstring_t::value_type));
            /*DEBUG*/xTEST_DIFF(- 1, iReaded);

            xCHECK_DO(sRv.size() * sizeof(std::tstring_t::value_type) > static_cast<size_t>( iReaded ), break);

            sRv.resize(sRv.size() * 2);
        }

        sRv.resize(iReaded);
    #elif xOS_FREEBSD
        #if defined(KERN_PROC_PATHNAME)
            int aiMib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, - 1};

            tchar_t szBuff[PATH_MAX + 1] = {0};
            size_t  uiBuffSize           = sizeof(szBuff) - 1;

            int iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), szBuff, &uiBuffSize, NULL, 0U);
            /*DEBUG*/xTEST_DIFF(- 1, iRv);

            sRv.assign(szBuff);
        #else
            std::vec_tstring_t vsArgs;

            bool bRv = CxCommandLine::bGetArgs(&vsArgs);
            /*DEBUG*/xTEST_EQ(true, bRv,                       std::tstring_t());
            /*DEBUG*/xTEST_EQ(false, vsArgs.empty(),            std::tstring_t());
            /*DEBUG*/xTEST_EQ(false, bIsAbsolute(vsArgs.at(0)));

            sRv = sGetAbsolute(vsArgs.at(0));
        #endif
    #endif
#endif

    /*DEBUG*/xTEST_EQ(true, CxFile::bIsExists(sRv));

    return sRv;
}
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN
    extern "C" IMAGE_DOS_HEADER __ImageBase;
#elif xOS_ENV_UNIX
    static void vFunction() { ; }
#endif

/* static */
std::tstring_t
CxPath::sGetDll() {
    /*DEBUG*/

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv.resize(xPATH_MAX);

    DWORD ulStored = ::GetModuleFileName(reinterpret_cast<HINSTANCE>( &__ImageBase ), &sRv.at(0), sRv.size());
    /*DEBUG*/xTEST_DIFF(0UL, ulStored);

    sRv.resize(ulStored);
#elif xOS_ENV_UNIX
    Dl_info  diInfo        = {0};
    void    *fpProcAddress = (void *)vFunction;

    int iRv = ::dladdr(fpProcAddress, &diInfo);
    /*DEBUF*/xTEST_LESS(0, iRv);

    sRv = sGetAbsolute(diInfo.dli_fname);
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sGetExeDir() {
    return sGetDir(sGetExe());
}
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

/* static */
std::tstring_t
CxPath::sGetDrive(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

    size_t uiDriveDelimPos = csFilePath.find(CxConst::xCOLON);
    /*DEBUG*/xTEST_DIFF(std::tstring_t::npos, uiDriveDelimPos);
    /*DEBUG*/xTEST_EQ(1U, uiDriveDelimPos);

    return csFilePath.substr(0, uiDriveDelimPos + CxConst::xCOLON.size());
}

#endif
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sGetDir(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    xCHECK_RET(std::tstring_t::npos == uiSlashPos, std::tstring_t());

    return csFilePath.substr(0, uiSlashPos);
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sGetDirName(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

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
/* static */
std::tstring_t
CxPath::sGetFileName(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    xCHECK_RET(std::tstring_t::npos == uiSlashPos, csFilePath);

    return csFilePath.substr(uiSlashPos + CxConst::xSLASH.size(), csFilePath.size());
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sGetFileBaseName(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    size_t uiDotPos   = csFilePath.rfind(CxConst::xDOT,   csFilePath.size());

    return CxString::sCut(csFilePath, uiSlashPos + CxConst::xSLASH.size(), uiDotPos);
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sGetExt(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

    size_t uiDotPos   = csFilePath.rfind(CxConst::xDOT,   csFilePath.size());
    xCHECK_RET(std::tstring_t::npos == uiDotPos, std::tstring_t());

    size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    //if dot after slash - extension not exists
    xCHECK_RET(uiDotPos < uiSlashPos && std::tstring_t::npos != uiSlashPos, std::tstring_t());

    return csFilePath.substr(uiDotPos + CxConst::xDOT.size());
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sGetStandartExt(
    const ExStandartExt cseFileExt
)
{
    std::tstring_t sRv;

    switch (cseFileExt) {
    #if   xOS_ENV_WIN
        case seExe: { sRv = xT("exe"); }   break;
        case seDll: { sRv = xT("dll"); }   break;
        case seLib: { sRv = xT("lib"); }   break;
        case seObj: { sRv = xT("obj"); }   break;
        case seBat: { sRv = xT("bat"); }   break;
    #elif xOS_ENV_UNIX
        case seExe: { sRv = xT("");    }   break;
        case seDll: { sRv = xT("so");  }   break;
        case seLib: { sRv = xT("a");   }   break;
        case seObj: { sRv = xT("o");   }   break;
        case seBat: { sRv = xT("sh");  }   break;
    #endif
        default:    { sRv = xT("");    }   break;
    }

    return sRv;
}
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

/* static */
std::tstring_t
CxPath::sSetDrive(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csDrivePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// csDrivePath

    std::tstring_t sRv(csFilePath);

    std::tstring_t sDrive = sGetDrive(sRv);
    /*DEBUG*/xTEST_EQ(false, sDrive.empty());

    size_t uiPos = sRv.find(sDrive);
    /*DEBUG*/xTEST_DIFF(std::tstring_t::npos, uiPos);

    return sRv.replace(uiPos, sDrive.size(), csDrivePath);
}

#endif
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sSetDir(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// csDirPath

    std::tstring_t sRv(csFilePath);

    std::tstring_t sDir = sGetDir(sRv);
    /*DEBUG*/xTEST_EQ(false, sDir.empty());

    size_t uiPos = sRv.find(sDir);
    /*DEBUG*/xTEST_DIFF(std::tstring_t::npos, uiPos);

    return sRv.replace(uiPos, sDir.size(), sSlashRemove(csDirPath));
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sSetFileName(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csFullName
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// csFullName

    std::tstring_t sRv(csFilePath);

    std::tstring_t sFullName = sGetFileName(sRv);
    /*DEBUG*/xTEST_EQ(false, sFullName.empty());

    size_t uiPos = sRv.rfind(sFullName);
    /*DEBUG*/xTEST_DIFF(std::tstring_t::npos, uiPos);

    return sRv.replace(uiPos, sFullName.size(), csFullName);
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sSetFileBaseName(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csName
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// csName

    std::tstring_t sRv(csFilePath);

    std::tstring_t sName = sGetFileBaseName(sRv);
    /*DEBUG*/xTEST_EQ(false, sName.empty());

    size_t uiPos = sRv.rfind(sName);
    /*DEBUG*/xTEST_DIFF(std::tstring_t::npos, uiPos);

    return sRv.replace(uiPos, sName.size(), csName);
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sSetExt(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csExt
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// csExt - n/a

    return sRemoveExt(csFilePath) + CxConst::xDOT + csExt;
}
//---------------------------------------------------------------------------


//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sRemoveExt(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

    size_t uiDotPos = csFilePath.rfind(CxConst::xDOT);

    return csFilePath.substr(0, uiDotPos);
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sRemoveExtIf(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csExt
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

    size_t uiExtPos = csFilePath.rfind(CxConst::xDOT + csExt);
    xCHECK_RET(std::tstring_t::npos == uiExtPos, csFilePath);

    size_t uiDotPos = csFilePath.rfind(CxConst::xDOT);
    /*DEBUG*/xTEST_DIFF(std::tstring_t::npos, uiDotPos);

    return csFilePath.substr(0, uiDotPos);
}
//---------------------------------------------------------------------------
//TODO: bIsValid
/* static */
bool
CxPath::bIsValid(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/// csFileName - n/a

    bool bRv = false;

    //is empty
    bRv = csFilePath.empty();
    xCHECK_RET(true == bRv, false);

    //check for size
    bRv = (xPATH_MAX < csFilePath.size());
    xCHECK_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
//TODO: bIsNameValid
/* static */
bool
CxPath::bIsNameValid(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/// csFileName - n/a

    bool bRv = false;

    const std::tstring_t csFileName = CxPath::sGetFileName(csFilePath);

    //is empty
    bRv = csFileName.empty();
    xCHECK_RET(true == bRv, false);

    //check for name size
    bRv = (xNAME_MAX < csFileName.size());
    xCHECK_RET(true == bRv, false);

    //cm. sSetValidName

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxPath::bIsAbsolute(
    const std::tstring_t &csFilePath
)
{
    xCHECK_RET(true                  == csFilePath.empty(), false);
    xCHECK_RET(CxConst::xSLASH.at(0) == csFilePath.at(0),   true);

#if   xOS_ENV_WIN
    xCHECK_RET(1 == csFilePath.size(),                                                          false);
    xCHECK_RET(CxChar::bIsAlpha(csFilePath.at(0)) && CxConst::xCOLON.at(0) == csFilePath.at(1), true);
#else
    // n/a
#endif

    return false;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sSetValidName(
    const std::tstring_t &csFileName
)
{
    /*DEBUG*/// n/a

    std::tstring_t sRv(csFileName);

    //-------------------------------------
    //is empty
    xCHECK_RET(true == sRv.empty(), std::tstring_t());

    //-------------------------------------
    //check for name size
    xCHECK_RET(xNAME_MAX <= sRv.size(), std::tstring_t());

#if   xOS_ENV_WIN
    //-------------------------------------
    //if only dots
    size_t uiDotPos = sRv.find_first_not_of(CxConst::xDOT);
    xCHECK_RET(std::tstring_t::npos == uiDotPos, std::tstring_t());

    //-------------------------------------
    //if the first character is a dot, the filename is okay or space
    xCHECK_RET(CxConst::xDOT.at(0) == sRv.at(0), std::tstring_t());

    //-------------------------------------
    //A device name was used. You can pass this value to GetIsValidFileNameErrStr to obtain a pointer to the name of this device.


    //-------------------------------------
    //All characters greater than ASCII 31 to be used except for the following:    "/*:<>?\|
    const std::tstring_t csFatalChars = xT("\\/:*<>|?\"\t\n\r");

    size_t uiFound = sRv.find_first_of(csFatalChars);
    while (std::tstring_t::npos != uiFound) {
        sRv.erase(uiFound, 1);
        uiFound = sRv.find_first_of(csFatalChars, uiFound);
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

    std::tstring_t sFileName = sRemoveExt(sRv);

    for (size_t i = 0; i < xARRAY_SIZE(csReservedNames); ++ i) {
        xCHECK_RET(true == CxString::bCompareNoCase(sFileName, csReservedNames[i]), std::tstring_t());
    }
#elif xOS_ENV_UNIX
    //TODO: sSetValidName
#endif

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sToWin(
    const std::tstring_t &csFilePath,
    const bool           cbIsSlashAtEnd
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    std::tstring_t sRv;

    if (true == cbIsSlashAtEnd) {
        sRv = sSlashAppend(csFilePath);
    } else {
        sRv = sSlashRemove(csFilePath);
    }

    sRv = CxString::sReplaceAll(sRv, CxConst::xUNIX_SLASH, CxConst::xWIN_SLASH);

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sToUnix(
    const std::tstring_t &csFilePath,
    const bool            cbIsSlashAtEnd
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    std::tstring_t sRv;

    if (true == cbIsSlashAtEnd) {
        sRv = sSlashAppend(csFilePath);
    } else {
        sRv = sSlashRemove(csFilePath);
    }

    sRv = CxString::sReplaceAll(sRv, CxConst::xWIN_SLASH, CxConst::xUNIX_SLASH);

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sToCurrentOs(
    const std::tstring_t &csFilePath,
    const bool            cbIsSlashAtEnd
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    std::tstring_t sRv;

    if (true == cbIsSlashAtEnd) {
        sRv = sSlashAppend(csFilePath);
    } else {
        sRv = sSlashRemove(csFilePath);
    }

#if   xOS_ENV_WIN
    sRv = CxString::sReplaceAll(sRv, CxConst::xUNIX_SLASH, CxConst::xSLASH);
#elif xOS_ENV_UNIX
    sRv = CxString::sReplaceAll(sRv, CxConst::xWIN_SLASH,  CxConst::xSLASH);
#endif

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sGetAbsolute(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    DWORD          ulRv = 0UL;
    std::tstring_t sBuff;

    ulRv = ::GetFullPathName(&csFilePath.at(0), 0, NULL, NULL);
    /*DEBUG*/xTEST_DIFF(0UL, ulRv);

    sBuff.resize(ulRv);

    ulRv = ::GetFullPathName(&csFilePath.at(0), sBuff.size(), &sBuff.at(0), NULL);
    /*DEBUG*/xTEST_DIFF(0UL, ulRv);

    sBuff.resize(ulRv);

    sRv = sBuff;
#elif xOS_ENV_UNIX
    std::tstring_t sBuff;

    sBuff.resize(xPATH_MAX);

    tchar_t *pszRes = ::realpath(&csFilePath.at(0), &sBuff.at(0));
    /*DEBUG*/xTEST_PTR(pszRes);

    sRv.assign(pszRes);
#endif

    /*DEBUG*/xTEST_EQ(true, bIsAbsolute(sRv));

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sGetShortName(
    const std::tstring_t &csFileName,
    const size_t          cuiMaxSize
)
{
    /*DEBUG*/xTEST_EQ(false, csFileName.empty());
    /*DEBUG*/xTEST_LESS(size_t(0), cuiMaxSize);

    std::tstring_t sRv;

    std::tstring_t sTildaDotExt;

    //if file extension exists or not
    if (true == sGetExt(csFileName).empty()) {
        sTildaDotExt = xT("~");
    } else {
        sTildaDotExt = xT("~") + CxConst::xDOT + sGetExt(csFileName);
    }

    if (csFileName.size() > cuiMaxSize) {
        if (cuiMaxSize < sTildaDotExt.size()) {
            sRv = csFileName.substr(0, cuiMaxSize);
        } else {
            sRv = csFileName.substr(0, cuiMaxSize - sTildaDotExt.size()) + sTildaDotExt;
        }
    } else {
        sRv = csFileName;
    }

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sGetShort(
    const std::tstring_t &csFilePath,
    const size_t          cuiMaxSize
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_LESS(size_t(0), cuiMaxSize);

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


    std::tstring_t sRv  = csFilePath;
    std::tstring_t sPath = csFilePath;
    size_t         uiNum = 0;

    _SSlashes::vMake(sPath, uiNum);

    while (sRv.size() > cuiMaxSize && uiNum > 2) {
        sPath = sRv;

        size_t uiNumNew = uiNum / 2;

        _SSlashes::vMake(sPath, uiNumNew);

        sRv.erase(sRv.find(sPath), sPath.size());

        uiNumNew = 2;
        _SSlashes::vMake(sPath, uiNumNew);

        sRv.append(CxConst::x3DOT + CxConst::xSLASH + sPath);

        -- uiNum;
    }

    sRv = sToCurrentOs(sRv, false);

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sSlashAppend(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());

    return CxString::sTrimRightChars(csDirPath, CxConst::xSLASH).append(CxConst::xSLASH);
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sSlashRemove(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());

    return CxString::sTrimRightChars(csDirPath, CxConst::xSLASH);
}
//--------------------------------------------------------------------------
/* static */
size_t
CxPath::uiGetMaxSize() {
    /*DEBUG*/

    size_t uiRes = 0;

#if   xOS_ENV_WIN
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
        long_t        liRv         = - 1L;
        ulong_t       ulLastError   = 0UL;

        (void)CxLastError::bSet(culSavedError);

        liRv       = ::pathconf("/", _PC_PATH_MAX);
        ulLastError = CxLastError::ulGet();
        /*DEBUG*/xASSERT_RET(- 1L == liRv && 0UL != culSavedError, 0);

        if (- 1L == liRv && culSavedError == ulLastError) {
            //system does not have a limit for the requested resource
            const size_t cuiDefaultSize = 1024;

            uiRes = cuiDefaultSize;
        } else {
            //relative root
            uiRes = static_cast<size_t>( liRv + 1 );
        }
    #endif
#endif

    return uiRes;
}
//---------------------------------------------------------------------------
/* static */
size_t
CxPath::uiGetNameMaxSize() {
    /*DEBUG*/

    size_t uiRes = 0;

#if   xOS_ENV_WIN
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
        long_t        liRv         = - 1L;
        ulong_t       ulLastError   = 0UL;

        (void)CxLastError::bSet(culSavedError);

        liRv       = ::pathconf("/", _PC_NAME_MAX);
        ulLastError = CxLastError::ulGet();
        /*DEBUG*/xASSERT_RET(- 1L == liRv && 0UL != culSavedError, 0);

        if (- 1L == liRv && culSavedError == ulLastError) {
            //system does not have a limit for the requested resource
            const size_t cuiDefaultSize = 1024;

            uiRes = cuiDefaultSize;
        } else {
            uiRes = static_cast<size_t>( liRv );
        }
    #endif
#endif

    return uiRes;
}
//---------------------------------------------------------------------------
#if xOS_ENV_UNIX

/* static */
std::tstring_t
CxPath::sGetProcValue(
    const std::tstring_t &csProcPath,   ///< file path to proc-file
    const std::tstring_t &csData        ///< target search data string
)
{
    // check for existance "/proc/" directory
    {
        bool bRv = false;

        bRv = CxDir::bIsExists(xT("/proc"));
        xCHECK_DO(false == bRv,
                  CxTracer::vWrite(xT("::: xLib: warning (/proc dir not mount) :::")); return std::tstring_t());

        bRv = CxDir::bIsEmpty(xT("/proc"));
        xCHECK_DO(true == bRv,
                  CxTracer::vWrite(xT("::: xLib: warning (/proc dir is empty) :::"));  return std::tstring_t());
    }


    std::tstring_t sRv;

    std::tifstream_t ifsStream(csProcPath.c_str());
    /*DEBUG*/xTEST_EQ(true,  !! ifsStream);
    /*DEBUG*/xTEST_EQ(false, ifsStream.fail());
    /*DEBUG*/xTEST_EQ(true,  ifsStream.good());
    /*DEBUG*/xTEST_EQ(true,  ifsStream.is_open());
    /*DEBUG*/xTEST_EQ(false, ifsStream.eof());

    for ( ; !ifsStream.eof(); ) {
        std::tstring_t sLine;

        std::getline(ifsStream, sLine);

        // TODO: no case search
        size_t uiPos = sLine.find(csData);
        xCHECK_DO(std::tstring_t::npos == uiPos, continue);

        // parse value
        size_t uiDelimPos = sLine.find(xT(":"));
        /*DEBUG*/xTEST_DIFF(std::string::npos, uiDelimPos);

        sRv = sLine.substr(uiDelimPos + 1);
        sRv = CxString::sTrimSpace(sRv);

        break;
    }

    return sRv;
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
/* virtual */
CxPath::~CxPath() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
