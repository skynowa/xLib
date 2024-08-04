/**
 * \file  FileBin.cpp
 * \brief Binary file
 */


#include "FileBin.h"


namespace xl::fs
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
FileBin::FileBin(
	std::ctstring_t &a_filePath
) :
	_filePath(a_filePath)
{
}
//-------------------------------------------------------------------------------------------------
void_t
FileBin::read(
    std::ustring_t *a_content
) const
{
    xTEST_PTR(a_content);

    a_content->clear();

    FileIO file(_filePath);
    file.open(FileIO::OpenMode::BinReadOnly);

    clonglong_t fileSize = file.size();
    xTEST_DIFF(fileSize, static_cast<longlong_t>(FileIO::PointerPosition::Error));
    xCHECK_DO(fileSize == 0LL, return);

    std::ustring_t usRv;
    usRv.resize( static_cast<size_t>(fileSize) );

    std::csize_t readLen = file.read((void_t *)&usRv.at(0), usRv.size());
    xTEST_EQ(readLen, usRv.size());

    // out
    a_content->swap(usRv);
}
//-------------------------------------------------------------------------------------------------
void_t
FileBin::write(
    std::custring_t   &a_content,
    FileIO::cOpenMode  a_mode
) const
{
    xTEST_NA(a_content);

    FileIO file(_filePath);
    file.open(a_mode);

    xCHECK_DO(a_content.empty(), return);

    std::csize_t writeLen = file.write((void_t *)&a_content.at(0), a_content.size());
    xTEST_EQ(writeLen, a_content.size());
}
//-------------------------------------------------------------------------------------------------

} // namespace
