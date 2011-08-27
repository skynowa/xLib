/**
 * \file  CxRandom.h
 * \brief random
 */


#ifndef xLib_Crypt_RandomH
#define xLib_Crypt_RandomH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxRandom :
    public CxNonCopyable
    /// random
{
    public:
                            CxRandom     (LONG liSeed = time(NULL));
        virtual            ~CxRandom     ();

        BOOL                bSetSeed     (LONG liSeed);

        INT                 iNextInt     ();
        INT                 iNextInt     (INT max);
        INT                 iNextInt     (INT a, INT b);
        LONG                liNextLong   ();
        bool                bNextBoolean ();
        FLOAT               fNextFloat   ();
        DOUBLE              bNextDouble  ();
        CHAR                chNextChar   ();
        CHAR                chNextFigure ();
        DOUBLE              dNextGaussian();

        static BOOL         bSetSeed     ();
        static LONG         liGetInt     (const LONG cliMin, const LONG cliMax);
        static LONG         liGetIntEx   (const LONG cliMin, const LONG cliMax);
        static std::tstring sGetString   (const size_t cuiSize);

    protected:
        LONG                liNext       ();

    private:
        static const INT A;
        static const INT M;
        static const INT Q;
        static const INT R;

        LONG                _m_liSeed;
        double              _m_dNextNextGaussian;
        bool                _m_bHaveNextNextGaussian;
};
//---------------------------------------------------------------------------
#endif    //xLib_Crypt_RandomH
