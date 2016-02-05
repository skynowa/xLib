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
    ctchar_t       separator;
    std::tstring_t filePath;
    std::tstring_t contennt;
};

xTYPEDEF_CONST(CsvData);

class Csv
    ///< Comma-Separated Values parser
{
public:
    explicit         Csv(cCsvData &data);
        ///< constructor
    virtual         ~Csv() {}
        ///< destructor

    std::size_t      rows();
    std::size_t      columns();
    std::tstring_t & item(std::csize_t i, std::csize_t j);

private:
    cCsvData &       _data;

    xNO_COPY_ASSIGN(Csv)
};

xNAMESPACE_END2(xlib, package)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Csv.cpp"
#endif
