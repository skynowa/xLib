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
xNAMESPACE2_BEGIN(xlib, crypt)

class xNO_VTABLE IxSeedPolicy
    /// seed policy interface
{
public:
                   IxSeedPolicy();
        ///< constructor
    virtual       ~IxSeedPolicy() {};
        ///< destructor

    virtual long_t next() = 0;
        ///< next value

protected:
    uint_t         _seed; ///< current seed

private:
    uint_t         _seedTimeBased() const;
        ///< get time based seed

    xNO_COPY_ASSIGN(IxSeedPolicy)
};
//-------------------------------------------------------------------------------------------------
class CxStdSeedPolicy :
    IxSeedPolicy
    /// std seed policy
{
public:
                   CxStdSeedPolicy();
        ///< constructor
    virtual       ~CxStdSeedPolicy();
        ///< destructor

    virtual long_t next();
        ///< get integer in the range between 0 and RAND_MAX
};
//-------------------------------------------------------------------------------------------------
class CxNativeSeedPolicy :
    IxSeedPolicy
    /// native seed policy
{
public:
                   CxNativeSeedPolicy();
        ///< constructor
    virtual       ~CxNativeSeedPolicy();
        ///< destructor

    virtual long_t next();
        ///< get long integer in the range between 0 and RAND_MAX

private:
#if   xOS_ENV_WIN
    HCRYPTPROV     _hProv;  ///< CSP handle
#elif xOS_ENV_UNIX
    random_data    _data;   ///< data for ::srandom_r()
#endif
};
//-------------------------------------------------------------------------------------------------
template <class RandomValue, class SeedPolicy>
class CxRandom
    /// random
{
public:
               CxRandom();
        ///< constructor
    virtual   ~CxRandom() {}
        ///< destructor

    bool_t     nextBool();
        ///< get bool value
    template <class T>
    T          nextChar();
        ///< get character value between min and max
    template <class T>
    T          nextInt(const T &min, const T &max);
        ///< get integer value between min and max
    template <class T>
    T          nextFloat(const T &min, const T &max);
       ///< get float value between min and max

private:
    const RandomValue _randMax;
    SeedPolicy _policy;

    xNO_COPY_ASSIGN(CxRandom)
};

typedef CxRandom<int_t,  CxStdSeedPolicy>    CxStdRandom;
typedef CxRandom<long_t, CxNativeSeedPolicy> CxNativeRandom;

xNAMESPACE2_END(xlib, crypt)
//-------------------------------------------------------------------------------------------------
#include "CxRandom.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxRandomH
