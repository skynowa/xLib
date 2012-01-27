/**
 * \file  CxHandleErrorT.h
 * \brief error handle value
 */


#ifndef xLib_Common_CxHandleErrorTH
#define xLib_Common_CxHandleErrorTH
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

enum EHandleValue
    /// error handle type
{
    hvNull,     ///< like "null"
    hvInvalid   ///< like "invalid"
};

template<EHandleValue hvTag>
struct CxHandleErrorT;
    /// handle error

template<>
struct CxHandleErrorT<hvNull>
    /// handle error is hvNull
{
    static TxNativeHandle
    hGet () { return xNATIVE_HANDLE_NULL; }
};

template<>
struct CxHandleErrorT<hvInvalid>
    /// handle error is hvInvalid
{
    static TxNativeHandle
    hGet () { return xNATIVE_HANDLE_INVALID; }
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxHandleErrorTH