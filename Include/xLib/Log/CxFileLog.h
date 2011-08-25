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
{
    public:
        enum ELogSizes {
            lsDefaultSize    = 20  * 1024 * 1024,
            lsDefaultMaxSize = 200 * 1024 * 1024,
            lsLimitSize      = 500 * 1024 * 1024
        };

                         CxFileLog   (const ULONG culMaxFileSizeBytes);
        virtual         ~CxFileLog   ();

        BOOL             bSetFilePath(const std::tstring &csFilePath);
        const std::tstring &  sGetFilePath() const;

        BOOL             bWrite      (LPCTSTR pcszFormat, ...);
        BOOL             bClear      ();
        BOOL             bDelete     ();

    private:
        std::tstring          _m_sFilePath;
        ULONG            _m_ulMaxFileSizeBytes;

    #if defined(xOS_WIN)
        ////CxMutex          _m_mtFile;
    #elif defined(xOS_LINUX)
        //TODO: CxMutex
    #endif

        BOOL             _bDeleteIfFull();
};
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxFileLogH
