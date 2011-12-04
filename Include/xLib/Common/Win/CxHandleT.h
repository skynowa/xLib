/**
 * \file  CxHandleT.h
 * \brief handle
 */


#ifndef xLib_Common_Win_CxHandleTH
#define xLib_Common_Win_CxHandleTH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxMacros.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_ANONYM_BEGIN

enum EHandleValue {
    hvNull,
    hvInvalid
};

template<EHandleValue hvTag>
struct CxHandleFailValue;

template<>
struct CxHandleFailValue<hvNull> {
    static HANDLE get () { return NULL; }
};

template<>
struct CxHandleFailValue<hvInvalid> {
    static HANDLE get () { return INVALID_HANDLE_VALUE; }
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
        explicit            CxHandleT               (const HANDLE chHandle);
            ///< constructor
        explicit            CxHandleT               (const CxHandleT &chHandle);
            ///< constructor
        virtual            ~CxHandleT               ();
            ///< destructor

        CxHandleT &         operator =              (const HANDLE chHandle);
            ///< operator =
        CxHandleT &         operator =              (const CxHandleT &chHandle);
            ///< operator =
                            operator HANDLE         () const;
            ///< operator HANDLE

        HANDLE              hGet                    () const;
            ///< get
        bool                bSet                    (const HANDLE chHandle);
            ///< set

        bool                bIsValid                () const;
            ///< is valid
        bool                bAttach                 (const HANDLE chHandle);
            ///< attach
        HANDLE              hDetach                 ();
            ///< detach
        bool                bClose                  ();
            ///< close

        ulong_t             ulGetInformation        () const;
            ///< get certain properties of an object handle
        bool                bSetInformation         (const ulong_t culMask, const ulong_t culFlags);
            ///< set information
        bool                bIsFlagInherit          () const;
            ///< is flag inherit
        bool                bIsFlagProtectFromClose () const;
            ///< is flag protect from close
        bool                bSetFlagInherit         (const bool cbFlagInherit);
            ///< set flaginherit
        bool                bSetFlagProtectFromClose(const bool cbFlagProtectFromClose);
            ///< set flag protect from close
        HANDLE              hDuplicate              (const HANDLE chTargetProcess, const ulong_t cluDesiredAccess, const bool cbInheritHandle/* = false*/, const ulong_t cluOptions/* = 0*/) const;
            ///< duplicates an object handle

        //static
        static bool         bIsValid                (const HANDLE chHandle);
            ///< is valid

    private:
        typedef CxHandleFailValue<hvTag>  TxFailValue;

        HANDLE              _m_hHandle;                 ///< handle
};
//---------------------------------------------------------------------------
typedef CxHandleT<hvNull>    CxHandle;
typedef CxHandleT<hvInvalid> CxFileHandle;

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include <Common/Win/CxHandleT.inl>

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Common_Win_CxHandleTH
