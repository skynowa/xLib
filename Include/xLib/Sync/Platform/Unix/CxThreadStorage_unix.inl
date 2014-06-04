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
    xTEST_EQ(_index, static_cast<pthread_key_t>( - 1 ));

    index_t indRv = (index_t)- 1;

    int_t iRv = ::pthread_key_create(&indRv, xPTR_NULL);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));

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
    void_t *pvRv = ::pthread_getspecific(_index);
    xCHECK_RET(pvRv == xPTR_NULL, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t *
CxThreadStorage::_value_impl() const
{
    xTEST_EQ(0 < _index, true);

    void_t *pvRv = ::pthread_getspecific(_index);
    xTEST_PTR(pvRv);

    return pvRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThreadStorage::_setValue_impl(
    void_t *a_value
) const
{
    xTEST_EQ(0 < _index, true);

    int_t iRv = ::pthread_setspecific(_index, a_value);
    xTEST_MSG_EQ(iRv, 0, CxLastError::format(iRv));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
