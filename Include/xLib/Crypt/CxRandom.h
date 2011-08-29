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
            ///< constructor
        virtual            ~CxRandom     ();
            ///< destructor

        BOOL                bSetSeed     (LONG liSeed);
            ///< set seed
        INT                 iNextInt     ();
            ///< next int
        INT                 iNextInt     (INT max);
            ///< next int
        INT                 iNextInt     (INT a, INT b);
            ///< next int
        LONG                liNextLong   ();
            ///< next long
        bool                bNextBoolean ();
            ///< next boolean
        FLOAT               fNextFloat   ();
            ///< next float
        DOUBLE              bNextDouble  ();
            ///< next double
        CHAR                chNextChar   ();
            ///< next char
        CHAR                chNextFigure ();
            ///< next figure
        DOUBLE              dNextGaussian();
            ///< next gaussian

        static BOOL         bSetSeed     ();
            ///< set seed
        static LONG         liGetInt     (const LONG cliMin, const LONG cliMax);
            ///< generates a random number between specified min/max boundaries
        static LONG         liGetIntEx   (const LONG cliMin, const LONG cliMax);
            ///< generates a random number between specified min/max boundaries using a vector to shuffle
        static std::tstring sGetString   (const size_t cuiSize);
            ///< get random string

    protected:
        LONG                liNext       ();
            ///< next long

    private:
        static const INT    A;  ///< for private use
        static const INT    M;  ///< for private use
        static const INT    Q;  ///< for private use
        static const INT    R;  ///< for private use

        LONG                _m_liSeed;                  ///< for private use
        double              _m_dNextNextGaussian;       ///< for private use
        bool                _m_bHaveNextNextGaussian;   ///< for private use
};
//---------------------------------------------------------------------------
#endif    //xLib_Crypt_RandomH
