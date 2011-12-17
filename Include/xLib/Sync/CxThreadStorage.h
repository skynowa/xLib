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
    private CxNonCopyable
    /// thread local storage
{
    public:
                 CxThreadStorage();
            ///< constructor
        virtual ~CxThreadStorage();
            ///< destructor

        bool     bIsSet         () const;

        void    *pvGetValue     () const;
            ///< get the value
        bool     bSetValue      (void *pvValue) const;
            ///< set value

    private:
    #if xOS_ENV_WIN
        typedef ulong_t         TxIndex;
    #elif xOS_ENV_UNIX
        typedef pthread_key_t TxIndex;
    #endif

        bool     _bAlloc        ();
            ///< allocates a thread storage index
        bool     _bFree         ();
            ///< releases a thread storage index

        TxIndex  _m_indIndex;
            ///< thread storage index
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //CxLib_Sync_CxThreadStorageH
