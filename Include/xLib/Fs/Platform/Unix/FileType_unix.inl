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
    auto ftRv = static_cast<types_t>(Type::Unknown);

    xTSTAT_STRUCT info {};

    int_t iRv = xTSTAT(filePath().c_str(), &info);
    xTEST_NA(iRv);
    if (iRv == - 1) {
        ftRv = static_cast<types_t>(Type::Unknown);
    } else {
        ftRv = (info.st_mode & S_IFMT);
    }

    return ftRv;
}
//-------------------------------------------------------------------------------------------------
void_t
FileType::_set_impl(
    ctypes_t a_values
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
bool_t
FileType::_isExecutable_impl() const
{
    int_t iRv = xTACCESS(filePath().c_str(), X_OK);
    xCHECK_RET(iRv == - 1, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

} // namespace
