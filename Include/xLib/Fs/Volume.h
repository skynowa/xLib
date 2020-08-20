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
    enum class Type
        /// drive type
    {
    #if   xENV_WIN
        Unknown   = DRIVE_UNKNOWN,
        NoRoot    = DRIVE_NO_ROOT_DIR,
        Removable = DRIVE_REMOVABLE,
        Fixed     = DRIVE_FIXED,
        Remote    = DRIVE_REMOTE,
        CdRom     = DRIVE_CDROM,
        Ram       = DRIVE_RAMDISK
    #elif xENV_UNIX
        Unknown   = 0,
        NoRoot    = 1,
        Removable = 2,
        Fixed     = 3,
        Remote    = 4,
        CdRom     = 5,
        Ram       = 6
    #endif
    };

///@name ctors, dtor
///@{
	explicit  Volume(std::ctstring_t &path);
	virtual  ~Volume() = default;

	xNO_DEFAULT_CONSTRUCT(Volume)
	xNO_COPY_ASSIGN(Volume)
///@}

    std::ctstring_t & path() const;
        ///< path
    Type            type() const;
        ///< type
    std::tstring_t  fileSystem() const;
        ///< filesystem type
    std::tstring_t  label() const;
        ///< get label
    bool_t          isValid() const;
        ///< is valid path
    bool_t          isReady() const;
        ///< is ready
    bool_t          isEmpty() const;
        ///< is empty
    void_t          mount(std::ctstring_t &destPath) const;
        ///< mount
    void_t          unMount(cbool_t &isForce) const;
        ///< unmount
    bool_t          isSpaceAvailable(culonglong_t needBytes) const;
        ///< is enough space

xPUBLIC_STATIC:
    static
    void_t space(std::ctstring_t &dirPath, ulonglong_t *totalBytes, ulonglong_t *availableBytes,
				ulonglong_t *freeBytes);
        ///< get free space
    static
    void_t currentSpace(ulonglong_t *totalBytes, ulonglong_t *availableBytes,
				ulonglong_t *freeBytes);
        ///< get free space of current valume
    static
    void_t paths(std::vec_tstring_t *volumePaths);
        ///< get paths

private:
    std::ctstring_t _path;  ///< volume path

xPLATFORM_IMPL:
	Type            _type_impl() const;
    std::tstring_t  _fileSystem_impl() const;
    std::tstring_t  _label_impl() const;
    bool_t          _isValid_impl() const;
    bool_t          _isReady_impl() const;
    void_t          _mount_impl(std::ctstring_t &destPath) const;
    void_t          _unMount_impl(cbool_t &isForce) const;

xPRIVATE_STATIC:
    static
    void_t _space_impl(std::ctstring_t &dirPath, ulonglong_t* &totalBytes,
				ulonglong_t* &availableBytes, ulonglong_t* &freeBytes);
    static
    void_t _paths_impl(std::vec_tstring_t *volumePaths);
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
