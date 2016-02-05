/**
 * \file   Csv.h
 * \brief  Comma-Separated Values parser
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, package)

struct CsvData
{
    std::tstring_t appName;
    std::tstring_t appVersionFull;
};

xTYPEDEF_CONST(CsvData);

class Csv
    ///< Comma-Separated Values parser
{
public:
    explicit Csv(cCsvData &data);
        ///< constructor
    virtual ~Csv() {}
        ///< destructor

private:
    cCsvData  &_data;

    xNO_COPY_ASSIGN(Csv)
};

xNAMESPACE_END2(xlib, package)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Csv.cpp"
#endif
