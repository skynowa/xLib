/**
 * \file  CxAutoIpcMutex.cpp
 * \brief auto mutex
 */


#include <xLib/Sync/CxAutoIpcMutex.h>

#include <xLib/Sync/CxIpcMutex.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxAutoIpcMutex::CxAutoIpcMutex(
    CxIpcMutex           &a_mtMutex,
    const std::tstring_t &a_csName
) :
    _m_mtMutex(a_mtMutex)
{
    bool bRv = _m_mtMutex.bCreate(a_csName);
    /*DEBUG*/xASSERT_DO(true == bRv, return);

    bRv = _m_mtMutex.bLock(xTIMEOUT_INFINITE);
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------
CxAutoIpcMutex::~CxAutoIpcMutex() {
    bool bRv = _m_mtMutex.bUnlock();
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
