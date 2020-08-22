/**
 * \file  Volume.inl
 * \brief volume
 */


#include "Volume.h"

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
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>

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


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Volume::Volume(
    std::ctstring_t &a_volumePath
) :
    _path(a_volumePath)
{
    xTEST(!path().empty());
}
//-------------------------------------------------------------------------------------------------
Volume::Type
Volume::type() const
{
    return _type_impl();
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Volume::path() const
{
    return _path;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Volume::fileSystem() const
{
    return _fileSystem_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Volume::label() const
{
    bool_t bRv = isReady();
    xCHECK_RET(!bRv, std::tstring_t());

    return _label_impl();
}
//-------------------------------------------------------------------------------------------------
bool_t
Volume::isValid() const
{
    return _isValid_impl();
}
//-------------------------------------------------------------------------------------------------
bool_t
Volume::isReady() const
{
    return _isReady_impl();
}
//-------------------------------------------------------------------------------------------------
bool_t
Volume::isEmpty() const
{
    return Dir( path() ).isEmpty( Const::maskAll() );
}
//-------------------------------------------------------------------------------------------------
void_t
Volume::mount(
    std::ctstring_t &a_destPath    ///< destination path
) const
{
    xTEST(!a_destPath.empty());

    _mount_impl(a_destPath);
}
//-------------------------------------------------------------------------------------------------
void_t
Volume::unMount(
    cbool_t &a_isForce     ///< force unmount even if busy
) const
{
    xTEST_NA(a_isForce);

    _unMount_impl(a_isForce);
}
//-------------------------------------------------------------------------------------------------
bool_t
Volume::isSpaceAvailable(
    culonglong_t a_needBytes ///< need space in bytes
) const
{
    xTEST_NA(a_needBytes);

    ulonglong_t availableBytes {};
    space(path(), nullptr, &availableBytes, nullptr);

    xCHECK_RET(a_needBytes >= availableBytes, false);

    return true;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void_t
Volume::space(
    std::ctstring_t &a_dirPath,          ///< directory path (if empty - use current volume)
    ulonglong_t     *a_totalBytes,       ///< total space
    ulonglong_t     *a_availableBytes,   ///< available space (for unprivileged users)
    ulonglong_t     *a_freeBytes         ///< free space
)
{
    xTEST_NA(a_dirPath);
    xTEST_NA(a_availableBytes);
    xTEST_NA(a_totalBytes);
    xTEST_NA(a_freeBytes);

	// empty dir - use root directory of the current volume
    std::ctstring_t dirPath = a_dirPath.empty() ? Path::exeDir() : a_dirPath;

    bool_t bRv = Dir(dirPath).isExists();
    xTEST_EQ(bRv, true);

    _space_impl(dirPath, a_totalBytes, a_availableBytes, a_freeBytes);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Volume::currentSpace(
    ulonglong_t *a_totalBytes,       ///< total space
    ulonglong_t *a_availableBytes,   ///< available space (for unprivileged users)
    ulonglong_t *a_freeBytes         ///< free space
)
{
	space({}, a_totalBytes, a_availableBytes, a_freeBytes);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Volume::paths(
    std::vec_tstring_t *a_volumePaths    ///< volume paths
)
{
    xTEST_PTR(a_volumePaths);

    _paths_impl(a_volumePaths);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
