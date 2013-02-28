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
    explicit              CxRandom     (clong_t &liSeed = std::time(NULL));
        ///< constructor
    virtual              ~CxRandom     ();
        ///< destructor

    void                  vSetSeed     (clong_t &liSeed);
        ///< set seed
    int_t                   iNextInt     () xWARN_UNUSED_RV;
        ///< next int_t
    int_t                   iNextInt     (cint_t &max) xWARN_UNUSED_RV;
        ///< next int_t
    int_t                   iNextInt     (cint_t &a, cint_t &b) xWARN_UNUSED_RV;
        ///< next int_t
    long_t                liNextLong   () xWARN_UNUSED_RV;
        ///< next long_t
    bool_t                  bNextBoolean () xWARN_UNUSED_RV;
        ///< next boolean
    float_t                 fNextFloat   () xWARN_UNUSED_RV;
        ///< next float_t
    double                bNextDouble  () xWARN_UNUSED_RV;
        ///< next double
    char                  chNextChar   () xWARN_UNUSED_RV;
        ///< next char
    char                  chNextFigure () xWARN_UNUSED_RV;
        ///< next figure
    double                dNextGaussian() xWARN_UNUSED_RV;
        ///< next gaussian

    static void           vSetSeed     ();
        ///< set seed
    static long_t         liInt        (clong_t &cliMin, clong_t &cliMax) xWARN_UNUSED_RV;
        ///< generates a random number between specified min/max boundaries
    static long_t         liIntEx      (clong_t &cliMin, clong_t &cliMax) xWARN_UNUSED_RV;
        ///< generates a random number between specified min/max boundaries using a vector to shuffle
    static std::tstring_t sString      (const size_t &cuiSize) xWARN_UNUSED_RV;
        ///< get random string

protected:
    long_t                liNext       () xWARN_UNUSED_RV;
        ///< next long_t

private:
    static cint_t      A;  ///< for private use
    static cint_t      M;  ///< for private use
    static cint_t      Q;  ///< for private use
    static cint_t      R;  ///< for private use

    long_t                _m_liSeed;                  ///< for private use
    double                _m_dNextNextGaussian;       ///< for private use
    bool_t                  _m_bHaveNextNextGaussian;   ///< for private use
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Crypt_RandomH
