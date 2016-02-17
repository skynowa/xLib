/**
 * \file   Csv.cpp
 * \brief  Comma-Separated Values parser
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Csv.h"
#endif

xNAMESPACE_BEGIN2(xlib, package)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
CsvReader::CsvReader(
    cCsvData &a_data
) :
    _data(a_data)
{
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public
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
    row_t row;

    return row;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
CsvReader::header(
    std::csize_t a_column
)
{
    xUNUSED(a_column);

    std::tstring_t sRv;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::size_t
CsvReader::columns()
{
    return 0;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::size_t
CsvReader::rows()
{
    return 0;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
CsvReader::cell(
    std::csize_t a_row,
    std::csize_t a_column
)
{
    xUNUSED(a_row);
    xUNUSED(a_column);

    std::tstring_t sRv;

    return sRv;
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
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CsvWriter::setHeaders(
    crow_t &a_values
)
{
    xUNUSED(a_values);

}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
CsvWriter::saveFile(
    const std::vector<row_t> &a_csv,
    std::ctstring_t          &a_filePath
)
{
    xUNUSED(a_csv);
    xUNUSED(a_filePath);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
CsvWriter::saveString(
    const std::vector<row_t> &a_csv,
    std::tstring_t           *a_rawString
)
{
    xUNUSED(a_csv);
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
