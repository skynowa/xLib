/**
 * \file  CxFileLog.h
 * \brief logging to file
 */


#ifndef xLib_Log_CxFileLogH
#define xLib_Log_CxFileLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if xOS_ENV_WIN
    #include <xLib/Sync/CxMutex.h>
#elif xOS_ENV_UNIX

#endif
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

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

        bool                 bSetFilePath(const std::tstring &csFilePath);
            ///< set log path
        const std::tstring & sGetFilePath() const;
            ///< get log path

        bool                 bWrite      (const tchar *pcszFormat, ...);
            ///< write
        bool                 bClear      ();
            ///< clear content
        bool                 bDelete     ();
            ///< delete

    private:
        std::tstring         _m_sFilePath;            ///< file path
        ULONG                _m_ulMaxFileSizeBytes;    ///< maximum file size in bytes

    #if xTODO
        CxAutoMutex          _m_mtFile;
    #endif

        bool                 _bDeleteIfFull();
            ///< delete log, if full
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxFileLogH
