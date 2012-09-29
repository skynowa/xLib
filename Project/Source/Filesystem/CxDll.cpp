/**
 * \file  CxDll.cpp
 * \brief dynamic linking loader
 */


#include <xLib/Filesystem/CxDll.h>

#if   xOS_ENV_WIN
    // lib: n/a
#elif xOS_ENV_UNIX
    // lib: -ldl, -lc (FreeBSD)
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxDll::CxDll() :
    _m_hDll(NULL)
{
}
//---------------------------------------------------------------------------
/* virtual */
CxDll::~CxDll() {
    (void)_bFree();
}
//---------------------------------------------------------------------------
bool
CxDll::bIsLoaded() const {
    xDEBUG_VARS_NA;

    return (NULL != _m_hDll);
}
//---------------------------------------------------------------------------
bool
CxDll::bLoad(
    const std::tstring_t &csDllPath
)
{
    xDEBUG_VARS_NA;
    /*DEBUG*/xASSERT_RET(false == csDllPath.empty(), false);

    bool bRv = _bFree();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

#if   xOS_ENV_WIN
    _m_hDll = ::LoadLibrary(csDllPath.c_str());
    /*DEBUG*/xASSERT_RET(NULL != _m_hDll, false);
#elif xOS_ENV_UNIX
    _m_hDll = ::dlopen(csDllPath.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    /*DEBUG*/xASSERT_RET(NULL != _m_hDll, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxDll::bIsProcExists(
    const std::tstring_t &csProcName
) const
{
    /*DEBUG*/xASSERT_RET(NULL != _m_hDll, false);

#if   xOS_ENV_WIN
    proc_address_t fpRes = ::GetProcAddress(_m_hDll, xTS2S(csProcName).c_str());
    xCHECK_RET(NULL == fpRes, false);
#elif xOS_ENV_UNIX
    const char *pszError = NULL;

    pszError = ::dlerror();
    /*DEBUG*/xASSERT_RET(NULL == pszError, false);

    (void)::dlsym(_m_hDll, csProcName.c_str());

    pszError = ::dlerror();
    xCHECK_RET(NULL != pszError, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
CxDll::proc_address_t
CxDll::fpGetProcAddress(
    const std::tstring_t &csProcName
) const
{
    /*DEBUG*/xASSERT_RET(NULL != _m_hDll, NULL);

    proc_address_t fpRes = NULL;

#if   xOS_ENV_WIN
    fpRes = ::GetProcAddress(_m_hDll, xTS2S(csProcName).c_str());
    /*DEBUG*/xASSERT_RET(NULL != fpRes, NULL);
#elif xOS_ENV_UNIX
    const char *pszError = NULL;

    pszError = ::dlerror();
    /*DEBUG*/xASSERT_RET(NULL == pszError, NULL);

    fpRes = ::dlsym(_m_hDll, csProcName.c_str());
    xDEBUG_VAR_NA(fpRes)

    pszError = ::dlerror();
    /*DEBUG*/xASSERT_RET(NULL == pszError, NULL);
#endif

    return fpRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxDll::_bFree() {
    xDEBUG_VARS_NA;

    xCHECK_RET(false == bIsLoaded(), true);

#if   xOS_ENV_WIN
    BOOL blRes = ::FreeLibrary(_m_hDll);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    int iRv = ::dlclose(_m_hDll);
    /*DEBUG*/xASSERT_RET(0 == iRv, false);
#endif

    _m_hDll = NULL;

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
