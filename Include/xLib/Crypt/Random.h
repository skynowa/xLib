/**
 * \file  Random.h
 * \brief random generator
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, crypt)

class xNO_VTABLE ISeedPolicy
    /// seed policy interface
{
public:
                   ISeedPolicy();
        ///< constructor
    virtual       ~ISeedPolicy() {};
        ///< destructor

    virtual long_t next() = 0;
        ///< next value

    static
    long_t         valueMax();
        ///< maximum possible value

protected:
    uint_t _seed; ///< current seed

private:
    uint_t         _seedTimeBased() const;
        ///< get time based seed

    xNO_COPY_ASSIGN(ISeedPolicy)
};
//-------------------------------------------------------------------------------------------------
class StdSeedPolicy :
    ISeedPolicy
    /// std seed policy
{
public:
                   StdSeedPolicy();
        ///< constructor
    virtual       ~StdSeedPolicy();
        ///< destructor

    virtual long_t next() override;
        ///< get integer in the range between 0 and RAND_MAX

xPLATFORM_IMPL:
    void_t         _construct_impl();
    long_t         _next_impl();
};
//-------------------------------------------------------------------------------------------------
class NativeSeedPolicy :
    ISeedPolicy
    /// native seed policy
{
public:
                   NativeSeedPolicy();
        ///< constructor
    virtual       ~NativeSeedPolicy();
        ///< destructor

    virtual long_t next() override;
        ///< get long integer in the range between 0 and RAND_MAX

private:
#if   xENV_WIN
    HCRYPTPROV     _hProv;  ///< CSP handle
#elif xENV_UNIX
    #if (cmHAVE_SRANDOM_R && cmHAVE_RANDOM_R)
        random_data _data;   ///< data for ::srandom_r()
    #endif
#endif

xPLATFORM_IMPL:
    void_t         _construct_impl();
    void_t         _destruct_impl();
    long_t         _next_impl();
};
//-------------------------------------------------------------------------------------------------
template<typename RandomValueT, class SeedPolicyT>
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
    template<typename T>
    T          nextChar();
        ///< get character value between min and max
    template<typename T>
    T          nextInt(const T &min, const T &max);
        ///< get integer value between min and max
    template<typename T>
    T          nextFloat(const T &min, const T &max);
       ///< get float value between min and max

private:
    const RandomValueT _randMax;
    SeedPolicyT _policy;

    xNO_COPY_ASSIGN(Random)
};

using StdRandom    = Random<int_t,  StdSeedPolicy>;
using NativeRandom = Random<long_t, NativeSeedPolicy>;

xNAMESPACE_END2(xl, crypt)
//-------------------------------------------------------------------------------------------------
#include "Random.inl"
