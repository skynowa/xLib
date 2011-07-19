/****************************************************************************
* Class name:  CxDll
* Description: dynamic linking loader
* File name:   CxDll.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.11.2009 23:39:28
*
*****************************************************************************/


#include <xLib/Filesystem/CxDll.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxDll
CxDll::CxDll() :
    _m_bRes(FALSE),
    _m_hDLL(NULL)
{
}
//---------------------------------------------------------------------------
//DONE: ~CxDll
/*virtual*/
CxDll::~CxDll() {
    _m_bRes = bFree();
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: bIsLoaded (is loading)
BOOL
CxDll::bIsLoaded() {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( NULL != _m_hDLL );
}
//---------------------------------------------------------------------------
//DONE: bLoad (loading)
BOOL
CxDll::bLoad(
    const tString &csDllPath
)
{
    /*DEBUG*/// n/a
    /*DEBUG*/xASSERT_RET(false == csDllPath.empty(), FALSE);

    _m_bRes = bFree();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

#if defined(xOS_WIN)
    _m_hDLL = ::LoadLibrary(csDllPath.c_str());
    /*DEBUG*/xASSERT_RET(NULL != _m_hDLL, FALSE);
#elif defined(xOS_LINUX)
    _m_hDLL = dlopen(csDllPath.c_str(), RTLD_LAZY);
    /*DEBUG*/xASSERT_RET(NULL != _m_hDLL, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: fpGetProcAddress (get address of an exported function or variable )
VOID * /*FARPROC*/
CxDll::fpGetProcAddress(
    const tString &csProcName
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_hDLL, NULL);

    VOID *fpRes = NULL;

#if defined(xOS_WIN)
    fpRes = (VOID *)( ::GetProcAddress(_m_hDLL, xTS2S(csProcName).c_str()) );
    /*DEBUG*/xASSERT_RET(NULL != fpRes, NULL);
#elif defined(xOS_LINUX)
    const CHAR *pszError = NULL;

    pszError = dlerror();
    /*DEBUG*/xASSERT_RET(NULL == pszError, NULL);

    fpRes = dlsym(_m_hDLL, csProcName.c_str());

    pszError = dlerror();
    /*DEBUG*/xASSERT_RET(NULL == pszError, NULL);
#endif

    return fpRes;
}
//---------------------------------------------------------------------------
//DONE: bFree (free)
BOOL
CxDll::bFree() {
    /*DEBUG*/// n/a

    xCHECK_RET(FALSE == bIsLoaded(), TRUE);

#if defined(xOS_WIN)
    _m_bRes = ::FreeLibrary(_m_hDLL);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
#elif defined(xOS_LINUX)
    INT iRes = dlclose(_m_hDLL);
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);
#endif

    _m_hDLL = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------
