/**
 * \file  FileType.h
 * \brief file type
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class FileType
    /// file attribute
{
public:
#if   xENV_WIN
    using types_t = DWORD;
#elif xENV_UNIX
    using types_t = mode_t;
#endif
    xUSING_CONST(types_t);
        ///< all types

    enum class Type : types_t
        /// attribute
    {
    #if   xENV_WIN
        faInvalid           = INVALID_FILE_ATTRIBUTES,
        faNormal            = FILE_ATTRIBUTE_NORMAL,
        faReadOnly          = FILE_ATTRIBUTE_READONLY,
        faHidden            = FILE_ATTRIBUTE_HIDDEN,
        faSystem            = FILE_ATTRIBUTE_SYSTEM,
        faDirectory         = FILE_ATTRIBUTE_DIRECTORY,
        faArchive           = FILE_ATTRIBUTE_ARCHIVE,
        faDevice            = FILE_ATTRIBUTE_DEVICE,
        faTemporary         = FILE_ATTRIBUTE_TEMPORARY,
        faSparseFile        = FILE_ATTRIBUTE_SPARSE_FILE,
        faReparsePoint      = FILE_ATTRIBUTE_REPARSE_POINT,
        faCompressed        = FILE_ATTRIBUTE_COMPRESSED,
        faOffline           = FILE_ATTRIBUTE_OFFLINE,
        faNotContentIndexed = FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
        faEncrypted         = FILE_ATTRIBUTE_ENCRYPTED
    #elif xENV_UNIX
        faInvalid           = static_cast<types_t>(-1),
        faDirectory         = S_IFDIR,
        faCharacterDevice   = S_IFCHR,
        faBlockDevice       = S_IFBLK,
        faRegularFile       = S_IFREG,
        faFifo              = S_IFIFO,
        faSymbolicLink      = S_IFLNK,
        faSocket            = S_IFSOCK
    #endif
    };
    xUSING_CONST(Type);

    explicit          FileType(std::ctstring_t &filePath);
        ///< constructor
    virtual          ~FileType() {}
        ///< destructor

    std::ctstring_t & filePath() const xWARN_UNUSED_RV;
        ///< file path

    bool_t            isExists(cType &value) const xWARN_UNUSED_RV;
        ///< is exists
    types_t           get() const xWARN_UNUSED_RV;
        ///< get
    void_t            set(ctypes_t &values) const;
        ///< set
    void_t            add(cType &value) const;
        ///< add
    void_t            remove(cType &value) const;
        ///< remove
    void_t            modify(cType &valueRemove, cType &valueAdd) const;
        ///< modify
    void_t            clear() const;
        ///< clear (set normal attributes, only for Windows)

private:
    std::ctstring_t   _filePath;

    xNO_COPY_ASSIGN(FileType)

xPLATFORM_IMPL:
    types_t           _get_impl() const xWARN_UNUSED_RV;
    void_t            _set_impl(ctypes_t &values) const;
    void_t            _clear_impl() const;
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
