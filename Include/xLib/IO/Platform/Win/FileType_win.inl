/**
 * \file  FileType.inl
 * \brief file type
 */


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline FileType::types_t
FileType::_get_impl() const
{
    types_t ftRv = faInvalid;

    ftRv = ::GetFileAttributes(filePath().c_str());
    xTEST_NA(ftRv);

    return ftRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
FileType::_set_impl(
    ctypes_t &a_values
) const
{
    BOOL blRv = ::SetFileAttributes(filePath().c_str(), a_values);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline void_t
FileType::_clear_impl() const
{
    set(faNormal);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
