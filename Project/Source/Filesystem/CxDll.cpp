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

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxDll::CxDll() :
    _m_hDll(NULL)
{
}
//------------------------------------------------------------------------------
/* virtual */
CxDll::~CxDll() {
    _destruct();
}
//------------------------------------------------------------------------------
bool_t
CxDll::isLoaded() const {
    xTESTS_NA;

    return (NULL != _m_hDll);
}
//------------------------------------------------------------------------------
void_t
CxDll::load(
    std::ctstring_t &csDllPath
)
{
    xTESTS_NA;
    xTEST_EQ(false, csDllPath.empty());

    _destruct();

#if   xOS_ENV_WIN
    _m_hDll = ::LoadLibrary(csDllPath.c_str());
    xTEST_PTR(_m_hDll);
#elif xOS_ENV_UNIX
    _m_hDll = ::dlopen(csDllPath.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    xTEST_PTR(_m_hDll);
#endif
}
//------------------------------------------------------------------------------
bool_t
CxDll::isProcExists(
    std::ctstring_t &csProcName
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

    (void_t)::dlsym(_m_hDll, csProcName.c_str());

    pszError = ::dlerror();
    xCHECK_RET(NULL != pszError, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
CxDll::proc_address_t
CxDll::procAddress(
    std::ctstring_t &csProcName
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
    xTEST_NA(fpRes)

    pszError = ::dlerror();
    xTEST_PTR_FAIL(pszError);
#endif

    return fpRes;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
CxDll::_destruct() {
    xTESTS_NA;

    xCHECK_DO(false == isLoaded(), return);

#if   xOS_ENV_WIN
    BOOL blRes = ::FreeLibrary(_m_hDll);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int_t iRv = ::dlclose(_m_hDll);
    xTEST_EQ(0, iRv);
#endif

    _m_hDll = NULL;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
