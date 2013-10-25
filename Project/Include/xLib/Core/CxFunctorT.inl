/**
 * \file  CxFunctorT.inl
 * \brief function object
 */


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
template <typename ClassT, typename ReturnT, typename ParamT>
CxFunctorT<ClassT, ReturnT, ParamT>::CxFunctorT(
    ClassT   *a_object,
    method_t  a_method
) :
    _object(a_object),
    _method(a_method)
{
    // TODO: debug code
#if xTODO
    xTEST_DIFF(NULL, a_object);
    xTEST_DIFF(NULL, a_method);
#endif
}
//------------------------------------------------------------------------------
template <typename ClassT, typename ReturnT, typename ParamT>
ReturnT
CxFunctorT<ClassT, ReturnT, ParamT>::operator()(
    ParamT a_param
)
{
    return (_object->*_method)(a_param);
}
//------------------------------------------------------------------------------
template <typename ClassT, typename ReturnT, typename ParamT>
ReturnT
CxFunctorT<ClassT, ReturnT, ParamT>::execute(
    ParamT a_param
)
{
    return operator()(a_param);
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
