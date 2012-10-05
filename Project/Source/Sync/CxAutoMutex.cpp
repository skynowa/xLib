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
    _m_mtMutex.vCreate();

    if (false == a_cbIsUseTry) {
        _m_mtMutex.vLock();

        _m_bIsLocked = true;
    } else {
        bool bRv = _m_mtMutex.bTryLock();
        /*DEBUG*/// n/a

        _m_bIsLocked = bRv;
    }
}
//---------------------------------------------------------------------------
CxAutoMutex::~CxAutoMutex() {
    if (false != _m_bIsLocked) {
        _m_mtMutex.vUnlock();
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
