/**
 * \file   CxFileTemp.h
 * \brief  temporary file
 */


#ifndef xLib_CxFileTempH
#define xLib_CxFileTempH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxFile;

class CxFileTemp :
    private CxNonCopyable
    /// temporary file
{
public:
    explicit        CxFileTemp(const bool &cbIsAutoDelete);
        ///< constructor
    virtual        ~CxFileTemp();
        ///< destructor

    void            vCreate   (const std::tstring_t &csFilePath, const std::tstring_t &csDirPath, CxFile *pfFile);
        ///< create temporary file, open it

private:
    const bool      _m_cbIsAutoDelete;    ///< autodelete flag
    CxFile         *_m_pfFile;            ///< temporary file handle
    std::tstring_t  _m_sFilePath;         ///< temporary file path
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_CxFileTempH
