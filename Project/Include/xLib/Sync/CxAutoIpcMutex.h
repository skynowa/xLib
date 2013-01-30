/**
 * \file  CxAutoIpcMutex.h
 * \brief auto mutex
 */


#ifndef xLib_Sync_CxAutoIpcMutexH
#define xLib_Sync_CxAutoIpcMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxIpcMutex;

class CxAutoIpcMutex :
    private CxNonCopyable
    /// auto mutex
{
public:
                CxAutoIpcMutex(CxIpcMutex &mtMutex, const std::tstring_t &csName);
    virtual    ~CxAutoIpcMutex();

private:
    CxIpcMutex &_m_mtMutex;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Sync_CxAutoIpcMutexH
