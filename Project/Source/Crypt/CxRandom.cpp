/**
 * \file  CxRandom.cpp
 * \brief random
 */


#include <xLib/Crypt/CxRandom.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
const int CxRandom::A = 48271;
const int CxRandom::M = RAND_MAX;
const int CxRandom::Q = M / A;
const int CxRandom::R = M % A;
//---------------------------------------------------------------------------
CxRandom::CxRandom(
    long_t a_liSeed
) :
    _m_liSeed               (0),
    _m_dNextNextGaussian    (false),
    _m_bHaveNextNextGaussian(false)
{
    bSetSeed(a_liSeed);

    liNext();
}
//---------------------------------------------------------------------------
/* virtual */
CxRandom::~CxRandom() {

}
//---------------------------------------------------------------------------
bool
CxRandom::bSetSeed(
    long_t a_liSeed
)
{
    std::srand(a_liSeed);

    #if xTEMP_DISABLED
        if (a_liSeed < 0)    {
            a_liSeed = a_liSeed + (M + 1);
        }
    #endif

    _m_liSeed = a_liSeed;

    if (0 == _m_liSeed) {
        _m_liSeed = 1;
    }

    _m_bHaveNextNextGaussian = false;

    return true;
}
//---------------------------------------------------------------------------
int
CxRandom::iNextInt() {
    return static_cast<int>( liNext() );
}
//---------------------------------------------------------------------------
int
CxRandom::iNextInt(
    int max
)
{
    return iNextInt() % max;
}
//---------------------------------------------------------------------------
int
CxRandom::iNextInt(
    int a,
    int b
)
{
    return iNextInt() % (b - a) + a;
}
//---------------------------------------------------------------------------
long_t
CxRandom::liNextLong() {
    return liNext();
}
//---------------------------------------------------------------------------
bool
CxRandom::bNextBoolean() {
    return 0 == (liNext() % 2);
}
//---------------------------------------------------------------------------
float
CxRandom::fNextFloat() {
    return static_cast<float>( iNextInt() / float(M) );
}
//---------------------------------------------------------------------------
double
CxRandom::bNextDouble() {
    return static_cast<double>( iNextInt() / double(M) );
}
//---------------------------------------------------------------------------
char
CxRandom::chNextChar() {
    return char(('z' - 'a' + 1) * bNextDouble() + 'a');
}
//---------------------------------------------------------------------------
char
CxRandom::chNextFigure() {
    return char(('9' - '0' + 1) * bNextDouble() + '0');
}
//---------------------------------------------------------------------------
double
CxRandom::dNextGaussian() {
    //See Knuth, ACP, Section 3.4.1 Algorithm C.
    if (_m_bHaveNextNextGaussian) {
        _m_bHaveNextNextGaussian = false;

        return static_cast<double>( _m_dNextNextGaussian );
    } else {
        double v1 = 0.0;
        double v2 = 0.0;
        double s  = 0.0;

        do {
            v1 = 2 * bNextDouble() - 1; // between -1 and 1
            v2 = 2 * bNextDouble() - 1; // between -1 and 1
            s = v1 * v1 + v2 * v2;
        }
        while (s >= 1 || s == 0);

        double multiplier = ::sqrt(-2 * ::log(s)/s);

        _m_dNextNextGaussian     = v2 * multiplier;
        _m_bHaveNextNextGaussian = true;

        return static_cast<double>( v1 * multiplier );
    }
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public, static
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxRandom::bSetSeed() {
    /*DEBUG*/// n/a

    uint_t uiSeed = 0;

#if   xOS_ENV_WIN
    uiSeed = static_cast<uint_t>( ::GetTickCount() );
#elif xOS_ENV_UNIX
    uiSeed = static_cast<uint_t>( std::time(NULL) );
#endif

    std::srand(uiSeed);
    /*DEBUG*/// n/a

    return true;
}
//---------------------------------------------------------------------------
/* static */
long_t
CxRandom::liGetInt(
    const long_t a_cliMin,
    const long_t a_cliMax
)
{
    /*DEBUG*/xASSERT_RET(a_cliMin < a_cliMax, 0L);

    long_t liRv = 0;

#if 1
    liRv   = (::rand() % (a_cliMax - a_cliMin))  + a_cliMin;
#else
    liRv   = (::rand() * (double)(a_cliMax - a_cliMin) / RAND_MAX) + a_cliMin;
#endif

    return liRv;
}
//---------------------------------------------------------------------------
/* static */
long_t
CxRandom::liGetIntEx(
    const long_t a_cliMin,
    const long_t a_cliMax
)
{
    /*DEBUG*/xASSERT_RET(a_cliMin < a_cliMax, 0)

    std::vector<long_t> vliRes;

    for (long_t i = a_cliMin; i < a_cliMax; ++ i) {
        vliRes.push_back(i);
    }

    /*DEBUG*/xASSERT_RET(false == vliRes.empty(), 0L);

    std::random_shuffle(vliRes.begin(), vliRes.end());

    return vliRes.at(0);
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxRandom::sGetString(
    const size_t a_cuiLength
)
{
    /*DEBUG*/

    xCHECK_RET(0U == a_cuiLength, std::tstring_t());

    const bool cbIsLetters      = true;
    const bool cbIsNumbers      = true;
    const bool cbIsAsciiSymbols = true;

    std::tstring_t sRv;
    std::tstring_t sAllPossible;

    if (true == cbIsLetters) {
        for (int i = 65; i <= 90; ++ i) {
            sAllPossible.push_back( static_cast<tchar_t>(i) );         //upper case
            sAllPossible.push_back( static_cast<tchar_t>(i + 32) );    //lower case
        }
    }

    if (true == cbIsNumbers) {
        for (int i = 48; i <= 57; ++ i) {
            sAllPossible.push_back( static_cast<tchar_t>(i) );
        }
    }

    if (true == cbIsAsciiSymbols) {
        for (int i = 33; i <= 47; ++ i) {
            sAllPossible.push_back( static_cast<tchar_t>(i) );
        }

        for (int i = 58; i <= 64; ++ i) {
            sAllPossible.push_back( static_cast<tchar_t>(i) );
        }

        for (int i = 91; i <= 96; ++ i) {
            sAllPossible.push_back( static_cast<tchar_t>(i) );
        }

        for (int i = 123; i <= 126; ++ i) {
            sAllPossible.push_back( static_cast<tchar_t>(i) );
        }
    }

    const size_t cuiPossibilitiesNum = sAllPossible.length();
    for (size_t i = 0; i < a_cuiLength; ++ i) {
        sRv.push_back( sAllPossible.at( liGetInt(0, cuiPossibilitiesNum) ) );
    }

    return sRv;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    protected
*
*****************************************************************************/

//---------------------------------------------------------------------------
long_t
CxRandom::liNext() {
    #if xTEMP_DISABLED
        int tmp = A * (_m_liSeed % Q) - R * (_m_liSeed / Q);
        if(tmp>=0)  _m_liSeed = tmp;
        else        _m_liSeed = tmp + M;

        return _m_liSeed;
    #endif

    return ::rand();
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
