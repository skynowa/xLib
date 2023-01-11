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
	std::uint32_t  buffSize = PATH_MAX;
	std::tstring_t buff(buffSize + 1, xT('\0'));

	int_t iRv = ::_NSGetExecutablePath(&buff[0], &buffSize);
	if (iRv != 0) {
		buff.resize(buffSize);

		iRv = ::_NSGetExecutablePath(&buff[0], &buffSize);
		xCHECK_RET(iRv == -1, std::tstring_t());
	}

	return buff.c_str();	// Trim '\0'
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
