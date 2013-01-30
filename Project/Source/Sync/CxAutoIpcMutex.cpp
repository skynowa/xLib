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
    _m_mtMutex.create(a_csName);
    _m_mtMutex.vLock(xTIMEOUT_INFINITE);
}
//---------------------------------------------------------------------------
CxAutoIpcMutex::~CxAutoIpcMutex() {
    _m_mtMutex.vUnlock();
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
