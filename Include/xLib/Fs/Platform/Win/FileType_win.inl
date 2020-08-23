/**
 * \file  FileType.inl
 * \brief file type
 */


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
FileType::types_t
FileType::_get_impl() const
{
    types_t ftRv = Type::Invalid;

    ftRv = ::GetFileAttributes(filePath().c_str());
    xTEST_NA(ftRv);

    return ftRv;
}
//-------------------------------------------------------------------------------------------------
void_t
FileType::_set_impl(
    ctypes_t a_values
) const
{
    BOOL blRv = ::SetFileAttributes(filePath().c_str(), a_values);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
void_t
FileType::_clear_impl() const
{
    set(Normal);
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
FileType::_isExecutable_impl() const
{
	DWORD binaryType {-1};
	BOOL blRv = ::GetBinaryType(filePath().c_str(), &binaryType);
	xUNUSED(binaryType);
	if (blRv == FALSE) {
		return false;
	}

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
