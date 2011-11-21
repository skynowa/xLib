/**
 * \file   CxFileTemp.h
 * \brief
 */


#ifndef xLib_CxFileTempH
#define xLib_CxFileTempH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Filesystem/CxFile.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxFileTemp :
    public CxNonCopyable
{
    public:
        explicit      CxFileTemp(const bool cbIsAutoDelete);
            ///< constructor
        virtual      ~CxFileTemp();
            ///< destructor

        bool          bCreate   (const std::tstring_t &csFilePath, const std::tstring_t &csDirPath, CxFile *pfFile);
            ///< create temporary file, open it

    private:
        friend class CxFile;

        const bool    _m_cbIsAutoDelete;    ///< autodelete flag
        CxFile       *_m_pfFile;            ///< temporary file handle
        std::tstring_t  _m_sFilePath;         ///< temporary file path
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_CxFileTempH
