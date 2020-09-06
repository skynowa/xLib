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
	explicit FileTemp(std::ctstring_t &filePathPrefix, std::ctstring_t &dirPath,
				cbool_t isAutoDelete);
	virtual ~FileTemp();

	xNO_DEFAULT_CONSTRUCT(FileTemp)
	xNO_COPY_ASSIGN(FileTemp)
///@}

    void_t create(FileIO *file);
        ///< create temporary file, open it

private:
    std::tstring_t  _filePath;         ///< temporary file path (not constant)
    cbool_t         _isAutoDelete {};  ///< auto delete flag
    FileIO         *_file {};          ///< temporary file

xPLATFORM_IMPL:
    void_t _create_impl(HandleStdFile &stdFile);
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
