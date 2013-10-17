/**
 * \file  CxAutoMutex.h
 * \brief auto critical section (using between threads)
 */


#include <xLib/Sync/CxAutoMutex.h>

#include <xLib/Sync/CxMutex.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxAutoMutex::CxAutoMutex(
    CxMutex *a_mutex
) :
    _mutex(a_mutex)
{
    _mutex->create();
    _mutex->lock();
}
//------------------------------------------------------------------------------
CxAutoMutex::~CxAutoMutex()
{
    _mutex->unlock();
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
