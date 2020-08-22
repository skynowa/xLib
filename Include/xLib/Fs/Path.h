/**
 * \file  Path.h
 * \brief file system path
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class Path
    /// file system path
{
public:
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

///@name ctors, dtor
///@{
	explicit       Path(std::ctstring_t &filePath);
	virtual       ~Path() = default;

	xNO_DEFAULT_CONSTRUCT(Path)
	xNO_COPY_ASSIGN(Path)
///@}

    // TODO: [skynowa] get objects

    std::ctstring_t & filePath() const;
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

    std::tstring_t setVolume(std::ctstring_t &volumePath) const;
        ///< set volume
    std::tstring_t setDir(std::ctstring_t &dirPath) const;
        ///< set dir
    std::tstring_t setFileName(std::ctstring_t &fullName) const;
        ///< set full name
    std::tstring_t setFileBaseName(std::ctstring_t &name) const;
        ///< set name
    std::tstring_t setExt(std::ctstring_t &ext) const;
        ///< set extension

    std::tstring_t removeExt() const;
        ///< remove extension
    std::tstring_t removeExtIf(std::ctstring_t &ext) const;
        ///< remove extension if it equal some string

	bool_t         isCaseSensitive() const;
		///< get case sensitivity
    bool_t         isAbsolute() const;
        ///< is absolute

    std::tstring_t toWin(cbool_t &isSlashAtEnd) const;
        ///< convert slashes to Windows style
    std::tstring_t toUnix(cbool_t &isSlashAtEnd) const;
        ///< convert slashes to Nix style
    std::tstring_t toNative(cbool_t &isSlashAtEnd) const;
        ///< convert slashes to native style
    std::tstring_t absolute() const;
        ///< get absolute path
    std::tstring_t brief(std::csize_t maxSize) const;
        ///< get short path
    std::tstring_t brief(std::csize_t leftDirsNum, std::csize_t rightDirsNum) const;
        ///< get short path (hide dirs as dots)
    std::tstring_t homeAsBrief() const;
		///< replace home dir with "~"

    std::tstring_t slashAppend() const;
        ///< append slash
    std::tstring_t slashRemove() const;
        ///< remove slash

xPUBLIC_STATIC:
    static
    std::tstring_t exe();
        ///< get full path to exe
    static
    std::tstring_t exeDir();
        ///< get dir path to exe
    static
    std::tstring_t dll();
        ///< get full path to dll
    static
    std::tstring_t fileExt(cFileExt fileExt);
        ///< get standard extension

    static
    bool_t         isValid(std::ctstring_t &filePath, std::tstring_t *filePathValid = nullptr);
        ///< path validation
    static
    bool_t         isNameValid(std::ctstring_t &fileName, std::tstring_t *fileNameValid = nullptr);
        ///< name validation

    static
    std::tstring_t briefName(std::ctstring_t &fileName, std::csize_t maxSize);
        ///< get short name

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
    bool_t         _isCaseSensitive_impl() const;
    bool_t         _isAbsolute_impl() const;
    std::tstring_t _absolute_impl() const;

    static
    std::tstring_t _exe_impl();
    static
    std::tstring_t _dll_impl();
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

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
// TODO: [skynowa] group methods
//-------------------------------------------------------------------------------------------------
