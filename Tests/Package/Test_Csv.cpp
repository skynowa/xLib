/**
 * \file   Test_Csv.cpp
 * \brief  test Csv
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Csv)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Csv::unit()
{
    xTEST_CASE("CsvReader")
    {
        xl::package::CsvOption option;
        option.fileExtension    = xT("csv");
        option.hasHeader        = true;
        option.eol              = xT("\n");
        option.delimiter        = xT(';');
        option.isTrimCells      = true;
        option.isSkipEmptyLines = true;

        xl::package::CsvReader csvReader(option);
        csvReader.loadFile(xT(""));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
