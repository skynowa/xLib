/**
 * \file  CxAutoMutex.h
 * \brief auto critical section (using between threads)
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
    CxMutex *a_mtMutex
) :
    _m_mtMutex(a_mtMutex)
{
    _m_mtMutex->create();
    _m_mtMutex->vLock();
}
//---------------------------------------------------------------------------
CxAutoMutex::~CxAutoMutex() {
    _m_mtMutex->vUnlock();
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
