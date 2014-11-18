/**
 * \file  Random.h
 * \brief random generator
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, crypt)

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

    static
    long_t         valueMax();
        ///< maximum possible value

protected:
    uint_t         _seed; ///< current seed

private:
    uint_t         _seedTimeBased() const;
        ///< get time based seed

    xNO_COPY_ASSIGN(IxSeedPolicy)
};
//-------------------------------------------------------------------------------------------------
class StdSeedPolicy :
    IxSeedPolicy
    /// std seed policy
{
public:
                   StdSeedPolicy();
        ///< constructor
    virtual       ~StdSeedPolicy();
        ///< destructor

    virtual long_t next();
        ///< get integer in the range between 0 and RAND_MAX

xPLATFORM_IMPL:
    void_t         _construct_impl();
    long_t         _next_impl();
};
//-------------------------------------------------------------------------------------------------
class NativeSeedPolicy :
    IxSeedPolicy
    /// native seed policy
{
public:
                   NativeSeedPolicy();
        ///< constructor
    virtual       ~NativeSeedPolicy();
        ///< destructor

    virtual long_t next();
        ///< get long integer in the range between 0 and RAND_MAX

private:
#if   xENV_WIN
    HCRYPTPROV     _hProv;  ///< CSP handle
#elif xENV_UNIX
    #if (xHAVE_SRANDOM_R && xHAVE_RANDOM_R)
        random_data _data;   ///< data for ::srandom_r()
    #endif
#endif

xPLATFORM_IMPL:
    void_t         _construct_impl();
    void_t         _destruct_impl();
    long_t         _next_impl();
};
//-------------------------------------------------------------------------------------------------
template <class RandomValue, class SeedPolicy>
class Random
    /// random
{
public:
               Random();
        ///< constructor
    virtual   ~Random() {}
        ///< destructor

    bool_t     nextBool();
        ///< get bool_t value
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

    xNO_COPY_ASSIGN(Random)
};

typedef Random<int_t,  StdSeedPolicy>    StdRandom;
typedef Random<long_t, NativeSeedPolicy> NativeRandom;

xNAMESPACE_END2(xlib, crypt)
//-------------------------------------------------------------------------------------------------
#include "Random.inl"

#if xOPTION_PROJECT_HEADER_ONLY
    #include "Random.cpp"
#endif
