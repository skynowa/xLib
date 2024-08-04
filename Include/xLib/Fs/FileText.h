/**
 * \file  FileText.h
 * \brief Text file
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Fs/FileIO.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class FileText
    /// Text file
{
public:
///\name ctors, dtor
///\{
    explicit FileText(std::ctstring_t &filePath);
    virtual ~FileText() = default;

    xNO_DEFAULT_CONSTRUCT(FileText)
    xNO_COPY_ASSIGN(FileText)
///\}

    void_t read(std::tstring_t *content) const;
    void_t read(std::vec_tstring_t *content) const;
    void_t read(std::ctstring_t &separator, std::map_tstring_t *content) const;

    void_t write(std::ctstring_t &content, FileIO::cOpenMode mode) const;
    void_t write(std::cvec_tstring_t &content, FileIO::cOpenMode mode) const;
    void_t write(std::ctstring_t &separator, std::cmap_tstring_t &content,
				FileIO::cOpenMode mode) const;

private:
	std::ctstring_t _filePath;
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * TODO
 *
 * - std::map_tstring_t -> std::multimap
 * - use text/bin methods vs FileIO
 */
//-------------------------------------------------------------------------------------------------
