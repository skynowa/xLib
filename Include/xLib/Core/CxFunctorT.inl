/**
 * \file  CxFunctorT.inl
 * \brief function object
 */


xNAMESPACE_BEGIN(xlib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template <class ClassT, class ReturnT, class ParamT>
CxFunctorT<ClassT, ReturnT, ParamT>::CxFunctorT(
    ClassT         *a_object,
    const method_t &a_method
) :
    _object(a_object),
    _method(a_method)
{
    xTEST_EQ(a_object != NULL, true);
    xTEST_EQ(a_method != NULL, true);
}
//-------------------------------------------------------------------------------------------------
template <class ClassT, class ReturnT, class ParamT>
ReturnT
CxFunctorT<ClassT, ReturnT, ParamT>::operator () (
    const ParamT &a_param
) const
{
    xTEST_NA(a_param);

    return (_object->*_method)(a_param);
}
//-------------------------------------------------------------------------------------------------
template <class ClassT, class ReturnT, class ParamT>
ReturnT
CxFunctorT<ClassT, ReturnT, ParamT>::execute(
    const ParamT &a_param
) const
{
    xTEST_NA(a_param);

    return operator()(a_param);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(xlib)
