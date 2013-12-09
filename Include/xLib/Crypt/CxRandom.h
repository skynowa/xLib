/**
 * \file  CxRandom.h
 * \brief random
 */


#pragma once

#ifndef xLib_CxRandomH
#define xLib_CxRandomH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxRandom
    /// random
{
public:
             CxRandom();
        ///< constructor
    virtual ~CxRandom() {}
        ///< destructor

    void     setSeed();
        ///< set default seed
    void     setSeed(cuint_t &seed);
        ///< set non-default seed
    template <class T>
    T        next(const T &min, const T &max);
        ///< get integer in the range between 0 and RAND_MAX

private:
    uint_t   _seed; ///< current seed

    uint_t   _seedTimeBased() const;
        ///< get time based seed
    int_t    _nextInt();
        ///< get integer in the range between 0 and RAND_MAX

    xNO_COPY_ASSIGN(CxRandom)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxRandom.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxRandomH
