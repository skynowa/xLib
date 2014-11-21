/**
 * \file  ThreadStorage.inl
 * \brief thread local storage
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
ThreadStorage::_construct_impl()
{
    xTEST_EQ(_index, static_cast<pthread_key_t>( - 1 ));

    index_t indRv = (index_t)- 1;

    int_t iRv = ::pthread_key_create(&indRv, xPTR_NULL);
    xTEST_EQ_MSG(iRv, 0, NativeError::format(iRv));

    _index = indRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
ThreadStorage::_destruct_impl()
{
    xTEST_EQ(0 < _index, true);

    int_t iRv = ::pthread_key_delete(_index);
    xTEST_EQ_MSG(iRv, 0, NativeError::format(iRv));

    _index = static_cast<pthread_key_t>( -1 );
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
ThreadStorage::_isSet_impl() const
{
    void_t *pvRv = ::pthread_getspecific(_index);
    xCHECK_RET(pvRv == xPTR_NULL, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t *
ThreadStorage::_value_impl() const
{
    xTEST_EQ(0 < _index, true);

    void_t *pvRv = ::pthread_getspecific(_index);
    xTEST_PTR(pvRv);

    return pvRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
ThreadStorage::_setValue_impl(
    void_t *a_value
) const
{
    xTEST_EQ(0 < _index, true);

    int_t iRv = ::pthread_setspecific(_index, a_value);
    xTEST_EQ_MSG(iRv, 0, NativeError::format(iRv));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
