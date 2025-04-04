/**
 * \file   Csv.h
 * \brief  Comma-Separated Values reader/writer
 *
 * \libs   https://github.com/d99kris/rapidcsv
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Const.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package
{
//-------------------------------------------------------------------------------------------------
struct CsvOption
{
	std::tstring_t fileExtension    {xT("csv")};	// TODO: [skynowa] now ignore
	bool_t         hasHeader        {true};			// TODO: [skynowa] now ignore
	std::tstring_t eol              {Const::nl()};	// TODO: [skynowa] now ignore
	tchar_t        delimiter        {xT(',')};
	tchar_t        textDelimeter    {xT('"')};		// TODO: [skynowa] now ignore
	bool_t         isTrimCells      {false};		// TODO: [skynowa] now ignore
	bool_t         isSkipEmptyLines {true};	        // TODO: [skynowa] now ignore
};
xUSING_CONST(CsvOption);

class ICsv
    /// CSV
{
public:
    using row_t = std::vec_tstring_t;
    xUSING_CONST(row_t);

    using rows_t = std::vector<row_t>;
    xUSING_CONST(rows_t);
};
//-------------------------------------------------------------------------------------------------
class CsvReader final :
    public ICsv
    /// CSV reader
{
public:
///\name ctors, dtor
///\{
	explicit  CsvReader(cCsvOption &option);
	virtual  ~CsvReader() = default;

	xNO_COPY_ASSIGN(CsvReader);
///\}

    bool_t         loadFile(std::ctstring_t &filePath);
    bool_t         loadString(std::ctstring_t &rawString);

    row_t          headers();
    std::tstring_t header(std::csize_t column);
    std::size_t    columns();
    std::size_t    rows();
    std::tstring_t cell(std::csize_t row, std::csize_t column);

private:
    cCsvOption &   _option;
    rows_t         _rows;

    bool_t         _isValid();
    void_t         _clear();
};
//-------------------------------------------------------------------------------------------------
class CsvWriter final :
    public ICsv
    /// CSV writer
{
public:
///\name ctors, dtor
///\{
	explicit  CsvWriter(cCsvOption &option);
	virtual  ~CsvWriter() = delete;

    xNO_COPY_ASSIGN(CsvWriter);
///\}

    void_t     saveFile(crow_t &header, crows_t &rows, std::ctstring_t &filePath);
    void_t     saveString(crow_t &header, crows_t &rows, std::tstring_t *rawString);

private:
    cCsvOption & _option;
};
//-------------------------------------------------------------------------------------------------
} // namespace
//-------------------------------------------------------------------------------------------------
