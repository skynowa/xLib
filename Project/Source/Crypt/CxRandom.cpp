/**
 * \file  CxRandom.cpp
 * \brief random
 */


#include <xLib/Crypt/CxRandom.h>

#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTracer.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxRandom::CxRandom(
    clong_t &a_seed
) :
    _seed               (0),
    _nextNextGaussian    (false),
    _isHaveNextNextGaussian(false)
{
    vSetSeed(a_seed);

    long_t liRv = liNext();
    xUNUSED(liRv);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxRandom::vSetSeed(
    clong_t &a_seed
)
{
    std::srand(a_seed);

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
//------------------------------------------------------------------------------
xINLINE_HO int_t
CxRandom::iNextInt() {
    return static_cast<int_t>( liNext() );
}
//------------------------------------------------------------------------------
xINLINE_HO int_t
CxRandom::iNextInt(
    cint_t &max
)
{
    return iNextInt() % max;
}
//------------------------------------------------------------------------------
xINLINE_HO int_t
CxRandom::iNextInt(
    cint_t &a,
    cint_t &b
)
{
    return iNextInt() % (b - a) + a;
}
//------------------------------------------------------------------------------
xINLINE_HO long_t
CxRandom::liNextLong()
{
    return liNext();
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxRandom::bNextBoolean()
{
    return ( 0 == (liNext() % 2) );
}
//------------------------------------------------------------------------------
xINLINE_HO float_t
CxRandom::fNextFloat()
{
    return static_cast<float_t>( iNextInt() / float_t(M) );
}
//------------------------------------------------------------------------------
xINLINE_HO double
CxRandom::bNextDouble()
{
    return static_cast<double>( iNextInt() / double(M) );
}
//------------------------------------------------------------------------------
xINLINE_HO char
CxRandom::chNextChar()
{
    return char(('z' - 'a' + 1) * bNextDouble() + 'a');
}
//------------------------------------------------------------------------------
xINLINE_HO char
CxRandom::chNextFigure()
{
    return char(('9' - '0' + 1) * bNextDouble() + '0');
}
//------------------------------------------------------------------------------
xINLINE_HO double
CxRandom::dNextGaussian()
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
            v1 = 2 * bNextDouble() - 1; // between - 1 and 1
            v2 = 2 * bNextDouble() - 1; // between - 1 and 1
            s = v1 * v1 + v2 * v2;
        }
        while (s >= 1 || s == 0);

        double multiplier = ::sqrt(-2 * ::log(s)/s);

        _nextNextGaussian     = v2 * multiplier;
        _isHaveNextNextGaussian = true;

        return static_cast<double>( v1 * multiplier );
    }
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public, static
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxRandom::vSetSeed()
{
    // n/a

    uint_t uiSeed = 0U;

#if xOS_ENV_WIN
    uiSeed = static_cast<uint_t>( ::GetTickCount() );
#else
    uiSeed = static_cast<uint_t>( std::time(NULL) );
#endif

    (void_t)std::srand(uiSeed);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO long_t
CxRandom::liInt(
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
//------------------------------------------------------------------------------
/* static */
xINLINE_HO long_t
CxRandom::liIntEx(
    clong_t &a_min,
    clong_t &a_max
)
{
    xTEST_LESS(a_min, a_max);

    std::vector<long_t> vliRes;

    for (long_t i = a_min; i < a_max; ++ i) {
        vliRes.push_back(i);
    }

    xTEST_EQ(false, vliRes.empty());

    std::random_shuffle(vliRes.begin(), vliRes.end());

    return vliRes.at(0);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxRandom::sString(
    std::csize_t &a_cuiLength
)
{
    xCHECK_RET(0U == a_cuiLength, std::tstring_t());

    cbool_t cbIsLetters      = true;
    cbool_t cbIsNumbers      = true;
    cbool_t cbIsAsciiSymbols = true;

    std::tstring_t sRv;
    std::tstring_t sAllPossible;

    if (cbIsLetters) {
        for (int_t i = 65; i <= 90; ++ i) {
            sAllPossible.push_back( static_cast<tchar_t>(i) );         //upper case
            sAllPossible.push_back( static_cast<tchar_t>(i + 32) );    //lower case
        }
    }

    if (cbIsNumbers) {
        for (int_t i = 48; i <= 57; ++ i) {
            sAllPossible.push_back( static_cast<tchar_t>(i) );
        }
    }

    if (cbIsAsciiSymbols) {
        for (int_t i = 33; i <= 47; ++ i) {
            sAllPossible.push_back( static_cast<tchar_t>(i) );
        }

        for (int_t i = 58; i <= 64; ++ i) {
            sAllPossible.push_back( static_cast<tchar_t>(i) );
        }

        for (int_t i = 91; i <= 96; ++ i) {
            sAllPossible.push_back( static_cast<tchar_t>(i) );
        }

        for (int_t i = 123; i <= 126; ++ i) {
            sAllPossible.push_back( static_cast<tchar_t>(i) );
        }
    }

    clong_t cuiPossibilitiesNum = static_cast<long_t>( sAllPossible.size() );
    for (ulong_t i = 0; i < a_cuiLength; ++ i) {
        sRv.push_back( sAllPossible.at( liInt(0, cuiPossibilitiesNum) ) );
    }

    return sRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    protected
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO long_t
CxRandom::liNext()
{
    #if xTEMP_DISABLED
        int_t tmp = A * (_seed % Q) - R * (_seed / Q);
        if(tmp>=0)  _seed = tmp;
        else        _seed = tmp + M;

        return _seed;
    #endif

    return ::rand();
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
