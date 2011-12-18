/**
 * \file  CxHandleT.h
 * \brief handle
 */


#ifndef xLib_Common_CxHandleTH
#define xLib_Common_CxHandleTH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxMacros.h>

#if 0
    #include <xLib/Sync/CxCurrentProcess.h>
#endif
//---------------------------------------------------------------------------
#if xOS_ENV_WIN
    typedef HANDLE TxHandle;
#elif xOS_ENV_UNIX
    typedef pid_t  TxHandle;
#endif
    ///< native handle

xNAMESPACE_ANONYM_BEGIN

enum EHandleValue 
    ///< error handle type
{
    hvNull,
    hvInvalid
};

template<EHandleValue hvTag>
struct CxHandleError;

template<>
struct CxHandleError<hvNull> {
    static TxHandle hGet () {
    #if defined(xOS_ENV_WIN)
        return NULL;
    #elif defined(xOS_ENV_UNIX)
        return 0;
    #endif
    }
};

template<>
struct CxHandleError<hvInvalid> {
    static TxHandle hGet () {
    #if defined(xOS_ENV_WIN)
        return INVALID_HANDLE_VALUE;
    #elif defined(xOS_ENV_UNIX)
        return - 1;
    #endif
    }
};

xNAMESPACE_ANONYM_END
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template<EHandleValue hvTag>
class CxHandleT
    /// handle
{
    public:
                    CxHandleT               ();
            ///< constructor
        explicit    CxHandleT               (const TxHandle chHandle);
            ///< constructor
        explicit    CxHandleT               (const CxHandleT &chHandle);
            ///< constructor
        virtual    ~CxHandleT               ();
            ///< destructor

        CxHandleT & operator =              (const TxHandle chHandle);
            ///< operator =
        CxHandleT & operator =              (const CxHandleT &chHandle);
            ///< operator =

        TxHandle    hGet                    () const;
            ///< get
        bool        bSet                    (const TxHandle chHandle);
            ///< set
        TxHandle    hDuplicate              () const;
            ///< duplicate handle

        bool        bIsValid                () const;
            ///< is valid
        bool        bAttach                 (const TxHandle chHandle);
            ///< attach
        TxHandle    hDetach                 ();
            ///< detach
        bool        bClose                  ();
            ///< close

    #if defined(xOS_ENV_WIN)
        ulong_t     ulGetInformation        () const;
            ///< get certain properties of an object handle
        bool        bSetInformation         (const ulong_t culMask, const ulong_t culFlags);
            ///< set information
    #endif

    private:
        typedef CxHandleError<hvTag>  TxErrorValue;

        TxHandle    _m_hHandle;    ///< handle
};
//---------------------------------------------------------------------------
typedef CxHandleT<hvNull>    CxHandle;
typedef CxHandleT<hvInvalid> CxFileHandle;

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include <Common/CxHandleT.inl>
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxHandleTH
