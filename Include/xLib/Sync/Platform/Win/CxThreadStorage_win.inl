/**
 * \file  CxThreadStorage.inl
 * \brief thread local storage
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxThreadStorage::_construct_impl()
{
    index_t indRv = (index_t)- 1;

    xTEST_EQ(_index, TLS_OUT_OF_INDEXES);

    indRv = ::TlsAlloc();
    xTEST_DIFF(indRv, TLS_OUT_OF_INDEXES);

    _index = indRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThreadStorage::_destruct_impl()
{
    xTEST_EQ(0 < _index, true);

    int_t iRv = ::pthread_key_delete(_index);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

    _index = static_cast<pthread_key_t>( -1 );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThreadStorage::_isSet_impl() const
{
    void_t *pvRv = ::TlsGetValue(_index);
    xCHECK_RET(pvRv == xPTR_NULL, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t *
CxThreadStorage::_value_impl() const
{
    xTEST_DIFF(TLS_OUT_OF_INDEXES, _index);

    void_t *pvRv = ::TlsGetValue(_index);
    xTEST_EQ((pvRv != xPTR_NULL) && (CxLastError::get() == ERROR_SUCCESS), true);

    return pvRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThreadStorage::_setValue_impl(
    void_t *a_value
) const
{
    xTEST_DIFF(_index, TLS_OUT_OF_INDEXES);

    BOOL blRv = ::TlsSetValue(_index, a_value);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
