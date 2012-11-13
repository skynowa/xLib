/**
 * \file  CxFunctorT.inl
 * \brief function object
 */


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
template <typename ClassT, typename ReturnT, typename ParamT>
CxFunctorT<ClassT, ReturnT, ParamT>::CxFunctorT(
    ClassT *pObject,
    Method  method
) :
    _m_pObject(pObject),
    _m_Method (method)
{
    // TODO: debug code
#if xTODO
    xTEST_DIFF(NULL, _m_pObject);
    xTEST_DIFF(NULL, _m_Method);
#endif
}
//---------------------------------------------------------------------------
template <typename ClassT, typename ReturnT, typename ParamT>
CxFunctorT<ClassT, ReturnT, ParamT>::~CxFunctorT() {
    
}
//---------------------------------------------------------------------------
template <typename ClassT, typename ReturnT, typename ParamT>
ReturnT
CxFunctorT<ClassT, ReturnT, ParamT>::operator()(
    ParamT Param
)
{
    return (_m_pObject->*_m_Method)(Param);
}
//---------------------------------------------------------------------------
template <typename ClassT, typename ReturnT, typename ParamT>
ReturnT
CxFunctorT<ClassT, ReturnT, ParamT>::Execute(
    ParamT Param
)
{
    return operator()(Param);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
