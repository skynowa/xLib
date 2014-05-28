/**
 * \file  CxVolume.inl
 * \brief volume
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTrace.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>

#if   xENV_WIN
    #include "Platform/Win/CxVolume_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxVolume_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxVolume_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxVolume_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxVolume::CxVolume(
    std::ctstring_t &a_volumePath
) :
    _path(a_volumePath)
{
    xTEST_EQ(path().empty(), false);
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxVolume::path() const
{
    xTEST_EQ(_path.empty(), false);

    return _path;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxVolume::fileSystem() const
{
    return _fileSystem_impl();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxVolume::label() const
{
    bool_t bRv = isReady();
    xCHECK_RET(!bRv, std::tstring_t());

    return _label_impl();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxVolume::isValid() const
{
    return _isValid_impl();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxVolume::isReady() const
{
    return _isReady_impl();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxVolume::isEmpty() const
{
    return CxDir( path() ).isEmpty( CxConst::maskAll() );
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxVolume::mount(
    std::ctstring_t &a_destPath    ///< destination path
) const
{
    xTEST_EQ(a_destPath.empty(), false);

    _mount_impl(a_destPath);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxVolume::unMount(
    cbool_t &a_isForce     ///< force unmount even if busy
) const
{
    xTEST_NA(a_isForce);

    _unMount_impl(a_isForce);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxVolume::isSpaceEnough(
    culonglong_t &a_needBytes ///< need space in bytes
) const
{
    xTEST_NA(a_needBytes);

    ulonglong_t totalFreeBytes = 0ULL;
    space(path(), xPTR_NULL, xPTR_NULL, &totalFreeBytes);

    xCHECK_RET(a_needBytes > totalFreeBytes, false);

    return true;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxVolume::space(
    std::ctstring_t &a_dirPath,     ///< directory path
    ulonglong_t     *a_available,   ///< available space (for unprivileged users)
    ulonglong_t     *a_total,       ///< total space
    ulonglong_t     *a_free         ///< free space
)
{
    xTEST_NA(a_dirPath);
    xTEST_NA(a_available);
    xTEST_NA(a_total);
    xTEST_NA(a_free);

    // if a_dirPath parameter is empty, uses the root of the current volume
    std::tstring_t dirPath;

    if (a_dirPath.empty()) {
        dirPath = CxPath::exeDir();
    } else {
        dirPath = a_dirPath;
    }

    bool_t bRv = CxDir(dirPath).isExists();
    xTEST_EQ(bRv, true);

    _space_impl(a_dirPath, a_available, a_total, a_free);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxVolume::paths(
    std::vec_tstring_t *a_volumePaths    ///< volume paths
)
{
    xTEST_PTR(a_volumePaths);

    _paths_impl(a_volumePaths);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
