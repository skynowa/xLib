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
    /*DEBUG*/xTEST_EQ(true, bRv);

    bRv = _m_mtMutex.bLock(xTIMEOUT_INFINITE);
    /*DEBUG*/xTEST_EQ(true, bRv);
}
//---------------------------------------------------------------------------
CxAutoIpcMutex::~CxAutoIpcMutex() {
    bool bRv = _m_mtMutex.bUnlock();
    /*DEBUG*/xTEST_EQ(true, bRv);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
