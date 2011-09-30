/**
 * \file  CxAutoMutex.cpp
 * \brief auto mutex
 */


#include <xLib/Sync/CxAutoMutex.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxAutoMutex ()
CxAutoMutex::CxAutoMutex(
    CxMutex &mtMutex
) :
    _m_mtMutex(mtMutex)
{
    BOOL bRes = FALSE;

    bRes = _m_mtMutex.bCreate(NULL, FALSE, xT(""));
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);

    bRes = _m_mtMutex.bWait(INFINITE);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxAutoMutex ()
CxAutoMutex::~CxAutoMutex() {
    BOOL bRes = FALSE;

    bRes = _m_mtMutex.bRelease();
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
#elif defined(xOS_ENV_UNIX)

#endif
