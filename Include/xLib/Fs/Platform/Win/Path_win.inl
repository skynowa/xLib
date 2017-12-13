/**
 * \file  Path.inl
 * \brief file system path
 */


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_exe_impl()
{
    // REVIEW: QueryFullProcessImageName on xOS_WIN_VER > xOS_WIN_S03

    std::tstring_t sRv;
    sRv.resize(xPATH_MAX);

    DWORD stored = ::GetModuleFileName(xPTR_NULL, &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(stored, 0UL);

    sRv.resize(stored);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

extern "C" IMAGE_DOS_HEADER __ImageBase;

xNAMESPACE_ANONYM_END

/* static */
std::tstring_t
Path::_dll_impl()
{
    std::tstring_t sRv;
    sRv.resize(xPATH_MAX);

    HMODULE procAddress = reinterpret_cast<HMODULE>( &__ImageBase );

    DWORD stored = ::GetModuleFileName(procAddress, &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(stored, 0UL);

    sRv.resize(stored);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::drive() const
{
    std::csize_t driveDelimPos = filePath().find(Const::colon());
    xTEST_DIFF(driveDelimPos, std::tstring_t::npos);
    xTEST_EQ(driveDelimPos, size_t(1));

    return filePath().substr(0, driveDelimPos + Const::colon().size());
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_fileExt_impl(
    const FileExt &a_fileExt
)
{
    std::tstring_t sRv;

    switch (a_fileExt) {
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
    default:
        sRv = xT("");
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::setDrive(
    std::ctstring_t &a_drivePath
)
{
    // csDrivePath

    std::tstring_t sRv(filePath());

    std::tstring_t driveStr = Path(sRv).drive();
    xTEST_EQ(driveStr.empty(), false);

    std::csize_t pos = sRv.find(driveStr);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return sRv.replace(pos, driveStr.size(), a_drivePath);
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Path::_isNameValid_impl(
    std::ctstring_t &a_fileName,                    ///< file, directory name
    std::tstring_t  *a_fileNameValid /* = xPTR_NULL */   ///< [out] normalized name
)
{
    std::tstring_t sRv(a_fileName);

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
        ctchar_t end   = *sRv.back();

        if (a_fileNameValid == xPTR_NULL) {
            // space
            xCHECK_RET(Const::space().at(0) == begin, false);
            xCHECK_RET(Const::space().at(0) == end,   false);

            // dot
            xCHECK_RET(Const::dot().at(0) == begin, false);
            xCHECK_RET(Const::dot().at(0) == end,   false);
        } else {
            // skip checks, trim right now
            sRv = String::trimChars(sRv, Const::space() + Const::dot());

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

        cit = std::find_if(sRv.begin(), sRv.end(), CharT::isControl);
        if (cit != sRv.end()) {
            xCHECK_RET(a_fileNameValid == xPTR_NULL, false);

            for ( ; ; ) {
                std::tstring_t::iterator itNewEnd;

                itNewEnd = std::remove_if(sRv.begin(), sRv.end(), CharT::isControl);
                sRv.erase(itNewEnd, sRv.end());

                cit = std::find_if(sRv.begin(), sRv.end(), CharT::isControl);
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

        std::ctstring_t baseFileName = Path(sRv).removeExt();

        for (size_t i = 0; i < xARRAY_SIZE(reservedNames); ++ i) {
            bool_t bRv = StringCI::compare(baseFileName, reservedNames[i]);
            xCHECK_DO(!bRv, continue);

            xCHECK_RET(a_fileNameValid == xPTR_NULL, false);

            a_fileNameValid->clear();
            return true;
        }

    }

    // out
    if (a_fileNameValid != xPTR_NULL) {
        *a_fileNameValid = sRv;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Path::_isCaseSensitive_impl() const
{
    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Path::_isAbsolute_impl() const
{
    xCHECK_RET(filePath().size() == 1, false);
    xCHECK_RET(CharT::isAlpha(filePath().at(0)) && Const::colon().at(0) == filePath().at(1), true);

    return false;
}
//-------------------------------------------------------------------------------------------------
void_t
Path::_toNative_impl(
    std::tstring_t *a_filePath
) const
{
    *a_filePath = String::replaceAll(*a_filePath, Const::unixSlash(), Const::slash());
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::_absolute_impl() const
{
    std::tstring_t sRv;

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

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
size_t
Path::_maxSize_impl()
{
    size_t uiRv = 0;

#if defined(MAX_PATH)
    uiRv = MAX_PATH;
#else
    std::csize_t defaultSize = 260;

    uiRv = defaultSize;
#endif

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
size_t
Path::_nameMaxSize_impl()
{
    size_t uiRv = 0;

#if defined(FILENAME_MAX)
    uiRv = FILENAME_MAX;
#else
    std::csize_t defaultSize = 260;

    uiRv = defaultSize;
#endif

    return uiRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
