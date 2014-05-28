/**
 * \file  CxPath.inl
 * \brief file system path
 */


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxPath::_exe_impl()
{
    std::tstring_t sRv;

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

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

static void_t function() { ; }

xNAMESPACE_ANONYM_END

/* static */
inline std::tstring_t
CxPath::_dll_impl()
{
    std::tstring_t sRv;

    Dl_info  diInfo;          xSTRUCT_ZERO(diInfo);
    void_t (*procAddress)() = ::function;

    int_t iRv = ::dladdr(&procAddress, &diInfo);
    xTEST_LESS(iRv, 0);

    sRv = CxPath(diInfo.dli_fname).absolute();

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxPath::_standartExt_impl(
    const ExStandartExt &a_fileExt
)
{
    std::tstring_t sRv;

    switch (a_fileExt) {
#if xENV_UNIX
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
#elif xENV_APPLE
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
/* static */
inline bool_t
CxPath::_isNameValid_impl(
    std::ctstring_t &a_fileName,                    ///< file, directory name
    std::tstring_t  *a_fileNameValid /* = xPTR_NULL */   ///< [out] normalized name
)
{
    std::tstring_t sRv(a_fileName);

#if xENV_UNIX
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
#elif xENV_APPLE
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
CxPath::_isAbsolute_impl() const
{
    return false;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxPath::_toNative_impl(
    std::tstring_t *a_filePath
) const
{
    *a_filePath = CxString::replaceAll(*a_filePath, CxConst::unixSlash(), CxConst::slash());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::_absolute_impl() const
{
    std::tstring_t sRv;

    std::tstring_t buff;
    buff.resize(xPATH_MAX);

    tchar_t *pszRv = ::realpath(&filePath().at(0), &buff.at(0));
    xTEST_PTR(pszRv);

    sRv.assign(pszRv);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline size_t
CxPath::_maxSize_impl()
{
    size_t uiRv = 0;

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

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline size_t
CxPath::_nameMaxSize_impl()
{
    size_t uiRv = 0;

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

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
