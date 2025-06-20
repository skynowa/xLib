/**
 * \file  Random.h
 * \brief random generator
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::crypt
{

class ISeedPolicy
    /// seed policy
{
public:
///\name ctors, dtor
///\{
			 ISeedPolicy();
	virtual ~ISeedPolicy() = default;

	xNO_COPY_ASSIGN(ISeedPolicy);
///\}

    virtual long_t next() = 0;
        ///< next value

    static
    long_t         valueMax();
        ///< maximum possible value

protected:
    uint_t _seed {}; ///< current seed

private:
    uint_t _seedTimeBased() const;
        ///< get time based seed
};
//-------------------------------------------------------------------------------------------------
class StdSeedPolicy :
    ISeedPolicy
    /// std seed policy
{
public:
///\name ctors, dtor
///\{
			 StdSeedPolicy();
	virtual ~StdSeedPolicy() = default;

	xNO_COPY_ASSIGN(StdSeedPolicy);
///\}

    virtual long_t next() final;
        ///< get integer in the range between 0 and RAND_MAX

xPLATFORM_IMPL:
    void_t _ctor_impl();
    long_t _next_impl();
};
//-------------------------------------------------------------------------------------------------
class NativeSeedPolicy :
    ISeedPolicy
    /// native seed policy
{
public:
///\name ctors, dtor
///\{
			 NativeSeedPolicy();
	virtual ~NativeSeedPolicy();

	xNO_COPY_ASSIGN(NativeSeedPolicy);
///\}

    virtual long_t next() final;
        ///< get long integer in the range between 0 and RAND_MAX

private:
#if   xENV_WIN
    HCRYPTPROV     _hProv {};  ///< CSP handle
#elif xENV_UNIX
    #if (cmHAVE_SRANDOM_R && cmHAVE_RANDOM_R)
        random_data _data {};   ///< data for ::srandom_r()
    #endif
#endif

xPLATFORM_IMPL:
    void_t _ctor_impl();
    void_t _dtor_impl();
    long_t _next_impl();
};
//-------------------------------------------------------------------------------------------------
template<typename RandomValueT, class SeedPolicyT>
class Random
    /// random
{
public:
///\name operators
///\{
			 Random();
	virtual ~Random() = default;

    xNO_COPY_ASSIGN(Random);
///\}

    bool_t nextBool();
        ///< get bool_t value
    template<typename T>
    T      nextChar();
        ///< get character value between min and max
    template<typename T>
    T      nextInt(const T &min, const T &max);
        ///< get integer value between min and max
    template<typename T>
    T      nextFloat(const T &min, const T &max);
       ///< get float value between min and max

private:
    const RandomValueT _randMax;
    SeedPolicyT _policy;
};

using StdRandom    = Random<int_t,  StdSeedPolicy>;
using NativeRandom = Random<long_t, NativeSeedPolicy>;

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Random.inl"
//-------------------------------------------------------------------------------------------------
/**
 * \file  Random.h
 * \todo
 *
 * - Random - rm
 */
