/****************************************************************************
* Class name:  CxMutexScopeLock
* Description: мъютекс в блоке
* File name:   CxAutoMutex.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     16.12.2009 10:06:46
*
*****************************************************************************/


#include <xLib/Sync/CxAutoMutex.h>


/****************************************************************************
*    public                                                           
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxAutoMutex ()
CxAutoMutex::CxAutoMutex(CxMutex &mtMutex) : 
    _m_mtMutex(mtMutex) 
{
    BOOL bRes = FALSE;

    bRes = _m_mtMutex.bWait(INFINITE);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//TODO: ~CxAutoMutex ()
CxAutoMutex::~CxAutoMutex() {
    BOOL bRes = FALSE;

    bRes = _m_mtMutex.bRelease();
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------