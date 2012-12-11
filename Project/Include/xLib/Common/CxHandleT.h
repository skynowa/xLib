/**
 * \file  CxHandleT.h
 * \brief handle
 */


#ifndef xLib_Common_CxHandleTH
#define xLib_Common_CxHandleTH
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxLastError;
class CxStackTrace;
class CxErrorReport;
class CxDebugger;

xNAMESPACE_END(NxLib)

#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleErrorT.h>
//---------------------------------------------------------------------------
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

        native_handle_t hGet       () const;
            ///< get
        void            vSet       (const native_handle_t &chHandle);
            ///< set
        native_handle_t hDuplicate () const;
            ///< duplicate handle

        bool            bIsValid   () const;
            ///< is valid
        void            vAttach    (const native_handle_t &chHandle);
            ///< attach
        native_handle_t hDetach    ();
            ///< detach
        void            vClose     ();
            ///< close

    #if xOS_ENV_WIN
        ulong_t         ulInfo     () const;
            ///< get certain properties of an object handle
        void            vSetInfo   (const ulong_t &culMask, const ulong_t &culFlags);
            ///< set information
    #endif

    private:
        typedef CxHandleErrorT<hvTag>  error_value_t;

        native_handle_t _m_hHandle;    ///< handle
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxHandleT.inl"
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

typedef CxHandleT<hvNull>    CxHandle;
typedef CxHandleT<hvInvalid> CxHandleInvalid;

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    // xLib_Common_CxHandleTH
