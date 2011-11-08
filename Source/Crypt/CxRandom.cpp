/**
 * \file  CxRandom.cpp
 * \brief random
 */


#include <xLib/Crypt/CxRandom.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
const INT CxRandom::A = 48271;
const INT CxRandom::M = RAND_MAX;
const INT CxRandom::Q = M / A;
const INT CxRandom::R = M % A;
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
    srand(liSeed);

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
INT
CxRandom::iNextInt() {
    return static_cast<INT>( liNext() );
}
//---------------------------------------------------------------------------
INT
CxRandom::iNextInt(
    INT max
)
{
    return iNextInt() % max;
}
//---------------------------------------------------------------------------
INT
CxRandom::iNextInt(
    INT a,
    INT b
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
FLOAT
CxRandom::fNextFloat() {
    return static_cast<FLOAT>( iNextInt() / FLOAT(M) );
}
//---------------------------------------------------------------------------
DOUBLE
CxRandom::bNextDouble() {
    return static_cast<DOUBLE>( iNextInt() / DOUBLE(M) );
}
//---------------------------------------------------------------------------
CHAR
CxRandom::chNextChar() {
    return CHAR(('z' - 'a' + 1) * bNextDouble() + 'a');
}
//---------------------------------------------------------------------------
CHAR
CxRandom::chNextFigure() {
    return CHAR(('9' - '0' + 1) * bNextDouble() + '0');
}
//---------------------------------------------------------------------------
DOUBLE
CxRandom::dNextGaussian() {
    //See Knuth, ACP, Section 3.4.1 Algorithm C.
    if (_m_bHaveNextNextGaussian) {
        _m_bHaveNextNextGaussian = false;

        return static_cast<DOUBLE>( _m_dNextNextGaussian );
    } else {
        DOUBLE v1 = 0.0;
        DOUBLE v2 = 0.0;
        DOUBLE s  = 0.0;

        do {
            v1 = 2 * bNextDouble() - 1; // between -1 and 1
            v2 = 2 * bNextDouble() - 1; // between -1 and 1
            s = v1 * v1 + v2 * v2;
        }
        while (s >= 1 || s == 0);

        DOUBLE multiplier = sqrt(-2 * log(s)/s);

        _m_dNextNextGaussian     = v2 * multiplier;
        _m_bHaveNextNextGaussian = true;

        return static_cast<DOUBLE>( v1 * multiplier );
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

#if defined(xOS_ENV_WIN)
    uiSeed = static_cast<UINT>( ::GetTickCount() );
#elif defined(xOS_ENV_UNIX)
    uiSeed = static_cast<UINT>( time(NULL) );
#endif

    srand(uiSeed);
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
    liRes   = (rand() % (cliMax - cliMin))  + cliMin;
#else
    liRes   = (rand() * (DOUBLE)(cliMax - cliMin) / RAND_MAX) + cliMin;
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
        for (INT i = 65; i <= 90; ++ i) {
            sAllPossible.push_back( static_cast<TCHAR>(i) );         //upper case
            sAllPossible.push_back( static_cast<TCHAR>(i + 32) );    //lower case
        }
    }

    if (TRUE == cbIsNumbers) {
        for (INT i = 48; i <= 57; ++ i) {
            sAllPossible.push_back( static_cast<TCHAR>(i) );
        }
    }

    if (TRUE == cbIsAsciiSymbols) {
        for (INT i = 33; i <= 47; ++ i) {
            sAllPossible.push_back( static_cast<TCHAR>(i) );
        }

        for (INT i = 58; i <= 64; ++ i) {
            sAllPossible.push_back( static_cast<TCHAR>(i) );
        }

        for (INT i = 91; i <= 96; ++ i) {
            sAllPossible.push_back( static_cast<TCHAR>(i) );
        }

        for (INT i = 123; i <= 126; ++ i) {
            sAllPossible.push_back( static_cast<TCHAR>(i) );
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
        INT tmp = A * (_m_liSeed % Q) - R * (_m_liSeed / Q);
        if(tmp>=0)  _m_liSeed = tmp;
        else        _m_liSeed = tmp + M;

        return _m_liSeed;
    #endif

    return rand();
}
//---------------------------------------------------------------------------
