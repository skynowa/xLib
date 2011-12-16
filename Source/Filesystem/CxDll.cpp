/**
 * \file  CxDll.cpp
 * \brief dynamic linking loader
 */


#include <xLib/Filesystem/CxDll.h>

#if defined(xOS_ENV_WIN)
    //lib: n/a
#elif defined(xOS_ENV_UNIX)
    //lib: -ldl, -lc (FreeBSD)
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxDll::CxDll() :
    _m_hDLL(NULL)
{
}
//---------------------------------------------------------------------------
/*virtual*/
CxDll::~CxDll() {
    (void)bFree();
}
//---------------------------------------------------------------------------
bool
CxDll::bIsLoaded() const {
    /*DEBUG*/// n/a

    return (NULL != _m_hDLL);
}
//---------------------------------------------------------------------------
bool
CxDll::bLoad(
    const std::tstring_t &csDllPath
)
{
    /*DEBUG*/// n/a
    /*DEBUG*/xASSERT_RET(false == csDllPath.empty(), false);

    bool bRes = bFree();
    /*DEBUG*/xASSERT_RET(true == bRes, false);

#if xOS_ENV_WIN
    _m_hDLL = ::LoadLibrary(csDllPath.c_str());
    /*DEBUG*/xASSERT_RET(NULL != _m_hDLL, false);
#elif xOS_ENV_UNIX
    _m_hDLL = ::dlopen(csDllPath.c_str(), RTLD_LAZY);
    /*DEBUG*/xASSERT_RET(NULL != _m_hDLL, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool 
CxDll::bIsProcExists(
    const std::tstring_t &csProcName
) const
{
    /*DEBUG*/xASSERT_RET(NULL != _m_hDLL, NULL);

    bool          bRes  = false;
    TxProcAddress fpRes = NULL;

#if xOS_ENV_WIN
    fpRes = ::GetProcAddress(_m_hDLL, xTS2S(csProcName).c_str());
    xCHECK_RET(NULL == fpRes, false);
#elif xOS_ENV_UNIX
    const char *pszError = NULL;

    pszError = ::dlerror();
    /*DEBUG*/xASSERT_RET(NULL == pszError, NULL);

    fpRes = ::dlsym(_m_hDLL, csProcName.c_str());
    /*DEBUG*/// n/a

    pszError = ::dlerror();
    xCHECK_RET(NULL != pszError, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
CxDll::TxProcAddress
CxDll::fpGetProcAddress(
    const std::tstring_t &csProcName
) const
{
    /*DEBUG*/xASSERT_RET(NULL != _m_hDLL, NULL);

    TxProcAddress fpRes = NULL;

#if xOS_ENV_WIN
    fpRes = ::GetProcAddress(_m_hDLL, xTS2S(csProcName).c_str());
    /*DEBUG*/xASSERT_RET(NULL != fpRes, NULL);
#elif xOS_ENV_UNIX
    const char *pszError = NULL;

    pszError = ::dlerror();
    /*DEBUG*/xASSERT_RET(NULL == pszError, NULL);

    fpRes = ::dlsym(_m_hDLL, csProcName.c_str());
    /*DEBUG*/// n/a

    pszError = ::dlerror();
    /*DEBUG*/xASSERT_RET(NULL == pszError, NULL);
#endif

    return fpRes;
}
//---------------------------------------------------------------------------
bool
CxDll::bFree() {
    /*DEBUG*/// n/a

    xCHECK_RET(false == bIsLoaded(), true);

#if xOS_ENV_WIN
    BOOL blRes = ::FreeLibrary(_m_hDLL);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::dlclose(_m_hDLL);
    /*DEBUG*/xASSERT_RET(0 == iRes, false);
#endif

    _m_hDLL = NULL;

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
