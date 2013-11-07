/**
 * \file  CxAutoIpcMutex.cpp
 * \brief auto mutex
 */


#include <xLib/Sync/CxAutoIpcMutex.h>

#include <xLib/Sync/CxIpcMutex.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE_HO
CxAutoIpcMutex::CxAutoIpcMutex(
    CxIpcMutex      &a_mutex,
    std::ctstring_t &a_name
) :
    _mutex(a_mutex)
{
    _mutex.create(a_name);
    _mutex.lock(xTIMEOUT_INFINITE);
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO
CxAutoIpcMutex::~CxAutoIpcMutex()
{
    _mutex.unlock();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
