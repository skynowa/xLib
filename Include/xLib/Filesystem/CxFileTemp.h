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
class CxFileTemp :
    public CxNonCopyable
{
	public:
		explicit      CxFileTemp(const BOOL cbIsAutoDelete);
            ///< constructor
		virtual      ~CxFileTemp();
		    ///< destructor

        BOOL          bCreate   (const std::tstring &csFilePath, const std::tstring &csDirPath, CxFile *pfFile);
            ///< create temporary file, open it

    private:
        friend class CxFile;

        const BOOL    _m_cbIsAutoDelete;    ///< autodelete flag
        CxFile       *_m_pfFile;            ///< temporary file handle
        std::tstring  _m_sFilePath;         ///< temporary file path
};
//---------------------------------------------------------------------------
#endif //xLib_CxFileTempH
