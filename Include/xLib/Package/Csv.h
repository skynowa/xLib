/**
 * \file   Csv.h
 * \brief  Comma-Separated Values reader/writer
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Const.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)
//-------------------------------------------------------------------------------------------------
struct CsvData
{
	std::tstring_t fileExtension    {xT("csv")};	// TODO: [skynowa] now ignore
	bool_t         hasHeader        {true};			// TODO: [skynowa] now ignore
	std::tstring_t eol              {Const::nl()};	// TODO: [skynowa] now ignore
	tchar_t        delimiter        {xT(',')};
	tchar_t        textDelimeter    {xT('"')};		// TODO: [skynowa] now ignore
	bool_t         isTrimCells      {false};		// TODO: [skynowa] now ignore
	bool_t         isSkipEmptyLines {true};	        // TODO: [skynowa] now ignore
};
xUSING_CONST(CsvData);

class ICsv
    ///< CSV interface
{
public:
    using row_t = std::vec_tstring_t;
    xUSING_CONST(row_t);

    using rows_t = std::vector<row_t>;
    xUSING_CONST(rows_t);
};
//-------------------------------------------------------------------------------------------------
class CsvReader :
    public ICsv
    ///< CSV reader
{
public:
    explicit       CsvReader(cCsvData &data);
        ///< constructor
    virtual       ~CsvReader() {}
        ///< destructor

    bool_t         loadFile(std::ctstring_t &filePath);
    bool_t         loadString(std::ctstring_t &rawString);

    row_t          headers();
    std::tstring_t header(std::csize_t column);
    std::size_t    columns();
    std::size_t    rows();
    std::tstring_t cell(std::csize_t row, std::csize_t column);

private:
    cCsvData &     _data;
    rows_t         _rows;

    bool_t         _isValid();
    void_t         _clear();

    xNO_COPY_ASSIGN(CsvReader)
};
//-------------------------------------------------------------------------------------------------
class CsvWriter :
    public ICsv
    ///< CSV writer
{
public:
    explicit   CsvWriter(cCsvData &data);
        ///< constructor
    virtual   ~CsvWriter() {}
        ///< destructor

    void_t     saveFile(crow_t &header, crows_t &rows, std::ctstring_t &filePath);
    void_t     saveString(crow_t &header, crows_t &rows, std::tstring_t *rawString);

private:
    cCsvData & _data;

    xNO_COPY_ASSIGN(CsvWriter)
};
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
