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
    types_t ftRv = faInvalid;

    xTSTAT_STRUCT info;   xSTRUCT_ZERO(info);

    int_t iRv = xTSTAT(filePath().c_str(), &info);
    xTEST_NA(iRv);
    if (iRv == - 1) {
        ftRv = faInvalid;
    } else {
        ftRv = (info.st_mode & S_IFMT);
    }

    return ftRv;
}
//-------------------------------------------------------------------------------------------------
void_t
FileType::_set_impl(
    ctypes_t &a_values
) const
{
    int_t iRv = xTCHMOD(filePath().c_str(), a_values);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
void_t
FileType::_clear_impl() const
{
    xNA
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
