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
//TODO: CxRandom
CxRandom::CxRandom(LONG liSeed) :
    _m_liSeed               (0),
    _m_dNextNextGaussian    (false),
    _m_bHaveNextNextGaussian(false)
{
    bSetSeed(liSeed);

    liNext();
}
//---------------------------------------------------------------------------
//TODO: ~CxRandom
/*virtual*/
CxRandom::~CxRandom() {

}
//---------------------------------------------------------------------------
//TODO: bSetSeed
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
//TODO: iNextInt
INT
CxRandom::iNextInt() {
    return static_cast<INT>( liNext() );
}
//---------------------------------------------------------------------------
//TODO: iNextInt
INT
CxRandom::iNextInt(INT max) {
    return iNextInt() % max;
}
//---------------------------------------------------------------------------
//TODO: iNextInt
INT
CxRandom::iNextInt(INT a, INT b) {
    return iNextInt() % (b - a) + a;
}
//---------------------------------------------------------------------------
//TODO: liNextLong
LONG
CxRandom::liNextLong() {
    return liNext();
}
//---------------------------------------------------------------------------
//TODO: bNextBoolean
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
//TODO: bNextDouble
DOUBLE
CxRandom::bNextDouble() {
    return static_cast<DOUBLE>( iNextInt() / DOUBLE(M) );
}
//---------------------------------------------------------------------------
//TODO:
CHAR
CxRandom::chNextChar() {
    return CHAR(('z' - 'a' + 1) * bNextDouble() + 'a');
}
//---------------------------------------------------------------------------
//TODO: chNextFigure
CHAR
CxRandom::chNextFigure() {
    return CHAR(('9' - '0' + 1) * bNextDouble() + '0');
}
//---------------------------------------------------------------------------
//TODO: dNextGaussian
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
*    protected
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: liNext
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
