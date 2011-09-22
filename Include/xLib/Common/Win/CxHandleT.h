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
#if defined(xOS_WIN)

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
        BOOL                bSet                    (const HANDLE chHandle);
            ///< set

        BOOL                bIsValid                () const;
            ///< is valid
        BOOL                bAttach                 (const HANDLE chHandle);
            ///< attach
        HANDLE              hDetach                 ();
            ///< detach
        BOOL                bClose                  ();
            ///< close

        ULONG               ulGetInformation        () const;
            ///< get certain properties of an object handle
        BOOL                bSetInformation         (const ULONG culMask, const ULONG culFlags);
            ///< set information
        BOOL 	            bIsFlagInherit          () const;
            ///< is flag inherit
        BOOL                bIsFlagProtectFromClose () const;
            ///< is flag protect from close
        BOOL                bSetFlagInherit         (const BOOL cbFlagInherit);
            ///< set flaginherit
        BOOL                bSetFlagProtectFromClose(const BOOL cbFlagProtectFromClose);
            ///< set flag protect from close
        HANDLE              hDuplicate              (const HANDLE chTargetProcess, const ULONG cluDesiredAccess, const BOOL cbInheritHandle/* = FALSE*/, const ULONG cluOptions/* = 0*/) const;
            ///< duplicates an object handle

        //static
        static HANDLE       hGetCurrentProcess      ();
            ///< get a pseudo handle for the current process
        static BOOL         bIsValid                (const HANDLE chHandle);
            ///< is valid

    private:
        typedef CxHandleFailValue<hvTag>  TxFailValue;

        mutable BOOL        _m_bRes;                    ///< for private use
        HANDLE              _m_hHandle;                 ///< handle

        static const HANDLE _ms_chCurrProcessHandle;    ///< current process handle
};
//---------------------------------------------------------------------------
typedef CxHandleT<hvNull>    CxHandle;
typedef CxHandleT<hvInvalid> CxFileHandle;
//---------------------------------------------------------------------------
#include <Common/Win/CxHandleT.inl>

#endif
//---------------------------------------------------------------------------
#endif	//xLib_Common_Win_CxHandleTH
