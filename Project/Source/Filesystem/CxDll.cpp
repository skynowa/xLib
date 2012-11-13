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
    _vFree();
}
//---------------------------------------------------------------------------
bool
CxDll::bIsLoaded() const {
    xDEBUG_VARS_NA;

    return (NULL != _m_hDll);
}
//---------------------------------------------------------------------------
void
CxDll::vLoad(
    const std::tstring_t &csDllPath
)
{
    xDEBUG_VARS_NA;
    xTEST_EQ(false, csDllPath.empty());

    _vFree();

#if   xOS_ENV_WIN
    _m_hDll = ::LoadLibrary(csDllPath.c_str());
    xTEST_PTR(_m_hDll);
#elif xOS_ENV_UNIX
    _m_hDll = ::dlopen(csDllPath.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    xTEST_PTR(_m_hDll);
#endif
}
//---------------------------------------------------------------------------
bool
CxDll::bIsProcExists(
    const std::tstring_t &csProcName
) const
{
    xTEST_PTR(_m_hDll);

#if   xOS_ENV_WIN
    proc_address_t fpRes = ::GetProcAddress(_m_hDll, xTS2S(csProcName).c_str());
    xCHECK_RET(NULL == fpRes, false);
#elif xOS_ENV_UNIX
    const char *pszError = NULL;

    pszError = ::dlerror();
    xTEST_PTR_FAIL(pszError);

    (void)::dlsym(_m_hDll, csProcName.c_str());

    pszError = ::dlerror();
    xCHECK_RET(NULL != pszError, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
CxDll::proc_address_t
CxDll::fpProcAddress(
    const std::tstring_t &csProcName
) const
{
    xTEST_PTR(_m_hDll);

    proc_address_t fpRes = NULL;

#if   xOS_ENV_WIN
    fpRes = ::GetProcAddress(_m_hDll, xTS2S(csProcName).c_str());
    xTEST_PTR(fpRes);
#elif xOS_ENV_UNIX
    const char *pszError = NULL;

    pszError = ::dlerror();
    xTEST_PTR_FAIL(pszError);

    fpRes = ::dlsym(_m_hDll, csProcName.c_str());
    xDEBUG_VAR_NA(fpRes)

    pszError = ::dlerror();
    xTEST_PTR_FAIL(pszError);
#endif

    return fpRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxDll::_vFree() {
    xDEBUG_VARS_NA;

    xCHECK_DO(false == bIsLoaded(), return);

#if   xOS_ENV_WIN
    BOOL blRes = ::FreeLibrary(_m_hDll);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::dlclose(_m_hDll);
    xTEST_EQ(0, iRv);
#endif

    _m_hDll = NULL;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
