/**
 * \file   Csv.cpp
 * \brief  Comma-Separated Values parser
 */


#include "Csv.h"

#include <xLib/Core/String.h>
#include <xLib/Fs/File.h>


xNAMESPACE_BEGIN2(xl, package)

/**************************************************************************************************
*   CsvReader - public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
CsvReader::CsvReader(
    cCsvData &a_data
) :
    _data(a_data),
	_rows()
{
}
//-------------------------------------------------------------------------------------------------
bool_t
CsvReader::loadFile(
    std::ctstring_t &a_filePath
)
{
    xUNUSED(a_filePath);

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
CsvReader::loadString(
    std::ctstring_t &a_rawString
)
{
    xUNUSED(a_rawString);

    return true;
}
//-------------------------------------------------------------------------------------------------
ICsv::row_t
CsvReader::headers()
{
    return _rows.at(0);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CsvReader::header(
    std::csize_t a_column
)
{
    return headers().at(a_column);
}
//-------------------------------------------------------------------------------------------------
std::size_t
CsvReader::columns()
{
    return headers().size();
}
//-------------------------------------------------------------------------------------------------
std::size_t
CsvReader::rows()
{
    return _rows.size();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CsvReader::cell(
    std::csize_t a_row,		///< row
    std::csize_t a_column	///< column
)
{
    return _rows.at(a_row).at(a_column);
}
//-------------------------------------------------------------------------------------------------
bool_t
CsvReader::_isValid()
{
    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
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
CsvWriter::CsvWriter(
    cCsvData &a_data
) :
    _data(a_data)
{
}
//-------------------------------------------------------------------------------------------------
void_t
CsvWriter::saveFile(
	crow_t          &a_header,
	crows_t         &a_rows,
    std::ctstring_t &a_filePath
)
{
	File::clear(a_filePath);

	// a_header
	{
		std::ctstring_t &header = String::join(a_header, _data.delimiter);

		File::textWrite(a_filePath, header + Const::nl(), File::omAppend);
	}

	// a_rows
	xFOR_EACH_CONST(crows_t, it_row, a_rows)
	{
		std::ctstring_t &row = String::join(*it_row, _data.delimiter);

		File::textWrite(a_filePath, row + Const::nl(), File::omAppend);
	}
}
//-------------------------------------------------------------------------------------------------
void_t
CsvWriter::saveString(
	crow_t         &a_header,
	crows_t        &a_rows,
    std::tstring_t *out_rawString
)
{
	out_rawString->clear();

	// a_header
	{
		std::ctstring_t &header = String::join(a_header, _data.delimiter);

		*out_rawString += header + Const::nl();
	}

	// a_rows
	xFOR_EACH_CONST(crows_t, it_row, a_rows)
	{
		std::ctstring_t &row = String::join(*it_row, _data.delimiter);

		*out_rawString += row + Const::nl();
	}
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
