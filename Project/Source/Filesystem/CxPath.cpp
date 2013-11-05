/**
 * \file  CxPath.cpp
 * \brief file system path
 */


#include <xLib/Filesystem/CxPath.h>

#include <xLib/Core/CxChar.h>
#include <xLib/Core/CxString.h>
#include <xLib/System/CxProcessInfo.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Sync/CxProcess.h>
#include <xLib/Log/CxTracer.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxPath::CxPath(
    std::ctstring_t &a_filePath
) :
    _filePath(a_filePath)
{
    xTEST_EQ(false, _filePath.empty());
}
//------------------------------------------------------------------------------
xINLINE_HO std::ctstring_t &
CxPath::filePath() const
{
    xTEST_EQ(false, _filePath.empty());

    return _filePath;
}
//------------------------------------------------------------------------------
// FAQ: http://www.cplusplus.com/forum/general/11104/
//      http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
//      http://libsylph.sourceforge.net/wiki/Full_path_to_binary
//      http://h21007.www2.hp.com/portal/site/dspp/menuitem.863c3e4cbcdc3f3515b49c108973a801?ciid=88086d6e1de021106d6e1de02110275d6e10RCRD

/* static */
xINLINE_HO std::tstring_t
CxPath::exe()
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    // REVIEW: QueryFullProcessImageName on xOS_WIN_VER > xOS_WIN_S03

    sRv.resize(xPATH_MAX);

    DWORD stored = ::GetModuleFileName(NULL, &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(0UL, stored);

    sRv.resize(stored);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        std::ctstring_t procFile = CxString::format(xT("/proc/%ld/exe"), ::getpid());

        bool_t bRv = CxFile::isExists(procFile);
        xCHECK_RET(!bRv, std::tstring_t());

        int_t readed = - 1;
        sRv.resize(xPATH_MAX);

        xFOREVER {
            readed = ::readlink(procFile.c_str(), &sRv.at(0), sRv.size() * sizeof(std::tstring_t::value_type));
            xTEST_DIFF(- 1, readed);

            xCHECK_DO(sRv.size() * sizeof(std::tstring_t::value_type) > static_cast<size_t>( readed ), break);

            sRv.resize(sRv.size() * 2);
        }

        sRv.resize(readed);
    #elif xOS_FREEBSD
        #if defined(KERN_PROC_PATHNAME)
            int_t mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, - 1};

            tchar_t      buff[PATH_MAX + 1] = {0};
            std::csize_t buffSize           = sizeof(buff) - 1;

            int_t iRv = ::sysctl(mib, xARRAY_SIZE(mib), buff, &buffSize, NULL, 0U);
            xTEST_DIFF(- 1, iRv);

            sRv.assign(buff);
        #else
            std::vec_tstring_t args;

            CxProcessInfo info;
            info.setProcessId(CxProcess::currentId());
            info.commandLine(&args);

            bool_t bRv = info.commandLine(CxProcess::currentId(), &args);
            xTEST_EQ(true,  bRv);
            xTEST_EQ(false, args.empty());
            xTEST_EQ(false, bIsAbsolute(args.at(0)));

            sRv = absolute(args.at(0));
        #endif
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    xTEST_EQ(true, CxFile::isExists(sRv));

    return sRv;
}
//------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

#if xOS_ENV_WIN
    extern "C" IMAGE_DOS_HEADER __ImageBase;
#else
    static void_t function() { ; }
#endif

xNAMESPACE_ANONYM_END

/* static */
xINLINE_HO std::tstring_t
CxPath::dll()
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv.resize(xPATH_MAX);

    DWORD stored = ::GetModuleFileName(
                            reinterpret_cast<HINSTANCE>( &__ImageBase ),
                            &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(0UL, stored);

    sRv.resize(stored);
#else
    Dl_info  diInfo      = {0};
    cvoid_t *procAddress = reinterpret_cast<cvoid_t *>( ::function );

    int_t iRv = ::dladdr(procAddress, &diInfo);
    /*DEBUF*/xTEST_LESS(0, iRv);

    sRv = CxPath(diInfo.dli_fname).absolute();
#endif

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxPath::exeDir()
{
    return CxPath(exe()).dir();
}
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xINLINE_HO std::tstring_t
CxPath::drive() const
{
    std::csize_t driveDelimPos = filePath().find(CxConst::xCOLON());
    xTEST_DIFF(std::tstring_t::npos, driveDelimPos);
    xTEST_EQ(size_t(1), driveDelimPos);

    return filePath().substr(0, driveDelimPos + CxConst::xCOLON().size());
}

#endif
//--------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::dir() const
{
    std::csize_t slashPos = filePath().rfind(CxConst::xSLASH(), filePath().size());
    xCHECK_RET(std::tstring_t::npos == slashPos, std::tstring_t());

    return filePath().substr(0, slashPos);
}
//--------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::dirName() const
{
    std::csize_t slashPos2 = filePath().rfind(CxConst::xSLASH());
    xCHECK_RET(std::tstring_t::npos == slashPos2, std::tstring_t());

    std::csize_t slashPos1 = filePath().rfind(CxConst::xSLASH(), slashPos2 - 1);
    if (std::tstring_t::npos == slashPos1) {
        return filePath().substr(0, slashPos2);
    } else {
        return filePath().substr(slashPos1 + 1, slashPos2 - slashPos1 - 1);
    }
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::fileName() const
{
    std::csize_t slashPos = filePath().rfind(CxConst::xSLASH(), filePath().size());
    xCHECK_RET(std::tstring_t::npos == slashPos, filePath());

    return filePath().substr(slashPos + CxConst::xSLASH().size());
}
//--------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::fileBaseName() const
{
    std::csize_t slashPos = filePath().rfind(CxConst::xSLASH(), filePath().size());
    std::csize_t dotPos   = filePath().rfind(CxConst::xDOT(),   filePath().size());

    return CxString::cut(filePath(), slashPos + CxConst::xSLASH().size(), dotPos);
}
//--------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::ext() const
{
    std::csize_t dotPos   = filePath().rfind(CxConst::xDOT(),   filePath().size());
    xCHECK_RET(std::tstring_t::npos == dotPos, std::tstring_t());

    std::csize_t slashPos = filePath().rfind(CxConst::xSLASH(), filePath().size());
    // if dot after slash - extension not exists
    xCHECK_RET(dotPos < slashPos && std::tstring_t::npos != slashPos, std::tstring_t());

    return filePath().substr(dotPos + CxConst::xDOT().size());
}
//--------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxPath::standartExt(
    const ExStandartExt &a_fileExt
)
{
    std::tstring_t sRv;

    switch (a_fileExt) {
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

xINLINE_HO std::tstring_t
CxPath::setDrive(
    std::ctstring_t &a_drivePath
)
{
    // csDrivePath

    std::tstring_t sRv(filePath());

    std::tstring_t driveStr = CxPath(sRv).drive();
    xTEST_EQ(false, driveStr.empty());

    std::csize_t pos = sRv.find(driveStr);
    xTEST_DIFF(std::tstring_t::npos, pos);

    return sRv.replace(pos, driveStr.size(), a_drivePath);
}

#endif
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::setDir(
    std::ctstring_t &a_dirPath
)
{
    // dirPath

    std::tstring_t sRv(filePath());

    std::tstring_t dirStr = CxPath(sRv).dir();
    xTEST_EQ(false, dirStr.empty());

    std::csize_t pos = sRv.find(dirStr);
    xTEST_DIFF(std::tstring_t::npos, pos);

    return sRv.replace(pos, dirStr.size(), CxPath(a_dirPath).slashRemove());
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::setFileName(
    std::ctstring_t &a_fullName
)
{
    // fullName

    std::tstring_t sRv(filePath());

    std::tstring_t fullName = CxPath(sRv).fileName();
    xTEST_EQ(false, fullName.empty());

    std::csize_t pos = sRv.rfind(fullName);
    xTEST_DIFF(std::tstring_t::npos, pos);

    return sRv.replace(pos, fullName.size(), a_fullName);
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::setFileBaseName(
    std::ctstring_t &a_name
)
{
    // name

    std::tstring_t sRv(filePath());

    std::tstring_t name = CxPath(sRv).fileBaseName();
    xTEST_EQ(false, name.empty());

    std::csize_t pos = sRv.rfind(name);
    xTEST_DIFF(std::tstring_t::npos, pos);

    return sRv.replace(pos, name.size(), a_name);
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::setExt(
    std::ctstring_t &a_ext
)
{
    xTEST_NA(a_ext);

    return removeExt() + CxConst::xDOT() + a_ext;
}
//------------------------------------------------------------------------------


//--------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::removeExt()
{
    std::csize_t dotPos = filePath().rfind(CxConst::xDOT());

    return filePath().substr(0, dotPos);
}
//--------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::removeExtIf(
    std::ctstring_t &a_ext
)
{
    std::csize_t extPos = filePath().rfind(CxConst::xDOT() + a_ext);
    xCHECK_RET(std::tstring_t::npos == extPos, filePath());

    std::csize_t dotPos = filePath().rfind(CxConst::xDOT());
    xTEST_DIFF(std::tstring_t::npos, dotPos);

    return filePath().substr(0, dotPos);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
CxPath::isValid(
    std::ctstring_t &a_filePath
)
{
    xTEST_NA(a_filePath);

    bool_t bRv = false;

    // is empty
    bRv = a_filePath.empty();
    xCHECK_RET(bRv, false);

    // check for size
    bRv = (xPATH_MAX < a_filePath.size());
    xCHECK_RET(bRv, false);

    // TODO: bIsValid

    return true;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
CxPath::isNameValid(
    std::ctstring_t &a_fileName
)
{
    xTEST_NA(a_fileName);

    bool_t bRv = false;

    //-------------------------------------
    // check: empty name
    {
        bRv = a_fileName.empty();
        xCHECK_RET(bRv, false);
    }

    //-------------------------------------
    // check: name size
    {
        bRv = (xNAME_MAX < a_fileName.size());
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
        ctchar_t begin = *a_fileName.begin();
        ctchar_t end   = *(a_fileName.end() - 1);

        // space
        bRv = (CxConst::xSPACE().at(0) == begin);
        xCHECK_RET(bRv, false);

        bRv = (CxConst::xSPACE().at(0) == end);
        xCHECK_RET(bRv, false);

        // dot
        bRv = (CxConst::xDOT().at(0)   == begin);
        xCHECK_RET(bRv, false);

        bRv = (CxConst::xDOT().at(0)   == end);
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
        std::ctstring_t exceptedChars = xT("<>:\"/\\|?*");

        std::csize_t pos = a_fileName.find_first_of(exceptedChars);
        bRv = (std::tstring_t::npos != pos);
        xCHECK_RET(bRv, false);
    }

    //-------------------------------------
    // check: control chars
    // MAN: For the standard ASCII character set (used by the "C" locale),
    // control characters are those between ASCII codes 0x00 (NUL) and 0x1f (US), plus 0x7f (DEL).
    {
        std::tstring_t::const_iterator cit;

        cit = std::find_if(a_fileName.begin(), a_fileName.end(), CxChar::isControl);
        bRv = (cit != a_fileName.end());
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
        std::ctstring_t reservedNames[] = {
            xT("CON"),  xT("PRN"),  xT("AUX"),  xT("NUL"),
            xT("COM0"), xT("COM1"), xT("COM2"), xT("COM3"), xT("COM4"),
            xT("COM5"), xT("COM6"), xT("COM7"), xT("COM8"), xT("COM9"),
            xT("LPT0"), xT("LPT1"), xT("LPT2"), xT("LPT3"), xT("LPT4"),
            xT("LPT5"), xT("LPT6"), xT("LPT7"), xT("LPT8"), xT("LPT9"),
            xT("CLOCK$")
        };

        std::ctstring_t baseFileName = CxPath(a_fileName).removeExt();

        for (size_t i = 0; i < xARRAY_SIZE(reservedNames); ++ i) {
            bRv = CxString::compareNoCase(baseFileName, reservedNames[i]);
            xCHECK_RET(bRv, false);
        }
    }
#elif xOS_ENV_UNIX
    //-------------------------------------
    // check: excepted chars
    // /  (forward slash)
    // \0 (NULL character)

    {
        std::tstring_t exceptedChars;
        exceptedChars.push_back(xT('/'));
        exceptedChars.push_back(xT('\0'));
        xTEST_EQ(size_t(2), exceptedChars.size());

        std::csize_t pos = a_fileName.find_first_of(exceptedChars);
        bRv = (std::tstring_t::npos != pos);
        xCHECK_RET(bRv, false);
    }
#elif xOS_ENV_MAC
    //-------------------------------------
    // check: excepted chars
    // / (forward slash)
    // : (colon)

    {
        std::ctstring_t exceptedChars = xT("/:");

        std::csize_t pos = a_fileName.find_first_of(exceptedChars);
        bRv = (std::tstring_t::npos != pos);
        xCHECK_RET(bRv, false);
    }
#endif

    return true;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxPath::isAbsolute() const {
    xCHECK_RET(true                    == filePath().empty(), false);
    xCHECK_RET(CxConst::xSLASH().at(0) == filePath().at(0),   true);

#if xOS_ENV_WIN
    xCHECK_RET(1 == filePath().size(),                                                           false);
    xCHECK_RET(CxChar::isAlpha(filePath().at(0)) && CxConst::xCOLON().at(0) == filePath().at(1), true);
#else
    xNA;
#endif

    return false;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxPath::setNameValid(
    std::ctstring_t &a_fileName
)
{
    xTEST_NA(a_fileName);

    std::tstring_t sRv(a_fileName);
    bool_t         bRv = false;

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
        sRv = CxString::trimChars(sRv, CxConst::xSPACE() + CxConst::xDOT());

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
        std::ctstring_t exceptedChars = xT("<>:\"/\\|?*");

        std::size_t pos = sRv.find_first_of(exceptedChars);
        bRv = (std::tstring_t::npos != pos);
        if (bRv) {
            while (std::tstring_t::npos != pos) {
                sRv.erase(pos, 1);
                pos = sRv.find_first_of(exceptedChars, pos);
            }
        }

        xCHECK_RET(sRv.empty(), std::tstring_t());
    }

    //-------------------------------------
    // check: control chars
    // MAN: For the standard ASCII character set (used by the "C" locale),
    // control characters are those between ASCII codes 0x00 (NUL) and 0x1f (US), plus 0x7f (DEL).
    {
        std::tstring_t::const_iterator cit;

        cit = std::find_if(sRv.begin(), sRv.end(), CxChar::isControl);
        bRv = (cit != sRv.end());
        if (bRv) {
            std::tstring_t::iterator itNewEnd;

            itNewEnd = std::remove_if(sRv.begin(), sRv.end(), CxChar::isControl);
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
        std::ctstring_t reservedNames[] = {
            xT("CON"),  xT("PRN"),  xT("AUX"),  xT("NUL"),
            xT("COM0"), xT("COM1"), xT("COM2"), xT("COM3"), xT("COM4"),
            xT("COM5"), xT("COM6"), xT("COM7"), xT("COM8"), xT("COM9"),
            xT("LPT0"), xT("LPT1"), xT("LPT2"), xT("LPT3"), xT("LPT4"),
            xT("LPT5"), xT("LPT6"), xT("LPT7"), xT("LPT8"), xT("LPT9"),
            xT("CLOCK$")
        };

        std::ctstring_t baseFileName = CxPath(sRv).removeExt();

        for (size_t i = 0; i < xARRAY_SIZE(reservedNames); ++ i) {
            bRv = CxString::compareNoCase(baseFileName, reservedNames[i]);
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
        std::tstring_t exceptedChars;
        exceptedChars.push_back(xT('/'));
        exceptedChars.push_back(xT('\0'));
        xTEST_EQ(size_t(2), exceptedChars.size());

        std::size_t pos = a_fileName.find_first_of(exceptedChars);
        bRv = (std::tstring_t::npos != pos);
        if (bRv) {
            while (std::tstring_t::npos != pos) {
                sRv.erase(pos, 1);
                pos = sRv.find_first_of(exceptedChars, pos);
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
        std::ctstring_t exceptedChars = xT("/:");

        std::size_t pos = a_fileName.find_first_of(exceptedChars);
        bRv = (std::tstring_t::npos != pos);
        if (bRv) {
            while (std::tstring_t::npos != pos) {
                sRv.erase(pos, 1);
                pos = sRv.find_first_of(exceptedChars, pos);
            }
        }

        xCHECK_RET(sRv.empty(), std::tstring_t());
    }
#endif

    return sRv;
}
//--------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::toWin(
    cbool_t &a_isSlashAtEnd
) const
{
    xTEST_NA(a_isSlashAtEnd);

    std::tstring_t sRv;

    if (a_isSlashAtEnd) {
        sRv = slashAppend();
    } else {
        sRv = slashRemove();
    }

    sRv = CxString::replaceAll(sRv, CxConst::xUNIX_SLASH(), CxConst::xWIN_SLASH());

    return sRv;
}
//--------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::toUnix(
    cbool_t &a_isSlashAtEnd
)  const
{
    xTEST_NA(a_isSlashAtEnd);

    std::tstring_t sRv;

    if (a_isSlashAtEnd) {
        sRv = slashAppend();
    } else {
        sRv = slashRemove();
    }

    sRv = CxString::replaceAll(sRv, CxConst::xWIN_SLASH(), CxConst::xUNIX_SLASH());

    return sRv;
}
//--------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::toNative(
    cbool_t &a_isSlashAtEnd
) const
{
    xTEST_NA(a_isSlashAtEnd);

    std::tstring_t sRv;

    if (a_isSlashAtEnd) {
        sRv = slashAppend();
    } else {
        sRv = slashRemove();
    }

#if xOS_ENV_WIN
    sRv = CxString::replaceAll(sRv, CxConst::xUNIX_SLASH(), CxConst::xSLASH());
#else
    sRv = CxString::replaceAll(sRv, CxConst::xWIN_SLASH(),  CxConst::xSLASH());
#endif

    return sRv;
}
//--------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::absolute() const
{
    std::tstring_t sRv;

#if xOS_ENV_WIN
    DWORD          dwRv = 0UL;
    std::tstring_t buff;

    dwRv = ::GetFullPathName(&filePath().at(0), 0, NULL, NULL);
    xTEST_DIFF(0UL, dwRv);

    buff.resize(dwRv);

    dwRv = ::GetFullPathName(&filePath().at(0), static_cast<DWORD>( buff.size() ), &buff.at(0), NULL);
    xTEST_DIFF(0UL, dwRv);

    buff.resize(dwRv);

    sRv = buff;
#else
    std::tstring_t buff;

    buff.resize(xPATH_MAX);

    tchar_t *pszRes = ::realpath(&filePath().at(0), &buff.at(0));
    xTEST_PTR(pszRes);

    sRv.assign(pszRes);
#endif

    xTEST_EQ(true, CxPath(sRv).isAbsolute());

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxPath::shortName(
    std::ctstring_t &a_fileName,
    std::csize_t    &a_maxSize
)
{
    xTEST_EQ(false, a_fileName.empty());
    xTEST_LESS(size_t(0), a_maxSize);

    std::tstring_t sRv;

    std::tstring_t tildaDotExt;

    if (CxPath(a_fileName).ext().empty()) {
        tildaDotExt = xT("~");
    } else {
        tildaDotExt = xT("~") + CxConst::xDOT() + CxPath(a_fileName).ext();
    }

    if (a_fileName.size() > a_maxSize) {
        if (a_maxSize < tildaDotExt.size()) {
            sRv = a_fileName.substr(0, a_maxSize);
        } else {
            sRv = a_fileName.substr(0, a_maxSize - tildaDotExt.size()) + tildaDotExt;
        }
    } else {
        sRv = a_fileName;
    }

    return sRv;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::brief(
    std::csize_t &a_maxSize
) const
{
    xTEST_LESS(size_t(0), a_maxSize);

    // util function
    struct _SSlashes
    {
        static
        void_t
        make(
            std::tstring_t &a_str,
            size_t         &a_num
        )
        {
            size_t index = 0;

            xFOREVER {
                std::csize_t pos = a_str.find_first_of(CxConst::xWIN_SLASH() + CxConst::xUNIX_SLASH());

                a_str.erase(0, pos + CxConst::xSLASH().size());

                xCHECK_DO(std::tstring_t::npos != pos,  ++ index);
                xCHECK_DO(index == a_num && 0 != a_num, break);
                xCHECK_DO(std::tstring_t::npos == pos,      break);
            }

            a_num = index;
        }
    };


    std::tstring_t sRv   = filePath();
    std::tstring_t sPath = filePath();
    size_t         num = 0;

    _SSlashes::make(sPath, num);

    while (sRv.size() > a_maxSize && num > 2) {
        sPath = sRv;

        std::size_t uiNumNew = num / 2;

        _SSlashes::make(sPath, uiNumNew);

        sRv.erase(sRv.find(sPath), sPath.size());

        uiNumNew = 2;
        _SSlashes::make(sPath, uiNumNew);

        sRv.append(CxConst::x3DOT() + CxConst::xSLASH() + sPath);

        -- num;
    }

    sRv = CxPath(sRv).toNative(false);

    return sRv;
}
//--------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::slashAppend() const
{
    return CxString::trimRightChars(filePath(), CxConst::xSLASH()).append(CxConst::xSLASH());
}
//--------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxPath::slashRemove() const
{
    return CxString::trimRightChars(filePath(), CxConst::xSLASH());
}
//--------------------------------------------------------------------------
/* static */
xINLINE_HO size_t
CxPath::maxSize()
{
    size_t uiRes = 0;

#if xOS_ENV_WIN
    #if defined(MAX_PATH)
        uiRes = MAX_PATH;
    #else
        std::csize_t defaultSize = 260;

        uiRes = defaultSize;
    #endif
#else
    #if defined(PATH_MAX)
        uiRes = PATH_MAX;
    #else
        culong_t savedError     = 0UL;
        long_t        liRv      = - 1L;
        ulong_t       lastError = 0UL;

        CxLastError::set(savedError);

        liRv       = ::pathconf("/", _PC_PATH_MAX);
        lastError = CxLastError::get();
        xTEST_EQ(true, - 1L == liRv && 0UL != savedError);

        if (- 1L == liRv && savedError == lastError) {
            //system does not have a limit for the requested resource
            std::csize_t defaultSize = 1024;

            uiRes = defaultSize;
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
xINLINE_HO size_t
CxPath::nameMaxSize()
{
    size_t uiRes = 0;

#if xOS_ENV_WIN
    #if defined(FILENAME_MAX)
        uiRes = FILENAME_MAX;
    #else
        std::csize_t defaultSize = 260;

        uiRes = defaultSize;
    #endif
#else
    #if defined(NAME_MAX)
        uiRes = NAME_MAX;
    #else
        culong_t savedError = 0UL;
        long_t   liRv       = - 1L;
        ulong_t  lastError  = 0UL;

        CxLastError::set(savedError);

        liRv      = ::pathconf("/", _PC_NAME_MAX);
        lastError = CxLastError::get();
        xTEST_EQ(true, - 1L == liRv && 0UL != savedError);

        if (- 1L == liRv && savedError == lastError) {
            //system does not have a limit for the requested resource
            std::csize_t defaultSize = 1024;

            uiRes = defaultSize;
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
xINLINE_HO void_t
CxPath::proc(
    std::ctstring_t    &a_procPath,
    std::vec_tstring_t *a_data
)
{
    // check for existence "/proc" directory
    {
        bool_t bRv = false;

        CxDir proc(xT("/proc"));

        bRv = proc.isExists();
        xCHECK_DO(!bRv,
                  CxTracer() << xT("::: xLib: warning (/proc dir not mount) :::"); return);

        bRv = proc.isEmpty();
        xCHECK_DO(bRv,
                  CxTracer() << xT("::: xLib: warning (/proc dir is empty) :::");  return);
    }

    std::vec_tstring_t vsRv;

    std::tifstream_t ifs(a_procPath.c_str());
    xTEST_EQ(true,  !! ifs);
    xTEST_EQ(false, ifs.fail());
    xTEST_EQ(true,  ifs.good());
    xTEST_EQ(true,  ifs.is_open());
    xTEST_EQ(false, ifs.eof());

    for ( ; !ifs.eof(); ) {
        std::tstring_t sLine;

        std::getline(ifs, sLine);
        vsRv.push_back(sLine);
    }

    // out
    (*a_data).swap(vsRv);
}

#endif
//------------------------------------------------------------------------------
#if !xOS_ENV_WIN

/* static */
xINLINE_HO std::tstring_t
CxPath::procValue(
    std::ctstring_t &a_procPath,   ///< file path to proc-file
    std::ctstring_t &a_data        ///< target search data string
)
{
    std::tstring_t     sRv;
    std::vec_tstring_t procFile;

    proc(a_procPath, &procFile);

    xFOREACH_CONST (std::vec_tstring_t, it, procFile) {
        // TODO: no case search
        std::csize_t pos = (*it).find(a_data);
        xCHECK_DO(std::tstring_t::npos == pos, continue);

        // parse value
        std::csize_t delimPos = (*it).find(xT(":"));
        xTEST_DIFF(std::string::npos, delimPos);

        sRv = (*it).substr(delimPos + 1);
        sRv = CxString::trimSpace(sRv);

        break;
    }

    return sRv;
}

#endif
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
