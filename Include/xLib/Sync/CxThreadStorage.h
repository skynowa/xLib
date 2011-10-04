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
                 CxThreadStorage();
            ///< constructor
        virtual ~CxThreadStorage();
            ///< destructor

        VOID    *pvGetValue     () const;
            ///< get the value
        BOOL     bSetValue      (VOID *pvValue) const;
            ///< set value

    private:
    #if defined(xOS_ENV_WIN)
        typedef ULONG         TxIndex;
    #elif defined(xOS_ENV_UNIX)
        typedef pthread_key_t TxIndex;
    #endif

        BOOL     _bAlloc        ();
            ///< allocates a thread storage index
        BOOL     _bFree         ();
            ///< releases a thread storage index

        TxIndex  _m_indIndex;
            ///< thread storage index
};
//---------------------------------------------------------------------------
#endif    //CxLib_Sync_CxThreadStorageH
