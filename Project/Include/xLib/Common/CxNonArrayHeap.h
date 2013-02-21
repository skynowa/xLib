/**
 * \file   CxNonArrayHeap.h
 * \brief  non heapable class for arrays
 */


#ifndef xLib_Common_CxNonArrayHeapH
#define xLib_Common_CxNonArrayHeapH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxNonArrayHeap
    /// non heapable class for arrays
{
public:
             CxNonArrayHeap     () { ; }
        ///< constructor
    virtual ~CxNonArrayHeap     () { ; }
        ///< destructor

protected:
    void *   operator new []    (size_t) throw() { return NULL; }
        ///< operator new []
    void     operator delete [] (void *) { ; }
        ///< operator delete []
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Common_CxNonArrayHeapH
