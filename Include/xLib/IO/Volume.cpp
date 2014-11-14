/**
 * \file  Volume.inl
 * \brief volume
 */


#if !xOPTION_HEADER_ONLY
    #include "Volume.h"
#endif

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/Dir.h>

#if   xENV_WIN
    #include "Platform/Win/Volume_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Volume_unix.inl"

    #if   xENV_LINUX
        // #if   xOS_ANDROID
            // #include "Platform/Linux/Volume_android.inl"
        // #elif xOS_LINUX
            #include "Platform/Linux/Volume_linux.inl"
        // #endif
    #elif xENV_BSD
        #include "Platform/Bsd/Volume_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/Volume_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Volume::Volume(
    std::ctstring_t &a_volumePath
) :
    _path(a_volumePath)
{
    xTEST_EQ(path().empty(), false);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Volume::path() const
{
    xTEST_EQ(_path.empty(), false);

    return _path;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Volume::fileSystem() const
{
    return _fileSystem_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Volume::label() const
{
    bool_t bRv = isReady();
    xCHECK_RET(!bRv, std::tstring_t());

    return _label_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Volume::isValid() const
{
    return _isValid_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Volume::isReady() const
{
    return _isReady_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Volume::isEmpty() const
{
    return Dir( path() ).isEmpty( Const::maskAll() );
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Volume::mount(
    std::ctstring_t &a_destPath    ///< destination path
) const
{
    xTEST_EQ(a_destPath.empty(), false);

    _mount_impl(a_destPath);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Volume::unMount(
    cbool_t &a_isForce     ///< force unmount even if busy
) const
{
    xTEST_NA(a_isForce);

    _unMount_impl(a_isForce);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Volume::isSpaceEnough(
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
xINLINE void_t
Volume::space(
    std::ctstring_t &a_dirPath,     ///< directory path (if empty - use current volume)
    ulonglong_t     *a_available,   ///< available space (for unprivileged users)
    ulonglong_t     *a_total,       ///< total space
    ulonglong_t     *a_free         ///< free space
)
{
    xTEST_NA(a_dirPath);
    xTEST_NA(a_available);
    xTEST_NA(a_total);
    xTEST_NA(a_free);

    std::tstring_t dirPath;

    if (a_dirPath.empty()) {
        // use root directory of the current volume
        dirPath = Path::exeDir();
    } else {
        dirPath = a_dirPath;
    }

    bool_t bRv = Dir(dirPath).isExists();
    xTEST_EQ(bRv, true);

    _space_impl(dirPath, a_available, a_total, a_free);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Volume::paths(
    std::vec_tstring_t *a_volumePaths    ///< volume paths
)
{
    xTEST_PTR(a_volumePaths);

    _paths_impl(a_volumePaths);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
