/**
 * \file  HandleT.h
 * \brief handle
 */


#pragma once

//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

namespace debug
{

class NativeError;
class StackTrace;
class ErrorReport;
class Debugger;

}

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
#include <xLib/Interface/IHandle.h>
#include <xLib/Core/HandleErrorT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

/**
 * Types:
 *
 * Native
 * NativeModule
 * StdFile
 *
 * Custom type
 */

template<typename T, ExHandleValue valueT>
class HandleT :
    public IHandle<T>
    /// handle
{
public:
              HandleT();
        ///< constructor
    explicit  HandleT(const T &handle);
        ///< constructor
    explicit  HandleT(const HandleT &handle);
        ///< constructor
    virtual  ~HandleT();
        ///< destructor

    HandleT & operator = (const T &handle);
        ///< operator =
    HandleT & operator = (const HandleT &handle);
        ///< operator =

    T         get() const xWARN_UNUSED_RV;
        ///< get
    void_t    set(const T &handle);
        ///< set
    T         dup() const xWARN_UNUSED_RV;
        ///< duplicate handle

    bool_t    isValid() const xWARN_UNUSED_RV;
        ///< is valid
    void_t    attach(const T &handle);
        ///< attach
    T         detach() xWARN_UNUSED_RV;
        ///< detach
    void_t    close();
        ///< close

#if xENV_WIN
    ulong_t   info() const xWARN_UNUSED_RV;
        ///< get certain properties of an object handle
    void_t    setInfo(culong_t &mask, culong_t &flags);
        ///< set information
#endif

private:
    typedef HandleErrorT<T, valueT> error_value_t;

    T         _handle;    ///< handle

xPLATFORM_IMPL:
    T         _dup_impl() const;
    bool_t    _isValid_impl() const;
    void_t    _close_impl();
};

typedef HandleT<native_handle_t, hvNull>    Handle;
typedef HandleT<native_handle_t, hvInvalid> HandleInvalid;

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "HandleT.inl"
