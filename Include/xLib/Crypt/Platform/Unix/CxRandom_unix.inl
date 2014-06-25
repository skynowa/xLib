/**
 * \file  CxRandom_unix.inl
 * \brief random generator
 */


xNAMESPACE_BEGIN2(xlib, crypt)

/**************************************************************************************************
*    CxStdSeedPolicy
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t inline
CxStdSeedPolicy::_construct_impl()
{
    xNA
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxStdSeedPolicy::_next_impl()
{
    long_t liRv = 0L;

#if xHAVE_RAND_R
    liRv = ::rand_r(&_seed);
#else
    liRv = ::rand();
#endif

    return liRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    CxNativeSeedPolicy
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxNativeSeedPolicy::_construct_impl()
{
#if xHAVE_SRANDOM_R
    xSTRUCT_ZERO(_data);

    int_t iRv = ::srandom_r(_seed, &_data);
    xTEST_DIFF(iRv, - 1);
#else
    (void_t)::srandom(_seed);
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxNativeSeedPolicy::_destruct_impl()
{
#if (xHAVE_SRANDOM_R && xHAVE_RANDOM_R)
    xSTRUCT_ZERO(_data)
#endif
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxNativeSeedPolicy::_next_impl()
{
    long_t liRv = 0L;

#if xHAVE_RANDOM_R
    int32_t i32Rv = 0;

    int iRv = ::random_r(&_data, &i32Rv);
    xTEST_DIFF(iRv, - 1);

    liRv = static_cast<long_t>( i32Rv );
#else
    liRv = ::random();
#endif

    return liRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, crypt)
