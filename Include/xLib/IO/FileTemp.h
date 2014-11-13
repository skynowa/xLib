/**
 * \file   FileTemp.h
 * \brief  temporary file
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, io)

class File;

class FileTemp
    /// temporary file
{
public:
    explicit        FileTemp(cbool_t &isAutoDelete);
        ///< constructor
    virtual        ~FileTemp();
        ///< destructor

    void_t          create(std::ctstring_t &filePath, std::ctstring_t &dirPath, File *file);
        ///< create temporary file, open it

private:
    cbool_t         _isAutoDelete;  ///< auto delete flag
    File           *_file;          ///< temporary file
    std::tstring_t  _filePath;      ///< temporary file path

    xNO_COPY_ASSIGN(FileTemp)

xPLATFORM:
    void_t          _create_impl(FILE *stdFile);
};

xNAMESPACE_END2(xlib, io)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "FileTemp.cpp"
#endif
