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
    CxIpcMutex              &mtMutex,
    const std::tstring_t &csName
) :
    _m_mtMutex(mtMutex)
{
    bool bRv = _m_mtMutex.bCreate(csName);
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
