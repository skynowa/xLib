/**
 * \file   CxNonHeap.h
 * \brief  non heapable class
 */


#ifndef xLib_Common_CxNonHeapH
#define xLib_Common_CxNonHeapH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxNonHeap
    /// non heapable class
{
public:
             CxNonHeap       () { ; }
        ///< constructor
    virtual ~CxNonHeap       () { ; }
        ///< destructor

protected:
    void_t * operator new    (size_t) throw() { return NULL; }
        ///< operator new
    void_t   operator delete (void_t *) { ; }
        ///< operator delete
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Common_CxNonHeapH
