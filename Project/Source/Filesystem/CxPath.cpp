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
CxPath::CxPath(
    const std::tstring_t &a_csFilePath
) :
    _m_sFilePath(a_csFilePath)
{
    xTEST_EQ(false, _m_sFilePath.empty());
}
//---------------------------------------------------------------------------
/* virtual */
CxPath::~CxPath() {

}
//---------------------------------------------------------------------------
const std::tstring_t &
CxPath::sFilePath() const {
    xTEST_EQ(false, _m_sFilePath.empty());

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
// FAQ: http://www.cplusplus.com/forum/general/11104/
//      http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
//      http://libsylph.sourceforge.net/wiki/Full_path_to_binary
//      http://h21007.www2.hp.com/portal/site/dspp/menuitem.863c3e4cbcdc3f3515b49c108973a801?ciid=88086d6e1de021106d6e1de02110275d6e10RCRD

/* static */
std::tstring_t
CxPath::sExe() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    // REVIEW: QueryFullProcessImageName on xOS_WIN_VER > xOS_WIN_S03

    sRv.resize(xPATH_MAX);

    DWORD dwStored = ::GetModuleFileName(NULL, &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(0UL, dwStored);

    sRv.resize(dwStored);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        const std::tstring_t csProcFile = CxString::format(xT("/proc/%ld/exe"), CxCurrentProcess::ulId());

        bool bRv = CxFile::bIsExists(csProcFile);
        xCHECK_RET(false == bRv, std::tstring_t());

        int iReaded = - 1;
        sRv.resize(xPATH_MAX);

        xFOREVER {
            iReaded = ::readlink(csProcFile.c_str(), &sRv.at(0), sRv.size() * sizeof(std::tstring_t::value_type));
            xTEST_DIFF(- 1, iReaded);

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
            xTEST_DIFF(- 1, iRv);

            sRv.assign(szBuff);
        #else
            std::vec_tstring_t vsArgs;

            bool bRv = CxCommandLine::bGetArgs(&vsArgs);
            xTEST_EQ(true,  bRv);
            xTEST_EQ(false, vsArgs.empty());
            xTEST_EQ(false, bIsAbsolute(vsArgs.at(0)));

            sRv = sGetAbsolute(vsArgs.at(0));
        #endif
    #endif
#endif

    xTEST_EQ(true, CxFile::bIsExists(sRv));

    return sRv;
}
//---------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

#if   xOS_ENV_WIN
    extern "C" IMAGE_DOS_HEADER __ImageBase;
#elif xOS_ENV_UNIX
    static void vFunction() { ; }
#endif

xNAMESPACE_ANONYM_END

/* static */
std::tstring_t
CxPath::sDll() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv.resize(xPATH_MAX);

    DWORD dwStored = ::GetModuleFileName(
                            reinterpret_cast<HINSTANCE>( &__ImageBase ),
                            &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(0UL, dwStored);

    sRv.resize(dwStored);
#elif xOS_ENV_UNIX
    Dl_info     diInfo        = {0};
    const void *fpProcAddress = reinterpret_cast<const void *>( vFunction );

    int iRv = ::dladdr(fpProcAddress, &diInfo);
    /*DEBUF*/xTEST_LESS(0, iRv);

    sRv = CxPath(diInfo.dli_fname).sAbsolute();
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sExeDir() {
    return CxPath(sExe()).sDir();
}
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

std::tstring_t
CxPath::sDrive() const {
    size_t uiDriveDelimPos = sFilePath().find(CxConst::xCOLON);
    xTEST_DIFF(std::tstring_t::npos, uiDriveDelimPos);
    xTEST_EQ(size_t(1), uiDriveDelimPos);

    return sFilePath().substr(0, uiDriveDelimPos + CxConst::xCOLON.size());
}

#endif
//--------------------------------------------------------------------------
std::tstring_t
CxPath::sDir() const {
    size_t uiSlashPos = sFilePath().rfind(CxConst::xSLASH, sFilePath().size());
    xCHECK_RET(std::tstring_t::npos == uiSlashPos, std::tstring_t());

    return sFilePath().substr(0, uiSlashPos);
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::sDirName() const {
    size_t uiSlashPos2 = sFilePath().rfind(CxConst::xSLASH);
    xCHECK_RET(std::tstring_t::npos == uiSlashPos2, std::tstring_t());

    size_t uiSlashPos1 = sFilePath().rfind(CxConst::xSLASH, uiSlashPos2 - 1);
    if (std::tstring_t::npos == uiSlashPos1) {
        return sFilePath().substr(0, uiSlashPos2);
    } else {
        return sFilePath().substr(uiSlashPos1 + 1, uiSlashPos2 - uiSlashPos1 - 1);
    }
}
//---------------------------------------------------------------------------
std::tstring_t
CxPath::sFileName() const {
    size_t uiSlashPos = sFilePath().rfind(CxConst::xSLASH, sFilePath().size());
    xCHECK_RET(std::tstring_t::npos == uiSlashPos, sFilePath());

    return sFilePath().substr(uiSlashPos + CxConst::xSLASH.size());
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::sFileBaseName() const {
    size_t uiSlashPos = sFilePath().rfind(CxConst::xSLASH, sFilePath().size());
    size_t uiDotPos   = sFilePath().rfind(CxConst::xDOT,   sFilePath().size());

    return CxString::cut(sFilePath(), uiSlashPos + CxConst::xSLASH.size(), uiDotPos);
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::sExt() const {
    size_t uiDotPos   = sFilePath().rfind(CxConst::xDOT,   sFilePath().size());
    xCHECK_RET(std::tstring_t::npos == uiDotPos, std::tstring_t());

    size_t uiSlashPos = sFilePath().rfind(CxConst::xSLASH, sFilePath().size());
    // if dot after slash - extension not exists
    xCHECK_RET(uiDotPos < uiSlashPos && std::tstring_t::npos != uiSlashPos, std::tstring_t());

    return sFilePath().substr(uiDotPos + CxConst::xDOT.size());
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sStandartExt(
    const ExStandartExt &a_cseFileExt
)
{
    std::tstring_t sRv;

    switch (a_cseFileExt) {
    #if   xOS_ENV_WIN
        case seExe:   { sRv = xT("exe"); }   break;
        case seDll:   { sRv = xT("dll"); }   break;
        case seLib:   { sRv = xT("lib"); }   break;
        case seObj:   { sRv = xT("obj"); }   break;
        case seShell: { sRv = xT("bat"); }   break;
    #elif xOS_ENV_UNIX
        case seExe:   { sRv = xT("");    }   break;
        case seDll:   { sRv = xT("so");  }   break;
        case seLib:   { sRv = xT("a");   }   break;
        case seObj:   { sRv = xT("o");   }   break;
        case seShell: { sRv = xT("sh");  }   break;
    #endif
        default:      { sRv = xT("");    }   break;
    }

    return sRv;
}
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

std::tstring_t
CxPath::sSetDrive(
    const std::tstring_t &a_csDrivePath
)
{
    // csDrivePath

    std::tstring_t sRv(sFilePath());

    std::tstring_t sDriveStr = CxPath(sRv).sDrive();
    xTEST_EQ(false, sDriveStr.empty());

    size_t uiPos = sRv.find(sDriveStr);
    xTEST_DIFF(std::tstring_t::npos, uiPos);

    return sRv.replace(uiPos, sDriveStr.size(), a_csDrivePath);
}

#endif
//---------------------------------------------------------------------------
std::tstring_t
CxPath::sSetDir(
    const std::tstring_t &a_csDirPath
)
{
    // csDirPath

    std::tstring_t sRv(sFilePath());

    std::tstring_t sDirStr = CxPath(sRv).sDir();
    xTEST_EQ(false, sDirStr.empty());

    size_t uiPos = sRv.find(sDirStr);
    xTEST_DIFF(std::tstring_t::npos, uiPos);

    return sRv.replace(uiPos, sDirStr.size(), CxPath(a_csDirPath).sSlashRemove());
}
//---------------------------------------------------------------------------
std::tstring_t
CxPath::sSetFileName(
    const std::tstring_t &a_csFullName
)
{
    // csFullName

    std::tstring_t sRv(sFilePath());

    std::tstring_t sFullName = CxPath(sRv).sFileName();
    xTEST_EQ(false, sFullName.empty());

    size_t uiPos = sRv.rfind(sFullName);
    xTEST_DIFF(std::tstring_t::npos, uiPos);

    return sRv.replace(uiPos, sFullName.size(), a_csFullName);
}
//---------------------------------------------------------------------------
std::tstring_t
CxPath::sSetFileBaseName(
    const std::tstring_t &a_csName
)
{
    // csName

    std::tstring_t sRv(sFilePath());

    std::tstring_t sName = CxPath(sRv).sFileBaseName();
    xTEST_EQ(false, sName.empty());

    size_t uiPos = sRv.rfind(sName);
    xTEST_DIFF(std::tstring_t::npos, uiPos);

    return sRv.replace(uiPos, sName.size(), a_csName);
}
//---------------------------------------------------------------------------
std::tstring_t
CxPath::sSetExt(
    const std::tstring_t &a_csExt
)
{
    xTEST_NA(a_csExt);

    return sRemoveExt() + CxConst::xDOT + a_csExt;
}
//---------------------------------------------------------------------------


//--------------------------------------------------------------------------
std::tstring_t
CxPath::sRemoveExt() {
    size_t uiDotPos = sFilePath().rfind(CxConst::xDOT);

    return sFilePath().substr(0, uiDotPos);
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::sRemoveExtIf(
    const std::tstring_t &a_csExt
)
{
    size_t uiExtPos = sFilePath().rfind(CxConst::xDOT + a_csExt);
    xCHECK_RET(std::tstring_t::npos == uiExtPos, sFilePath());

    size_t uiDotPos = sFilePath().rfind(CxConst::xDOT);
    xTEST_DIFF(std::tstring_t::npos, uiDotPos);

    return sFilePath().substr(0, uiDotPos);
}
//---------------------------------------------------------------------------
/* static */
bool
CxPath::bIsValid(
    const std::tstring_t &a_csFilePath
)
{
    xTEST_NA(a_csFilePath);

    bool bRv = false;

    // is empty
    bRv = a_csFilePath.empty();
    xCHECK_RET(true == bRv, false);

    // check for size
    bRv = (xPATH_MAX < a_csFilePath.size());
    xCHECK_RET(true == bRv, false);

    // TODO: bIsValid

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxPath::bIsNameValid(
    const std::tstring_t &a_csFileName
)
{
    xTEST_NA(a_csFilePath);

    bool bRv = false;

    //-------------------------------------
    // check: empty name
    {
        bRv = a_csFileName.empty();
        xCHECK_RET(true == bRv, false);
    }

    //-------------------------------------
    // check: name size
    {
        bRv = (xNAME_MAX < a_csFileName.size());
        xCHECK_RET(true == bRv, false);
    }

#if   xOS_ENV_WIN
    // MSDN: http://msdn.microsoft.com/en-us/library/windows/desktop/aa365247(v=vs.85).aspx
    // FAQ:  Boost Path Name Portability Guide

    //-------------------------------------
    // MSDN: Do not end a file or directory name with a space or a period.
    // Although the underlying file system may support such names,
    // the Windows shell and user interface does not.
    // However, it is acceptable to specify a period
    // as the first character of a name. For example, ".temp".
    {
        const tchar_t cchBegin = *a_csFileName.begin();
        const tchar_t cchEnd   = *(a_csFileName.end() - 1);

        // space
        bRv = (CxConst::xSPACE.at(0) == cchBegin);
        xCHECK_RET(true == bRv, false);

        bRv = (CxConst::xSPACE.at(0) == cchEnd);
        xCHECK_RET(true == bRv, false);

        // dot
        bRv = (CxConst::xDOT.at(0)   == cchBegin);
        xCHECK_RET(true == bRv, false);

        bRv = (CxConst::xDOT.at(0)   == cchEnd);
        xCHECK_RET(true == bRv, false);
    }

    //-------------------------------------
    // check: excepted chars
    // < (less than)
    // > (greater than)
    // : (colon)
    // " (double quote)
    // / (forward slash)
    // \ (backslash)
    // | (vertical bar or pipe)
    // ? (question mark)
    // * (asterisk)
    {
        const std::tstring_t csExceptedChars = xT("<>:\"/\\|?*");

        size_t uiPos = a_csFileName.find_first_of(csExceptedChars);
        bRv = (std::tstring_t::npos != uiPos);
        xCHECK_RET(true == bRv, false);
    }

    //-------------------------------------
    // check: control chars
    // MAN: For the standard ASCII character set (used by the "C" locale),
    // control characters are those between ASCII codes 0x00 (NUL) and 0x1f (US), plus 0x7f (DEL).
    {
        struct _SNested {
            static bool
            bIsCharControl(const std::tstring_t::value_type &cchChat) {
                return CxChar::isControl(cchChat);
            }
        };

        std::tstring_t::const_iterator cit;

        cit = std::find_if(a_csFileName.begin(), a_csFileName.end(), _SNested::bIsCharControl);
        bRv = (cit != a_csFileName.end());
        xCHECK_RET(true == bRv, false);
    }

    //-------------------------------------
    // check: device names
    // MSDN: Do not use the following reserved names for the name of a file:
    // CON, PRN, AUX, NUL, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8,
    // COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, and LPT9.
    // Also avoid these names followed immediately by an extension;
    // for example, NUL.txt is not recommended.
    {
        const std::tstring_t casReservedNames[] = {
            xT("CON"),  xT("PRN"),  xT("AUX"),  xT("NUL"),
            xT("COM0"), xT("COM1"), xT("COM2"), xT("COM3"), xT("COM4"),
            xT("COM5"), xT("COM6"), xT("COM7"), xT("COM8"), xT("COM9"),
            xT("LPT0"), xT("LPT1"), xT("LPT2"), xT("LPT3"), xT("LPT4"),
            xT("LPT5"), xT("LPT6"), xT("LPT7"), xT("LPT8"), xT("LPT9"),
            xT("CLOCK$")
        };

        const std::tstring_t csBaseFileName = CxPath(a_csFileName).sRemoveExt();

        for (size_t i = 0; i < xARRAY_SIZE(casReservedNames); ++ i) {
            bRv = CxString::compareNoCase(csBaseFileName, casReservedNames[i]);
            xCHECK_RET(true == bRv, false);
        }
    }
#elif xOS_ENV_UNIX
    //-------------------------------------
    // check: excepted chars
    // /  (forward slash)
    // \0 (NULL character)

    {
        std::tstring_t sExceptedChars;
        sExceptedChars.push_back(xT('/'));
        sExceptedChars.push_back(xT('\0'));
        xTEST_EQ(size_t(2), sExceptedChars.size());

        size_t uiPos = a_csFileName.find_first_of(sExceptedChars);
        bRv = (std::tstring_t::npos != uiPos);
        xCHECK_RET(true == bRv, false);
    }
#elif xOS_ENV_MAC
    //-------------------------------------
    // check: excepted chars
    // / (forward slash)
    // : (colon)

    {
        const std::tstring_t csExceptedChars = xT("/:");

        size_t uiPos = a_csFileName.find_first_of(csExceptedChars);
        bRv = (std::tstring_t::npos != uiPos);
        xCHECK_RET(true == bRv, false);
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxPath::bIsAbsolute() const {
    xCHECK_RET(true                  == sFilePath().empty(), false);
    xCHECK_RET(CxConst::xSLASH.at(0) == sFilePath().at(0),   true);

#if   xOS_ENV_WIN
    xCHECK_RET(1 == sFilePath().size(),                                                           false);
    xCHECK_RET(CxChar::isAlpha(sFilePath().at(0)) && CxConst::xCOLON.at(0) == sFilePath().at(1), true);
#elif xOS_ENV_UNIX
    xNA;
#endif

    return false;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sSetNameValid(
    const std::tstring_t &a_csFileName
)
{
    xTEST_NA(a_csFileName);

    std::tstring_t sRv(a_csFileName);
    bool           bRv = false;

    //-------------------------------------
    // check: empty name
    {
        bRv = sRv.empty();
        if (true == bRv) {
            return std::tstring_t();
        }
    }

    //-------------------------------------
    // check: name size
    {
        bRv = (xNAME_MAX < sRv.size());
        if (true == bRv) {
            sRv.resize(xNAME_MAX);
        }
    }

#if   xOS_ENV_WIN
    // MSDN: http://msdn.microsoft.com/en-us/library/windows/desktop/aa365247(v=vs.85).aspx
    // FAQ:  Boost Path Name Portability Guide

    //-------------------------------------
    // MSDN: Do not end a file or directory name with a space or a period.
    // Although the underlying file system may support such names,
    // the Windows shell and user interface does not.
    // However, it is acceptable to specify a period
    // as the first character of a name. For example, ".temp".
    {
        // skip checks, trim right now
        sRv = CxString::trimChars(sRv, CxConst::xSPACE + CxConst::xDOT);

        xCHECK_RET(true == sRv.empty(), std::tstring_t());
    }

    //-------------------------------------
    // check: excepted chars
    // < (less than)
    // > (greater than)
    // : (colon)
    // " (double quote)
    // / (forward slash)
    // \ (backslash)
    // | (vertical bar or pipe)
    // ? (question mark)
    // * (asterisk)
    {
        const std::tstring_t csExceptedChars = xT("<>:\"/\\|?*");

        size_t uiPos = sRv.find_first_of(csExceptedChars);
        bRv = (std::tstring_t::npos != uiPos);
        if (true == bRv) {
            while (std::tstring_t::npos != uiPos) {
                sRv.erase(uiPos, 1);
                uiPos = sRv.find_first_of(csExceptedChars, uiPos);
            }
        }

        xCHECK_RET(true == sRv.empty(), std::tstring_t());
    }

    //-------------------------------------
    // check: control chars
    // MAN: For the standard ASCII character set (used by the "C" locale),
    // control characters are those between ASCII codes 0x00 (NUL) and 0x1f (US), plus 0x7f (DEL).
    {
        struct _SNested {
            static bool
            bIsCharControl(const std::tstring_t::value_type &cchChat) {
                return CxChar::isControl(cchChat);
            }
        };

        std::tstring_t::const_iterator cit;

        cit = std::find_if(sRv.begin(), sRv.end(), _SNested::bIsCharControl);
        bRv = (cit != sRv.end());
        if (true == bRv) {
            std::tstring_t::iterator itNewEnd;

            itNewEnd = std::remove_if(sRv.begin(), sRv.end(), _SNested::bIsCharControl);
            sRv.erase(itNewEnd, sRv.end());
        }

        xCHECK_RET(true == sRv.empty(), std::tstring_t());
    }

    //-------------------------------------
    // check: device names
    // MSDN: Do not use the following reserved names for the name of a file:
    // CON, PRN, AUX, NUL, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8,
    // COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, and LPT9.
    // Also avoid these names followed immediately by an extension;
    // for example, NUL.txt is not recommended.
    {
        const std::tstring_t casReservedNames[] = {
            xT("CON"),  xT("PRN"),  xT("AUX"),  xT("NUL"),
            xT("COM0"), xT("COM1"), xT("COM2"), xT("COM3"), xT("COM4"),
            xT("COM5"), xT("COM6"), xT("COM7"), xT("COM8"), xT("COM9"),
            xT("LPT0"), xT("LPT1"), xT("LPT2"), xT("LPT3"), xT("LPT4"),
            xT("LPT5"), xT("LPT6"), xT("LPT7"), xT("LPT8"), xT("LPT9"),
            xT("CLOCK$")
        };

        const std::tstring_t csBaseFileName = CxPath(sRv).sRemoveExt();

        for (size_t i = 0; i < xARRAY_SIZE(casReservedNames); ++ i) {
            bRv = CxString::compareNoCase(csBaseFileName, casReservedNames[i]);
            if (true == bRv) {
                return std::tstring_t();
            }
        }

    }
#elif xOS_ENV_UNIX
    //-------------------------------------
    // check: excepted chars
    // /  (forward slash)
    // \0 (NULL character)

    {
        std::tstring_t sExceptedChars;
        sExceptedChars.push_back(xT('/'));
        sExceptedChars.push_back(xT('\0'));
        xTEST_EQ(size_t(2), sExceptedChars.size());

        size_t uiPos = a_csFileName.find_first_of(sExceptedChars);
        bRv = (std::tstring_t::npos != uiPos);
        if (true == bRv) {
            while (std::tstring_t::npos != uiPos) {
                sRv.erase(uiPos, 1);
                uiPos = sRv.find_first_of(sExceptedChars, uiPos);
            }
        }

        xCHECK_RET(true == sRv.empty(), std::tstring_t());
    }
#elif xOS_ENV_MAC
    //-------------------------------------
    // check: excepted chars
    // / (forward slash)
    // : (colon)

    {
        const std::tstring_t csExceptedChars = xT("/:");

        size_t uiPos = a_csFileName.find_first_of(csExceptedChars);
        bRv = (std::tstring_t::npos != uiPos);
        if (true == bRv) {
            while (std::tstring_t::npos != uiPos) {
                sRv.erase(uiPos, 1);
                uiPos = sRv.find_first_of(csExceptedChars, uiPos);
            }
        }

        xCHECK_RET(true == sRv.empty(), std::tstring_t());
    }
#endif

    return sRv;
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::sToWin(
    const bool &a_cbIsSlashAtEnd
) const
{
    xTEST_NA(a_cbIsSlashAtEnd);

    std::tstring_t sRv;

    if (true == a_cbIsSlashAtEnd) {
        sRv = sSlashAppend();
    } else {
        sRv = sSlashRemove();
    }

    sRv = CxString::replaceAll(sRv, CxConst::xUNIX_SLASH, CxConst::xWIN_SLASH);

    return sRv;
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::sToUnix(
    const bool &a_cbIsSlashAtEnd
)  const
{
    xTEST_NA(a_cbIsSlashAtEnd);

    std::tstring_t sRv;

    if (true == a_cbIsSlashAtEnd) {
        sRv = sSlashAppend();
    } else {
        sRv = sSlashRemove();
    }

    sRv = CxString::replaceAll(sRv, CxConst::xWIN_SLASH, CxConst::xUNIX_SLASH);

    return sRv;
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::sToNative(
    const bool &a_cbIsSlashAtEnd
) const
{
    xTEST_NA(a_cbIsSlashAtEnd);

    std::tstring_t sRv;

    if (true == a_cbIsSlashAtEnd) {
        sRv = sSlashAppend();
    } else {
        sRv = sSlashRemove();
    }

#if   xOS_ENV_WIN
    sRv = CxString::replaceAll(sRv, CxConst::xUNIX_SLASH, CxConst::xSLASH);
#elif xOS_ENV_UNIX
    sRv = CxString::replaceAll(sRv, CxConst::xWIN_SLASH,  CxConst::xSLASH);
#endif

    return sRv;
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::sAbsolute() const {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    DWORD          dwRv = 0UL;
    std::tstring_t sBuff;

    dwRv = ::GetFullPathName(&sFilePath().at(0), 0, NULL, NULL);
    xTEST_DIFF(0UL, dwRv);

    sBuff.resize(dwRv);

    dwRv = ::GetFullPathName(&sFilePath().at(0), static_cast<DWORD>( sBuff.size() ), &sBuff.at(0), NULL);
    xTEST_DIFF(0UL, dwRv);

    sBuff.resize(dwRv);

    sRv = sBuff;
#elif xOS_ENV_UNIX
    std::tstring_t sBuff;

    sBuff.resize(xPATH_MAX);

    tchar_t *pszRes = ::realpath(&sFilePath().at(0), &sBuff.at(0));
    xTEST_PTR(pszRes);

    sRv.assign(pszRes);
#endif

    xTEST_EQ(true, CxPath(sRv).bIsAbsolute());

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::sShortName(
    const std::tstring_t &a_csFileName,
    const size_t         &a_cuiMaxSize
)
{
    xTEST_EQ(false, a_csFileName.empty());
    xTEST_LESS(size_t(0), a_cuiMaxSize);

    std::tstring_t sRv;

    std::tstring_t sTildaDotExt;

    if (true == CxPath(a_csFileName).sExt().empty()) {
        sTildaDotExt = xT("~");
    } else {
        sTildaDotExt = xT("~") + CxConst::xDOT + CxPath(a_csFileName).sExt();
    }

    if (a_csFileName.size() > a_cuiMaxSize) {
        if (a_cuiMaxSize < sTildaDotExt.size()) {
            sRv = a_csFileName.substr(0, a_cuiMaxSize);
        } else {
            sRv = a_csFileName.substr(0, a_cuiMaxSize - sTildaDotExt.size()) + sTildaDotExt;
        }
    } else {
        sRv = a_csFileName;
    }

    return sRv;
}
//---------------------------------------------------------------------------
std::tstring_t
CxPath::sShort(
    const size_t &a_cuiMaxSize
) const
{
    xTEST_LESS(size_t(0), a_cuiMaxSize);

    // util function
    struct _SSlashes
    {
        static void
        vMake(std::tstring_t &a_cStr, size_t &a_uiNum) {
            size_t uiIndex = 0;

            xFOREVER {
                size_t uiPos = a_cStr.find_first_of(CxConst::xWIN_SLASH + CxConst::xUNIX_SLASH);

                a_cStr.erase(0, uiPos + CxConst::xSLASH.size());

                xCHECK_DO(std::tstring_t::npos != uiPos,  ++ uiIndex);
                xCHECK_DO(uiIndex == a_uiNum && 0 != a_uiNum, break);
                xCHECK_DO(std::tstring_t::npos == uiPos,      break);
            }

            a_uiNum = uiIndex;
        }
    };


    std::tstring_t sRv   = sFilePath();
    std::tstring_t sPath = sFilePath();
    size_t         uiNum = 0;

    _SSlashes::vMake(sPath, uiNum);

    while (sRv.size() > a_cuiMaxSize && uiNum > 2) {
        sPath = sRv;

        size_t uiNumNew = uiNum / 2;

        _SSlashes::vMake(sPath, uiNumNew);

        sRv.erase(sRv.find(sPath), sPath.size());

        uiNumNew = 2;
        _SSlashes::vMake(sPath, uiNumNew);

        sRv.append(CxConst::x3DOT + CxConst::xSLASH + sPath);

        -- uiNum;
    }

    sRv = CxPath(sRv).sToNative(false);

    return sRv;
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::sSlashAppend() const {
    return CxString::trimRightChars(sFilePath(), CxConst::xSLASH).append(CxConst::xSLASH);
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::sSlashRemove() const {
    return CxString::trimRightChars(sFilePath(), CxConst::xSLASH);
}
//--------------------------------------------------------------------------
/* static */
size_t
CxPath::uiMaxSize() {
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
        long_t        liRv          = - 1L;
        ulong_t       ulLastError   = 0UL;

        CxLastError::vSet(culSavedError);

        liRv       = ::pathconf("/", _PC_PATH_MAX);
        ulLastError = CxLastError::ulGet();
        xTEST_EQ(true, - 1L == liRv && 0UL != culSavedError);

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
CxPath::uiNameMaxSize() {
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
        long_t        liRv          = - 1L;
        ulong_t       ulLastError   = 0UL;

        CxLastError::vSet(culSavedError);

        liRv       = ::pathconf("/", _PC_NAME_MAX);
        ulLastError = CxLastError::ulGet();
        xTEST_EQ(true, - 1L == liRv && 0UL != culSavedError);

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
void
CxPath::vProc(
    const std::tstring_t &a_csProcPath,
    std::vec_tstring_t   *a_pvsData
)
{
    // check for existance "/proc" directory
    {
        bool bRv = false;

        CxDir drProc(xT("/proc"));

        bRv = drProc.bIsExists();
        xCHECK_DO(false == bRv,
                  CxTracer() << xT("::: xLib: warning (/proc dir not mount) :::"); return);

        bRv = drProc.bIsEmpty();
        xCHECK_DO(true == bRv,
                  CxTracer() << xT("::: xLib: warning (/proc dir is empty) :::");  return);
    }

    std::vec_tstring_t vsRv;

    std::tifstream_t ifsStream(a_csProcPath.c_str());
    xTEST_EQ(true,  !! ifsStream);
    xTEST_EQ(false, ifsStream.fail());
    xTEST_EQ(true,  ifsStream.good());
    xTEST_EQ(true,  ifsStream.is_open());
    xTEST_EQ(false, ifsStream.eof());

    for ( ; !ifsStream.eof(); ) {
        std::tstring_t sLine;

        std::getline(ifsStream, sLine);
        vsRv.push_back(sLine);
    }

    // out
    (*a_pvsData).swap(vsRv);
}

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_UNIX

/* static */
std::tstring_t
CxPath::sProcValue(
    const std::tstring_t &a_csProcPath,   ///< file path to proc-file
    const std::tstring_t &a_csData        ///< target search data string
)
{
    std::tstring_t     sRv;
    std::vec_tstring_t vsProcFile;

    vProc(a_csProcPath, &vsProcFile);

    xFOREACH_CONST (std::vec_tstring_t, it, vsProcFile) {
        // TODO: no case search
        size_t uiPos = (*it).find(a_csData);
        xCHECK_DO(std::tstring_t::npos == uiPos, continue);

        // parse value
        size_t uiDelimPos = (*it).find(xT(":"));
        xTEST_DIFF(std::string::npos, uiDelimPos);

        sRv = (*it).substr(uiDelimPos + 1);
        sRv = CxString::trimSpace(sRv);

        break;
    }

    return sRv;
}

#endif
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
