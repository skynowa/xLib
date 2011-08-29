/**
 * \file  CxFileLog.h
 * \brief logging to file
 */


#ifndef xLib_Log_CxFileLogH
#define xLib_Log_CxFileLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_WIN)
    #include <xLib/Sync/CxMutex.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
class CxFileLog :
    public CxNonCopyable
    /// logging to file
{
    public:
        enum ELogSizes
            /// log size
        {
            lsDefaultSize    = 20  * 1024 * 1024,
            lsDefaultMaxSize = 200 * 1024 * 1024,
            lsLimitSize      = 500 * 1024 * 1024
        };

                             CxFileLog   (const ULONG culMaxFileSizeBytes);
            ///< constructor
        virtual             ~CxFileLog   ();
        	///< destructor

        BOOL                 bSetFilePath(const std::tstring &csFilePath);
    		///< set log path
        const std::tstring & sGetFilePath() const;
    		///< get log path

        BOOL                 bWrite      (LPCTSTR pcszFormat, ...);
    		///< write
        BOOL                 bClear      ();
    		///< clear content
        BOOL                 bDelete     ();
    		///< delete

    private:
        std::tstring         _m_sFilePath;			///< file path
        ULONG                _m_ulMaxFileSizeBytes;	///< maximum file size in bytes

    #if xTODO
        CxAutoMutex          _m_mtFile;
    #endif

        BOOL                 _bDeleteIfFull();
    		///< delete log, if full
};
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxFileLogH
