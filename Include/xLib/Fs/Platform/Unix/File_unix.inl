/**
 * \file  File.inl
 * \brief file
 */


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
bool_t
File::_isFile_impl(
    const FileType &a_type
)
{
    bool_t bRv = a_type.isExists(FileType::faRegularFile);
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
File::_time_impl(
    std::ctstring_t &a_filePath,
    time_t          *a_create,
    time_t          *a_access,
    time_t          *a_modified
)
{
    xUNUSED(a_create);

    xTSTAT_STRUCT info; xSTRUCT_ZERO(info);

    int_t iRv = xTSTAT(a_filePath.c_str(), &info);
    xTEST_DIFF(iRv, - 1);

    // create - n/a
    Utils::ptrAssignT(a_access,   static_cast<const time_t &>( info.st_atime ));
    Utils::ptrAssignT(a_modified, static_cast<const time_t &>( info.st_mtime ));
}
//-------------------------------------------------------------------------------------------------
/*static */
void_t
File::_setTime_impl(
    std::ctstring_t &a_filePath,
    const time_t    &a_create,
    const time_t    &a_access,
    const time_t    &a_modified
)
{
    xUNUSED(a_create);

    utimbuf times = {0, 0};

    // times.create - n/a
    times.actime  = a_access;
    times.modtime = a_modified;

    int_t iRv = ::utime(xT2A(a_filePath).c_str(), &times);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
