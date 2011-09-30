/**
 * \file  CxTls.h
 * \brief thread local storage
 */


#ifndef CxLib_Sync_CxTlsH
#define CxLib_Sync_CxTlsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxTls :
    public CxNonCopyable
    /// thread local storage
{
    public:
                 CxTls     ();
        virtual ~CxTls     ();

        BOOL     bAlloc    ();
        BOOL     bFree     ();
        VOID    *pvGetValue();
        BOOL     bSetValue (VOID *pvValue);

    private:
        ULONG    _m_ulIndex;
};
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#endif    //CxLib_Sync_CxTlsH
