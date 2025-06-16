/**
 * \file  ThreadStorage.h
 * \brief thread local storage
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class ThreadStorage
    /// thread local storage
{
public:
///\name ctors, dtor
///\{
			 ThreadStorage();
	virtual ~ThreadStorage();

	xNO_COPY_ASSIGN(ThreadStorage);
///\}

    bool_t   isValid() const;
        ///< is valid
    bool_t   isSet() const;
        ///< is set value
    void_t  *value() const;
        ///< get the value
    void_t   setValue(void_t **value) const;
        ///< set value

private:
#if xENV_WIN
    using index_t = DWORD;
#elif xENV_UNIX
    using index_t = pthread_key_t;
#endif

#if   xENV_WIN
    index_t _index {TLS_OUT_OF_INDEXES};
#elif xENV_UNIX
    index_t _index {static_cast<index_t>( - 1 )};
#endif
        ///< thread storage index

xPLATFORM_IMPL:
    index_t  _indexInvalid_impl() const;
    void_t   _ctor_impl();
    void_t   _dtor_impl();
    bool_t   _isSet_impl() const;
    void_t  *_value_impl() const;
    void_t   _setValue_impl(void_t **value) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
