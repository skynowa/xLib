/**
 * \file   CxFileTemp.h
 * \brief  temporary file
 */


#ifndef xLib_CxFileTempH
#define xLib_CxFileTempH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxFile;

class CxFileTemp :
    private CxNonCopyable
    /// temporary file
{
public:
    explicit        CxFileTemp(cbool_t &cbIsAutoDelete);
        ///< constructor
    virtual        ~CxFileTemp();
        ///< destructor

    void_t          create    (std::ctstring_t &csFilePath, std::ctstring_t &csDirPath, CxFile *pfFile);
        ///< create temporary file, open it

private:
    cbool_t         _m_cbIsAutoDelete;    ///< auto delete flag
    CxFile         *_m_pfFile;            ///< temporary file handle
    std::tstring_t  _m_sFilePath;         ///< temporary file path
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_CxFileTempH
