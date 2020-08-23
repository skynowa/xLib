/**
 * \file   FileTemp.h
 * \brief  temporary file
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class FileIO;

class FileTemp
    /// temporary file
{
public:
///@name ctors, dtor
///@{
	explicit FileTemp(cbool_t &isAutoDelete);
	virtual ~FileTemp();

	xNO_DEFAULT_CONSTRUCT(FileTemp)
	xNO_COPY_ASSIGN(FileTemp)
///@}

    void_t   create(std::ctstring_t &filePath, std::ctstring_t &dirPath, FileIO *file);
        ///< create temporary file, open it

private:
    cbool_t         _isAutoDelete {};  ///< auto delete flag
    FileIO           *_file {};          ///< temporary file
    std::tstring_t  _filePath;         ///< temporary file path

xPLATFORM_IMPL:
    void_t          _create_impl(HandleStdFile &stdFile);
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
