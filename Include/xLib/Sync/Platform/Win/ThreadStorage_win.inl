/**
 * \file  ThreadStorage_win.inl
 * \brief thread local storage
 */


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ThreadStorage::index_t
ThreadStorage::_indexInvalid_impl() const
{
    return TLS_OUT_OF_INDEXES;
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadStorage::_ctor_impl()
{
    _index = ::TlsAlloc();
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadStorage::_dtor_impl()
{
    BOOL blRv = ::TlsFree(_index);
    xTEST_DIFF(blRv, FALSE);

    _index = _indexInvalid_impl();
}
//-------------------------------------------------------------------------------------------------
bool_t
ThreadStorage::_isSet_impl() const
{
    void_t *pvRv = ::TlsGetValue(_index);
    xCHECK_RET(pvRv == nullptr, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t *
ThreadStorage::_value_impl() const
{
    void_t *pvRv = ::TlsGetValue(_index);
    xTEST((pvRv != nullptr) && (NativeError::get() == ERROR_SUCCESS));

    return pvRv;
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadStorage::_setValue_impl(
    void_t **a_value
) const
{
    BOOL blRv = ::TlsSetValue(_index, a_value);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

} // namespace
