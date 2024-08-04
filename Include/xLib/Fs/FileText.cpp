/**
 * \file  FileText.cpp
 * \brief Text file
 */


#include "FileText.h"

#include <xLib/Core/String.h>


namespace xl::fs
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
FileText::FileText(
	std::ctstring_t &a_filePath
) :
	_filePath(a_filePath)
{
}
//-------------------------------------------------------------------------------------------------
void_t
FileText::read(
    std::tstring_t *a_content
) const
{
    xTEST_PTR(a_content);

    a_content->clear();

    std::tstring_t sRv;

    FileIO file(_filePath);
    file.open(FileIO::OpenMode::BinReadOnly);

    clonglong_t fileSize = file.size();
    xTEST_DIFF(fileSize, static_cast<longlong_t>(FileIO::PointerPosition::Error));
    xCHECK_DO(fileSize == 0LL, a_content->clear(); return);

    sRv.resize( static_cast<size_t>(fileSize) );

    std::csize_t readLen = file.read((void_t *)&sRv.at(0), sRv.size());
    xTEST_EQ(readLen, sRv.size());

    // out
    a_content->swap(sRv);
}
//-------------------------------------------------------------------------------------------------
void_t
FileText::read(
    std::vec_tstring_t *a_content
) const
{
    xTEST(FileInfo(_filePath).isExists());
    xTEST_PTR(a_content);

    a_content->clear();

    std::tstring_t content;
    read(&content);

    std::vec_tstring_t vsRv;
    String::split(content, Const::nl(), &vsRv);

    // out
    a_content->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------
void_t
FileText::read(
    std::ctstring_t    &a_separator,
    std::map_tstring_t *a_content
) const
{
    xTEST(FileInfo(_filePath).isExists());
    xTEST_PTR(a_content);

    a_content->clear();

    // if file empty
    xCHECK_DO(FileInfo(_filePath).size() == 0L, a_content->clear(); return);

    std::locale::global( std::locale() );

    std::tifstream_t ifs(xT2A(_filePath));
    xTEST(!! ifs);
    xTEST(!ifs.fail());
    xTEST(ifs.good());
    xTEST(ifs.is_open());
    xTEST(!ifs.eof());

    std::map_tstring_t msRv;
    std::tstring_t     line;
    std::vec_tstring_t lines;

    for (size_t i = 0; !ifs.eof(); ++ i) {
        std::getline(ifs, line);
        line = String::trimRightChars(line, Const::eol());

        if ( line.empty() ) {
            auto prRv = msRv.insert( {Const::strEmpty(), Const::strEmpty()} );
            xTEST_NA(prRv);
        } else {
            String::split(line, a_separator, &lines);
            xTEST_EQ(lines.size(), size_t(2));

            auto prRv = msRv.insert( {lines.at(0), lines.at(1)} );
            xTEST_NA(prRv);
        }
    }

    // out
    a_content->swap(msRv);

#if xTODO
    bool_t             bRv {};
    std::map_tstring_t msRv;
    std::vec_tstring_t vsRv;

    bRv = textRead(filePath, &vsRv);
    xTEST(bRv);

    for (const auto it = vsRv.cbegin(); it != vsRv.cend(); ++ it) {
        std::vec_tstring_t lines;
        String::split(vsRv.at(0), separator, &lines);

        msRv.insert( {lines.at(0), lines.at(1)} );
    }

    // out
    content.swap(msRv);
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
FileText::write(
    std::ctstring_t   &a_content,
    FileIO::cOpenMode  a_mode
) const
{
    xTEST_NA(a_content);
    xTEST_NA(a_mode);

    FileIO file(_filePath);
    file.open(a_mode);

    xCHECK_DO(a_content.empty(), return);

    std::csize_t writeLen = file.write((void_t *)&a_content.at(0), a_content.size());
    xTEST_EQ(writeLen, a_content.size());
}
//-------------------------------------------------------------------------------------------------
void_t
FileText::write(
    std::cvec_tstring_t &a_content,
    FileIO::cOpenMode    a_mode
) const
{
    xTEST_NA(a_content);
    xTEST_NA(a_mode);

    std::ctstring_t &content = String::join(a_content, Const::nl());
    write(content, a_mode);
}
//-------------------------------------------------------------------------------------------------
void_t
FileText::write(
    std::ctstring_t     &a_separator,
    std::cmap_tstring_t &a_content,
    FileIO::cOpenMode    a_mode
) const
{
    xTEST(!_filePath.empty());
    xTEST(!a_separator.empty());
    xTEST_NA(a_content);
    xTEST_NA(a_mode);

    FileIO file(_filePath);
    file.open(a_mode);

    xCHECK_DO(a_content.empty(), return);

    for (const auto &[key, value] : a_content) {
        file.writeLine(key + a_separator + value);
    }
}
//-------------------------------------------------------------------------------------------------

} // namespace
