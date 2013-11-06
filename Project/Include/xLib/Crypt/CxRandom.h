/**
 * \file  CxRandom.h
 * \brief random
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxRandom :
    private CxNonCopyable
    /// random
{
public:
    explicit              CxRandom(clong_t &seed = std::time(NULL));
        ///< constructor
    virtual              ~CxRandom();
        ///< destructor

    void_t                vSetSeed(clong_t &seed);
        ///< set seed
    int_t                 iNextInt() xWARN_UNUSED_RV;
        ///< next int_t
    int_t                 iNextInt(cint_t &max) xWARN_UNUSED_RV;
        ///< next int_t
    int_t                 iNextInt(cint_t &a, cint_t &b) xWARN_UNUSED_RV;
        ///< next int_t
    long_t                liNextLong() xWARN_UNUSED_RV;
        ///< next long_t
    bool_t                bNextBoolean() xWARN_UNUSED_RV;
        ///< next boolean
    float_t               fNextFloat() xWARN_UNUSED_RV;
        ///< next float_t
    double                bNextDouble() xWARN_UNUSED_RV;
        ///< next double
    char                  chNextChar() xWARN_UNUSED_RV;
        ///< next char
    char                  chNextFigure() xWARN_UNUSED_RV;
        ///< next figure
    double                dNextGaussian() xWARN_UNUSED_RV;
        ///< next gaussian

    static void_t         vSetSeed();
        ///< set seed
    static long_t         liInt(clong_t &min, clong_t &max) xWARN_UNUSED_RV;
        ///< generates a random number between specified min/max boundaries
    static long_t         liIntEx(clong_t &min, clong_t &max) xWARN_UNUSED_RV;
        ///< generates a random number between specified min/max boundaries using a vector
        ///< to shuffle
    static std::tstring_t sString(std::csize_t &size) xWARN_UNUSED_RV;
        ///< get random string

protected:
    long_t                liNext() xWARN_UNUSED_RV;
        ///< next long_t

private:
    static cint_t         A = 48271;
    static cint_t         M = RAND_MAX;
    static cint_t         Q = M / A;
    static cint_t         R = M % A;

    long_t                _seed;                  ///< for private use
    double                _nextNextGaussian;       ///< for private use
    bool_t                _isHaveNextNextGaussian;   ///< for private use
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Crypt/CxRandom.cpp>
#endif
