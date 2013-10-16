/**
 * \file  CxDll.cpp
 * \brief dynamic linking loader
 */


#include <xLib/Filesystem/CxDll.h>

#if xOS_ENV_WIN
    // lib: n/a
#else
    // lib: -ldl, -lc (FreeBSD)
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxDll::CxDll() :
    _dll(NULL)
{
}
//------------------------------------------------------------------------------
/* virtual */
CxDll::~CxDll()
{
    _destruct();
}
//------------------------------------------------------------------------------
bool_t
CxDll::isLoaded() const
{
    xTESTS_NA;

    return (NULL != _dll);
}
//------------------------------------------------------------------------------
void_t
CxDll::load(
    std::ctstring_t &a_dllPath
)
{
    xTESTS_NA;
    xTEST_EQ(false, a_dllPath.empty());

    _destruct();

#if xOS_ENV_WIN
    _dll = ::LoadLibrary(dllPath.c_str());
    xTEST_PTR(_dll);
#else
    _dll = ::dlopen(a_dllPath.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    xTEST_PTR(_dll);
#endif
}
//------------------------------------------------------------------------------
bool_t
CxDll::isProcExists(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_dll);

#if xOS_ENV_WIN
    proc_address_t fpRes = ::GetProcAddress(_dll, xTS2S(a_procName).c_str());
    xCHECK_RET(NULL == fpRes, false);
#else
    const char *pszError = NULL;

    pszError = ::dlerror();
    xTEST_PTR_FAIL(pszError);

    (void_t)::dlsym(_dll, a_procName.c_str());

    pszError = ::dlerror();
    xCHECK_RET(NULL != pszError, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
CxDll::proc_address_t
CxDll::procAddress(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_dll);

    proc_address_t fpRes = NULL;

#if xOS_ENV_WIN
    fpRes = ::GetProcAddress(_dll, xTS2S(a_procName).c_str());
    xTEST_PTR(fpRes);
#else
    const char *pszError = NULL;

    pszError = ::dlerror();
    xTEST_PTR_FAIL(pszError);

    fpRes = ::dlsym(_dll, a_procName.c_str());
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
CxDll::_destruct()
{
    xTESTS_NA;

    xCHECK_DO(!isLoaded(), return);

#if   xOS_ENV_WIN
    BOOL blRes = ::FreeLibrary(_dll);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int_t iRv = ::dlclose(_dll);
    xTEST_EQ(0, iRv);
#endif

    _dll = NULL;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
