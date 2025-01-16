/**
 * \file  FileBin.h
 * \brief Binary file
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Fs/FileIO.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class FileBin
    /// Binary file
{
public:
///\name ctors, dtor
///\{
    explicit FileBin(std::ctstring_t &filePath);
    virtual ~FileBin() = default;

    xNO_DEFAULT_CONSTRUCT(FileBin);
    xNO_COPY_ASSIGN(FileBin);
///\}

    void_t read(std::ustring_t *content) const;
    void_t write(std::custring_t &content, FileIO::cOpenMode mode) const;

private:
	std::ctstring_t _filePath;
};

} // namespace
//-------------------------------------------------------------------------------------------------
