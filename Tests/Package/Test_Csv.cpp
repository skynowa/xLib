/**
 * \file   Test_Csv.cpp
 * \brief  test Csv
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xlib;

xTEST_CLASS(Test_Csv)
xTEST_UNIT(Test_Csv)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Csv::unit()
{
    xTEST_CASE("CsvReader::CsvReader")
    {
        xlib::package::CsvData csvData;
        csvData.fileExtension    = xT("csv");
        csvData.hasHeader        = true;
        csvData.eol              = xT("\n");
        csvData.delimiter        = xT(';');
        csvData.isTrimCells      = true;
        csvData.isSkipEmptyLines = true;

        xlib::package::CsvReader csvReader(csvData);
        csvReader.loadFile(xT(""));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
