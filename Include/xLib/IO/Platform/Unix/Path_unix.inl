/**
 * \file  Path.inl
 * \brief file system path
 */


#include <xLib/Core/Const.h>


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

static void_t function() { ; }

xNAMESPACE_ANONYM_END

/* static */
xINLINE std::tstring_t
Path::_dll_impl()
{
    std::tstring_t sRv;

#if (xPROJECT_LIB_SHARE || cmOPTION_PROJECT_LIB_MODULE)
    Dl_info  diInfo;          xSTRUCT_ZERO(diInfo);
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
xINLINE bool_t
Path::_isNameValid_impl(
    std::ctstring_t &a_fileName,                    ///< file, directory name
    std::tstring_t  *a_fileNameValid /* = xPTR_NULL */   ///< [out] normalized name
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
#else
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
#endif

    // out
    if (a_fileNameValid != xPTR_NULL) {
        *a_fileNameValid = sRv;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Path::_isAbsolute_impl() const
{
    return false;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Path::_toNative_impl(
    std::tstring_t *a_filePath
) const
{
    *a_filePath = String::replaceAll(*a_filePath, Const::winSlash(), Const::slash());
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Path::_absolute_impl() const
{
    std::string asRv;

    std::string buff;
    buff.resize(xPATH_MAX);

    const char *pszRv = ::realpath(xT2A(filePath()).c_str(), &buff.at(0));
    xTEST_PTR(pszRv);

    asRv.assign(pszRv);

    return xA2T(asRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE size_t
Path::_maxSize_impl()
{
    size_t uiRv = 0;

#if defined(PATH_MAX)
    uiRv = PATH_MAX;
#else
    culong_t savedError  = 0UL;
    long_t   liRv        = - 1L;
    ulong_t  nativeError = 0UL;

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
        uiRv = static_cast<size_t>( liRv + 1 );
    }
#endif

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE size_t
Path::_nameMaxSize_impl()
{
    size_t uiRv = 0;

#if defined(NAME_MAX)
    uiRv = NAME_MAX;
#else
    culong_t savedError  = 0UL;
    long_t   liRv        = - 1L;
    ulong_t  nativeError = 0UL;

    NativeError::set(savedError);

    liRv        = ::pathconf("/", _PC_NAME_MAX);
    nativeError = NativeError::get();
    xTEST_EQ(liRv == - 1L && savedError != 0UL, true);

    if (liRv == - 1L && savedError == nativeError) {
        // system does not have a limit for the requested resource
        std::csize_t defaultSize = 1024;

        uiRv = defaultSize;
    } else {
        uiRv = static_cast<size_t>( liRv );
    }
#endif

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Path::proc(
    std::ctstring_t    &a_procPath,
    std::vec_tstring_t *a_fileLines
)
{
    // check for existence "/proc" directory
    {
        bool_t bRv = false;

        Dir proc(xT("/proc"));

        bRv = proc.isExists();
        xCHECK_DO(!bRv, Trace() << xT("::: xLib: warning (/proc dir not mount) :::"); return);

        bRv = proc.isEmpty();
        xCHECK_DO(bRv, Trace() << xT("::: xLib: warning (/proc dir is empty) :::");  return);
    }

    std::vec_tstring_t vsRv;

    std::tifstream_t ifs( xT2A(a_procPath).c_str() );
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
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Path::procValue(
    std::ctstring_t &a_procPath,    ///< file path to proc-file
    std::ctstring_t &a_key          ///< target search data string
)
{
    std::tstring_t     sRv;
    std::vec_tstring_t procFile;

    proc(a_procPath, &procFile);

    xFOR_EACH_CONST(std::vec_tstring_t, it, procFile) {
        std::csize_t pos = StringCI::find(*it, a_key);
        xCHECK_DO(pos == std::tstring_t::npos, continue);

        // parse value
        std::csize_t delimPos = it->find(xT(":"));
        xTEST_DIFF(delimPos, std::string::npos);

        sRv = it->substr(delimPos + 1);
        sRv = String::trimSpace(sRv);

        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
