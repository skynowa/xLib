/**
 * \file   CxSemaphore.h
 * \brief  semaphore (user space)
 */


#ifndef xLib_CxSemaphoreH
#define xLib_CxSemaphoreH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSemaphore :
    public CxNonCopyable
    /// semaphore
{
public:
             CxSemaphore();
        ///< constructor
    virtual ~CxSemaphore();
        ///< destructor

private:

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_CxSemaphoreH
