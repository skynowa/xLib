/**
 * \file  CxAutoMutex.h
 * \brief auto critical section (using between threads)
 */


#include <xLib/Sync/CxMutex.h>


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxAutoMutex::CxAutoMutex(
    CxMutex *a_mutex
) :
    _mutex(a_mutex)
{
    _mutex->create();
    _mutex->lock();
}
//-------------------------------------------------------------------------------------------------
inline
CxAutoMutex::~CxAutoMutex()
{
    _mutex->unlock();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
