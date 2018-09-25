/**
 * \file  Random_win.inl
 * \brief random generator
 */


xNAMESPACE_BEGIN2(xl, crypt)

/**************************************************************************************************
*    StdSeedPolicy
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
StdSeedPolicy::_construct_impl()
{
    (void_t)std::srand(_seed);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
long_t
StdSeedPolicy::_next_impl()
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
*    NativeSeedPolicy
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
NativeSeedPolicy::_construct_impl()
{
    _hProv = nullptr;

    BOOL blRv = ::CryptAcquireContext(&_hProv, nullptr, nullptr, PROV_RSA_FULL,
        CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
void_t
NativeSeedPolicy::_destruct_impl()
{
    BOOL blRv = ::CryptReleaseContext(_hProv, 0UL);   _hProv = nullptr;
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
long_t
NativeSeedPolicy::_next_impl()
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

xNAMESPACE_END2(xl, crypt)
