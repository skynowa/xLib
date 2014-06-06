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

    xTSTAT_STRUCT info;   xSTRUCT_ZERO(info);

    int_t iRv = ::xTSTAT(filePath().c_str(), &info);
    xTEST_NA(iRv);
    if (iRv == - 1) {
        ftRv = faInvalid;
    } else {
        ftRv = (info.st_mode & S_IFMT);
    }

    return ftRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::_set_impl(
    ctypes_t &a_values
) const
{
    int_t iRv = ::xTCHMOD(filePath().c_str(), a_values);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::_clear_impl() const
{
    xNA
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
