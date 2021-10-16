/**
 * \file  FileInfo_win.inl
 * \brief File information
 */


namespace xl::fs
{

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
    FILETIME timeCreate   {};
    FILETIME timeAccess   {};
    FILETIME timeModified {};

    HandleNativeInvalid file;

    file = ::CreateFile(_filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
        FileType::RegularFile, nullptr);
    xTEST_EQ(file.get().isValid(), true);

    BOOL blRv = ::GetFileTime(file.get(), &timeCreate, &timeAccess, &timeModified);
    xTEST_DIFF(blRv, FALSE);

    Utils::ptrAssignT(a_create,   DateTime::fileToUnix(timeCreate));
    Utils::ptrAssignT(a_access,   DateTime::fileToUnix(timeAccess));
    Utils::ptrAssignT(a_modified, DateTime::fileToUnix(timeModified));
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
    FILETIME timeCreate {};
    DateTime::unixToFile(a_create, &timeCreate);

    FILETIME timeAccess {};
    DateTime::unixToFile(a_access, &timeAccess);

    FILETIME timeModified {};
    DateTime::unixToFile(a_modified, &timeModified);

    HandleNativeInvalid file;

    file = ::CreateFile(_filePath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, OPEN_EXISTING,
        FileType::Normal, nullptr);
    xTEST(file.get().isValid());

    BOOL blRv = ::SetFileTime(file.get(), &timeCreate, &timeAccess, &timeModified);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

} // namespace
