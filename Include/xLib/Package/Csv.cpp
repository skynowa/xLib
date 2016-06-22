/**
 * \file   Csv.cpp
 * \brief  Comma-Separated Values parser
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Csv.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/IO/File.h>


xNAMESPACE_BEGIN2(xlib, package)

/**************************************************************************************************
*   CsvReader - public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
CsvReader::CsvReader(
    cCsvData &a_data
) :
    _data(a_data),
	_rows()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
CsvReader::loadFile(
    std::ctstring_t &a_filePath
)
{
    xUNUSED(a_filePath);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
CsvReader::loadString(
    std::ctstring_t &a_rawString
)
{
    xUNUSED(a_rawString);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE ICsv::row_t
CsvReader::headers()
{
    return _rows.at(0);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
CsvReader::header(
    std::csize_t a_column
)
{
    return headers().at(a_column);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::size_t
CsvReader::columns()
{
    return headers().size();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::size_t
CsvReader::rows()
{
    return _rows.size();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
CsvReader::cell(
    std::csize_t a_row,		///< row
    std::csize_t a_column	///< column
)
{
    return _rows.at(a_row).at(a_column);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
CsvReader::_isValid()
{
    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CsvReader::_clear()
{
	_rows.clear();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   CsvReader - public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
CsvWriter::CsvWriter(
    cCsvData &a_data
) :
    _data(a_data)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CsvWriter::saveFile(
	crow_t          &a_header,
	crows_t         &a_rows,
    std::ctstring_t &a_filePath
)
{
	File::clear(a_filePath);

	// a_header
	{
		std::ctstring_t &header = String::join(a_header, Const::nl());

		File::textWrite(a_filePath, header, File::omAppend);
	}

	// a_rows
	xFOR_EACH_CONST(crows_t, it_row, a_rows)
	{
		std::ctstring_t &row = String::join(*it_row, Const::nl());

		File::textWrite(a_filePath, row, File::omAppend);
	}
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CsvWriter::saveString(
	crow_t         &a_header,
	crows_t        &a_rows,
    std::tstring_t *out_rawString
)
{
	out_rawString->clear();

	// a_header
	{
		std::ctstring_t &content = String::join(a_header, Const::nl());

		*out_rawString += content;
	}

	// a_rows
	xFOR_EACH_CONST(crows_t, it_row, a_rows)
	{
		std::ctstring_t &content = String::join(*it_row, Const::nl());

		*out_rawString += content;
	}
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, package)
