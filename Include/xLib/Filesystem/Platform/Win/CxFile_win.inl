/**
 * \file  CxFile.inl
 * \brief file
 */


xNAMESPACE_BEGIN2(xlib, filesystem)

//-------------------------------------------------------------------------------------------------
inline void_t
CxFile::setMode(
    const ExTranslationMode &a_mode
) const
{
    xTEST_NA(a_mode);

    int_t iRv = ::setmode(_nativeHandle(get()), a_mode);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------

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
    bool_t bRv = false;

    bRv = a_type.isExists(CxFileType::faDirectory);
    xCHECK_RET(bRv, false);

    bRv = a_type.isExists(CxFileType::faDevice);
    xCHECK_RET(bRv, false);

    bRv = a_type.isExists(CxFileType::faReparsePoint);
    xCHECK_RET(bRv, false);

    bRv = a_type.isExists(CxFileType::faOffline);
    xCHECK_RET(bRv, false);

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
    FILETIME timeCreate   = {0};
    FILETIME timeAccess   = {0};
    FILETIME timeModified = {0};

    CxHandleInvalid file;

    file = ::CreateFile(a_filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, xPTR_NULL, OPEN_EXISTING,
        CxFileType::faNormal, xPTR_NULL);
    xTEST_EQ(file.isValid(), true);

    BOOL blRv = ::GetFileTime(file.get(), &timeCreate, &timeAccess, &timeModified);
    xTEST_DIFF(blRv, FALSE);

    CxUtils::ptrAssignT(a_create,   CxDateTime::fileTimeToUnixTime(timeCreate));
    CxUtils::ptrAssignT(a_access,   CxDateTime::fileTimeToUnixTime(timeAccess));
    CxUtils::ptrAssignT(a_modified, CxDateTime::fileTimeToUnixTime(timeModified));
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
    FILETIME timeCreate = {0};
    CxDateTime::unixTimeToFileTime(a_create, &timeCreate);

    FILETIME timeAccess = {0};
    CxDateTime::unixTimeToFileTime(a_access, &timeAccess);

    FILETIME timeModified = {0};
    CxDateTime::unixTimeToFileTime(a_modified, &timeModified);

    CxHandleInvalid file;

    file = ::CreateFile(a_filePath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, xPTR_NULL,
        OPEN_EXISTING, CxFileType::faNormal, xPTR_NULL);
    xTEST_EQ(file.isValid(), true);

    BOOL blRv = ::SetFileTime(file.get(), &timeCreate, &timeAccess, &timeModified);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
