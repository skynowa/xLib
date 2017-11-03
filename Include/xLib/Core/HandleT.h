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
#include <xLib/Core/HandleErrorT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<ExHandleValue tagT>
class HandleT
    /// handle
{
public:
                    HandleT();
        ///< constructor
    explicit        HandleT(cnative_handle_t &handle);
        ///< constructor
    explicit        HandleT(const HandleT &handle);
        ///< constructor
    virtual        ~HandleT();
        ///< destructor

    HandleT &     operator = (cnative_handle_t &handle);
        ///< operator =
    HandleT &     operator = (const HandleT &handle);
        ///< operator =

    native_handle_t get() const xWARN_UNUSED_RV;
        ///< get
    void_t          set(cnative_handle_t &handle);
        ///< set
    native_handle_t duplicate() const xWARN_UNUSED_RV;
        ///< duplicate handle

    bool_t          isValid() const xWARN_UNUSED_RV;
        ///< is valid
    void_t          attach(cnative_handle_t &handle);
        ///< attach
    native_handle_t detach() xWARN_UNUSED_RV;
        ///< detach
    void_t          close();
        ///< close

#if xENV_WIN
    ulong_t         info() const xWARN_UNUSED_RV;
        ///< get certain properties of an object handle
    void_t          setInfo(culong_t &mask, culong_t &flags);
        ///< set information
#endif

private:
    typedef HandleErrorT<tagT> error_value_t;

    native_handle_t _handle;    ///< handle

xPLATFORM_IMPL:
    native_handle_t _duplicate_impl() const;
    bool_t          _isValid_impl() const;
    void_t          _close_impl();
};

typedef HandleT<hvNull>    Handle;
typedef HandleT<hvInvalid> HandleInvalid;

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "HandleT.inl"
