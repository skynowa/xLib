/**
 * \file  ThreadStorage.h
 * \brief thread local storage
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class ThreadStorage
    /// thread local storage
{
public:
             ThreadStorage();
        ///< constructor
    virtual ~ThreadStorage();
        ///< destructor

    bool_t   isValid() const xWARN_UNUSED_RV;
        ///< is valid
    bool_t   isSet() const xWARN_UNUSED_RV;
        ///< is set value
    void_t  *value() const xWARN_UNUSED_RV;
        ///< get the value
    void_t   setValue(void_t **value) const;
        ///< set value

private:
#if xENV_WIN
    typedef DWORD         index_t;
#elif xENV_UNIX
    typedef pthread_key_t index_t;
#endif

    index_t  _index;
        ///< thread storage index

    xNO_COPY_ASSIGN(ThreadStorage)

xPLATFORM_IMPL:
    index_t  _indexInvalid_impl() const;
    void_t   _construct_impl();
    void_t   _destruct_impl();
    bool_t   _isValid_impl() const xWARN_UNUSED_RV;
    bool_t   _isSet_impl() const xWARN_UNUSED_RV;
    void_t  *_value_impl() const xWARN_UNUSED_RV;
    void_t   _setValue_impl(void_t **value) const;
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "ThreadStorage.cpp"
#endif
