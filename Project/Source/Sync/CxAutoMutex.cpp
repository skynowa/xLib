/**
 * \file  CxAutoMutex.cpp
 * \brief auto mutex
 */


#include <xLib/Sync/CxAutoMutex.h>

#include <xLib/Sync/CxMutex.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxAutoMutex::CxAutoMutex(
    CxMutex              &mtMutex,
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
CxAutoMutex::~CxAutoMutex() {
    bool bRv = _m_mtMutex.bUnlock();
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
