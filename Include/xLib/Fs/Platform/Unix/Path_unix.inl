/**
 * \file  Path.inl
 * \brief file system path
 */


#include <xLib/Core/Const.h>
#include <xLib/System/Environment.h>

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
	xTEST_DIFF(iRv, 0);

	sRv = Path(diInfo.dli_fname).absolute();
#else
	sRv = Const::strEmpty();
#endif

	return sRv;
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
    std::string asRv;

    User()._passwd(nullptr, nullptr, nullptr, nullptr, &asRv, nullptr);
    xCHECK_RET(!asRv.empty(), xA2T(asRv));

    // try to get from system environment
    std::ctstring_t sRv = Environment(xT("HOME")).var();
    xTEST(!sRv.empty());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_shellPath_impl()
{
    std::string sRv;

    User()._passwd(nullptr, nullptr, nullptr, nullptr, nullptr, &sRv);

    return xA2T(sRv);
}
//-------------------------------------------------------------------------------------------------
/**
 * https://stackoverflow.com/questions/17964439/move-files-to-trash-recycle-bin-in-qt
 */
/* static */
std::tstring_t
Path::_trashPath_impl()
{
	std::tstring_t sRv;

	std::vec_tstring_t paths;

	// env XDG_DATA_HOME
	{
		std::ctstring_t &xdgDataHome = Environment(xT("XDG_DATA_HOME")).var();
		if ( !xdgDataHome.empty() ) {
			paths.emplace_back(xdgDataHome + xT("/Trash"));
		}
	}

	// Home dirs
	{
		std::ctstring_t &home = homeDir().str();

		paths.emplace_back(home + xT("/.local/share/Trash"));
		paths.emplace_back(home + xT("/.trash"));
	}

	// detect
	for (const auto &it_path : paths) {
		if ( Dir(it_path).isExists() ) {
			sRv = it_path;
			break;
		}
	}

	// checks
	{
		if ( sRv.empty() ) {
			xTEST(false && "Can't detect trash folder");
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
    std::ctstring_t &a_fileName,                    ///< file, directory name
    std::tstring_t  *a_fileNameValid /* = nullptr */   ///< [out] normalized name
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
        std::ctstring_t exceptedChars = xT("/:");

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
#else
   /**
    * check: excepted chars
    * /  (forward slash)
    * \0 (nullptr character)
    */
    {
        std::tstring_t exceptedChars;
        exceptedChars.push_back(xT('/'));
        exceptedChars.push_back(xT('\0'));
        xTEST_EQ(size_t(2), exceptedChars.size());

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

    std::string buff;
    buff.resize( maxSize() );

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

#if defined(PATH_MAX)
    uiRv = PATH_MAX;
#else
    culong_t savedError  {};
    long_t   liRv        {};
    ulong_t  nativeError {};

    NativeError::set(savedError);

    liRv        = ::pathconf("/", _PC_PATH_MAX);
    nativeError = NativeError::get();
    xTEST_EQ(liRv == - 1L && savedError != 0UL, true);

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
void_t
Path::proc(
    std::ctstring_t    &a_procPath,
    std::vec_tstring_t *a_fileLines
)
{
    // check for existence "/proc" directory
    {
        bool_t bRv {};

        Dir proc(xT("/proc"));

        bRv = proc.isExists();
        xCHECK_DO(!bRv, Trace() << xT("::: xLib: warning (/proc dir not mount) :::"); return);

        bRv = proc.isEmpty();
        xCHECK_DO(bRv, Trace() << xT("::: xLib: warning (/proc dir is empty) :::");  return);
    }

    std::vec_tstring_t vsRv;

    std::tifstream_t ifs( xT2A(a_procPath) );
    xTEST(!! ifs);
    xTEST(!ifs.fail());
    xTEST(ifs.good());
    xTEST(ifs.is_open());
    xTEST(!ifs.eof());

    for ( ; !ifs.eof(); ) {
        std::tstring_t line;
        std::getline(ifs, line);
        xCHECK_DO(line.empty(), continue);

        vsRv.push_back(line);
    }

    // out
    a_fileLines->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::procValue(
    std::ctstring_t &a_procPath,    ///< file path to proc-file
    std::ctstring_t &a_key          ///< target search data string
)
{
    std::tstring_t     sRv;
    std::vec_tstring_t procFile;

    proc(a_procPath, &procFile);

    for (const auto &it : procFile) {
        std::csize_t pos = StringCI::find(it, a_key);
        xCHECK_DO(pos == std::tstring_t::npos, continue);

        // parse value
        std::csize_t delimPos = it.find(xT(":"));
        xTEST_DIFF(delimPos, std::string::npos);

        sRv = it.substr(delimPos + 1);
        sRv = String::trimSpace(sRv);

        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
