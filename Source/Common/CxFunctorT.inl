/****************************************************************************
* Class name:  CxFunctorT
* Description: function object
* File name:   CxFunctorT.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     30.09.2010 15:28:35
*
*****************************************************************************/


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
    /*DEBUG*/xASSERT_DO(NULL != _m_pObject, return);
    /*DEBUG*/xASSERT_DO(NULL != _m_Method,  return);
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
