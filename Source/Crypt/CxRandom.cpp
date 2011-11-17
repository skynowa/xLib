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
    LONG liSeed
) :
    _m_liSeed               (0),
    _m_dNextNextGaussian    (false),
    _m_bHaveNextNextGaussian(false)
{
    bSetSeed(liSeed);

    liNext();
}
//---------------------------------------------------------------------------
/*virtual*/
CxRandom::~CxRandom() {

}
//---------------------------------------------------------------------------
BOOL
CxRandom::bSetSeed(
    LONG liSeed
)
{
    std::srand(liSeed);

    #if xTEMP_DISABLED
        if (liSeed < 0)    {
            liSeed = liSeed + (M + 1);
        }
    #endif

    _m_liSeed = liSeed;

    if (0 == _m_liSeed) {
        _m_liSeed = 1;
    }

    _m_bHaveNextNextGaussian = false;

    return TRUE;
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
LONG
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
BOOL
CxRandom::bSetSeed() {
    /*DEBUG*/// n/a

    UINT uiSeed = 0;

#if xOS_ENV_WIN
    uiSeed = static_cast<UINT>( ::GetTickCount() );
#elif xOS_ENV_UNIX
    uiSeed = static_cast<UINT>( std::time(NULL) );
#endif

    std::srand(uiSeed);
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
LONG
CxRandom::liGetInt(
    const LONG cliMin,
    const LONG cliMax
)
{
    /*DEBUG*/xASSERT_RET(cliMin < cliMax, 0L);

    LONG liRes = 0;

#if 1
    liRes   = (::rand() % (cliMax - cliMin))  + cliMin;
#else
    liRes   = (::rand() * (double)(cliMax - cliMin) / RAND_MAX) + cliMin;
#endif

    return liRes;
}
//---------------------------------------------------------------------------
/*static*/
LONG
CxRandom::liGetIntEx(
    const LONG cliMin,
    const LONG cliMax
)
{
    /*DEBUG*/xASSERT_RET(cliMin < cliMax, 0)

    std::vector<LONG> vliRes;

    for (LONG i = cliMin; i < cliMax; ++ i) {
        vliRes.push_back(i);
    }

    /*DEBUG*/xASSERT_RET(false == vliRes.empty(), 0L);

    std::random_shuffle(vliRes.begin(), vliRes.end());

    return vliRes.at(0);
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxRandom::sGetString(
    const size_t cuiLength
)
{
    /*DEBUG*/

    xCHECK_RET(0 == cuiLength, std::string_t());

    const BOOL cbIsLetters      = TRUE;
    const BOOL cbIsNumbers      = TRUE;
    const BOOL cbIsAsciiSymbols = TRUE;

    std::string_t sRes;
    std::string_t sAllPossible;

    if (TRUE == cbIsLetters) {
        for (int i = 65; i <= 90; ++ i) {
            sAllPossible.push_back( static_cast<char_t>(i) );         //upper case
            sAllPossible.push_back( static_cast<char_t>(i + 32) );    //lower case
        }
    }

    if (TRUE == cbIsNumbers) {
        for (int i = 48; i <= 57; ++ i) {
            sAllPossible.push_back( static_cast<char_t>(i) );
        }
    }

    if (TRUE == cbIsAsciiSymbols) {
        for (int i = 33; i <= 47; ++ i) {
            sAllPossible.push_back( static_cast<char_t>(i) );
        }

        for (int i = 58; i <= 64; ++ i) {
            sAllPossible.push_back( static_cast<char_t>(i) );
        }

        for (int i = 91; i <= 96; ++ i) {
            sAllPossible.push_back( static_cast<char_t>(i) );
        }

        for (int i = 123; i <= 126; ++ i) {
            sAllPossible.push_back( static_cast<char_t>(i) );
        }
    }

    const size_t cuiPossibilitiesNum = sAllPossible.length();
    for (size_t i = 0; i < cuiLength; ++ i) {
        sRes.push_back( sAllPossible.at( liGetInt(0, cuiPossibilitiesNum) ) );
    }

    return sRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    protected
*
*****************************************************************************/

//---------------------------------------------------------------------------
LONG
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
