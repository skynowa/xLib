/**
 * \file  CxHandleT.h
 * \brief handle
 */


#ifndef xLib_Common_CxHandleTH
#define xLib_Common_CxHandleTH
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxLastError;
class CxStackTrace;
class CxErrorReport;
class CxDebugger;

xNAMESPACE_END(NxLib)

#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleErrorT.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template<ExHandleValue hvTag>
class CxHandleT
    /// handle
{
public:
                    CxHandleT  ();
        ///< constructor
    explicit        CxHandleT  (const native_handle_t &chHandle);
        ///< constructor
    explicit        CxHandleT  (const CxHandleT &chHandle);
        ///< constructor
    virtual        ~CxHandleT  ();
        ///< destructor

    CxHandleT &     operator = (const native_handle_t &chHandle);
        ///< operator =
    CxHandleT &     operator = (const CxHandleT &chHandle);
        ///< operator =

    native_handle_t get        () const xWARN_UNUSED_RESULT;
        ///< get
    void            set        (const native_handle_t &chHandle);
        ///< set
    native_handle_t duplicate  () const xWARN_UNUSED_RESULT;
        ///< duplicate handle

    bool            isValid    () const xWARN_UNUSED_RESULT;
        ///< is valid
    void            attach     (const native_handle_t &chHandle);
        ///< attach
    native_handle_t detach     () xWARN_UNUSED_RESULT;
        ///< detach
    void            close      ();
        ///< close

#if xOS_ENV_WIN
    ulong_t         info       () const xWARN_UNUSED_RESULT;
        ///< get certain properties of an object handle
    void            setInfo    (const ulong_t &culMask, const ulong_t &culFlags);
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
#endif // xLib_Common_CxHandleTH
