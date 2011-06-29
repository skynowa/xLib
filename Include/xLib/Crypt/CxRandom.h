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


#ifndef xLib_Crypt_RandomH
#define xLib_Crypt_RandomH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxRandom :
    public CxNonCopyable
{
    public:
                         CxRandom     (LONG liSeed = time(NULL));
        virtual         ~CxRandom     ();

        BOOL             bSetSeed     (LONG liSeed);

        INT              iNextInt     ();
        INT              iNextInt     (INT max);
        INT              iNextInt     (INT a, INT b);
        LONG             liNextLong   ();
        bool             bNextBoolean ();
        FLOAT            fNextFloat   ();
        DOUBLE           bNextDouble  ();
        CHAR             chNextChar   ();
        CHAR             chNextFigure ();
        DOUBLE           dNextGaussian();

        static tString   sGetString   ();

    protected:
        LONG             liNext       ();

    private:
        static const INT A;
        static const INT M;
        static const INT Q;
        static const INT R;

        LONG             _m_liSeed;
        double           _m_dNextNextGaussian;
        bool             _m_bHaveNextNextGaussian;
};
//---------------------------------------------------------------------------
#endif    //xLib_Crypt_RandomH
