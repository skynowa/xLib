/**
 * \file  File.h
 * \brief File
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Fs/FileIO.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class File
    /// File
{
public:
///@name ctors, dtor
///@{
    explicit File(std::ctstring_t &filePath);
    virtual ~File();

	xNO_DEFAULT_CONSTRUCT(File)
    xNO_COPY_ASSIGN(File)
///@}

///@name actions
///@{
    void_t remove() const;
    void_t tryRemove(std::csize_t attempts, culong_t timeoutMsec) const;
    void_t wipe(std::csize_t passes) const;
    void_t unlink() const;
    void_t rename(std::ctstring_t &filePathNew) const;
    void_t move(std::ctstring_t &dirPath) const;
    void_t copy(std::ctstring_t &filePathTo, cbool_t isFailIfExists) const /* throw(Exception) */;
    void_t createSymlink(std::ctstring_t &filePathTo) const;
///@}

///@name text
    void_t textRead(std::tstring_t *content) const;
    void_t textRead(std::vec_tstring_t *content) const;
    void_t textRead(std::ctstring_t &separator, std::map_tstring_t *content) const;

    void_t textWrite(std::ctstring_t &content, FileIO::cOpenMode mode) const;
    void_t textWrite(std::cvec_tstring_t &content, FileIO::cOpenMode mode) const;
    void_t textWrite(std::ctstring_t &separator, std::cmap_tstring_t &content,
				FileIO::cOpenMode mode) const;
///@}

///@name binary
    void_t binRead(std::ustring_t *content) const;
    void_t binWrite(std::custring_t &content, FileIO::cOpenMode mode) const;
///@}

private:
	std::ctstring_t _filePath;

xPLATFORM_IMPL:
	void_t _createSymlink_impl(std::ctstring_t &filePathTo) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
// TODO: std::map_tstring_t -> std::multimap
// TODO: use text/bin methods vs FileIO
//-------------------------------------------------------------------------------------------------
