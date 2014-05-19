/**
 * \file  CxThreadStorage.h
 * \brief thread local storage
 */


#pragma once

#ifndef xLib_CxThreadStorageH
#define xLib_CxThreadStorageH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class CxThreadStorage
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
#if xENV_WIN
    typedef ulong_t       index_t;
#elif xENV_UNIX
    typedef pthread_key_t index_t;
#endif

    void_t   _construct();
        ///< allocates a thread storage index
    void_t   _destruct();
        ///< releases a thread storage index

    index_t  _index;
        ///< thread storage index

    xNO_COPY_ASSIGN(CxThreadStorage)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxThreadStorage.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxThreadStorageH
