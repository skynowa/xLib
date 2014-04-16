/**
 * \file  CxRandom.inl
 * \brief random
 */


#include <xLib/Core/xFunctions.h>
#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTrace.h>


xNAMESPACE2_BEGIN(xlib, crypt)

/**************************************************************************************************
*    IxSeedPolicy
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
IxSeedPolicy::IxSeedPolicy() :
    _seed( _seedTimeBased() )
{
}
//-------------------------------------------------------------------------------------------------
inline uint_t
IxSeedPolicy::_seedTimeBased() const
{
    timeval tv = {0, 0};
    int_t iRv = xGETTIMEOFDAY(&tv, xPTR_NULL);
    xTEST_DIFF(iRv, - 1);

    return static_cast<uint_t>( tv.tv_usec );
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    CxStdSeedPolicy
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxStdSeedPolicy::CxStdSeedPolicy() :
    IxSeedPolicy()
{
#if xOS_ENV_WIN
    (void_t)std::srand(_seed);
#endif
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxStdSeedPolicy::~CxStdSeedPolicy()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline long_t
CxStdSeedPolicy::next()
{
    int_t iRv = 0U;

#if   xOS_ENV_WIN
   /**
    * VC++'s C runtime is multithreaded by default.
    * There's no need for rand_r, rand works fine in this case
    */
    iRv = std::rand();
#elif xOS_ENV_UNIX
    iRv = ::rand_r(&_seed);
#endif

    return iRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    CxNativeSeedPolicy
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxNativeSeedPolicy::CxNativeSeedPolicy() :
    IxSeedPolicy()
{
#if   xOS_ENV_WIN
    _hProv = xPTR_NULL;

    BOOL blRv = ::CryptAcquireContext(&_hProv, xPTR_NULL, xPTR_NULL, PROV_RSA_FULL,
        CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
    xTEST_DIFF(blRv, FALSE);
#elif xOS_ENV_UNIX
    xSTRUCT_ZERO(_data);

    int_t iRv = ::srandom_r(_seed, &_data);
    xTEST_DIFF(iRv, - 1);
#endif
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxNativeSeedPolicy::~CxNativeSeedPolicy()
{
#if   xOS_ENV_WIN
    BOOL blRv = ::CryptReleaseContext(_hProv, 0UL);   _hProv = xPTR_NULL;
    xTEST_DIFF(blRv, FALSE);
#elif xOS_ENV_UNIX
    xSTRUCT_ZERO(_data);
#endif
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline long_t
CxNativeSeedPolicy::next()
{
    long_t liRv = 0L;

#if   xOS_ENV_WIN
    union RandBuff
    {
        BYTE   buff[ sizeof(long_t) ];
        long_t value;
    } randBuff;

    BOOL blRv = ::CryptGenRandom(_hProv, sizeof(randBuff), reinterpret_cast<BYTE *>( &randBuff ));
    xTEST_DIFF(blRv, FALSE);

    liRv = randBuff.value;
#elif xOS_ENV_UNIX
    int32_t i32Rv = 0;

    int iRv = ::random_r(&_data, &i32Rv);
    xTEST_DIFF(iRv, - 1);

    liRv = static_cast<long_t>( i32Rv );
#endif

    return liRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template <class RandomValue, class SeedPolicy>
CxRandom<RandomValue, SeedPolicy>::CxRandom() :
    _randMax( (std::numeric_limits<RandomValue>::max)() )
{
}
//-------------------------------------------------------------------------------------------------
template <class RandomValue, class SeedPolicy>
bool_t
CxRandom<RandomValue, SeedPolicy>::nextBool()
{
    return (0 == (_policy.next() % 2));
}
//-------------------------------------------------------------------------------------------------
template <class RandomValue, class SeedPolicy>
template <class T>
T
CxRandom<RandomValue, SeedPolicy>::nextChar()
{
    clong_t min = (std::numeric_limits<T>::min)();
    clong_t max = (std::numeric_limits<T>::max)();

    return static_cast<T>( nextInt(min, max) );
}
//-------------------------------------------------------------------------------------------------
template <class RandomValue, class SeedPolicy>
template <class T>
T
CxRandom<RandomValue, SeedPolicy>::nextInt(
    const T &min,
    const T &max
)
{
    clong_t width = static_cast<long_t>(max - min) + 1;

    return static_cast<T>(_policy.next() % width) + min;
}
//-------------------------------------------------------------------------------------------------
template <class RandomValue, class SeedPolicy>
template <class T>
T
CxRandom<RandomValue, SeedPolicy>::nextFloat(
    const T &min,
    const T &max
)
{
    const T factor = (max - min) / static_cast<T>(_randMax);

    return static_cast<T>( _policy.next() ) * factor + min;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

xNAMESPACE2_END(xlib, crypt)
