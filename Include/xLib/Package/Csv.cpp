/**
 * \file   Csv.cpp
 * \brief  Comma-Separated Values parser
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Csv.h"
#endif


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
    return _rows.at(0).at(a_column);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::size_t
CsvReader::columns()
{
    return _rows.at(0).size();
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
xINLINE bool_t
CsvWriter::saveFile(
	crow_t          &a_header,
	crows_t         &a_rows,
    std::ctstring_t &a_filePath
)
{
    xUNUSED(a_header);
    xUNUSED(a_rows);
    xUNUSED(a_filePath);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
CsvWriter::saveString(
	crow_t         &a_header,
	crows_t        &a_rows,
    std::tstring_t *a_rawString
)
{
    xUNUSED(a_header);
    xUNUSED(a_rows);
    xUNUSED(a_rawString);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
CsvWriter::_isValid()
{
    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CsvWriter::_clear()
{
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, package)
