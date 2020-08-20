/**
 * \file  FileInfo_unix.inl
 * \brief File information
 */


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void_t
FileInfo::_time_impl(
    time_t *a_create,
    time_t *a_access,
    time_t *a_modified
) const
{
    xUNUSED(a_create);

    xTSTAT_STRUCT info {};

    int_t iRv = xTSTAT(_filePath.c_str(), &info);
    xTEST_DIFF(iRv, - 1);

    // create - n/a
    Utils::ptrAssignT(a_access,   static_cast<const time_t &>( info.st_atime ));
    Utils::ptrAssignT(a_modified, static_cast<const time_t &>( info.st_mtime ));
}
//-------------------------------------------------------------------------------------------------
/*static */
void_t
FileInfo::_setTime_impl(
    const time_t a_create,
    const time_t a_access,
    const time_t a_modified
) const
{
    xUNUSED(a_create);

    utimbuf times {};
    // times.create - n/a
    times.actime  = a_access;
    times.modtime = a_modified;

    int_t iRv = ::utime(xT2A(_filePath).c_str(), &times);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
