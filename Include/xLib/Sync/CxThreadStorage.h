/**
 * \file  CxThreadStorage.h
 * \brief thread local storage
 */


#ifndef CxLib_Sync_CxThreadStorageH
#define CxLib_Sync_CxThreadStorageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxThreadStorage :
    public CxNonCopyable
    /// thread local storage
{
    public:
                 CxThreadStorage     ();
            ///< constructor
        virtual ~CxThreadStorage     ();
            ///< destructor

        VOID    *pvGetValue() const;
            ///< retrieves the value in the calling thread's thread local storage (TLS) slot for the specified TLS index
        BOOL     bSetValue (VOID *pvValue) const;
            ///< stores a value in the calling thread's thread local storage (TLS) slot for the specified TLS index

    private:
    #if defined(xOS_ENV_WIN)
        typedef ULONG         TxIndex;
    #elif defined(xOS_ENV_UNIX)
        typedef pthread_key_t TxIndex;
    #endif

        BOOL     _bAlloc    ();
            ///< allocates a thread local storage (TLS) index
        BOOL     _bFree     ();
            ///< releases a thread local storage (TLS) index, making it available for reuse

        TxIndex  _m_indIndex;
};
//---------------------------------------------------------------------------
#endif    //CxLib_Sync_CxThreadStorageH
