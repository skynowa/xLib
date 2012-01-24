/**
 * \file  CxHandleT.h
 * \brief handle
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




#ifndef xLib_Common_CxHandleTH
#define xLib_Common_CxHandleTH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxMacros.h>

#if 0
    #include <xLib/Sync/CxCurrentProcess.h>
#endif
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template<EHandleValue hvTag>
class CxHandleT
    /// handle
{
    public:
                       CxHandleT       ();
            ///< constructor
        explicit       CxHandleT       (const TxNativeHandle chHandle);
            ///< constructor
        explicit       CxHandleT       (const CxHandleT &chHandle);
            ///< constructor
        virtual       ~CxHandleT       ();
            ///< destructor

        CxHandleT &    operator =      (const TxNativeHandle chHandle);
            ///< operator =
        CxHandleT &    operator =      (const CxHandleT &chHandle);
            ///< operator =

        TxNativeHandle hGet            () const;
            ///< get
        bool           bSet            (const TxNativeHandle chHandle);
            ///< set
        TxNativeHandle hDuplicate      () const;
            ///< duplicate handle

        bool           bIsValid        () const;
            ///< is valid
        bool           bAttach         (const TxNativeHandle chHandle);
            ///< attach
        TxNativeHandle hDetach         ();
            ///< detach
        bool           bClose          ();
            ///< close

    #if defined(xOS_ENV_WIN)
        ulong_t        ulGetInformation() const;
            ///< get certain properties of an object handle
        bool           bSetInformation (const ulong_t culMask, const ulong_t culFlags);
            ///< set information
    #endif

    private:
        typedef CxHandleErrorT<hvTag>  TxErrorValue;

        TxNativeHandle _m_hHandle;    ///< handle
};
//---------------------------------------------------------------------------
typedef CxHandleT<hvNull>    CxHandle;
typedef CxHandleT<hvInvalid> CxFileHandle;

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include <Common/CxHandleT.inl>
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxHandleTH
