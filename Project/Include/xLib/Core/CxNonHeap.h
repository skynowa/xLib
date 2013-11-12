/**
 * \file   CxNonHeap.h
 * \brief  non heapable class
 */


#pragma once

#ifndef xLib_CxNonHeapH
#define xLib_CxNonHeapH
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxNonHeap
    /// non heapable class
{
public:
             CxNonHeap() { ; }
        ///< constructor
    virtual ~CxNonHeap() { ; }
        ///< destructor

protected:
    void_t * operator new(size_t) throw() { return NULL; }
        ///< operator new
    void_t   operator delete(void_t *) { ; }
        ///< operator delete
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxNonHeapH
