/**
 * \file  File.h
 * \brief File
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Fs/FileIO.h>
#include <xLib/Fs/FileInfo.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class File
    /// File
{
public:
///\name ctors, dtor
///\{
    explicit File(std::ctstring_t &filePath);
    explicit File(const FileInfo &fileInfo);
    virtual ~File();

	xNO_DEFAULT_CONSTRUCT(File);
    xNO_COPY_ASSIGN(File);
///\}

///\name actions
///\{
    void_t clear() const;
    void_t remove() const;
    void_t tryRemove(std::csize_t attempts, culong_t timeoutMsec) const;
    void_t wipe(std::csize_t passes) const;
    void_t unlink() const;
    void_t rename(std::ctstring_t &filePathNew) const;
    void_t move(std::ctstring_t &dirPath) const;

	enum class CopyError
		/// errors codes
    {
		Ok             = 0, ///< Success
		DestFileExists = 1, ///< Destination file is exists
		CopyFail       = 2, ///< Copy fail
		FilesDiffrent  = 3, ///< Files are diffrent
		Unknown        = 4  ///< Unknown
	};
	xUSING_CONST(CopyError);

	CopyError copy(std::ctstring_t &filePathTo, cbool_t isFailIfExists) const;
    void_t createSymlink(std::ctstring_t &filePathTo) const;
///\}

private:
	std::ctstring_t _filePath;

xPLATFORM_IMPL:
	void_t _createSymlink_impl(std::ctstring_t &filePathTo) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * TODO
 *
 */
//-------------------------------------------------------------------------------------------------
