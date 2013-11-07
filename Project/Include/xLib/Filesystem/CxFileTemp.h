/**
 * \file   CxFileTemp.h
 * \brief  temporary file
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxFile;

class CxFileTemp :
    public CxNonCopyable
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
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Filesystem/CxFileTemp.cpp>
#endif
