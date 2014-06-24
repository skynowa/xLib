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
    #if xHAVE_RAND_R
        int_t iRv = ::rand_r(&_seed);
    #else

    #endif

    return iRv;
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
    xSTRUCT_ZERO(_data);

#if xHAVE_SRANDOM_R
    int_t iRv = ::srandom_r(_seed, &_data);
    xTEST_DIFF(iRv, - 1);
#else

#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxNativeSeedPolicy::_destruct_impl()
{
    xSTRUCT_ZERO(_data);
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

#endif

    return liRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, crypt)
