/**
 * \file  FileType.h
 * \brief file type
 */


#pragma once

#include <xLib/Core/Core.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

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
		Unknown           = INVALID_FILE_ATTRIBUTES,
        RegularFile       = FILE_ATTRIBUTE_NORMAL,
        Directory         = FILE_ATTRIBUTE_DIRECTORY,
        Device            = FILE_ATTRIBUTE_DEVICE,

        ReadOnly          = FILE_ATTRIBUTE_READONLY,
        Hidden            = FILE_ATTRIBUTE_HIDDEN,
        System            = FILE_ATTRIBUTE_SYSTEM,
        Archive           = FILE_ATTRIBUTE_ARCHIVE,
        Temporary         = FILE_ATTRIBUTE_TEMPORARY,
        SparseFile        = FILE_ATTRIBUTE_SPARSE_FILE,
        ReparsePoint      = FILE_ATTRIBUTE_REPARSE_POINT,
        Compressed        = FILE_ATTRIBUTE_COMPRESSED,
        Offline           = FILE_ATTRIBUTE_OFFLINE,
        NotContentIndexed = FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
        Encrypted         = FILE_ATTRIBUTE_ENCRYPTED
    #elif xENV_UNIX
		Unknown           = static_cast<types_t>(-1),	///< Status cannot be determined
        RegularFile       = S_IFREG,					///<
        Directory         = S_IFDIR,					///<
        CharacterDevice   = S_IFCHR,					///<
        BlockDevice       = S_IFBLK,					///<
        Device            = (CharacterDevice | BlockDevice), ///<

        Fifo              = S_IFIFO,					///<
        SymbolicLink      = S_IFLNK,					///<
        Socket            = S_IFSOCK					///<
    #endif
    };
    xUSING_CONST(Type);

///@name ctors, dtor
///@{
	explicit FileType(std::ctstring_t &filePath);
	virtual ~FileType() = default;

	xNO_DEFAULT_CONSTRUCT(FileType)
	xNO_COPY_ASSIGN(FileType)
///@}

    std::ctstring_t & filePath() const;
        ///< file path

    bool_t            isExists(cType value) const;
        ///< is exists
    types_t           get() const;
        ///< get
    void_t            set(ctypes_t values) const;
        ///< set
    void_t            add(cType value) const;
        ///< add
    void_t            remove(cType value) const;
        ///< remove
    void_t            modify(cType valueRemove, cType valueAdd) const;
        ///< modify
    void_t            clear() const;
        ///< clear (set normal attributes, only for Windows)

    bool_t            isFile() const;
        ///< check for file
    bool_t            isExecutable() const;
        ///< is executable

private:
    std::ctstring_t _filePath;

xPLATFORM_IMPL:
    types_t _get_impl() const;
    void_t  _set_impl(ctypes_t values) const;
    void_t  _clear_impl() const;

    bool_t  _isExecutable_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * TODO:
 *
 * - Type: https://docs.microsoft.com/en-us/cpp/standard-library/filesystem-enumerations?view=vs-2019
 *	NotFound -1 Represents a file that does not exist.
 *	None      0 Represents a file that has no type attribute. (Not supported.)
 */
