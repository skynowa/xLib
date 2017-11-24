/**
 * \file  ThreadStorage_unix.inl
 * \brief thread local storage
 */


xNAMESPACE_BEGIN2(xl, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ThreadStorage::index_t
ThreadStorage::_indexInvalid_impl() const
{
    return static_cast<index_t>( - 1 );
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadStorage::_construct_impl()
{
    index_t index = _indexInvalid_impl();

    int_t iRv = ::pthread_key_create(&index, xPTR_NULL);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    _index = index;
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadStorage::_destruct_impl()
{
    int_t iRv = ::pthread_key_delete(_index);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    _index = _indexInvalid_impl();
}
//-------------------------------------------------------------------------------------------------
bool_t
ThreadStorage::_isSet_impl() const
{
    void_t *pvRv = ::pthread_getspecific(_index);
    xCHECK_RET(pvRv == xPTR_NULL, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t *
ThreadStorage::_value_impl() const
{
    void_t *pvRv = ::pthread_getspecific(_index);
    xTEST_PTR(pvRv);

    return pvRv;
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadStorage::_setValue_impl(
    void_t **a_value
) const
{
    int_t iRv = ::pthread_setspecific(_index, *a_value);
    xTEST_EQ_MSG(iRv, 0, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
