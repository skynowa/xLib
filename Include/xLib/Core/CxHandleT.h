/**
 * \file  CxHandleT.h
 * \brief handle
 */


#pragma once

//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

namespace debug {
    class CxLastError;
    class CxStackTrace;
    class CxErrorReport;
    class CxDebugger;
}

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleErrorT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

template<ExHandleValue tagT>
class CxHandleT
    /// handle
{
public:
                    CxHandleT();
        ///< constructor
    explicit        CxHandleT(cnative_handle_t &handle);
        ///< constructor
    explicit        CxHandleT(const CxHandleT &handle);
        ///< constructor
    virtual        ~CxHandleT();
        ///< destructor

    CxHandleT &     operator = (cnative_handle_t &handle);
        ///< operator =
    CxHandleT &     operator = (const CxHandleT &handle);
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
    typedef CxHandleErrorT<tagT> error_value_t;

    native_handle_t _handle;    ///< handle
};

typedef CxHandleT<hvNull>    CxHandle;
typedef CxHandleT<hvInvalid> CxHandleInvalid;

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "CxHandleT.inl"
