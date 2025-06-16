/**
 * \file  Random_unix.inl
 * \brief random generator
 */


namespace xl::crypt
{

/**************************************************************************************************
*    StdSeedPolicy
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
StdSeedPolicy::_ctor_impl()
{
    xNA
}
//-------------------------------------------------------------------------------------------------
long_t
StdSeedPolicy::_next_impl()
{
    long_t liRv = 0L;

#if cmHAVE_RAND_R
    liRv = ::rand_r(&_seed);
#else
    liRv = ::rand();
#endif

    return liRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    NativeSeedPolicy
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
NativeSeedPolicy::_ctor_impl()
{
#if cmHAVE_SRANDOM_R
    int_t iRv = 0;

    _data = {};

    char state[32] = {0};
    iRv = ::initstate_r(_seed, state, sizeof(state), &_data);
    xTEST_DIFF(iRv, - 1);

    iRv = ::srandom_r(_seed, &_data);
    xTEST_DIFF(iRv, - 1);
#else
    (void_t)::srandom(_seed);
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
NativeSeedPolicy::_dtor_impl()
{
#if (cmHAVE_SRANDOM_R && cmHAVE_RANDOM_R)
    _data = {};
#endif
}
//-------------------------------------------------------------------------------------------------
long_t
NativeSeedPolicy::_next_impl()
{
    long_t liRv = 0L;

#if cmHAVE_RANDOM_R
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

} // namespace
