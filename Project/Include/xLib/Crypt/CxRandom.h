/**
 * \file  CxRandom.h
 * \brief random
 */


#ifndef xLib_Crypt_RandomH
#define xLib_Crypt_RandomH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxRandom :
    private CxNonCopyable
    /// random
{
public:
    explicit              CxRandom     (const long_t &liSeed = std::time(NULL));
        ///< constructor
    virtual              ~CxRandom     ();
        ///< destructor

    void                  vSetSeed     (const long_t &liSeed);
        ///< set seed
    int                   iNextInt     ();
        ///< next int
    int                   iNextInt     (const int &max);
        ///< next int
    int                   iNextInt     (const int &a, const int &b);
        ///< next int
    long_t                liNextLong   ();
        ///< next long_t
    bool                  bNextBoolean ();
        ///< next boolean
    float                 fNextFloat   ();
        ///< next float
    double                bNextDouble  ();
        ///< next double
    char                  chNextChar   ();
        ///< next char
    char                  chNextFigure ();
        ///< next figure
    double                dNextGaussian();
        ///< next gaussian

    static void           vSetSeed     ();
        ///< set seed
    static long_t         liInt        (const long_t &cliMin, const long_t &cliMax);
        ///< generates a random number between specified min/max boundaries
    static long_t         liIntEx      (const long_t &cliMin, const long_t &cliMax);
        ///< generates a random number between specified min/max boundaries using a vector to shuffle
    static std::tstring_t sString      (const size_t &cuiSize);
        ///< get random string

protected:
    long_t                liNext       ();
        ///< next long_t

private:
    static const int      A;  ///< for private use
    static const int      M;  ///< for private use
    static const int      Q;  ///< for private use
    static const int      R;  ///< for private use

    long_t                _m_liSeed;                  ///< for private use
    double                _m_dNextNextGaussian;       ///< for private use
    bool                  _m_bHaveNextNextGaussian;   ///< for private use
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Crypt_RandomH
