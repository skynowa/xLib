/**
 * \file  CxDll.h
 * \brief dynamic linking loader
 */


#ifndef xLib_Filesystem_CxDllH
#define xLib_Filesystem_CxDllH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDll :
    private CxNonCopyable
    /// dynamic linking loader
{
public:
#if   xOS_ENV_WIN
    typedef FARPROC proc_address_t;
#elif xOS_ENV_UNIX
    typedef void *  proc_address_t;
#endif
                    CxDll       ();
        ///< constructor
    virtual        ~CxDll       ();
        ///< destructor

    bool_t            isLoaded    () const xWARN_UNUSED_RV;
        ///< is loaded
    void            load        (const std::tstring_t &csDllPath);
        ///< load
    bool_t            isProcExists(const std::tstring_t &csProcName) const xWARN_UNUSED_RV;
        ///< is function exists
    proc_address_t  procAddress (const std::tstring_t &csProcName) const xWARN_UNUSED_RV;
        ///< get address of an exported function or variable

private:
#if   xOS_ENV_WIN
    typedef HMODULE handle_t;
#elif xOS_ENV_UNIX
    typedef void *  handle_t;
#endif

    handle_t        _m_hDll;   ///< dll module handle

    void            _free       ();
        ///< free
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Filesystem_CxDllH
