/**
 * \file  CxHandleT.h
 * \brief handle
 */


#pragma once

//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxLastError;
class CxStackTrace;
class CxErrorReport;
class CxDebugger;

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleErrorT.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template<ExHandleValue hvTag>
class CxHandleT
    /// handle
{
public:
                    CxHandleT  ();
        ///< constructor
    explicit        CxHandleT  (cnative_handle_t &chHandle);
        ///< constructor
    explicit        CxHandleT  (const CxHandleT &chHandle);
        ///< constructor
    virtual        ~CxHandleT  ();
        ///< destructor

    CxHandleT &     operator = (cnative_handle_t &chHandle);
        ///< operator =
    CxHandleT &     operator = (const CxHandleT &chHandle);
        ///< operator =

    native_handle_t get        () const xWARN_UNUSED_RV;
        ///< get
    void_t          set        (cnative_handle_t &chHandle);
        ///< set
    native_handle_t duplicate  () const xWARN_UNUSED_RV;
        ///< duplicate handle

    bool_t          isValid    () const xWARN_UNUSED_RV;
        ///< is valid
    void_t          attach     (cnative_handle_t &chHandle);
        ///< attach
    native_handle_t detach     () xWARN_UNUSED_RV;
        ///< detach
    void_t          close      ();
        ///< close

#if xOS_ENV_WIN
    ulong_t         info       () const xWARN_UNUSED_RV;
        ///< get certain properties of an object handle
    void_t          setInfo    (culong_t &culMask, culong_t &culFlags);
        ///< set information
#endif

private:
    typedef CxHandleErrorT<hvTag>  error_value_t;

    native_handle_t _m_hHandle;    ///< handle
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#include "CxHandleT.inl"
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

typedef CxHandleT<hvNull>    CxHandle;
typedef CxHandleT<hvInvalid> CxHandleInvalid;

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
