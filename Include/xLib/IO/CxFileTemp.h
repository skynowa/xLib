/**
 * \file   CxFileTemp.h
 * \brief  temporary file
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, io)

class CxFile;

class CxFileTemp
    /// temporary file
{
public:
    explicit        CxFileTemp(cbool_t &isAutoDelete);
        ///< constructor
    virtual        ~CxFileTemp();
        ///< destructor

    void_t          create(std::ctstring_t &filePath, std::ctstring_t &dirPath, CxFile *file);
        ///< create temporary file, open it

private:
    cbool_t         _isAutoDelete;  ///< auto delete flag
    CxFile         *_file;          ///< temporary file handle
    std::tstring_t  _filePath;      ///< temporary file path

    xNO_COPY_ASSIGN(CxFileTemp)

xPLATFORM:
    void_t          _create_impl(FILE *stdFile);
};

xNAMESPACE_END2(xlib, io)
//-------------------------------------------------------------------------------------------------
#include "CxFileTemp.inl"
