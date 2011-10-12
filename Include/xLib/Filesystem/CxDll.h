/**
 * \file  CxDll.h
 * \brief dynamic linking loader
 */


#ifndef xLib_Filesystem_CxDllH
#define xLib_Filesystem_CxDllH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxDll :
    public CxNonCopyable
    /// dynamic linking loader
{
    public:
    #if defined(xOS_ENV_WIN)
        typedef FARPROC TxProcAddress;
    #elif defined(xOS_ENV_UNIX)
        typedef VOID *  TxProcAddress;
    #endif
                      CxDll           ();
            ///< constructor
        virtual      ~CxDll           ();
            ///< destructor

        BOOL          bIsLoaded       () const;
            ///< is loaded
        BOOL          bLoad           (const std::tstring &csDllPath);
            ///< load
        TxProcAddress fpGetProcAddress(const std::tstring &csProcName) const;
            ///< get address of an exported function or variable
        BOOL          bFree           ();
            ///< free

    private:
    #if defined(xOS_ENV_WIN)
        typedef HMODULE  TxHandle;
    #elif defined(xOS_ENV_UNIX)
        typedef VOID *   TxHandle;
    #endif

        TxHandle      _m_hDLL;   ///< dll module handle
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxDllH
