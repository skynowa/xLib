/**
 * \file  CxRandom.cpp
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
#include <xLib/Log/CxTracer.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxRandom::CxRandom() :
    _seed(0U)
{
}
//-------------------------------------------------------------------------------------------------
inline void
CxRandom::setSeed()
{
    _seed = _seedTimeBased();

#if xOS_ENV_WIN
    (void_t)std::srand(_seed);
#endif
}
//-------------------------------------------------------------------------------------------------
inline void
CxRandom::setSeed(
    cuint_t &a_seed
)
{
    _seed = a_seed;

#if xOS_ENV_WIN
    (void_t)std::srand(_seed);
#endif
}
//-------------------------------------------------------------------------------------------------
template <class T>
T
CxRandom::nextInt(
    const T &min,
    const T &max
)
{
    cint_t width = static_cast<int_t>(max - min) + 1;

    return static_cast<T>(_nextInt() % width) + min;
}
//-------------------------------------------------------------------------------------------------
template <class T>
T
CxRandom::nextFloat(
    const T &min,
    const T &max
)
{
    const T factor = (max - min) / static_cast<T>(RAND_MAX);

    return static_cast<T>( _nextInt() ) * factor + min;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline uint_t
CxRandom::_seedTimeBased() const
{
    struct timeval tv = {0, 0};
    int_t iRv = xGETTIMEOFDAY(&tv, NULL);
    xTEST_DIFF(iRv, - 1);

    return static_cast<uint_t>( tv.tv_usec );
}

//-------------------------------------------------------------------------------------------------
inline int_t
CxRandom::_nextInt()
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

xNAMESPACE_END(NxLib)
