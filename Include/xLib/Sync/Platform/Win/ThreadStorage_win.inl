/**
 * \file  ThreadStorage_win.inl
 * \brief thread local storage
 */


xNAMESPACE_BEGIN2(xl, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE ThreadStorage::index_t
ThreadStorage::_indexInvalid_impl() const;
{
    return TLS_OUT_OF_INDEXES;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
ThreadStorage::_construct_impl()
{
    _index = ::TlsAlloc();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
ThreadStorage::_destruct_impl()
{
    BOOL blRv = ::TlsFree(_index);
    xTEST_DIFF(blRv, FALSE);

    _index = _indexInvalid_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
ThreadStorage::_isSet_impl() const
{
    void_t *pvRv = ::TlsGetValue(_index);
    xCHECK_RET(pvRv == xPTR_NULL, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t *
ThreadStorage::_value_impl() const
{
    void_t *pvRv = ::TlsGetValue(_index);
    xTEST_EQ((pvRv != xPTR_NULL) && (NativeError::get() == ERROR_SUCCESS), true);

    return pvRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
ThreadStorage::_setValue_impl(
    void_t* &a_value
) const
{
    BOOL blRv = ::TlsSetValue(_index, a_value);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
