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
	std::tstring_t sRv;

	// TODO: [skynowa] Path::_exe_impl()

	return sRv;
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
        sRv = xT("");
        break;
    case FileExt::Dll:
        sRv = xT("dylib");
        break;
    case FileExt::Lib:
        sRv = xT("a");
        break;
    case FileExt::Obj:
        sRv = xT("o");
        break;
    case FileExt::Shell:
        sRv = xT("sh");
        break;
    default:
        sRv = xT("");
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
