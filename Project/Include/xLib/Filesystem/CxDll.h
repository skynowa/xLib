/**
 * \file  CxDll.h
 * \brief dynamic linking loader
 */


#ifndef xLib_Filesystem_CxDllH
#define xLib_Filesystem_CxDllH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDll :
    private CxNonCopyable
    /// dynamic linking loader
{
    public:
    #if xOS_ENV_WIN
        typedef FARPROC TxProcAddress;
    #elif xOS_ENV_UNIX
        typedef void *  TxProcAddress;
    #endif
                      CxDll           ();
            ///< constructor
        virtual      ~CxDll           ();
            ///< destructor

        bool          bIsLoaded       () const;
            ///< is loaded
        bool          bLoad           (const std::tstring_t &csDllPath);
            ///< load
        bool          bIsProcExists   (const std::tstring_t &csProcName) const;
            ///< is function exists
        TxProcAddress fpGetProcAddress(const std::tstring_t &csProcName) const;
            ///< get address of an exported function or variable

    private:
    #if xOS_ENV_WIN
        typedef HMODULE  TxHandle;
    #elif xOS_ENV_UNIX
        typedef void *   TxHandle;
    #endif

        TxHandle      _m_hDll;   ///< dll module handle

        bool          _bFree          ();
            ///< free
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxDllH
