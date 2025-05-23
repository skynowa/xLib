/**
 * \file  Path.inl
 * \brief file system path
 */


namespace xl::fs
{

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

	std::tstring_t sRv(maxSize() + 1, {});

	DWORD stored = ::GetModuleFileName(nullptr, &sRv.at(0), static_cast<DWORD>( sRv.size() ));
	xTEST_DIFF(stored, 0UL);

	sRv.resize(stored);

	return sRv;
}
//-------------------------------------------------------------------------------------------------
namespace
{

extern "C" IMAGE_DOS_HEADER __ImageBase;

}

/* static */
std::tstring_t
Path::_dll_impl()
{
    std::tstring_t sRv(maxSize() + 1, {});

    auto procAddress = reinterpret_cast<HMODULE>( &__ImageBase );

    DWORD stored = ::GetModuleFileName(procAddress, &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(stored, 0UL);

    sRv.resize(stored);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_shell_impl()
{
    std::tstring_t sRv;

    LPITEMIDLIST idList {};
    HRESULT hrRv = ::SHGetSpecialFolderLocation(nullptr, CSIDL_WINDOWS, &idList);
    xTEST_EQ(hrRv, S_OK);

    tchar_t buff[MAX_PATH + 1] {};
    BOOL blRv = ::SHGetPathFromIDList(idList, buff);
    xTEST_DIFF(blRv, FALSE);

    sRv.append(buff);
    sRv.append(Const::slash());
    sRv.append(xT("explorer.exe"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_homeDir_impl()
{
    std::tstring_t sRv;

    tchar_t buff[MAX_PATH + 1] {};

    HRESULT hrRv = SHGetFolderPath(nullptr, CSIDL_PROFILE, nullptr, 0UL, &buff[0]);
    xTEST(S_OK == hrRv);

    sRv.assign(buff);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_trashDir_impl()
{
    std::tstring_t sRv;

    LPITEMIDLIST idList {};
    HRESULT hrRv = ::SHGetSpecialFolderLocation(nullptr, CSIDL_BITBUCKET, &idList);
    xTEST_EQ(hrRv, S_OK);

    tchar_t buff[MAX_PATH + 1] {};
    BOOL blRv = ::SHGetPathFromIDList(idList, buff);
    xTEST_DIFF(blRv, FALSE);

    sRv = buff;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::_volume_impl() const
{
    std::csize_t driveDelimPos = _filePath.find(Const::colon());
    xTEST_DIFF(driveDelimPos, std::tstring_t::npos);
    xTEST_EQ(driveDelimPos, size_t(1));

    return _filePath.substr(0, driveDelimPos + Const::colon().size());
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_fileExt_impl(
    cFileExt a_fileExt
)
{
    std::tstring_t sRv;

    switch (a_fileExt) {
    case FileExt::Exe:
        sRv = xT("exe");
        break;
    case FileExt::Dll:
        sRv = xT("dll");
        break;
    case FileExt::Lib:
        sRv = xT("lib");
        break;
    case FileExt::Obj:
        sRv = xT("obj");
        break;
    case FileExt::Shell:
        sRv = xT("bat");
        break;
    default:
        sRv = xT("");
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Path::_isNameValid_impl(
    std::ctstring_t &a_fileName,                    ///< file, directory name
    std::tstring_t  *a_fileNameValid /* = nullptr */   ///< [out] normalized name
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
    * the Windows shell and user does not.
    * However, it is acceptable to specify a period
    * as the first character of a name. For example, ".temp".
    */
    {
        ctchar_t begin = sRv.front();
        ctchar_t end   = sRv.back();

        if (a_fileNameValid == nullptr) {
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

        std::size_t pos = sRv.find_first_of(exceptedChars);
        if (pos != std::tstring_t::npos) {
            xCHECK_RET(a_fileNameValid == nullptr, false);

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
        auto isControl = [](ctchar_t a_ch) -> bool
        {
            return Char(a_ch).isControl();
        };

        auto cit = std::find_if(sRv.cbegin(), sRv.cend(), isControl);
        if (cit != sRv.cend()) {
            xCHECK_RET(a_fileNameValid == nullptr, false);

            for ( ; ; ) {
                std::tstring_t::iterator itNewEnd;

                itNewEnd = std::remove_if(sRv.begin(), sRv.end(), isControl);
                sRv.erase(itNewEnd, sRv.cend());

                cit = std::find_if(sRv.cbegin(), sRv.cend(), isControl);
                xCHECK_DO(cit == sRv.cend(), break);
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
        std::ctstring_t reservedNames[]
		{
            xT("CON"),  xT("PRN"),  xT("AUX"),  xT("NUL"),  xT("CLOCK$"),
            xT("COM0"), xT("COM1"), xT("COM2"), xT("COM3"), xT("COM4"),
            xT("COM5"), xT("COM6"), xT("COM7"), xT("COM8"), xT("COM9"),
            xT("LPT0"), xT("LPT1"), xT("LPT2"), xT("LPT3"), xT("LPT4"),
            xT("LPT5"), xT("LPT6"), xT("LPT7"), xT("LPT8"), xT("LPT9")
        };

        std::ctstring_t baseFileName = Path(sRv).removeExt().str();

        for (size_t i = 0; i < xARRAY_SIZE(reservedNames); ++ i) {
            bool_t bRv = StringCI::compare(baseFileName, reservedNames[i]);
            xCHECK_DO(!bRv, continue);

            xCHECK_RET(a_fileNameValid == nullptr, false);

            a_fileNameValid->clear();

            return true;
        }

    }

    // out
    if (a_fileNameValid != nullptr) {
        *a_fileNameValid = sRv;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Path::_isAbsolute_impl() const
{
    xCHECK_RET(_filePath.size() == 1, false);
    xCHECK_RET(Char(_filePath.at(0)).isAlpha() && Const::colon().at(0) == _filePath.at(1), true);

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

    DWORD          dwRv {};
    std::tstring_t buff;

    dwRv = ::GetFullPathName(&_filePath.at(0), 0, nullptr, nullptr);
    xTEST_DIFF(dwRv, 0UL);

    buff.resize(dwRv);

    dwRv = ::GetFullPathName(&_filePath.at(0), static_cast<DWORD>( buff.size() ), &buff.at(0),
        nullptr);
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
    size_t uiRv {};

#if defined(MAX_PATH)
    uiRv = MAX_PATH;
#else
    std::csize_t defaultSize {260};

    uiRv = defaultSize;
#endif

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
size_t
Path::_nameMaxSize_impl()
{
    size_t uiRv {};

#if defined(FILENAME_MAX)
    uiRv = FILENAME_MAX;
#else
    std::csize_t defaultSize {260};

    uiRv = defaultSize;
#endif

    return uiRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
