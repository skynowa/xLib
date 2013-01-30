/**
 * \file  CxAutoMutex.h
 * \brief auto critical section (using between threads)
 */


#ifndef xLib_Sync_CxAutoMutexH
#define xLib_Sync_CxAutoMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMutex;

class CxAutoMutex :
    private CxNonCopyable
    /// auto critical section
{
public:
    explicit CxAutoMutex(CxMutex *mtMutex);
        ///< constructor
    virtual ~CxAutoMutex();
        ///< destructor

private:
    CxMutex *_m_mtMutex;    ///< mutex
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Sync_CxAutoMutexH
