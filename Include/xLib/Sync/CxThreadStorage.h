/**
 * \file  CxThreadStorage.h
 * \brief thread local storage
 */


#ifndef CxLib_Sync_CxThreadStorageH
#define CxLib_Sync_CxThreadStorageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxThreadStorage :
    public CxNonCopyable
    /// thread local storage
{
    public:
                 CxThreadStorage();
            ///< constructor
        virtual ~CxThreadStorage();
            ///< destructor

        BOOL     bIsSet         () const;

        void    *pvGetValue     () const;
            ///< get the value
        BOOL     bSetValue      (void *pvValue) const;
            ///< set value

    private:
    #if xOS_ENV_WIN
        typedef ULONG         TxIndex;
    #elif xOS_ENV_UNIX
        typedef pthread_key_t TxIndex;
    #endif

        BOOL     _bAlloc        ();
            ///< allocates a thread storage index
        BOOL     _bFree         ();
            ///< releases a thread storage index

        TxIndex  _m_indIndex;
            ///< thread storage index
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //CxLib_Sync_CxThreadStorageH
