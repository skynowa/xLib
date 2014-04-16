/**
 * \file  CxPath.inl
 * \brief file system path
 */


#include <xLib/Core/CxChar.h>
#include <xLib/Core/CxString.h>
#include <xLib/System/CxProcessInfo.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Sync/CxProcess.h>
#include <xLib/Log/CxTrace.h>


xNAMESPACE2_BEGIN(xlib, filesystem)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxPath::CxPath(
    std::ctstring_t &a_filePath
) :
    _filePath(a_filePath)
{
    xTEST_EQ(_filePath.empty(), false);
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxPath::filePath() const
{
    xTEST_EQ(_filePath.empty(), false);

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
/**
* FAQ:
*   http://www.cplusplus.com/forum/general/11104/
*   http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
*   http://libsylph.sourceforge.net/wiki/Full_path_to_binary
*   http://h21007.www2.hp.com/portal/site/dspp/menuitem.863c3e4cbcdc3f3515b49c108973a801?
*       ciid=88086d6e1de021106d6e1de02110275d6e10RCRD
*/

/* static */
inline std::tstring_t
CxPath::exe()
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    // REVIEW: QueryFullProcessImageName on xOS_WIN_VER > xOS_WIN_S03

    sRv.resize(xPATH_MAX);

    DWORD stored = ::GetModuleFileName(xPTR_NULL, &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(stored, 0UL);

    sRv.resize(stored);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        std::ctstring_t procFile = CxString::format(xT("/proc/%ld/exe"), ::getpid());

        bool_t bRv = CxFile::isExists(procFile);
        xCHECK_RET(!bRv, std::tstring_t());

        ssize_t readed = - 1;
        sRv.resize(xPATH_MAX);

        for ( ; ; ) {
            readed = ::readlink(procFile.c_str(), &sRv.at(0), sRv.size() *
                sizeof(std::tstring_t::value_type));
            xTEST_DIFF(readed, ssize_t(- 1));

            xCHECK_DO(sRv.size() * sizeof(std::tstring_t::value_type) >
                static_cast<size_t>( readed ), break);

            sRv.resize(sRv.size() * 2);
        }

        sRv.resize(readed);
    #elif xOS_FREEBSD
        #if defined(KERN_PROC_PATHNAME)
            int_t mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, - 1};

            tchar_t     buff[PATH_MAX + 1] = {0};
            std::size_t buffSize           = sizeof(buff) - 1;

            int_t iRv = ::sysctl(mib, xARRAY_SIZE(mib), buff, &buffSize, xPTR_NULL, 0U);
            xTEST_DIFF(iRv, - 1);

            sRv.assign(buff);
        #else
            std::vec_tstring_t args;

            CxProcessInfo info;
            info.setProcessId(CxProcess::currentId());
            info.commandLine(&args);

            bool_t bRv = info.commandLine(CxProcess::currentId(), &args);
            xTEST_EQ(bRv, true);
            xTEST_EQ(args.empty(), false);
            xTEST_EQ(isAbsolute(args.at(0)), false);

            sRv = absolute(args.at(0));
        #endif
    #endif
#elif xOS_ENV_APPLE
    xNOT_IMPLEMENTED
#endif

    xTEST_EQ(CxFile::isExists(sRv), true);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

#if   xOS_ENV_WIN
    extern "C" IMAGE_DOS_HEADER __ImageBase;
#elif xOS_ENV_UNIX
    static void_t function() { ; }
#endif

xNAMESPACE_ANONYM_END

/* static */
inline std::tstring_t
CxPath::dll()
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv.resize(xPATH_MAX);

    DWORD stored = ::GetModuleFileName(reinterpret_cast<HINSTANCE>( &__ImageBase ),
        &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(stored, 0UL);

    sRv.resize(stored);
#elif xOS_ENV_UNIX
    Dl_info  diInfo;    xSTRUCT_ZERO(diInfo);
    cvoid_t *procAddress = reinterpret_cast<cvoid_t *>( ::function );

    int_t iRv = ::dladdr(procAddress, &diInfo);
    /*DEBUF*/xTEST_LESS(0, iRv);

    sRv = CxPath(diInfo.dli_fname).absolute();
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxPath::exeDir()
{
    return CxPath(exe()).dir();
}
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

inline std::tstring_t
CxPath::drive() const
{
    std::csize_t driveDelimPos = filePath().find(CxConst::colon());
    xTEST_DIFF(driveDelimPos, std::tstring_t::npos);
    xTEST_EQ(driveDelimPos, size_t(1));

    return filePath().substr(0, driveDelimPos + CxConst::colon().size());
}

#endif
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::dir() const
{
    std::csize_t slashPos = filePath().rfind(CxConst::slash(), filePath().size());
    xCHECK_RET(slashPos == std::tstring_t::npos, std::tstring_t());

    return filePath().substr(0, slashPos);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::dirName() const
{
    std::csize_t slashPos2 = filePath().rfind(CxConst::slash());
    xCHECK_RET(slashPos2 == std::tstring_t::npos, std::tstring_t());

    std::csize_t slashPos1 = filePath().rfind(CxConst::slash(), slashPos2 - 1);
    if (slashPos1 == std::tstring_t::npos) {
        return filePath().substr(0, slashPos2);
    } else {
        return filePath().substr(slashPos1 + 1, slashPos2 - slashPos1 - 1);
    }
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::fileName() const
{
    std::csize_t slashPos = filePath().rfind(CxConst::slash(), filePath().size());
    xCHECK_RET(slashPos == std::tstring_t::npos, filePath());

    return filePath().substr(slashPos + CxConst::slash().size());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::fileBaseName() const
{
    std::csize_t slashPos = filePath().rfind(CxConst::slash(), filePath().size());
    std::csize_t dotPos   = filePath().rfind(CxConst::dot(),   filePath().size());

    return CxString::cut(filePath(), slashPos + CxConst::slash().size(), dotPos);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::ext() const
{
    std::csize_t dotPos   = filePath().rfind(CxConst::dot(),   filePath().size());
    xCHECK_RET(dotPos == std::tstring_t::npos, std::tstring_t());

    std::csize_t slashPos = filePath().rfind(CxConst::slash(), filePath().size());
    // if dot after slash - extension not exists
    xCHECK_RET(dotPos < slashPos && slashPos != std::tstring_t::npos, std::tstring_t());

    return filePath().substr(dotPos + CxConst::dot().size());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
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
#elif xOS_ENV_APPLE
    case seExe:
        sRv = xT("");
        break;
    case seDll:
        sRv = xT("dylib");
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
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

inline std::tstring_t
CxPath::setDrive(
    std::ctstring_t &a_drivePath
)
{
    // csDrivePath

    std::tstring_t sRv(filePath());

    std::tstring_t driveStr = CxPath(sRv).drive();
    xTEST_EQ(driveStr.empty(), false);

    std::csize_t pos = sRv.find(driveStr);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return sRv.replace(pos, driveStr.size(), a_drivePath);
}

#endif
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::setDir(
    std::ctstring_t &a_dirPath
)
{
    // dirPath

    std::tstring_t sRv(filePath());

    std::tstring_t dirStr = CxPath(sRv).dir();
    xTEST_EQ(dirStr.empty(), false);

    std::csize_t pos = sRv.find(dirStr);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return sRv.replace(pos, dirStr.size(), CxPath(a_dirPath).slashRemove());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::setFileName(
    std::ctstring_t &a_fullName
)
{
    // fullName

    std::tstring_t sRv(filePath());

    std::tstring_t fullName = CxPath(sRv).fileName();
    xTEST_EQ(fullName.empty(), false);

    std::csize_t pos = sRv.rfind(fullName);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return sRv.replace(pos, fullName.size(), a_fullName);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::setFileBaseName(
    std::ctstring_t &a_name
)
{
    // name

    std::tstring_t sRv(filePath());

    std::tstring_t name = CxPath(sRv).fileBaseName();
    xTEST_EQ(name.empty(), false);

    std::csize_t pos = sRv.rfind(name);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return sRv.replace(pos, name.size(), a_name);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::setExt(
    std::ctstring_t &a_ext
)
{
    xTEST_NA(a_ext);

    return removeExt() + CxConst::dot() + a_ext;
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::removeExt()
{
    std::csize_t dotPos = filePath().rfind(CxConst::dot());

    return filePath().substr(0, dotPos);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::removeExtIf(
    std::ctstring_t &a_ext
)
{
    std::csize_t extPos = filePath().rfind(CxConst::dot() + a_ext);
    xCHECK_RET(extPos == std::tstring_t::npos, filePath());

    std::csize_t dotPos = filePath().rfind(CxConst::dot());
    xTEST_DIFF(dotPos, std::tstring_t::npos);

    return filePath().substr(0, dotPos);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxPath::isValid(
    std::ctstring_t &a_filePath,                    ///< file, directory path
    std::tstring_t  *a_filePathValid /* = xPTR_NULL */   ///< [out] normalized path
)
{
    xTEST_NA(a_filePath);
    xTEST_NA(a_filePathValid);

    // is empty
    xCHECK_RET(a_filePath.empty(), false);

    // check for size
    xCHECK_RET(a_filePath.size() > xPATH_MAX, false);

    // TODO: CxPath::isValid() - more checks

    // name
    {
        std::ctstring_t fileName = CxPath(a_filePath).fileName();

        xCHECK_RET(!isNameValid(fileName, a_filePathValid), false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxPath::isNameValid(
    std::ctstring_t &a_fileName,                    ///< file, directory name
    std::tstring_t  *a_fileNameValid /* = xPTR_NULL */   ///< [out] normalized name
)
{
    xTEST_NA(a_fileName);
    xTEST_NA(a_isNormalize);
    xTEST_NA(a_fileNameValid);

    std::tstring_t sRv(a_fileName);

    // check: empty name
    if ( sRv.empty() ) {
        xCHECK_RET(a_fileNameValid == xPTR_NULL, false);

        a_fileNameValid->clear();
        return true;
    }

    // check: name size
    if (sRv.size() > xNAME_MAX) {
        xCHECK_RET(a_fileNameValid == xPTR_NULL, false);

        sRv.resize(xNAME_MAX);
    }

#if   xOS_ENV_WIN
   /**
    * MSDN: http://msdn.microsoft.com/en-us/library/windows/desktop/aa365247(v=vs.85).aspx
    * FAQ:  Boost Path Name Portability Guide
    */

   /**
    * MSDN: Do not end a file or directory name with a space or a period.
    * Although the underlying file system may support such names,
    * the Windows shell and user interface does not.
    * However, it is acceptable to specify a period
    * as the first character of a name. For example, ".temp".
    */
    {
        ctchar_t begin = *sRv.begin();
        ctchar_t end   = *(sRv.end() - 1);

        if (a_fileNameValid == xPTR_NULL) {
            // space
            xCHECK_RET(CxConst::space().at(0) == begin, false);
            xCHECK_RET(CxConst::space().at(0) == end,   false);

            // dot
            xCHECK_RET(CxConst::dot().at(0) == begin, false);
            xCHECK_RET(CxConst::dot().at(0) == end,   false);
        } else {
            // skip checks, trim right now
            sRv = CxString::trimChars(sRv, CxConst::space() + CxConst::dot());

            if ( sRv.empty() ) {
                a_fileNameValid->clear();
                return true;
            }
        }

    }

   /**
    * check: excepted chars
    * < (less than)
    * > (greater than)
    * : (colon)
    * " (double quote)
    * / (forward slash)
    * \ (backslash)
    * | (vertical bar or pipe)
    * ? (question mark)
    * * (asterisk)
    */
    {
        std::ctstring_t exceptedChars = xT("<>:\"/\\|?*");

        std::csize_t pos = sRv.find_first_of(exceptedChars);
        if (pos != std::tstring_t::npos) {
            xCHECK_RET(a_fileNameValid == xPTR_NULL, false);

            for ( ; ; ) {
                sRv.erase(pos, 1);
                pos = sRv.find_first_of(exceptedChars, pos);
                xCHECK_DO(pos == std::tstring_t::npos, break);
            }

            if ( sRv.empty() ) {
                a_fileNameValid->clear();
                return true;
            }
        }

    }

   /**
    * check: control chars
    * MAN: For the standard ASCII character set (used by the "C" locale),
    * control characters are those between ASCII codes 0x00 (NUL) and 0x1f (US), plus 0x7f (DEL).
    */
    {
        std::tstring_t::const_iterator cit;

        cit = std::find_if(sRv.begin(), sRv.end(), CxChar::isControl);
        if (cit != sRv.end()) {
            xCHECK_RET(a_fileNameValid == xPTR_NULL, false);

            for ( ; ; ) {
                std::tstring_t::iterator itNewEnd;

                itNewEnd = std::remove_if(sRv.begin(), sRv.end(), CxChar::isControl);
                sRv.erase(itNewEnd, sRv.end());

                cit = std::find_if(sRv.begin(), sRv.end(), CxChar::isControl);
                xCHECK_DO(cit == sRv.end(), break);
            }

            if ( sRv.empty() ) {
                a_fileNameValid->clear();
                return true;
            }
        }

    }

   /**
    * check: device names
    * MSDN: Do not use the following reserved names for the name of a file:
    * CON, PRN, AUX, NUL, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8,
    * COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, and LPT9.
    * Also avoid these names followed immediately by an extension;
    * for example, NUL.txt is not recommended.
    */
    {
        std::ctstring_t reservedNames[] = {
            xT("CON"),  xT("PRN"),  xT("AUX"),  xT("NUL"),  xT("CLOCK$"),
            xT("COM0"), xT("COM1"), xT("COM2"), xT("COM3"), xT("COM4"),
            xT("COM5"), xT("COM6"), xT("COM7"), xT("COM8"), xT("COM9"),
            xT("LPT0"), xT("LPT1"), xT("LPT2"), xT("LPT3"), xT("LPT4"),
            xT("LPT5"), xT("LPT6"), xT("LPT7"), xT("LPT8"), xT("LPT9")
        };

        std::ctstring_t baseFileName = CxPath(sRv).removeExt();

        for (size_t i = 0; i < xARRAY_SIZE(reservedNames); ++ i) {
            bool_t bRv = CxStringCI::compare(baseFileName, reservedNames[i]);
            xCHECK_DO(!bRv, continue);

            xCHECK_RET(a_fileNameValid == xPTR_NULL, false);

            a_fileNameValid->clear();
            return true;
        }

    }
#elif xOS_ENV_UNIX
   /**
    * check: excepted chars
    * /  (forward slash)
    * \0 (xPTR_NULL character)
    */
    {
        std::tstring_t exceptedChars;
        exceptedChars.push_back(xT('/'));
        exceptedChars.push_back(xT('\0'));
        xTEST_EQ(size_t(2), exceptedChars.size());

        std::size_t pos = sRv.find_first_of(exceptedChars);
        if (pos != std::tstring_t::npos) {
            xCHECK_RET(a_fileNameValid == xPTR_NULL, false);

            for ( ; ; ) {
                sRv.erase(pos, 1);
                pos = sRv.find_first_of(exceptedChars, pos);
                xCHECK_DO(pos == std::tstring_t::npos, break);
            }

            if ( sRv.empty() ) {
                a_fileNameValid->clear();
                return true;
            }
        }

    }
#elif xOS_ENV_APPLE
   /**
    * check: excepted chars
    * / (forward slash)
    * : (colon)
    */
    {
        std::ctstring_t exceptedChars = xT("/:");

        std::size_t pos = sRv.find_first_of(exceptedChars);
        if (pos != std::tstring_t::npos) {
            xCHECK_RET(a_fileNameValid == xPTR_NULL, false);

            for ( ; ; ) {
                sRv.erase(pos, 1);
                pos = sRv.find_first_of(exceptedChars, pos);
                xCHECK_DO(pos == std::tstring_t::npos, break);
            }

            if ( sRv.empty() ) {
                a_fileNameValid->clear();
                return true;
            }
        }

    }
#endif

    // out
    if (a_fileNameValid != xPTR_NULL) {
        *a_fileNameValid = sRv;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxPath::isAbsolute() const {
    xCHECK_RET(filePath().empty(),                         false);
    xCHECK_RET(filePath().at(0) == CxConst::slash().at(0), true);

#if xOS_ENV_WIN
    xCHECK_RET(filePath().size() == 1, false);
    xCHECK_RET(CxChar::isAlpha(filePath().at(0)) && CxConst::colon().at(0) == filePath().at(1), true);
#endif

    return false;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
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

    sRv = CxString::replaceAll(sRv, CxConst::unixSlash(), CxConst::winSlash());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
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

    sRv = CxString::replaceAll(sRv, CxConst::winSlash(), CxConst::unixSlash());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
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

#if   xOS_ENV_WIN
    std::ctstring_t slash = CxConst::unixSlash();
#elif xOS_ENV_UNIX
    std::ctstring_t slash = CxConst::winSlash();
#endif

    sRv = CxString::replaceAll(sRv, slash, CxConst::slash());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::absolute() const
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    DWORD          dwRv = 0UL;
    std::tstring_t buff;

    dwRv = ::GetFullPathName(&filePath().at(0), 0, xPTR_NULL, xPTR_NULL);
    xTEST_DIFF(dwRv, 0UL);

    buff.resize(dwRv);

    dwRv = ::GetFullPathName(&filePath().at(0), static_cast<DWORD>( buff.size() ), &buff.at(0),
        xPTR_NULL);
    xTEST_DIFF(dwRv, 0UL);

    buff.resize(dwRv);

    sRv = buff;
#elif xOS_ENV_UNIX
    std::tstring_t buff;

    buff.resize(xPATH_MAX);

    tchar_t *pszRv = ::realpath(&filePath().at(0), &buff.at(0));
    xTEST_PTR(pszRv);

    sRv.assign(pszRv);
#endif

    xTEST_EQ(CxPath(sRv).isAbsolute(), true);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxPath::shortName(
    std::ctstring_t &a_fileName,
    std::csize_t    &a_maxSize
)
{
    xTEST_EQ(a_fileName.empty(), false);
    xTEST_LESS(size_t(0), a_maxSize);

    std::tstring_t sRv;

    std::tstring_t tildaDotExt;

    if ( CxPath(a_fileName).ext().empty() ) {
        tildaDotExt = xT("~");
    } else {
        tildaDotExt = xT("~") + CxConst::dot() + CxPath(a_fileName).ext();
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
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::brief(
    std::csize_t &a_maxSize
) const
{
    xTEST_LESS(size_t(0), a_maxSize);

    // util function
    struct _Functor
    {
        static void_t
        slashesMake(
            std::tstring_t &a_str,
            size_t         *a_num
        )
        {
            size_t index = 0;

            for ( ; ; ) {
                std::csize_t pos = a_str.find_first_of(CxConst::winSlash() + CxConst::unixSlash());

                a_str.erase(0, pos + CxConst::slash().size());

                xCHECK_DO(pos != std::tstring_t::npos,    ++ index);
                xCHECK_DO(*a_num == index && *a_num != 0, break);
                xCHECK_DO(pos == std::tstring_t::npos,    break);
            }

            *a_num = index;
        }
    };


    std::tstring_t sRv  = filePath();
    std::tstring_t path = filePath();
    size_t         num  = 0;

    _Functor::slashesMake(path, &num);

    while (sRv.size() > a_maxSize && num > 2) {
        path = sRv;

        std::size_t numNew = num / 2;

        _Functor::slashesMake(path, &numNew);

        sRv.erase(sRv.find(path), path.size());

        numNew = 2;
        _Functor::slashesMake(path, &numNew);

        sRv.append(CxConst::dot3() + CxConst::slash() + path);

        -- num;
    }

    sRv = CxPath(sRv).toNative(false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::slashAppend() const
{
    return CxString::trimRightChars(filePath(), CxConst::slash()).append(CxConst::slash());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::slashRemove() const
{
    return CxString::trimRightChars(filePath(), CxConst::slash());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline size_t
CxPath::maxSize()
{
    size_t uiRv = 0;

#if   xOS_ENV_WIN
    #if defined(MAX_PATH)
        uiRv = MAX_PATH;
    #else
        std::csize_t defaultSize = 260;

        uiRv = defaultSize;
    #endif
#elif xOS_ENV_UNIX
    #if defined(PATH_MAX)
        uiRv = PATH_MAX;
    #else
        culong_t savedError = 0UL;
        long_t   liRv       = - 1L;
        ulong_t  lastError  = 0UL;

        CxLastError::set(savedError);

        liRv      = ::pathconf("/", _PC_PATH_MAX);
        lastError = CxLastError::get();
        xTEST_EQ(liRv == - 1L && savedError != 0UL, true);

        if (liRv == - 1L && savedError == lastError) {
            // system does not have a limit for the requested resource
            std::csize_t defaultSize = 1024;

            uiRv = defaultSize;
        } else {
            // relative root
            uiRv = static_cast<size_t>( liRv + 1 );
        }
    #endif
#endif

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline size_t
CxPath::nameMaxSize()
{
    size_t uiRv = 0;

#if   xOS_ENV_WIN
    #if defined(FILENAME_MAX)
        uiRv = FILENAME_MAX;
    #else
        std::csize_t defaultSize = 260;

        uiRv = defaultSize;
    #endif
#elif xOS_ENV_UNIX
    #if defined(NAME_MAX)
        uiRv = NAME_MAX;
    #else
        culong_t savedError = 0UL;
        long_t   liRv       = - 1L;
        ulong_t  lastError  = 0UL;

        CxLastError::set(savedError);

        liRv      = ::pathconf("/", _PC_NAME_MAX);
        lastError = CxLastError::get();
        xTEST_EQ(liRv == - 1L && savedError != 0UL, true);

        if (liRv == - 1L && savedError == lastError) {
            // system does not have a limit for the requested resource
            std::csize_t defaultSize = 1024;

            uiRv = defaultSize;
        } else {
            uiRv = static_cast<size_t>( liRv );
        }
    #endif
#endif

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_UNIX

/* static */
inline void_t
CxPath::proc(
    std::ctstring_t    &a_procPath,
    std::vec_tstring_t *a_fileLines
)
{
    // check for existence "/proc" directory
    {
        bool_t bRv = false;

        CxDir proc(xT("/proc"));

        bRv = proc.isExists();
        xCHECK_DO(!bRv, CxTrace() << xT("::: xLib: warning (/proc dir not mount) :::"); return);

        bRv = proc.isEmpty();
        xCHECK_DO(bRv, CxTrace() << xT("::: xLib: warning (/proc dir is empty) :::");  return);
    }

    std::vec_tstring_t vsRv;

    std::tifstream_t ifs(a_procPath.c_str());
    xTEST_EQ(!! ifs, true);
    xTEST_EQ(ifs.fail(), false);
    xTEST_EQ(ifs.good(), true);
    xTEST_EQ(ifs.is_open(), true);
    xTEST_EQ(ifs.eof(), false);

    for ( ; !ifs.eof(); ) {
        std::tstring_t line;

        std::getline(ifs, line);
        xCHECK_DO(line.empty(), continue);

        vsRv.push_back(line);
    }

    // out
    a_fileLines->swap(vsRv);
}

#endif
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_UNIX

/* static */
inline std::tstring_t
CxPath::procValue(
    std::ctstring_t &a_procPath,    ///< file path to proc-file
    std::ctstring_t &a_key          ///< target search data string
)
{
    std::tstring_t     sRv;
    std::vec_tstring_t procFile;

    proc(a_procPath, &procFile);

    xFOREACH_CONST(std::vec_tstring_t, it, procFile) {
        std::csize_t pos = CxStringCI::find(*it, a_key);
        xCHECK_DO(pos == std::tstring_t::npos, continue);

        // parse value
        std::csize_t delimPos = it->find(xT(":"));
        xTEST_DIFF(delimPos, std::string::npos);

        sRv = it->substr(delimPos + 1);
        sRv = CxString::trimSpace(sRv);

        break;
    }

    return sRv;
}

#endif
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, filesystem)
