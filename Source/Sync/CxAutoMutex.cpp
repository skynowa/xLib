/**
 * \file  CxAutoMutex.cpp
 * \brief auto mutex
 */


#include <xLib/Sync/CxAutoMutex.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxAutoMutex::CxAutoMutex(
    CxMutex &mtMutex
) :
    _m_mtMutex(mtMutex)
{
    bool bRes = _m_mtMutex.bCreate(xT(""));
    /*DEBUG*/xASSERT_DO(true == bRes, return);

    bRes = _m_mtMutex.bLock(xTIMEOUT_INFINITE);
    /*DEBUG*/xASSERT_DO(true == bRes, return);
}
//---------------------------------------------------------------------------
CxAutoMutex::~CxAutoMutex() {
    bool bRes = _m_mtMutex.bUnlock();
    /*DEBUG*/xASSERT_DO(true == bRes, return);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
