/**
 * \file   Csv.h
 * \brief  Comma-Separated Values reader/writer
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Const.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, package)
//-------------------------------------------------------------------------------------------------
struct CsvData
{
	std::tstring_t fileExtension;		// TODO: now ignore
	bool_t         hasHeader;			// TODO: now ignore
	std::tstring_t eol;					// TODO: now ignore
	tchar_t        delimiter;
	tchar_t        textDelimeter;		// TODO: now ignore
	bool_t         isTrimCells;			// TODO: now ignore
	bool_t         isSkipEmptyLines;	// TODO: now ignore

	CsvData() :
		fileExtension   ( xT("csv") ),
		hasHeader       ( true ),
		eol             ( Const::nl() ),
		delimiter       ( xT(',') ),
		textDelimeter   ( xT('"') ),
		isTrimCells     ( false ),
		isSkipEmptyLines( true )
	{
	}
};
xTYPEDEF_CONST(CsvData);

class ICsv
    ///< CSV interface
{
public:
    typedef std::vec_tstring_t row_t;
    xTYPEDEF_CONST(row_t);

    typedef std::vector<row_t> rows_t;
    xTYPEDEF_CONST(rows_t);
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
xNAMESPACE_END2(xlib, package)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "Csv.cpp"
#endif
