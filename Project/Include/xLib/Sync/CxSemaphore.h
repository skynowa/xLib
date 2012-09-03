/**
 * \file   CxSemaphore.h
 * \brief  semaphore (user space)
 */


#ifndef xLib_CxSemaphoreH
#define xLib_CxSemaphoreH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxSemaphore :
    public CxNonCopyable
{
    public:
                 CxSemaphore();
            ///< constructor
        virtual ~CxSemaphore();
            ///< destructor

    private:

};
//---------------------------------------------------------------------------
#endif //xLib_CxSemaphoreH
