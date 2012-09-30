/**
 * \file  CxAutoMutex.h
 * \brief auto critical section (using between threads)
 */


#include <xLib/Sync/CxAutoMutex.h>

#include <xLib/Sync/CxMutex.h>
#include <xLib/Sync/CxIpcMutex.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxAutoMutex::CxAutoMutex(
    CxMutex    &a_mtMutex,
    const bool &a_cbIsUseTry /* = false */
) :
    _m_mtMutex  (a_mtMutex),
    _m_bIsLocked(false)
{
    bool bRv = false;

    bRv = _m_mtMutex.bCreate();
    /*DEBUG*/xTEST_EQ(true, bRv);

    if (false == a_cbIsUseTry) {
        bRv = _m_mtMutex.bLock();
        /*DEBUG*/xTEST_EQ(true, bRv);
    } else {
        bRv = _m_mtMutex.bTryLock();
        /*DEBUG*/// n/a
    }

    _m_bIsLocked = bRv;
}
//---------------------------------------------------------------------------
CxAutoMutex::~CxAutoMutex() {
    if (false != _m_bIsLocked) {
        bool bRv = _m_mtMutex.bUnlock();
        /*DEBUG*/xTEST_EQ(true, bRv);
    }

    _m_bIsLocked = false;
}
//---------------------------------------------------------------------------
bool
CxAutoMutex::bIsLocked() const {
    return _m_bIsLocked;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
