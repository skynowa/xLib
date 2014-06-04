/**
 * \file  CxThreadStorage.h
 * \brief thread local storage
 */


#pragma once

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

    index_t  _index;
        ///< thread storage index

    xNO_COPY_ASSIGN(CxThreadStorage)

xPLATFORM:
    void_t   _construct_impl();
    void_t   _destruct_impl();
    bool_t   _isSet_impl() const xWARN_UNUSED_RV;
    void_t  *_value_impl() const xWARN_UNUSED_RV;
    void_t   _setValue_impl(void_t *value) const;
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxThreadStorage.inl"
