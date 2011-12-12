/**
 * \file  CxHandleT.h
 * \brief handle
 */


#ifndef xLib_Common_CxHandleTH
#define xLib_Common_CxHandleTH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxMacros.h>

#if xTODO
    #include <xLib/Sync/CxCurrentProcess.h>
#endif
//---------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

#if xOS_ENV_WIN
    typedef HANDLE TxHandle; ///< handle
#elif xOS_ENV_UNIX
    typedef pid_t  TxHandle; ///< handle
#endif

enum EHandleValue {
    hvNull,
    hvInvalid
};

template<EHandleValue hvTag>
struct CxHandleFailValue;

template<>
struct CxHandleFailValue<hvNull> {
    static TxHandle get () { return NULL; }
};

template<>
struct CxHandleFailValue<hvInvalid> {
    static TxHandle get () { 
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
                    operator TxHandle       () const;
            ///< operator TxHandle

        TxHandle    hGet                    () const;
            ///< get
        bool        bSet                    (const TxHandle chHandle);
            ///< set

        bool        bIsValid                () const;
            ///< is valid
        bool        bAttach                 (const TxHandle chHandle);
            ///< attach
        TxHandle    hDetach                 ();
            ///< detach
        bool        bClose                  ();
            ///< close

        ulong_t     ulGetInformation        () const;
            ///< get certain properties of an object handle
        bool        bSetInformation         (const ulong_t culMask, const ulong_t culFlags);
            ///< set information
        bool        bIsFlagInherit          () const;
            ///< is flag inherit
        bool        bIsFlagProtectFromClose () const;
            ///< is flag protect from close
        bool        bSetFlagInherit         (const bool cbFlagInherit);
            ///< set flaginherit
        bool        bSetFlagProtectFromClose(const bool cbFlagProtectFromClose);
            ///< set flag protect from close
        TxHandle    hDuplicate              (const TxHandle chTargetProcess, const ulong_t cluDesiredAccess, const bool cbInheritHandle/* = false*/, const ulong_t cluOptions/* = 0*/) const;
            ///< duplicates an object handle

        //static
        static bool bIsValid                (const TxHandle chHandle);
            ///< is valid

    private:
        typedef CxHandleFailValue<hvTag>  TxFailValue;

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
