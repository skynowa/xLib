// Copyright 2003 "Gilles Degottex"

// This file is part of "CppAddons"

// "CppAddons" is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// "CppAddons" is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



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
//DONE: CxRandom
CxRandom::CxRandom(LONG liSeed) :
    _m_liSeed               (0),
    _m_dNextNextGaussian    (false),
    _m_bHaveNextNextGaussian(false)
{
    bSetSeed(liSeed);

    liNext();
}
//---------------------------------------------------------------------------
//DONE: ~CxRandom
/*virtual*/
CxRandom::~CxRandom() {

}
//---------------------------------------------------------------------------
//DONE: bSetSeed
BOOL
CxRandom::bSetSeed(LONG liSeed) {
    srand(liSeed);

////    if (liSeed < 0)    {
////        liSeed = liSeed + (M + 1);
////    }

    _m_liSeed = liSeed;

    if (0 == _m_liSeed) {
        _m_liSeed = 1;
    }

    _m_bHaveNextNextGaussian = false;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: iNextInt
INT
CxRandom::iNextInt() {
    return static_cast<INT>( liNext() );
}
//---------------------------------------------------------------------------
//DONE: iNextInt
INT
CxRandom::iNextInt(INT max) {
    return iNextInt() % max;
}
//---------------------------------------------------------------------------
//DONE: iNextInt
INT
CxRandom::iNextInt(INT a, INT b) {
    return iNextInt() % (b - a) + a;
}
//---------------------------------------------------------------------------
//DONE: liNextLong
LONG
CxRandom::liNextLong() {
    return liNext();
}
//---------------------------------------------------------------------------
//DONE: bNextBoolean
bool
CxRandom::bNextBoolean() {
    return 0 == (liNext() % 2);
}
//---------------------------------------------------------------------------
//TODO: fNextFloat
FLOAT
CxRandom::fNextFloat() {
    return static_cast<FLOAT>( iNextInt() / FLOAT(M) );
}
//---------------------------------------------------------------------------
//DONE: bNextDouble
DOUBLE
CxRandom::bNextDouble() {
    return static_cast<DOUBLE>( iNextInt() / DOUBLE(M) );
}
//---------------------------------------------------------------------------
//DONE:
CHAR
CxRandom::chNextChar() {
    return CHAR(('z' - 'a' + 1) * bNextDouble() + 'a');
}
//---------------------------------------------------------------------------
//DONE: chNextFigure
CHAR
CxRandom::chNextFigure() {
    return CHAR(('9' - '0' + 1) * bNextDouble() + '0');
}
//---------------------------------------------------------------------------
//DONE: dNextGaussian
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
//DONE: bSetSeed
BOOL 
CxRandom::bSetSeed() {
    /*DEBUG*/// n/a

    UINT uiSeed = 0;

#if defined(xOS_WIN)
    uiSeed = static_cast<UINT>( ::GetTickCount() );
#elif defined(xOS_LINUX)
    uiSeed = static_cast<UINT>( time(NULL) );
#endif

    srand(uiSeed);
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: liGetInt (Generates a random number between specified min/max boundaries) 
/*static*/
LONG 
CxRandom::liGetInt( 
    const LONG cliMin, 
    const LONG cliMax 
)
{
    /*DEBUG*/xASSERT_RET(cliMin < cliMax, 0)

    const LONG cliRange = cliMax - cliMin;
    const LONG cliNum   = rand() % cliRange;

    return cliNum + cliMin;
}
//---------------------------------------------------------------------------
//DONE: liGetIntEx (Generates a random number between specified min/max boundaries using a vector to shuffle)
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

    std::random_shuffle(vliRes.begin(), vliRes.end());

	return vliRes[0];
}
//---------------------------------------------------------------------------
//DONE: sGetString (get random string)
/*static*/
tString
CxRandom::sGetString(
    const size_t cuiLength
)
{
    /*DEBUG*/

    const BOOL cbIsLetters      = TRUE;
    const BOOL cbIsNumbers      = TRUE;
    const BOOL cbIsAsciiSymbols = TRUE;

    tString sRes;
    tString sAllPossible;

    if (TRUE == cbIsLetters) {
        for (INT i = 65; i <= 90; ++ i) {
            sAllPossible.push_back(static_cast<TCHAR>(i) );         //upper case
            sAllPossible.push_back(static_cast<TCHAR>(i + 32) );    //lower case
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
        sRes += sAllPossible[ liGetInt(0, cuiPossibilitiesNum) ];
    }

    //std::random_shuffle(sRes.begin(), sRes.end());

    return sRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    protected
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: liNext
LONG
CxRandom::liNext() {
//  INT tmp = A * (_m_liSeed % Q) - R * (_m_liSeed / Q);
//  if(tmp>=0)  _m_liSeed = tmp;
//  else        _m_liSeed = tmp + M;
//
//  return _m_liSeed;

    return rand();
}
//---------------------------------------------------------------------------
