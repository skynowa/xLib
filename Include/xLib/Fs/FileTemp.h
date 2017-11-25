/**
 * \file   FileTemp.h
 * \brief  temporary file
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/HandleT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

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

xPLATFORM_IMPL:
    void_t          _create_impl(HandleStdFile &stdFile);
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
