/**
 * \file   Test_Csv.cpp
 * \brief  test Csv
 */


#include <Test/Package/Test_Csv.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Csv)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Csv::unit(
    std::csize_t &a_caseLoops
)
{
    xTEST_CASE("CsvReader::CsvReader", a_caseLoops)
    {
        xlib::package::ICsv::CsvData csvData;
        csvData.fileExtension    = xT("csv");
        csvData.hasHeader        = true;
        csvData.eol              = xT("\n");
        csvData.delimiter        = xT(';');
        csvData.isTrimCells      = true;
        csvData.isSkipEmptyLines = true;

        xlib::package::CsvReader csvReader(csvData);
        csvReader.loadFile(xT(""));
    }
}
//-------------------------------------------------------------------------------------------------
