/**
 * \file  CxRandom.inl
 * \brief random generator
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

#if   xENV_WIN
    #include "Platform/Win/CxRandom_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxRandom_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxRandom_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxRandom_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, crypt)

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
    _construct_impl();
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
    return _next_impl();
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
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxNativeSeedPolicy::~CxNativeSeedPolicy()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline long_t
CxNativeSeedPolicy::next()
{
    return _next_impl();
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

xNAMESPACE_END2(xlib, crypt)
