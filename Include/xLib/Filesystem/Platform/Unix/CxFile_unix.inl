/**
 * \file  CxFile.inl
 * \brief file
 */


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxFile::_isFile_impl(
    const CxFileType &a_type
)
{
    bool_t bRv = a_type.isExists(CxFileType::faRegularFile);
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFile::_time_impl(
    std::ctstring_t &a_filePath,
    time_t          *a_create,
    time_t          *a_access,
    time_t          *a_modified
)
{
    xUNUSED(a_create);

    xTSTAT_STRUCT info; xSTRUCT_ZERO(info);

    int_t iRv = ::xTSTAT(a_filePath.c_str(), &info);
    xTEST_DIFF(iRv, - 1);

    // create - n/a
    CxUtils::ptrAssignT(a_access,   info.st_atime);
    CxUtils::ptrAssignT(a_modified, info.st_mtime);
}
//-------------------------------------------------------------------------------------------------
/*static */
inline void_t
CxFile::_setTime_impl(
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

    int_t iRv = ::utime(a_filePath.c_str(), &times);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
