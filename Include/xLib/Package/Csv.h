/**
 * \file   Csv.h
 * \brief  Comma-Separated Values reader/writer
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, package)
//-------------------------------------------------------------------------------------------------
class ICsv
    ///< Comma-separated values reader
{
public:
    typedef std::vector<std::tstring_t> row_t;
    xTYPEDEF_CONST(row_t);

    struct CsvData
    {
        std::tstring_t fileExtension;
        bool_t         hasHeader;
        std::tstring_t eol;
        tchar_t        delimiter;
        bool_t         isTrimCells;
        bool_t         isSkipEmptyLines;
    };
    xTYPEDEF_CONST(CsvData);
};
//-------------------------------------------------------------------------------------------------
class CsvReader :
    public ICsv
    ///< Comma-separated values reader
{
public:
    explicit         CsvReader(cCsvData &data);
        ///< constructor
    virtual         ~CsvReader() {}
        ///< destructor

    bool_t           loadFile(std::ctstring_t &filePath);
    bool_t           loadString(std::ctstring_t &rawString);

    row_t            headers();
    std::tstring_t   header(std::csize_t column);
    std::size_t      columns();
    std::size_t      rows();
    std::tstring_t & cell(std::csize_t row, std::csize_t column);

private:
    cCsvData &       _data;

    bool_t           _isValid();
    void_t           _clear();

    xNO_COPY_ASSIGN(CsvReader)
};
//-------------------------------------------------------------------------------------------------
class CsvWriter :
    public ICsv
    ///< Comma-separated values writer
{
public:
    explicit         CsvWriter(cCsvData &data);
        ///< constructor
    virtual         ~CsvWriter() {}
        ///< destructor

    void_t           setHeaders(crow_t &values);

    bool_t           saveFile(const std::vector<row_t> &csv, std::ctstring_t &filePath);
    bool_t           saveString(const std::vector<row_t> &csv, std::tstring_t *rawString);

private:
    cCsvData &       _data;

    bool_t           _isValid();
    void_t           _clear();

    xNO_COPY_ASSIGN(CsvWriter)
};
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xlib, package)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Csv.cpp"
#endif
