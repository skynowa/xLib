/**
 * \file  File_win.inl
 * \brief File
 */


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
File::_createSymlink_impl(
	std::ctstring_t &a_filePathTo
) const
{
	BOOL bRv {};

	DWORD flags {};
	bRv = ::CreateSymbolicLink(_filePath.c_str(), a_filePathTo.c_str(), flags);
	xTEST_DIFF(bRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
