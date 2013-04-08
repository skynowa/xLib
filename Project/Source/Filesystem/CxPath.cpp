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

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxPath::CxPath(
    std::ctstring_t &a_csFilePath
) :
    _m_sFilePath(a_csFilePath)
{
    xTEST_EQ(false, _m_sFilePath.empty());
}
//------------------------------------------------------------------------------
/* virtual */
CxPath::~CxPath() {

}
//------------------------------------------------------------------------------
std::ctstring_t &
CxPath::filePath() const {
    xTEST_EQ(false, _m_sFilePath.empty());

    return _m_sFilePath;
}
//------------------------------------------------------------------------------
// FAQ: http://www.cplusplus.com/forum/general/11104/
//      http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
//      http://libsylph.sourceforge.net/wiki/Full_path_to_binary
//      http://h21007.www2.hp.com/portal/site/dspp/menuitem.863c3e4cbcdc3f3515b49c108973a801?ciid=88086d6e1de021106d6e1de02110275d6e10RCRD

/* static */
std::tstring_t
CxPath::exe() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    // REVIEW: QueryFullProcessImageName on xOS_WIN_VER > xOS_WIN_S03

    sRv.resize(xPATH_MAX);

    DWORD dwStored = ::GetModuleFileName(NULL, &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(0UL, dwStored);

    sRv.resize(dwStored);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        std::ctstring_t csProcFile = CxString::format(xT("/proc/%ld/exe"), CxCurrentProcess::id());

        bool_t bRv = CxFile::isExists(csProcFile);
        xCHECK_RET(!bRv, std::tstring_t());

        int_t iReaded = - 1;
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
            int_t aiMib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, - 1};

            tchar_t      szBuff[PATH_MAX + 1] = {0};
            std::csize_t uiBuffSize           = sizeof(szBuff) - 1;

            int_t iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), szBuff, &uiBuffSize, NULL, 0U);
            xTEST_DIFF(- 1, iRv);

            sRv.assign(szBuff);
        #else
            std::vec_tstring_t vsArgs;

            bool_t bRv = CxCommandLine::args(&vsArgs);
            xTEST_EQ(true,  bRv);
            xTEST_EQ(false, vsArgs.empty());
            xTEST_EQ(false, bIsAbsolute(vsArgs.at(0)));

            sRv = absolute(vsArgs.at(0));
        #endif
    #endif
#endif

    xTEST_EQ(true, CxFile::isExists(sRv));

    return sRv;
}
//------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

#if   xOS_ENV_WIN
    extern "C" IMAGE_DOS_HEADER __ImageBase;
#elif xOS_ENV_UNIX
    static void_t vFunction() { ; }
#endif

xNAMESPACE_ANONYM_END

/* static */
std::tstring_t
CxPath::dll() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv.resize(xPATH_MAX);

    DWORD dwStored = ::GetModuleFileName(
                            reinterpret_cast<HINSTANCE>( &__ImageBase ),
                            &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(0UL, dwStored);

    sRv.resize(dwStored);
#elif xOS_ENV_UNIX
    Dl_info  diInfo        = {0};
    cvoid_t *fpProcAddress = reinterpret_cast<cvoid_t *>( vFunction );

    int_t iRv = ::dladdr(fpProcAddress, &diInfo);
    /*DEBUF*/xTEST_LESS(0, iRv);

    sRv = CxPath(diInfo.dli_fname).absolute();
#endif

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::exeDir() {
    return CxPath(exe()).dir();
}
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

std::tstring_t
CxPath::drive() const {
    std::csize_t uiDriveDelimPos = filePath().find(CxConst::xCOLON);
    xTEST_DIFF(std::tstring_t::npos, uiDriveDelimPos);
    xTEST_EQ(size_t(1), uiDriveDelimPos);

    return filePath().substr(0, uiDriveDelimPos + CxConst::xCOLON.size());
}

#endif
//--------------------------------------------------------------------------
std::tstring_t
CxPath::dir() const {
    std::csize_t uiSlashPos = filePath().rfind(CxConst::xSLASH, filePath().size());
    xCHECK_RET(std::tstring_t::npos == uiSlashPos, std::tstring_t());

    return filePath().substr(0, uiSlashPos);
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::dirName() const {
    std::csize_t uiSlashPos2 = filePath().rfind(CxConst::xSLASH);
    xCHECK_RET(std::tstring_t::npos == uiSlashPos2, std::tstring_t());

    std::csize_t uiSlashPos1 = filePath().rfind(CxConst::xSLASH, uiSlashPos2 - 1);
    if (std::tstring_t::npos == uiSlashPos1) {
        return filePath().substr(0, uiSlashPos2);
    } else {
        return filePath().substr(uiSlashPos1 + 1, uiSlashPos2 - uiSlashPos1 - 1);
    }
}
//------------------------------------------------------------------------------
std::tstring_t
CxPath::fileName() const {
    std::csize_t uiSlashPos = filePath().rfind(CxConst::xSLASH, filePath().size());
    xCHECK_RET(std::tstring_t::npos == uiSlashPos, filePath());

    return filePath().substr(uiSlashPos + CxConst::xSLASH.size());
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::fileBaseName() const {
    std::csize_t uiSlashPos = filePath().rfind(CxConst::xSLASH, filePath().size());
    std::csize_t uiDotPos   = filePath().rfind(CxConst::xDOT,   filePath().size());

    return CxString::cut(filePath(), uiSlashPos + CxConst::xSLASH.size(), uiDotPos);
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::ext() const {
    std::csize_t uiDotPos   = filePath().rfind(CxConst::xDOT,   filePath().size());
    xCHECK_RET(std::tstring_t::npos == uiDotPos, std::tstring_t());

    std::csize_t uiSlashPos = filePath().rfind(CxConst::xSLASH, filePath().size());
    // if dot after slash - extension not exists
    xCHECK_RET(uiDotPos < uiSlashPos && std::tstring_t::npos != uiSlashPos, std::tstring_t());

    return filePath().substr(uiDotPos + CxConst::xDOT.size());
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::standartExt(
    const ExStandartExt &a_cseFileExt
)
{
    std::tstring_t sRv;

    switch (a_cseFileExt) {
    #if   xOS_ENV_WIN
        case seExe:
            sRv = xT("exe");
            break;
        case seDll:
            sRv = xT("dll");
            break;
        case seLib:
            sRv = xT("lib");
            break;
        case seObj:
            sRv = xT("obj");
            break;
        case seShell:
            sRv = xT("bat");
            break;
    #elif xOS_ENV_UNIX
        case seExe:
            sRv = xT("");
            break;
        case seDll:
            sRv = xT("so");
            break;
        case seLib:
            sRv = xT("a");
            break;
        case seObj:
            sRv = xT("o");
            break;
        case seShell:
            sRv = xT("sh");
            break;
    #endif

        default:
            sRv = xT("");
            break;
    }

    return sRv;
}
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

std::tstring_t
CxPath::setDrive(
    std::ctstring_t &a_csDrivePath
)
{
    // csDrivePath

    std::tstring_t sRv(filePath());

    std::tstring_t sDriveStr = CxPath(sRv).drive();
    xTEST_EQ(false, sDriveStr.empty());

    std::csize_t uiPos = sRv.find(sDriveStr);
    xTEST_DIFF(std::tstring_t::npos, uiPos);

    return sRv.replace(uiPos, sDriveStr.size(), a_csDrivePath);
}

#endif
//------------------------------------------------------------------------------
std::tstring_t
CxPath::setDir(
    std::ctstring_t &a_csDirPath
)
{
    // csDirPath

    std::tstring_t sRv(filePath());

    std::tstring_t sDirStr = CxPath(sRv).dir();
    xTEST_EQ(false, sDirStr.empty());

    std::csize_t uiPos = sRv.find(sDirStr);
    xTEST_DIFF(std::tstring_t::npos, uiPos);

    return sRv.replace(uiPos, sDirStr.size(), CxPath(a_csDirPath).slashRemove());
}
//------------------------------------------------------------------------------
std::tstring_t
CxPath::setFileName(
    std::ctstring_t &a_csFullName
)
{
    // csFullName

    std::tstring_t sRv(filePath());

    std::tstring_t sFullName = CxPath(sRv).fileName();
    xTEST_EQ(false, sFullName.empty());

    std::csize_t uiPos = sRv.rfind(sFullName);
    xTEST_DIFF(std::tstring_t::npos, uiPos);

    return sRv.replace(uiPos, sFullName.size(), a_csFullName);
}
//------------------------------------------------------------------------------
std::tstring_t
CxPath::setFileBaseName(
    std::ctstring_t &a_csName
)
{
    // csName

    std::tstring_t sRv(filePath());

    std::tstring_t sName = CxPath(sRv).fileBaseName();
    xTEST_EQ(false, sName.empty());

    std::csize_t uiPos = sRv.rfind(sName);
    xTEST_DIFF(std::tstring_t::npos, uiPos);

    return sRv.replace(uiPos, sName.size(), a_csName);
}
//------------------------------------------------------------------------------
std::tstring_t
CxPath::setExt(
    std::ctstring_t &a_csExt
)
{
    xTEST_NA(a_csExt);

    return removeExt() + CxConst::xDOT + a_csExt;
}
//------------------------------------------------------------------------------


//--------------------------------------------------------------------------
std::tstring_t
CxPath::removeExt() {
    std::csize_t uiDotPos = filePath().rfind(CxConst::xDOT);

    return filePath().substr(0, uiDotPos);
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::removeExtIf(
    std::ctstring_t &a_csExt
)
{
    std::csize_t uiExtPos = filePath().rfind(CxConst::xDOT + a_csExt);
    xCHECK_RET(std::tstring_t::npos == uiExtPos, filePath());

    std::csize_t uiDotPos = filePath().rfind(CxConst::xDOT);
    xTEST_DIFF(std::tstring_t::npos, uiDotPos);

    return filePath().substr(0, uiDotPos);
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxPath::isValid(
    std::ctstring_t &a_csFilePath
)
{
    xTEST_NA(a_csFilePath);

    bool_t bRv = false;

    // is empty
    bRv = a_csFilePath.empty();
    xCHECK_RET(bRv, false);

    // check for size
    bRv = (xPATH_MAX < a_csFilePath.size());
    xCHECK_RET(bRv, false);

    // TODO: bIsValid

    return true;
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxPath::isNameValid(
    std::ctstring_t &a_csFileName
)
{
    xTEST_NA(a_csFilePath);

    bool_t bRv = false;

    //-------------------------------------
    // check: empty name
    {
        bRv = a_csFileName.empty();
        xCHECK_RET(bRv, false);
    }

    //-------------------------------------
    // check: name size
    {
        bRv = (xNAME_MAX < a_csFileName.size());
        xCHECK_RET(bRv, false);
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
        ctchar_t cchBegin = *a_csFileName.begin();
        ctchar_t cchEnd   = *(a_csFileName.end() - 1);

        // space
        bRv = (CxConst::xSPACE.at(0) == cchBegin);
        xCHECK_RET(bRv, false);

        bRv = (CxConst::xSPACE.at(0) == cchEnd);
        xCHECK_RET(bRv, false);

        // dot
        bRv = (CxConst::xDOT.at(0)   == cchBegin);
        xCHECK_RET(bRv, false);

        bRv = (CxConst::xDOT.at(0)   == cchEnd);
        xCHECK_RET(bRv, false);
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
        std::ctstring_t csExceptedChars = xT("<>:\"/\\|?*");

        std::csize_t uiPos = a_csFileName.find_first_of(csExceptedChars);
        bRv = (std::tstring_t::npos != uiPos);
        xCHECK_RET(bRv, false);
    }

    //-------------------------------------
    // check: control chars
    // MAN: For the standard ASCII character set (used by the "C" locale),
    // control characters are those between ASCII codes 0x00 (NUL) and 0x1f (US), plus 0x7f (DEL).
    {
        struct _SIsCharControl {
            bool_t
            operator () (
                const std::tstring_t::value_type &a_cchChar
            ) const
            {
                return CxChar::isControl(a_cchChar);
            }
        };

        std::tstring_t::const_iterator cit;

        cit = std::find_if(a_csFileName.begin(), a_csFileName.end(), _SIsCharControl());
        bRv = (cit != a_csFileName.end());
        xCHECK_RET(bRv, false);
    }

    //-------------------------------------
    // check: device names
    // MSDN: Do not use the following reserved names for the name of a file:
    // CON, PRN, AUX, NUL, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8,
    // COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, and LPT9.
    // Also avoid these names followed immediately by an extension;
    // for example, NUL.txt is not recommended.
    {
        std::ctstring_t casReservedNames[] = {
            xT("CON"),  xT("PRN"),  xT("AUX"),  xT("NUL"),
            xT("COM0"), xT("COM1"), xT("COM2"), xT("COM3"), xT("COM4"),
            xT("COM5"), xT("COM6"), xT("COM7"), xT("COM8"), xT("COM9"),
            xT("LPT0"), xT("LPT1"), xT("LPT2"), xT("LPT3"), xT("LPT4"),
            xT("LPT5"), xT("LPT6"), xT("LPT7"), xT("LPT8"), xT("LPT9"),
            xT("CLOCK$")
        };

        std::ctstring_t csBaseFileName = CxPath(a_csFileName).removeExt();

        for (size_t i = 0; i < xARRAY_SIZE(casReservedNames); ++ i) {
            bRv = CxString::compareNoCase(csBaseFileName, casReservedNames[i]);
            xCHECK_RET(bRv, false);
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

        std::csize_t uiPos = a_csFileName.find_first_of(sExceptedChars);
        bRv = (std::tstring_t::npos != uiPos);
        xCHECK_RET(bRv, false);
    }
#elif xOS_ENV_MAC
    //-------------------------------------
    // check: excepted chars
    // / (forward slash)
    // : (colon)

    {
        std::ctstring_t csExceptedChars = xT("/:");

        std::csize_t uiPos = a_csFileName.find_first_of(csExceptedChars);
        bRv = (std::tstring_t::npos != uiPos);
        xCHECK_RET(bRv, false);
    }
#endif

    return true;
}
//------------------------------------------------------------------------------
bool_t
CxPath::isAbsolute() const {
    xCHECK_RET(true                  == filePath().empty(), false);
    xCHECK_RET(CxConst::xSLASH.at(0) == filePath().at(0),   true);

#if   xOS_ENV_WIN
    xCHECK_RET(1 == filePath().size(),                                                         false);
    xCHECK_RET(CxChar::isAlpha(filePath().at(0)) && CxConst::xCOLON.at(0) == filePath().at(1), true);
#elif xOS_ENV_UNIX
    xNA;
#endif

    return false;
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::setNameValid(
    std::ctstring_t &a_csFileName
)
{
    xTEST_NA(a_csFileName);

    std::tstring_t sRv(a_csFileName);
    bool_t           bRv = false;

    //-------------------------------------
    // check: empty name
    {
        bRv = sRv.empty();
        if (bRv) {
            return std::tstring_t();
        }
    }

    //-------------------------------------
    // check: name size
    {
        bRv = (xNAME_MAX < sRv.size());
        if (bRv) {
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

        xCHECK_RET(sRv.empty(), std::tstring_t());
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
        std::ctstring_t csExceptedChars = xT("<>:\"/\\|?*");

        std::size_t uiPos = sRv.find_first_of(csExceptedChars);
        bRv = (std::tstring_t::npos != uiPos);
        if (bRv) {
            while (std::tstring_t::npos != uiPos) {
                sRv.erase(uiPos, 1);
                uiPos = sRv.find_first_of(csExceptedChars, uiPos);
            }
        }

        xCHECK_RET(sRv.empty(), std::tstring_t());
    }

    //-------------------------------------
    // check: control chars
    // MAN: For the standard ASCII character set (used by the "C" locale),
    // control characters are those between ASCII codes 0x00 (NUL) and 0x1f (US), plus 0x7f (DEL).
    {
        struct _SIsCharControl {
            bool_t
            operator () (
                std::ctstring_t::value_type &a_cchChar
            ) const
            {
                return CxChar::isControl(a_cchChar);
            }
        };

        std::tstring_t::const_iterator cit;

        cit = std::find_if(sRv.begin(), sRv.end(), _SIsCharControl());
        bRv = (cit != sRv.end());
        if (bRv) {
            std::tstring_t::iterator itNewEnd;

            itNewEnd = std::remove_if(sRv.begin(), sRv.end(), _SIsCharControl());
            sRv.erase(itNewEnd, sRv.end());
        }

        xCHECK_RET(sRv.empty(), std::tstring_t());
    }

    //-------------------------------------
    // check: device names
    // MSDN: Do not use the following reserved names for the name of a file:
    // CON, PRN, AUX, NUL, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8,
    // COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, and LPT9.
    // Also avoid these names followed immediately by an extension;
    // for example, NUL.txt is not recommended.
    {
        std::ctstring_t casReservedNames[] = {
            xT("CON"),  xT("PRN"),  xT("AUX"),  xT("NUL"),
            xT("COM0"), xT("COM1"), xT("COM2"), xT("COM3"), xT("COM4"),
            xT("COM5"), xT("COM6"), xT("COM7"), xT("COM8"), xT("COM9"),
            xT("LPT0"), xT("LPT1"), xT("LPT2"), xT("LPT3"), xT("LPT4"),
            xT("LPT5"), xT("LPT6"), xT("LPT7"), xT("LPT8"), xT("LPT9"),
            xT("CLOCK$")
        };

        std::ctstring_t csBaseFileName = CxPath(sRv).removeExt();

        for (size_t i = 0; i < xARRAY_SIZE(casReservedNames); ++ i) {
            bRv = CxString::compareNoCase(csBaseFileName, casReservedNames[i]);
            if (bRv) {
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

        std::size_t uiPos = a_csFileName.find_first_of(sExceptedChars);
        bRv = (std::tstring_t::npos != uiPos);
        if (bRv) {
            while (std::tstring_t::npos != uiPos) {
                sRv.erase(uiPos, 1);
                uiPos = sRv.find_first_of(sExceptedChars, uiPos);
            }
        }

        xCHECK_RET(sRv.empty(), std::tstring_t());
    }
#elif xOS_ENV_MAC
    //-------------------------------------
    // check: excepted chars
    // / (forward slash)
    // : (colon)

    {
        std::ctstring_t csExceptedChars = xT("/:");

        std::csize_t uiPos = a_csFileName.find_first_of(csExceptedChars);
        bRv = (std::tstring_t::npos != uiPos);
        if (bRv) {
            while (std::tstring_t::npos != uiPos) {
                sRv.erase(uiPos, 1);
                uiPos = sRv.find_first_of(csExceptedChars, uiPos);
            }
        }

        xCHECK_RET(sRv.empty(), std::tstring_t());
    }
#endif

    return sRv;
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::toWin(
    cbool_t &a_cbIsSlashAtEnd
) const
{
    xTEST_NA(a_cbIsSlashAtEnd);

    std::tstring_t sRv;

    if (a_cbIsSlashAtEnd) {
        sRv = slashAppend();
    } else {
        sRv = slashRemove();
    }

    sRv = CxString::replaceAll(sRv, CxConst::xUNIX_SLASH, CxConst::xWIN_SLASH);

    return sRv;
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::toUnix(
    cbool_t &a_cbIsSlashAtEnd
)  const
{
    xTEST_NA(a_cbIsSlashAtEnd);

    std::tstring_t sRv;

    if (a_cbIsSlashAtEnd) {
        sRv = slashAppend();
    } else {
        sRv = slashRemove();
    }

    sRv = CxString::replaceAll(sRv, CxConst::xWIN_SLASH, CxConst::xUNIX_SLASH);

    return sRv;
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::toNative(
    cbool_t &a_cbIsSlashAtEnd
) const
{
    xTEST_NA(a_cbIsSlashAtEnd);

    std::tstring_t sRv;

    if (a_cbIsSlashAtEnd) {
        sRv = slashAppend();
    } else {
        sRv = slashRemove();
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
CxPath::absolute() const {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    DWORD          dwRv = 0UL;
    std::tstring_t sBuff;

    dwRv = ::GetFullPathName(&filePath().at(0), 0, NULL, NULL);
    xTEST_DIFF(0UL, dwRv);

    sBuff.resize(dwRv);

    dwRv = ::GetFullPathName(&filePath().at(0), static_cast<DWORD>( sBuff.size() ), &sBuff.at(0), NULL);
    xTEST_DIFF(0UL, dwRv);

    sBuff.resize(dwRv);

    sRv = sBuff;
#elif xOS_ENV_UNIX
    std::tstring_t sBuff;

    sBuff.resize(xPATH_MAX);

    tchar_t *pszRes = ::realpath(&filePath().at(0), &sBuff.at(0));
    xTEST_PTR(pszRes);

    sRv.assign(pszRes);
#endif

    xTEST_EQ(true, CxPath(sRv).isAbsolute());

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxPath::shortName(
    std::ctstring_t &a_csFileName,
    std::csize_t    &a_cuiMaxSize
)
{
    xTEST_EQ(false, a_csFileName.empty());
    xTEST_LESS(size_t(0), a_cuiMaxSize);

    std::tstring_t sRv;

    std::tstring_t sTildaDotExt;

    if (CxPath(a_csFileName).ext().empty()) {
        sTildaDotExt = xT("~");
    } else {
        sTildaDotExt = xT("~") + CxConst::xDOT + CxPath(a_csFileName).ext();
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
//------------------------------------------------------------------------------
std::tstring_t
CxPath::brief(
    std::csize_t &a_cuiMaxSize
) const
{
    xTEST_LESS(size_t(0), a_cuiMaxSize);

    // util function
    struct _SSlashes
    {
        static
        void_t
        vMake(
            std::tstring_t &a_cStr,
            size_t         &a_uiNum
        )
        {
            size_t uiIndex = 0;

            xFOREVER {
                std::csize_t uiPos = a_cStr.find_first_of(CxConst::xWIN_SLASH + CxConst::xUNIX_SLASH);

                a_cStr.erase(0, uiPos + CxConst::xSLASH.size());

                xCHECK_DO(std::tstring_t::npos != uiPos,  ++ uiIndex);
                xCHECK_DO(uiIndex == a_uiNum && 0 != a_uiNum, break);
                xCHECK_DO(std::tstring_t::npos == uiPos,      break);
            }

            a_uiNum = uiIndex;
        }
    };


    std::tstring_t sRv   = filePath();
    std::tstring_t sPath = filePath();
    size_t         uiNum = 0;

    _SSlashes::vMake(sPath, uiNum);

    while (sRv.size() > a_cuiMaxSize && uiNum > 2) {
        sPath = sRv;

        std::size_t uiNumNew = uiNum / 2;

        _SSlashes::vMake(sPath, uiNumNew);

        sRv.erase(sRv.find(sPath), sPath.size());

        uiNumNew = 2;
        _SSlashes::vMake(sPath, uiNumNew);

        sRv.append(CxConst::x3DOT + CxConst::xSLASH + sPath);

        -- uiNum;
    }

    sRv = CxPath(sRv).toNative(false);

    return sRv;
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::slashAppend() const {
    return CxString::trimRightChars(filePath(), CxConst::xSLASH).append(CxConst::xSLASH);
}
//--------------------------------------------------------------------------
std::tstring_t
CxPath::slashRemove() const {
    return CxString::trimRightChars(filePath(), CxConst::xSLASH);
}
//--------------------------------------------------------------------------
/* static */
size_t
CxPath::maxSize() {
    size_t uiRes = 0;

#if   xOS_ENV_WIN
    #if defined(MAX_PATH)
        uiRes = MAX_PATH;
    #else
        std::csize_t cuiDefaultSize = 260;

        uiRes = cuiDefaultSize;
    #endif
#elif xOS_ENV_UNIX
    #if defined(PATH_MAX)
        uiRes = PATH_MAX;
    #else
        culong_t culSavedError = 0UL;
        long_t        liRv          = - 1L;
        ulong_t       ulLastError   = 0UL;

        CxLastError::set(culSavedError);

        liRv       = ::pathconf("/", _PC_PATH_MAX);
        ulLastError = CxLastError::get();
        xTEST_EQ(true, - 1L == liRv && 0UL != culSavedError);

        if (- 1L == liRv && culSavedError == ulLastError) {
            //system does not have a limit for the requested resource
            std::csize_t cuiDefaultSize = 1024;

            uiRes = cuiDefaultSize;
        } else {
            //relative root
            uiRes = static_cast<size_t>( liRv + 1 );
        }
    #endif
#endif

    return uiRes;
}
//------------------------------------------------------------------------------
/* static */
size_t
CxPath::nameMaxSize() {
    size_t uiRes = 0;

#if   xOS_ENV_WIN
    #if defined(FILENAME_MAX)
        uiRes = FILENAME_MAX;
    #else
        std::csize_t cuiDefaultSize = 260;

        uiRes = cuiDefaultSize;
    #endif
#elif xOS_ENV_UNIX
    #if defined(NAME_MAX)
        uiRes = NAME_MAX;
    #else
        culong_t culSavedError = 0UL;
        long_t        liRv          = - 1L;
        ulong_t       ulLastError   = 0UL;

        CxLastError::set(culSavedError);

        liRv       = ::pathconf("/", _PC_NAME_MAX);
        ulLastError = CxLastError::get();
        xTEST_EQ(true, - 1L == liRv && 0UL != culSavedError);

        if (- 1L == liRv && culSavedError == ulLastError) {
            //system does not have a limit for the requested resource
            std::csize_t cuiDefaultSize = 1024;

            uiRes = cuiDefaultSize;
        } else {
            uiRes = static_cast<size_t>( liRv );
        }
    #endif
#endif

    return uiRes;
}
//------------------------------------------------------------------------------
#if !xOS_ENV_WIN

/* static */
void_t
CxPath::proc(
    std::ctstring_t &a_csProcPath,
    std::vec_tstring_t   *a_pvsData
)
{
    // check for existence "/proc" directory
    {
        bool_t bRv = false;

        CxDir drProc(xT("/proc"));

        bRv = drProc.isExists();
        xCHECK_DO(!bRv,
                  CxTracer() << xT("::: xLib: warning (/proc dir not mount) :::"); return);

        bRv = drProc.isEmpty();
        xCHECK_DO(bRv,
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
//------------------------------------------------------------------------------
#if !xOS_ENV_WIN

/* static */
std::tstring_t
CxPath::procValue(
    std::ctstring_t &a_csProcPath,   ///< file path to proc-file
    std::ctstring_t &a_csData        ///< target search data string
)
{
    std::tstring_t     sRv;
    std::vec_tstring_t vsProcFile;

    proc(a_csProcPath, &vsProcFile);

    xFOREACH_CONST (std::vec_tstring_t, it, vsProcFile) {
        // TODO: no case search
        std::csize_t uiPos = (*it).find(a_csData);
        xCHECK_DO(std::tstring_t::npos == uiPos, continue);

        // parse value
        std::csize_t uiDelimPos = (*it).find(xT(":"));
        xTEST_DIFF(std::string::npos, uiDelimPos);

        sRv = (*it).substr(uiDelimPos + 1);
        sRv = CxString::trimSpace(sRv);

        break;
    }

    return sRv;
}

#endif
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
