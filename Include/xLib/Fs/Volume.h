/**
 * \file  Volume.h
 * \brief volume
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class Volume
    /// volume
{
public:
    enum Type
        /// drive type
    {
    #if   xENV_WIN
        dtUnknown   = DRIVE_UNKNOWN,
        dtNoRoot    = DRIVE_NO_ROOT_DIR,
        dtRemovable = DRIVE_REMOVABLE,
        dtFixed     = DRIVE_FIXED,
        dtRemote    = DRIVE_REMOTE,
        dtCdRom     = DRIVE_CDROM,
        dtRam       = DRIVE_RAMDISK
    #elif xENV_UNIX
        dtUnknown   = 0,
        dtNoRoot    = 1,
        dtRemovable = 2,
        dtFixed     = 3,
        dtRemote    = 4,
        dtCdRom     = 5,
        dtRam       = 6,
        dtOther     = 7
    #endif
    };

    explicit        Volume(std::ctstring_t &path);
        ///< constructor
    virtual        ~Volume() {}
        ///< destructor

    std::ctstring_t & path() const xWARN_UNUSED_RV;
        ///< volume path
#if xENV_WIN
    Type            type() const xWARN_UNUSED_RV;
        ///< drive type
#endif
    std::tstring_t  fileSystem() const xWARN_UNUSED_RV;
        ///< filesystem type
    std::tstring_t  label() const xWARN_UNUSED_RV;
        ///< get label
    bool_t          isValid() const xWARN_UNUSED_RV;
        ///< is valid path
    bool_t          isReady() const xWARN_UNUSED_RV;
        ///< is ready
    bool_t          isEmpty() const xWARN_UNUSED_RV;
        ///< is empty
    void_t          mount(std::ctstring_t &destPath) const;
        ///< mount
    void_t          unMount(cbool_t &isForce) const;
        ///< unmount
    bool_t          isSpaceEnough(culonglong_t &needBytes) const xWARN_UNUSED_RV;
        ///< is enough space

    // static
    static
    void_t          space(std::ctstring_t &dirPath, ulonglong_t *available, ulonglong_t *total,
                        ulonglong_t *free);
        ///< get free space
    static
    void_t          paths(std::vec_tstring_t *volumePaths);
        ///< get paths

private:
    std::ctstring_t _path;  ///< volume path

    xNO_COPY_ASSIGN(Volume)

xPLATFORM_IMPL:
    std::tstring_t  _fileSystem_impl() const xWARN_UNUSED_RV;
    std::tstring_t  _label_impl() const xWARN_UNUSED_RV;
    bool_t          _isValid_impl() const xWARN_UNUSED_RV;
    bool_t          _isReady_impl() const xWARN_UNUSED_RV;
    void_t          _mount_impl(std::ctstring_t &destPath) const;
    void_t          _unMount_impl(cbool_t &isForce) const;

    // static
    static
    void_t          _space_impl(std::ctstring_t &dirPath, ulonglong_t* &available,
                        ulonglong_t* &total, ulonglong_t* &free);
    static
    void_t          _paths_impl(std::vec_tstring_t *volumePaths);

};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "Volume.cpp"
#endif
