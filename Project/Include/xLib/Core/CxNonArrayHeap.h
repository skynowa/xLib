/**
 * \file   CxNonArrayHeap.h
 * \brief  non heapable class for arrays
 */


#pragma once

#ifndef xLib_CxNonArrayHeapH
#define xLib_CxNonArrayHeapH
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxNonArrayHeap
    /// non heapable class for arrays
{
public:
             CxNonArrayHeap() { ; }
        ///< constructor
    virtual ~CxNonArrayHeap() { ; }
        ///< destructor

protected:
    void_t * operator new [](size_t) throw() { return NULL; }
        ///< operator new []
    void_t   operator delete [](void_t *) { ; }
        ///< operator delete []
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxNonArrayHeapH
