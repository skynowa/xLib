/**
 * \file  CxFileType.inl
 * \brief file type
 */


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxFileType::types_t
CxFileType::_get_impl() const
{
    types_t ftRv = faInvalid;

    ftRv = ::GetFileAttributes(filePath().c_str());
    xTEST_NA(ftRv);

    return ftRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::_set_impl(
    ctypes_t &a_values
) const
{
    BOOL blRv = ::SetFileAttributes(filePath().c_str(), a_values);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::_clear_impl() const
{
    set(faNormal);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
