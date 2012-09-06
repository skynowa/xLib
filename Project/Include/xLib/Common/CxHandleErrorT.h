/**
 * \file  CxHandleErrorT.h
 * \brief error handle value
 */


#ifndef xLib_Common_CxHandleErrorTH
#define xLib_Common_CxHandleErrorTH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

enum ExHandleValue
    /// error handle type
{
    hvInvalid = - 1,    ///< like "invalid"
    hvNull    = 0,      ///< like "null"
};

template<ExHandleValue hvTag>
struct CxHandleErrorT;
    /// handle error

template<>
struct CxHandleErrorT<hvInvalid>
    /// handle error is hvInvalid
{
    static 
    native_handle_t hGet() { 
        return xNATIVE_HANDLE_INVALID; 
    }
};

template<>
struct CxHandleErrorT<hvNull>
    /// handle error is hvNull
{
    static 
    native_handle_t hGet() { 
        return xNATIVE_HANDLE_NULL; 
    }
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif  // xLib_Common_CxHandleErrorTH
