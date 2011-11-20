/**
 * \file  CxAutoMutex.cpp
 * \brief auto mutex
 */


#include <xLib/Sync/CxAutoMutex.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

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
    bool bRes = false;

    bRes = _m_mtMutex.bCreate(NULL, false, xT(""));
    /*DEBUG*/xASSERT_DO(false != bRes, return);

    bRes = _m_mtMutex.bWait(INFINITE);
    /*DEBUG*/xASSERT_DO(false != bRes, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxAutoMutex ()
CxAutoMutex::~CxAutoMutex() {
    bool bRes = false;

    bRes = _m_mtMutex.bRelease();
    /*DEBUG*/xASSERT_DO(false != bRes, return);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
