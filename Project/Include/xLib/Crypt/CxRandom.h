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
    explicit              CxRandom(clong_t &seed = std::time(NULL));
        ///< constructor
    virtual              ~CxRandom() {}
        ///< destructor

    void_t                setSeed(clong_t &seed);
        ///< set seed
    int_t                 nextInt() xWARN_UNUSED_RV;
        ///< _next int_t
    int_t                 nextInt(cint_t &max) xWARN_UNUSED_RV;
        ///< _next int_t
    int_t                 nextInt(cint_t &a, cint_t &b) xWARN_UNUSED_RV;
        ///< _next int_t
    long_t                nextLong() xWARN_UNUSED_RV;
        ///< _next long_t
    bool_t                nextBool() xWARN_UNUSED_RV;
        ///< _next boolean
    float_t               nextFloat() xWARN_UNUSED_RV;
        ///< _next float_t
    double                nextDouble() xWARN_UNUSED_RV;
        ///< _next double
    char                  nextChar() xWARN_UNUSED_RV;
        ///< _next char
    char                  nextFigure() xWARN_UNUSED_RV;
        ///< _next figure
    double                nextGaussian() xWARN_UNUSED_RV;
        ///< _next gaussian

    static void_t         setSeed();
        ///< set seed
    static long_t         nextIntEx(clong_t &min, clong_t &max) xWARN_UNUSED_RV;
        ///< generates a random number between specified min/max boundaries
    static std::tstring_t nextString(std::csize_t &size) xWARN_UNUSED_RV;
        ///< get random string

protected:
    long_t                _next() xWARN_UNUSED_RV;
        ///< _next long_t

private:
    static cint_t         A = 48271;
    static cint_t         M = RAND_MAX;
    static cint_t         Q = M / A;
    static cint_t         R = M % A;

    long_t                _seed;                    ///< for private use
    double                _nextNextGaussian;        ///< for private use
    bool_t                _isHaveNextNextGaussian;  ///< for private use

xNO_COPY_ASSIGN(CxRandom)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxRandom.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxRandomH
