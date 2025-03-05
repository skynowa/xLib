/**
 * \file  Path.h
 * \brief file system path
 *
 * \faq   https://github.com/Quintus/pathie-cpp/blob/master/src/path.cpp
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Interface/IPrinter.h>
#include <xLib/Interface/IStr.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class Path final :
	public IPrinter<std::tostream_t>,
	public IStrConstRef
    /// file system path
{
public:
///\name ctors, dtor
///\{
	explicit  Path(std::ctstring_t &filePath);
	virtual  ~Path();

	xNO_DEFAULT_CONSTRUCT(Path);
	xNO_COPY_ASSIGN(Path);

   /**
	* Standard paths
	*
	* - https://doc.qt.io/qt-5/qstandardpaths.html#StandardLocation-enum
	* - https://docs.microsoft.com/en-us/previous-versions/windows/embedded/aa453706(v%3Dmsdn.10)
	*
	* [TODO] desktop, documents, downloads, ...
	*/

	// files
	static Path exe();
	static Path dll();
	static Path shell();

	// dirs
	static Path homeDir();
	static Path trashDir();
///\}

///\name Overrides
///\{
	void_t            print(std::tostream_t &stream) const final;
    std::ctstring_t & str() const final;
        ///< file path
///\}

    bool_t         isAbsolute() const;
        ///< is absolute
    bool_t         isRelative() const;
        ///< is relative
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

    static std::tstring_t fileExt(cFileExt fileExt);
        ///< get standard extension
    static std::tstring_t fileDotExt(cFileExt fileExt);
        ///< get standard extension with dot (if needed, for "exe" - n/n)

    static bool_t         isValid(std::ctstring_t &filePath, std::tstring_t *filePathValid);
        ///< path validation
    static bool_t         isNameValid(std::ctstring_t &fileName, std::tstring_t *fileNameValid);
        ///< name validation

    static size_t         maxSize();
        ///< get max path length in symbols
    static size_t         nameMaxSize();
        ///< get max name length in symbols

#if xENV_UNIX
///\name Proc file
///\{
	static std::tstring_t proc(std::ctstring_t &procPath,
		std::function<bool_t(std::ctstring_t &line)> cond,
		std::function<std::tstring_t(std::ctstring_t &line)> op);
		///< get file lines from UNIX proc file
	static std::tstring_t procValue(std::ctstring_t &procPath, std::ctstring_t &key);
		///< get value by data from UNIX proc file

	static std::tstring_t readSymLink(std::ctstring_t &symLinkPath);
		///< read symlink content
///\}
#endif

private:
    std::ctstring_t _filePath;

xPLATFORM_IMPL:
	// files
	static std::tstring_t _exe_impl();
	static std::tstring_t _dll_impl();
    static std::tstring_t _shell_impl();

    // dirs
    static std::tstring_t _homeDir_impl();
    static std::tstring_t _trashDir_impl();

    std::tstring_t        _volume_impl() const;
    void_t                _toNative_impl(std::tstring_t *filePath) const;
    bool_t                _isAbsolute_impl() const;
    std::tstring_t        _absolute_impl() const;

    static std::tstring_t _fileExt_impl(cFileExt fileExt);
    static bool_t         _isNameValid_impl(std::ctstring_t &fileName,
                              std::tstring_t *fileNameValid = nullptr);
    static size_t         _maxSize_impl();
    static size_t         _nameMaxSize_impl();
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * TODO
 *
 * - [ ] ctor - filePath -> fsPath
 * - [ ] isRootPath()
 * - [ ] proc - use in xLib
 * - [+] Utils::readSymLink - move to Path
 */
//-------------------------------------------------------------------------------------------------
