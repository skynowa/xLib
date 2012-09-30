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
template <class ClassT, typename ReturnT, typename ParamT>
CxFunctorT<ClassT, ReturnT, ParamT>::CxFunctorT(
    ClassT *pObject,
    Method  method
) :
    _m_pObject(pObject),
    _m_Method (method)
{
    // TODO: debug code
#if xTODO
    /*DEBUG*/xTEST_DIFF(NULL, _m_pObject);
    /*DEBUG*/xTEST_DIFF(NULL, _m_Method);
#endif
}
//---------------------------------------------------------------------------
template <class ClassT, typename ReturnT, typename ParamT>
CxFunctorT<ClassT, ReturnT, ParamT>::~CxFunctorT() {
    /*DEBUG*/
}
//---------------------------------------------------------------------------
template <class ClassT, typename ReturnT, typename ParamT>
ReturnT
CxFunctorT<ClassT, ReturnT, ParamT>::operator()(
    ParamT Param
)
{
    return (_m_pObject->*_m_Method)(Param);
}
//---------------------------------------------------------------------------
template <class ClassT, typename ReturnT, typename ParamT>
ReturnT
CxFunctorT<ClassT, ReturnT, ParamT>::Execute(
    ParamT Param
)
{
    return operator()(Param);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
