/**
 * \file  CxVolume.inl
 * \brief volume
 */


#if !xCOMPILER_MINGW
    #pragma comment(lib, "mpr.lib")
#endif


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxVolume::ExType
CxVolume::type() const
{
    std::ctstring_t rootPath = CxPath( path() ).slashAppend();

    UINT uiRv = ::GetDriveType( rootPath.c_str() );
    xTEST_NA(uiRv);

    return static_cast<ExType>(uiRv);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxVolume::_fileSystem_impl() const
{
    std::tstring_t sRv;

    tchar_t fileSystemName[MAX_PATH + 1] = {0};

    CxLastError::reset();

    BOOL blRv = ::GetVolumeInformation(CxPath( path() ).slashAppend().c_str(), xPTR_NULL, 0UL, xPTR_NULL,
        xPTR_NULL, xPTR_NULL, &fileSystemName[0], static_cast<DWORD>( xARRAY_SIZE(fileSystemName) ));
    xTEST_DIFF(blRv != FALSE && CxLastError::isSuccess(), false);

    sRv.assign(volumeName);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxVolume::_label_impl() const
{
    std::tstring_t sRv;

    tchar_t volumeName[MAX_PATH + 1] = {0};

    CxLastError::reset();

    BOOL blRv = ::GetVolumeInformation(CxPath( path() ).slashAppend().c_str(), &volumeName[0],
        static_cast<DWORD>( xARRAY_SIZE(volumeName) ), xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL, 0UL);
    xTEST_DIFF(blRv != FALSE && CxLastError::isSuccess(), false);

    sRv.assign(volumeName);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxVolume::_isValid_impl() const
{
    bool_t bRv = CxDir( path() ).isRoot();
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxVolume::_isReady_impl() const
{
    bool_t         bRv           = false;
    std::tstring_t volumeDirPath = CxPath( path() ).slashAppend();
    std::tstring_t oldDirPath;

    std::tstring_t sRv;
    UINT           oldErrorMode = 0U;

    oldErrorMode = ::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT |
        SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
    xTEST_NA(oldErrorMode);

    oldDirPath = CxDir::current();
    xTEST_NA(oldDirPath);

    bRv = !!::SetCurrentDirectory(volumeDirPath.c_str());
    xTEST_NA(bRv);

    CxDir::setCurrent(oldDirPath);

    (void_t)::SetErrorMode(oldErrorMode);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxVolume::_mount_impl(
    std::ctstring_t &a_destPath    ///< destination path
) const
{
    // TODO: CxVolume::mount - is it correct?
    NETRESOURCE netResource = {0};

    netResource.dwScope       = RESOURCE_GLOBALNET;
    netResource.dwType        = RESOURCETYPE_DISK;
    netResource.dwDisplayType = RESOURCEDISPLAYTYPE_GENERIC;
    netResource.dwUsage       = RESOURCEUSAGE_CONTAINER;
    netResource.lpLocalName   = const_cast<tchar_t *>( a_destPath.c_str() );
    netResource.lpRemoteName  = const_cast<tchar_t *>( path().c_str() );
    netResource.lpComment     = xPTR_NULL;
    netResource.lpProvider    = xPTR_NULL;

    DWORD dwRv = ::WNetAddConnection2(&netResource, xPTR_NULL, xPTR_NULL, CONNECT_UPDATE_PROFILE);
    xTEST_EQ(dwRv, static_cast<DWORD>( NO_ERROR ));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxVolume::_unMount_impl(
    cbool_t &a_isForce     ///< force unmount even if busy
) const
{
    // TODO: CxVolume::unMount() - is it correct?
    DWORD dwRv = ::WNetCancelConnection2(path().c_str(), CONNECT_UPDATE_PROFILE, a_isForce);
    xTEST_EQ(dwRv, static_cast<DWORD>( NO_ERROR ));
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxVolume::_space_impl(
    std::ctstring_t &a_dirPath,     ///< directory path
    ulonglong_t     *a_available,   ///< available space (for unprivileged users)
    ulonglong_t     *a_total,       ///< total space
    ulonglong_t     *a_free         ///< free space
)
{
    ULARGE_INTEGER available = {{0}};
    ULARGE_INTEGER total     = {{0}};
    ULARGE_INTEGER free      = {{0}};

    BOOL blRv = ::GetDiskFreeSpaceEx(a_dirPath.c_str(), &available, &total, &free);
    xTEST_DIFF(blRv, FALSE);

    CxUtils::ptrAssignT(a_available, available.QuadPart);
    CxUtils::ptrAssignT(a_total,     total.QuadPart);
    CxUtils::ptrAssignT(a_free,      free.QuadPart);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxVolume::_paths_impl(
    std::vec_tstring_t *a_volumePaths    ///< volume paths
)
{
    std::vec_tstring_t vsRv;

    std::tstring_t sRv;
    DWORD          dwRv = 0UL;

    dwRv = ::GetLogicalDriveStrings(0UL, xPTR_NULL);
    xTEST_DIFF(dwRv, 0UL);

    sRv.resize(dwRv);

    dwRv = ::GetLogicalDriveStrings(static_cast<DWORD>( sRv.size() ), &sRv.at(0));
    xTEST_DIFF(dwRv, 0UL);

    for (ctchar_t *s = sRv.c_str(); 0 != *s; s += ::lstrlen(s) + 1) {
        vsRv.push_back(s);
    }

    // out
    a_volumePaths->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
