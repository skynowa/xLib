/**
 * \file  CxRandom_win.inl
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
    (void_t)std::srand(_seed);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline long_t
CxStdSeedPolicy::_next_impl()
{
   /**
    * VC++'s C runtime is multithreaded by default.
    * There's no need for rand_r, rand works fine in this case
    */
    int_t iRv = std::rand();

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
    _hProv = xPTR_NULL;

    BOOL blRv = ::CryptAcquireContext(&_hProv, xPTR_NULL, xPTR_NULL, PROV_RSA_FULL,
        CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxNativeSeedPolicy::_destruct_impl()
{
    BOOL blRv = ::CryptReleaseContext(_hProv, 0UL);   _hProv = xPTR_NULL;
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxNativeSeedPolicy::_next_impl()
{
    long_t liRv = 0L;

    union RandBuff
    {
        BYTE   buff[ sizeof(long_t) ];
        long_t value;
    } randBuff;

    BOOL blRv = ::CryptGenRandom(_hProv, sizeof(randBuff), reinterpret_cast<BYTE *>( &randBuff ));
    xTEST_DIFF(blRv, FALSE);

    liRv = randBuff.value;

    return liRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, crypt)
