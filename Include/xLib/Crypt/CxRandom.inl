/**
 * \file  CxRandom.cpp
 * \brief random
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTracer.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxRandom::CxRandom(
    clong_t &a_seed
) :
    _seed                  (0L),
    _nextNextGaussian      (false),
    _isHaveNextNextGaussian(false)
{
    setSeed(a_seed);

    long_t liRv = _next();
    xUNUSED(liRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxRandom::setSeed(
    clong_t &a_seed
)
{
    std::srand( static_cast<uint_t>(a_seed) );

#if xTEMP_DISABLED
    if (a_seed < 0)    {
        a_seed = a_seed + (M + 1);
    }
#endif

    _seed = a_seed;

    if (0L == _seed) {
        _seed = 1L;
    }

    _isHaveNextNextGaussian = false;
}
//-------------------------------------------------------------------------------------------------
inline int_t
CxRandom::nextInt()
{
    return static_cast<int_t>( _next() );
}
//-------------------------------------------------------------------------------------------------
inline int_t
CxRandom::nextInt(
    cint_t &a_max
)
{
    return nextInt() % a_max;
}
//-------------------------------------------------------------------------------------------------
inline int_t
CxRandom::nextInt(
    cint_t &a,
    cint_t &b
)
{
    return nextInt() % (b - a) + a;
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxRandom::nextLong()
{
    return _next();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxRandom::nextBool()
{
    return ( 0 == (_next() % 2) );
}
//-------------------------------------------------------------------------------------------------
inline float_t
CxRandom::nextFloat()
{
    return static_cast<float_t>( static_cast<float_t>(nextInt()) / static_cast<float_t>(M) );
}
//-------------------------------------------------------------------------------------------------
inline double
CxRandom::nextDouble()
{
    return static_cast<double>( nextInt() / static_cast<double>(M) );
}
//-------------------------------------------------------------------------------------------------
inline char
CxRandom::nextChar()
{
    return char(('z' - 'a' + 1) * nextDouble() + 'a');
}
//-------------------------------------------------------------------------------------------------
inline char
CxRandom::nextFigure()
{
    return char(('9' - '0' + 1) * nextDouble() + '0');
}
//-------------------------------------------------------------------------------------------------
inline double
CxRandom::nextGaussian()
{
    // See Knuth, ACP, Section 3.4.1 Algorithm C.
    if (_isHaveNextNextGaussian) {
        _isHaveNextNextGaussian = false;

        return static_cast<double>( _nextNextGaussian );
    } else {
        double v1 = 0.0;
        double v2 = 0.0;
        double s  = 0.0;

        do {
            v1 = 2 * nextDouble() - 1; // between - 1 and 1
            v2 = 2 * nextDouble() - 1; // between - 1 and 1
            s = v1 * v1 + v2 * v2;
        }
        while (s >= 1 || s == 0);

        double multiplier = ::sqrt(-2 * ::log(s) / s);

        _nextNextGaussian       = v2 * multiplier;
        _isHaveNextNextGaussian = true;

        return static_cast<double>( v1 * multiplier );
    }
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxRandom::setSeed()
{
    // n/a

    uint_t seed = 0U;

#if xOS_ENV_WIN
    seed = static_cast<uint_t>( ::GetTickCount() );
#else
    seed = static_cast<uint_t>( std::time(NULL) );
#endif

    (void_t)std::srand(seed);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline long_t
CxRandom::nextIntEx(
    clong_t &a_min,
    clong_t &a_max
)
{
    xTEST_LESS(a_min, a_max);

    long_t liRv = 0L;

#if 1
    liRv = (::rand() % (a_max - a_min))  + a_min;
#else
    liRv = (::rand() * (double)(a_max - a_min) / RAND_MAX) + a_min;
#endif

    return liRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxRandom::nextString(
    std::csize_t &a_length
)
{
    xCHECK_RET(0U == a_length, std::tstring_t());

    cbool_t isLetters      = true;
    cbool_t isNumbers      = true;
    cbool_t isAsciiSymbols = true;

    std::tstring_t sRv;
    std::tstring_t allPossible;

    if (isLetters) {
        for (int_t i = 65; i <= 90; ++ i) {
            allPossible.push_back( static_cast<tchar_t>(i) );       // upper case
            allPossible.push_back( static_cast<tchar_t>(i + 32) );  // lower case
        }
    }

    if (isNumbers) {
        for (int_t i = 48; i <= 57; ++ i) {
            allPossible.push_back( static_cast<tchar_t>(i) );
        }
    }

    if (isAsciiSymbols) {
        for (int_t i = 33; i <= 47; ++ i) {
            allPossible.push_back( static_cast<tchar_t>(i) );
        }

        for (int_t i = 58; i <= 64; ++ i) {
            allPossible.push_back( static_cast<tchar_t>(i) );
        }

        for (int_t i = 91; i <= 96; ++ i) {
            allPossible.push_back( static_cast<tchar_t>(i) );
        }

        for (int_t i = 123; i <= 126; ++ i) {
            allPossible.push_back( static_cast<tchar_t>(i) );
        }
    }

    clong_t possibilitiesNum = static_cast<long_t>( allPossible.size() );
    for (ulong_t i = 0; i < a_length; ++ i) {
        sRv.push_back( allPossible.at( nextIntEx(0, possibilitiesNum) ) );
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline long_t
CxRandom::_next()
{
#if 0
    int_t tmp = A * (_seed % Q) - R * (_seed / Q);
    if (tmp >= 0) {
        _seed = tmp;
    } else {
        _seed = tmp + M;
    }
#else
    _seed = ::rand();
#endif

    return _seed;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
