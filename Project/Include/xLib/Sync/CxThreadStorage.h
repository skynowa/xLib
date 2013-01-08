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

    bool     isSet          () const xWARN_UNUSED_RESULT;

    void    *value          () const xWARN_UNUSED_RESULT;
        ///< get the value
    void     setValue       (void *pvValue) const;
        ///< set value

private:
#if   xOS_ENV_WIN
    typedef ulong_t       index_t;
#elif xOS_ENV_UNIX
    typedef pthread_key_t index_t;
#endif

    void     _alloc         ();
        ///< allocates a thread storage index
    void     _free          ();
        ///< releases a thread storage index

    index_t  _m_indIndex;
        ///< thread storage index
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //CxLib_Sync_CxThreadStorageH
