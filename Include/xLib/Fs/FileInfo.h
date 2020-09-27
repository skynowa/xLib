/**
 * \file  FileInfo.h
 * \brief File information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class Path;
class FileIO;

class FileInfo
    /// File information
{
public:
	enum class AccessMode
		/// access mode
	{
		Existence = 0,
		Write     = 2,
		Read      = 4,
		ReadWrite = 6
	};
	xUSING_CONST(AccessMode);

    enum class PermissionMode
        /// permission mode
    {
    #if xENV_WIN
        Read             = _S_IREAD,
        Write            = _S_IWRITE,
        ReadWrite        = (_S_IREAD | _S_IWRITE)
    #else
        Read             = S_IRUSR,
        Write            = S_IWUSR,
        ReadWrite        = (S_IRUSR | S_IWUSR),

        SetUserId        = S_ISUID,
        SetGroupId       = S_ISGID,
        StickyBit        = S_ISVTX,

        ExecSearch       = S_IXUSR,

        GroupRead        = S_IRGRP,
        GroupWrite       = S_IWGRP,
        GroupExecSearch  = S_IXGRP,

        OthersRead       = S_IROTH,
        OthersWrite      = S_IWOTH,
        OthersExecSearch = S_IXOTH
    #endif
    };
    xUSING_CONST(PermissionMode);

///@name ctors, dtor
///@{
    explicit FileInfo(std::ctstring_t &filePath);
    explicit FileInfo(const Path &path);
    explicit FileInfo(const FileIO &file);

    virtual ~FileInfo();

    xNO_DEFAULT_CONSTRUCT(FileInfo)
    xNO_COPY_ASSIGN(FileInfo)
///@}

    longlong_t     size() const;
        ///< get size
    bool_t         isEmpty() const;
        ///< is empty
    ulonglong_t    lines() const;
        ///< get number of lines
    void_t         time(time_t *create, time_t *access, time_t *modified) const;
        ///< get time
    void_t         setTime(const time_t create, const time_t access, const time_t modified) const;
        ///< set time
    void_t         resetTime() const;
        ///< reset time

    bool_t         isExists() const;
        ///< check for existence
    std::tstring_t isExistsEx() const;
        ///< check for existence, if exists - generate new file name (file path), which not exists
    bool_t         checkAccess(cAccessMode mode) const;
        ///< determine file-access permission
    void_t         chmod(cPermissionMode mode) const;
        ///< change the file-permission settings

private:
    std::ctstring_t _filePath; ///< file path

xPLATFORM_IMPL:
	void_t _time_impl(time_t *create, time_t *access, time_t *modified) const;
	void_t _setTime_impl(const time_t create, const time_t access, const time_t modified) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
