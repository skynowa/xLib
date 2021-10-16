/**
 * \file  FileType.inl
 * \brief file type
 */


namespace xl::fs
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
FileType::types_t
FileType::_get_impl() const
{
    types_t ftRv = ::GetFileAttributes(filePath().c_str());
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
    set( static_cast<ctypes_t>(Type::RegularFile) );
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
FileType::_isExecutable_impl() const
{
	DWORD binaryType {};
	BOOL blRv = ::GetBinaryType(filePath().c_str(), &binaryType);
	xUNUSED(binaryType);
	if (blRv == FALSE) {
		return false;
	}

    return true;
}
//-------------------------------------------------------------------------------------------------

} // namespace
