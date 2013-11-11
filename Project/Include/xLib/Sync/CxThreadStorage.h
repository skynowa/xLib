/**
 * \file  CxThreadStorage.h
 * \brief thread local storage
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
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

    bool_t   isSet() const xWARN_UNUSED_RV;

    void_t  *value() const xWARN_UNUSED_RV;
        ///< get the value
    void_t   setValue(void_t *value) const;
        ///< set value

private:
#if xOS_ENV_WIN
    typedef ulong_t       index_t;
#else
    typedef pthread_key_t index_t;
#endif

    void_t   _construct();
        ///< allocates a thread storage index
    void_t   _destruct();
        ///< releases a thread storage index

    index_t  _index;
        ///< thread storage index
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Sync/CxThreadStorage.inl>
