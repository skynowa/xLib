/**
 * \file  CxRandom.h
 * \brief random
 */


#ifndef xLib_Crypt_RandomH
#define xLib_Crypt_RandomH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
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
    int                   iNextInt     () xWARN_UNUSED_RESULT;
        ///< next int
    int                   iNextInt     (const int &max) xWARN_UNUSED_RESULT;
        ///< next int
    int                   iNextInt     (const int &a, const int &b) xWARN_UNUSED_RESULT;
        ///< next int
    long_t                liNextLong   () xWARN_UNUSED_RESULT;
        ///< next long_t
    bool                  bNextBoolean () xWARN_UNUSED_RESULT;
        ///< next boolean
    float                 fNextFloat   () xWARN_UNUSED_RESULT;
        ///< next float
    double                bNextDouble  () xWARN_UNUSED_RESULT;
        ///< next double
    char                  chNextChar   () xWARN_UNUSED_RESULT;
        ///< next char
    char                  chNextFigure () xWARN_UNUSED_RESULT;
        ///< next figure
    double                dNextGaussian() xWARN_UNUSED_RESULT;
        ///< next gaussian

    static void           vSetSeed     ();
        ///< set seed
    static long_t         liInt        (const long_t &cliMin, const long_t &cliMax) xWARN_UNUSED_RESULT;
        ///< generates a random number between specified min/max boundaries
    static long_t         liIntEx      (const long_t &cliMin, const long_t &cliMax) xWARN_UNUSED_RESULT;
        ///< generates a random number between specified min/max boundaries using a vector to shuffle
    static std::tstring_t sString      (const size_t &cuiSize) xWARN_UNUSED_RESULT;
        ///< get random string

protected:
    long_t                liNext       () xWARN_UNUSED_RESULT;
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
//------------------------------------------------------------------------------
#endif // xLib_Crypt_RandomH
