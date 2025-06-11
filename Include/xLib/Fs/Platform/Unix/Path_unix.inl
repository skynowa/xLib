/**
 * \file  Path.inl
 * \brief file system path
 */


#include <xLib/Core/Const.h>
#include <xLib/Log/Cout.h>
#include <xLib/System/Env.h>

namespace xl::fs
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
namespace
{

#if (cmOPTION_PROJECT_LIB_SHARE || cmOPTION_PROJECT_LIB_MODULE)
static void_t function() {}
#endif

}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_dll_impl()
{
	std::tstring_t sRv;

#if (cmOPTION_PROJECT_LIB_SHARE || cmOPTION_PROJECT_LIB_MODULE)
	Dl_info  diInfo {};
	void_t (*procAddress)() = function;

	int_t iRv = ::dladdr(&procAddress, &diInfo);
	if (iRv == 0) {
		sRv = Const::strEmpty();
	} else {
		xTEST_GR(iRv, 0);

		sRv = Path(diInfo.dli_fname).absolute().str();
	}
#else
	sRv = Const::strEmpty();
#endif

	return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_shell_impl()
{
    std::string sRv;

    User()._passwd(nullptr, nullptr, nullptr, nullptr, nullptr, &sRv);

    return xA2T(sRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_homeDir_impl()
{
   /*
    * MAN: user's home directory
    *
    * Login programs use the value of this field to initialize
    * the HOME environment variable for the login shell.
    * An application that wants to determine its user's home directory
    * should inspect the value of HOME (rather than the value getpwuid(getuid())->pw_dir)
    * since this allows the user to modify their notion of "the home directory"
    * during a login session. To determine the (initial) home directory of another user,
    * it is necessary to use getpwnam("username")->pw_dir or similar.
    */

    // try to get from API
	{
		std::string asRv;

		User()._passwd(nullptr, nullptr, nullptr, nullptr, &asRv, nullptr);
		xCHECK_RET(!asRv.empty(), xA2T(asRv));
	}

    // try to get from system environment
    std::ctstring_t sRv = Env(xT("HOME")).value();
    xTEST(!sRv.empty());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/**
 * https://stackoverflow.com/questions/17964439/move-files-to-trash-recycle-bin-in-qt
 */
/* static */
std::tstring_t
Path::_trashDir_impl()
{
	std::tstring_t sRv;

	{
		std::vec_tstring_t paths;

		// env XDG_DATA_HOME
		{
			std::ctstring_t &xdgDataHome = Env(xT("XDG_DATA_HOME")).value();
			if ( !xdgDataHome.empty() ) {
				paths.emplace_back(xdgDataHome + xT("/Trash"));
			}
		}

		// Home dirs
		{
			std::ctstring_t &home = homeDir().str();

			paths.emplace_back(home + xT("/.local/share/Trash"));
			paths.emplace_back(home + xT("/.trash"));

		#if xENV_APPLE
		   /**
			* https://stackoverflow.com/questions/64663834/determine-if-a-file-is-inside-any-macos-trash-folder
			*/
			paths.emplace_back(home + xT("/.Trash"));
			paths.emplace_back(xT("/.Trashes"));

			// "/Users/[user]/.Trash"     - any other user's trash - n/a
			// "/Volumes/[user]/.Trashes" - n/a
			// "~/Library/Mobile Documents/com~apple~CloudDocs/.Trash" - iCloud - n/a
		#endif
		}

		// detect
		for (const auto &it_path : paths) {
			if ( Dir(it_path).isExists() ) {
				sRv = it_path;
				break;
			}
		}
	}

	// checks
	{
		if ( sRv.empty() ) {
			LogCoutWarning() << Format::str(xT("{} - Can't detect"), xFUNCTION);
			return {};
		}

		std::ctstring_t &pathInfo = sRv + xT("/info");
		if ( !Dir(pathInfo).isExists() ) {
			xTEST(false && "Trash doesnt looks like FreeDesktop.org Trash specification");
			return {};
		}

		std::ctstring_t &pathFiles = sRv + xT("/files");
		if ( !Dir(pathFiles).isExists() ) {
			xTEST(false && "Trash doesnt looks like FreeDesktop.org Trash specification");
			return {};
		}
	}

	return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::_volume_impl() const
{
    xCHECK_RET(_filePath.empty(), std::tstring_t());

    return std::tstring_t(1, _filePath[0]);
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Path::_isNameValid_impl(
    std::ctstring_t &a_fileName,                     ///< file, directory name
    std::tstring_t  *a_fileNameValid /* = nullptr */ ///< [out] normalized name
)
{
    std::tstring_t sRv(a_fileName);

#if xENV_APPLE
   /**
    * check: excepted chars
    * / (forward slash)
    * : (colon)
    */
    {
        std::ctstring_t exceptedChars  {xT('/'), xT(':')};

        std::size_t pos = sRv.find_first_of(exceptedChars);
        if (pos != std::tstring_t::npos) {
            xCHECK_RET(a_fileNameValid == nullptr, false);

            // Normalize
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
#else
   /**
    * check: excepted chars
    * /  (forward slash)
    * \0 (nullptr character)
    */
    {
        std::ctstring_t exceptedChars {xT('/'), xT('\0')};
        xTEST_EQ(exceptedChars.size(), size_t(2));

        std::size_t pos = sRv.find_first_of(exceptedChars);
        if (pos != std::tstring_t::npos) {
            xCHECK_RET(a_fileNameValid == nullptr, false);

            // Normalize
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
    if (a_fileNameValid != nullptr) {
        *a_fileNameValid = sRv;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Path::_isAbsolute_impl() const
{
    return false;
}
//-------------------------------------------------------------------------------------------------
void_t
Path::_toNative_impl(
    std::tstring_t *a_filePath
) const
{
    *a_filePath = String::replaceAll(*a_filePath, Const::winSlash(), Const::slash());
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::_absolute_impl() const
{
    std::string asRv;

    std::string buff(maxSize() + 1, {});

    const char *pszRv = ::realpath(xT2A(_filePath).c_str(), &buff.at(0));
    xTEST_PTR(pszRv);

    asRv.assign(pszRv);

    return xA2T(asRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
size_t
Path::_maxSize_impl()
{
	std::size_t uiRv {};

#if   defined(MAXPATHLEN)
    uiRv = MAXPATHLEN;
#elif defined(PATH_MAX)
    uiRv = PATH_MAX;
#else
    culong_t savedError  {};
    long_t   liRv        {};
    ulong_t  nativeError {};

    NativeError::set(savedError);

    liRv        = ::pathconf("/", _PC_PATH_MAX);
    nativeError = NativeError::get();
    xTEST(liRv == - 1L && savedError != 0UL);

    if (liRv == - 1L && savedError == nativeError) {
        // system does not have a limit for the requested resource
        std::csize_t defaultSize = 1024;

        uiRv = defaultSize;
    } else {
        // relative root
        uiRv = static_cast<size_t>(liRv + 1);
    }
#endif

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
size_t
Path::_nameMaxSize_impl()
{
	std::size_t uiRv {};

#if defined(NAME_MAX)
    uiRv = NAME_MAX;
#else
    culong_t savedError  {};
    long_t   liRv        {};
    ulong_t  nativeError {};

    NativeError::set(savedError);

    liRv        = ::pathconf("/", _PC_NAME_MAX);
    nativeError = NativeError::get();
    xTEST(liRv == - 1L && savedError != 0UL);

    if (liRv == - 1L && savedError == nativeError) {
        // system does not have a limit for the requested resource
        std::csize_t defaultSize = 1024;

        uiRv = defaultSize;
    } else {
        uiRv = static_cast<size_t>(liRv);
    }
#endif

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::proc(
	std::ctstring_t                                      &a_procPath,	///< file path to proc-file
	std::function<bool_t(std::ctstring_t &line)>          a_cond,		///< condition
	std::function<std::tstring_t(std::ctstring_t &line)>  a_op			///< operation
)
{
    // check for existence "/proc" directory
    {
        Dir proc(xT("/proc"));
        xCHECK_DO(!proc.isExists(), LogCoutWarning() << xT("::: xLib: warning (/proc dir not mount) :::"));
        xCHECK_DO(proc.isEmpty(),   LogCoutWarning() << xT("::: xLib: warning (/proc dir is empty) :::"));
    }

	std::tifstream_t ifs(a_procPath);
	xTEST(!! ifs);
	xTEST(!ifs.fail());
	xTEST(ifs.good());
	xTEST(ifs.is_open());
	xTEST(!ifs.eof());

	for ( ; !ifs.eof(); ) {
		std::tstring_t line;
		std::getline(ifs, line);

		if ( a_cond(line) ) {
			return a_op(line);
		}
	}

	return {};
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::procValue(
    std::ctstring_t &a_procPath, ///< file path to proc-file
    std::ctstring_t &a_key       ///< target search data string
)
{
	auto cond = [&](std::ctstring_t &it_line) -> bool_t
	{
		return (it_line.find(a_key) != std::tstring_t::npos);
	};

	auto op = [](std::ctstring_t &a_line) -> std::tstring_t
	{
		std::tstring_t sRv;

		// parse value
		std::csize_t delimPos = a_line.find(xT(":"));
		xTEST_DIFF(delimPos, std::string::npos);

		sRv = a_line.substr(delimPos + 1);
		sRv = String::trimSpace(sRv);

		return sRv;
	};

	return proc(a_procPath, cond, op);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::readSymLink(
	std::ctstring_t &a_symLinkPath
)
{
    bool_t bRv = FileInfo(a_symLinkPath).isExists();
    xCHECK_RET(!bRv, std::tstring_t());

    std::string asRv(Path::maxSize() + 1, {});

    ssize_t readed {- 1};

    for ( ; ; ) {
        readed = ::readlink(xT2A(a_symLinkPath).c_str(), &asRv.at(0), asRv.size() *
            sizeof(std::string::value_type));
        xCHECK_DO(readed == ssize_t(- 1), break);	// TODO: test - add ??
        xCHECK_DO(asRv.size() * sizeof(std::string::value_type) > static_cast<size_t>(readed), break);

        asRv.resize(asRv.size() * 2);
    }

    asRv.resize( static_cast<std::size_t>(readed) );

    return xA2T(asRv);
}
//-------------------------------------------------------------------------------------------------

} // namespace
