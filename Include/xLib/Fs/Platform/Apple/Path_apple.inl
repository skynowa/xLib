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
    std::tstring_t sRv;

    // TODO: [skynowa] Path::_exe_impl()

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_fileExt_impl(
    cFileExt &a_fileExt
)
{
    std::tstring_t sRv;

    switch (a_fileExt) {
    case FileExt::seExe:
        sRv = xT("");
        break;
    case FileExt::seDll:
        sRv = xT("dylib");
        break;
    case FileExt::seLib:
        sRv = xT("a");
        break;
    case FileExt::seObj:
        sRv = xT("o");
        break;
    case FileExt::seShell:
        sRv = xT("sh");
        break;
    default:
        sRv = xT("");
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Path::_isCaseSensitive_impl() const
{
	return ::pathconf(_filePath.c_str(), _PC_CASE_SENSITIVE) ? true : false;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
