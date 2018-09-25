/**
 * \file  Volume.inl
 * \brief volume
 */


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Volume::Type
Volume::type() const
{
    std::ctstring_t rootPath = Path( path() ).slashAppend();

    UINT uiRv = ::GetDriveType( rootPath.c_str() );
    xTEST_NA(uiRv);

    return static_cast<Type>(uiRv);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Volume::_fileSystem_impl() const
{
    std::tstring_t sRv;

    tchar_t fileSystemName[MAX_PATH + 1] = {0};

    NativeError::reset();

    BOOL blRv = ::GetVolumeInformation(Path( path() ).slashAppend().c_str(), nullptr, 0UL, nullptr,
        nullptr, nullptr, &fileSystemName[0], static_cast<DWORD>( xARRAY_SIZE(fileSystemName) ));
    xTEST_DIFF(blRv != FALSE && NativeError::isSuccess(), false);

    sRv.assign(volumeName);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Volume::_label_impl() const
{
    std::tstring_t sRv;

    tchar_t volumeName[MAX_PATH + 1] = {0};

    NativeError::reset();

    BOOL blRv = ::GetVolumeInformation(Path( path() ).slashAppend().c_str(), &volumeName[0],
        static_cast<DWORD>( xARRAY_SIZE(volumeName) ), nullptr, nullptr, nullptr, nullptr, 0UL);
    xTEST_DIFF(blRv != FALSE && NativeError::isSuccess(), false);

    sRv.assign(volumeName);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Volume::_isValid_impl() const
{
    bool_t bRv = Dir( path() ).isRoot();
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Volume::_isReady_impl() const
{
    bool_t         bRv           = false;
    std::tstring_t volumeDirPath = Path( path() ).slashAppend();
    std::tstring_t oldDirPath;

    UINT oldErrorMode = ::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT |
        SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
    xTEST_NA(oldErrorMode);

    oldDirPath = Dir::current();
    xTEST_NA(oldDirPath);

    bRv = !!::SetCurrentDirectory(volumeDirPath.c_str());
    xTEST_NA(bRv);

    Dir::setCurrent(oldDirPath);

    (void_t)::SetErrorMode(oldErrorMode);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Volume::_mount_impl(
    std::ctstring_t &a_destPath    ///< destination path
) const
{
    // TODO: [skynowa] Volume::mount - is it correct?
    NETRESOURCE netResource = {0};

    netResource.dwScope       = RESOURCE_GLOBALNET;
    netResource.dwType        = RESOURCETYPE_DISK;
    netResource.dwDisplayType = RESOURCEDISPLAYTYPE_GENERIC;
    netResource.dwUsage       = RESOURCEUSAGE_CONTAINER;
    netResource.lpLocalName   = const_cast<tchar_t *>( a_destPath.c_str() );
    netResource.lpRemoteName  = const_cast<tchar_t *>( path().c_str() );
    netResource.lpComment     = nullptr;
    netResource.lpProvider    = nullptr;

    DWORD dwRv = ::WNetAddConnection2(&netResource, nullptr, nullptr, CONNECT_UPDATE_PROFILE);
    xTEST_EQ(dwRv, static_cast<DWORD>( NO_ERROR ));
}
//-------------------------------------------------------------------------------------------------
void_t
Volume::_unMount_impl(
    cbool_t &a_isForce     ///< force unmount even if busy
) const
{
    // TODO: [skynowa] Volume::unMount() - is it correct?
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
void_t
Volume::_space_impl(
    std::ctstring_t &a_dirPath,     ///< directory path
    ulonglong_t*    &a_available,   ///< available space (for unprivileged users)
    ulonglong_t*    &a_total,       ///< total space
    ulonglong_t*    &a_free         ///< free space
)
{
    ULARGE_INTEGER available = {{0}};
    ULARGE_INTEGER total     = {{0}};
    ULARGE_INTEGER free      = {{0}};

    BOOL blRv = ::GetDiskFreeSpaceEx(a_dirPath.c_str(), &available, &total, &free);
    xTEST_DIFF(blRv, FALSE);

    Utils::ptrAssignT(a_available, available.QuadPart);
    Utils::ptrAssignT(a_total,     total.QuadPart);
    Utils::ptrAssignT(a_free,      free.QuadPart);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Volume::_paths_impl(
    std::vec_tstring_t *a_volumePaths    ///< volume paths
)
{
    std::vec_tstring_t vsRv;

    std::tstring_t sRv;
    DWORD          dwRv = 0UL;

    dwRv = ::GetLogicalDriveStrings(0UL, nullptr);
    xTEST_DIFF(dwRv, 0UL);

    sRv.resize(dwRv);

    dwRv = ::GetLogicalDriveStrings(static_cast<DWORD>( sRv.size() ), &sRv.at(0));
    xTEST_DIFF(dwRv, 0UL);

    for (cptr_ctchar_t s = sRv.c_str(); 0 != *s; s += ::lstrlen(s) + 1) {
        vsRv.push_back(s);
    }

    // out
    a_volumePaths->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
