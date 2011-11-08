/**
 * \file  CxDll.cpp
 * \brief dynamic linking loader
 */


#include <xLib/Filesystem/CxDll.h>


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
BOOL
CxDll::bIsLoaded() const {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( NULL != _m_hDLL );
}
//---------------------------------------------------------------------------
BOOL
CxDll::bLoad(
    const std::string_t &csDllPath
)
{
    /*DEBUG*/// n/a
    /*DEBUG*/xASSERT_RET(false == csDllPath.empty(), FALSE);

    BOOL bRes = bFree();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

#if defined(xOS_ENV_WIN)
    _m_hDLL = ::LoadLibrary(csDllPath.c_str());
    /*DEBUG*/xASSERT_RET(NULL != _m_hDLL, FALSE);
#elif defined(xOS_ENV_UNIX)
    _m_hDLL = dlopen(csDllPath.c_str(), RTLD_LAZY);
    /*DEBUG*/xASSERT_RET(NULL != _m_hDLL, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
CxDll::TxProcAddress
CxDll::fpGetProcAddress(
    const std::string_t &csProcName
) const
{
    /*DEBUG*/xASSERT_RET(NULL != _m_hDLL, NULL);

    TxProcAddress fpRes = NULL;

#if defined(xOS_ENV_WIN)
    fpRes = (TxProcAddress)( ::GetProcAddress(_m_hDLL, xTS2S(csProcName).c_str()) );
    /*DEBUG*/xASSERT_RET(NULL != fpRes, NULL);
#elif defined(xOS_ENV_UNIX)
    const char *pszError = NULL;

    pszError = dlerror();
    /*DEBUG*/xASSERT_RET(NULL == pszError, NULL);

    fpRes = dlsym(_m_hDLL, csProcName.c_str());

    pszError = dlerror();
    /*DEBUG*/xASSERT_RET(NULL == pszError, NULL);
#endif

    return fpRes;
}
//---------------------------------------------------------------------------
BOOL
CxDll::bFree() {
    /*DEBUG*/// n/a

    xCHECK_RET(FALSE == bIsLoaded(), TRUE);

#if defined(xOS_ENV_WIN)
    BOOL bRes = ::FreeLibrary(_m_hDLL);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    int iRes = dlclose(_m_hDLL);
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);
#endif

    _m_hDLL = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------
