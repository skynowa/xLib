/**
 * \file  Path.h
 * \brief file system path
 *
 * https://github.com/Quintus/pathie-cpp/blob/master/src/path.cpp
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class Path
    /// file system path
{
public:
///@name ctors, dtor
///@{
	explicit  Path(std::ctstring_t &filePath);
	virtual  ~Path() = default;

	xNO_DEFAULT_CONSTRUCT(Path)
	xNO_COPY_ASSIGN(Path)
///@}

    bool_t         isAbsolute() const;
        ///< is absolute

    std::ctstring_t & str() const;
        ///< file path

    std::tstring_t volume() const;
        ///< get drive
    std::tstring_t dir() const;
        ///< get dir path, without a trailing backslash '\'
    std::tstring_t dirName() const;
        ///< get dir name
    std::tstring_t fileName() const;
        ///< get name.extension
    std::tstring_t fileBaseName() const;
        ///< get name without extension
    std::tstring_t ext() const;
        ///< get extension
    void_t         split(std::vec_tstring_t *values) const;
        ///< split into parts by slashes

    Path setVolume(std::ctstring_t &volumePath) const;
        ///< set volume
    Path setDir(std::ctstring_t &dirPath) const;
        ///< set dir
    Path setFileName(std::ctstring_t &fullName) const;
        ///< set full name
    Path setFileBaseName(std::ctstring_t &name) const;
        ///< set name
    Path setExt(std::ctstring_t &ext) const;
        ///< set extension
    Path removeExt() const;
        ///< remove extension
    Path removeExtIf(std::ctstring_t &ext) const;
        ///< remove extension if it equal some string

    Path toWin(cbool_t isSlashAtEnd) const;
        ///< convert slashes to Windows style
    Path toUnix(cbool_t isSlashAtEnd) const;
        ///< convert slashes to Nix style
    Path toNative(cbool_t isSlashAtEnd) const;
        ///< convert slashes to native style
    Path absolute() const;
        ///< get absolute path
    Path brief(std::csize_t maxSize) const;
        ///< get short path
    Path brief(std::csize_t leftDirsNum, std::csize_t rightDirsNum) const;
        ///< get short path (hide dirs as dots)
    Path briefName(std::csize_t maxSize) const;
        ///< get short name
    Path homeAsBrief() const;
		///< replace home dir with "~"

    Path slashAppend() const;
        ///< append slash
    Path slashRemove() const;
        ///< remove slash

xPUBLIC_STATIC:
	enum class FileExt
		/// file extension
	{
		Exe,    ///< execute module
		Dll,    ///< dynamically linked shared library
		Lib,    ///< static library
		Obj,    ///< object file
		Shell,  ///< shell script file
		Config, ///< config file
		Log,    ///< log file
		Db,     ///< database file
		Dat,    ///< data file
		Backup, ///< backup file
		Temp,   ///< temprary file
		Text    ///< text file
	};
	xUSING_CONST(FileExt);

    static
    std::tstring_t fileExt(cFileExt fileExt);
        ///< get standard extension
    static
    std::tstring_t fileDotExt(cFileExt fileExt);
        ///< get standard extension with dot (if needed, for "exe" - n/n)

    static
    bool_t         isValid(std::ctstring_t &filePath, std::tstring_t *filePathValid);
        ///< path validation
    static
    bool_t         isNameValid(std::ctstring_t &fileName, std::tstring_t *fileNameValid);
        ///< name validation

    static
    size_t         maxSize();
        ///< get max path length in symbols
    static
    size_t         nameMaxSize();
        ///< get max name length in symbols

#if xENV_UNIX
    static
    void_t         proc(std::ctstring_t &procPath, std::vec_tstring_t *fileLines);
        ///< get file lines from UNIX proc file
    static
    std::tstring_t procValue(std::ctstring_t &procPath, std::ctstring_t &key);
        ///< get value by data from UNIX proc file
#endif

private:
    std::ctstring_t _filePath;

xPLATFORM_IMPL:
    std::tstring_t _volume_impl() const;
    void_t         _toNative_impl(std::tstring_t *filePath) const;
    bool_t         _isAbsolute_impl() const;
    std::tstring_t _absolute_impl() const;

    static
    std::tstring_t _fileExt_impl(cFileExt fileExt);
    static
    bool_t         _isNameValid_impl(std::ctstring_t &fileName,
                      std::tstring_t *fileNameValid = nullptr);
    static
    size_t         _maxSize_impl();
    static
    size_t         _nameMaxSize_impl();
};

std::tostream_t & operator << (std::tostream_t &stream, const Path &path);

} // namespace
//-------------------------------------------------------------------------------------------------
