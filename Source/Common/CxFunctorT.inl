/****************************************************************************
* Class name:  CxFunctorT
* Description: function object
* File name:   CxFunctorT.cpp
* Compilers:   Visual C++ 2010, C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     30.09.2010 15:28:35
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxFunctorT (constructor)
template <class ClassT, typename ReturnT, typename ParamT>
CxFunctorT<ClassT, ReturnT, ParamT>::CxFunctorT(ClassT *pObject, Method method) :
	_m_pObject(pObject),
	_m_Method (method)
{
	/*DEBUG*/xASSERT_DO(NULL != _m_pObject, return);
	/*DEBUG*/xASSERT_DO(NULL != _m_Method,  return);
}
//---------------------------------------------------------------------------
//TODO: - ~CxFunctorT (destuctor)
template <class ClassT, typename ReturnT, typename ParamT>
CxFunctorT<ClassT, ReturnT, ParamT>::~CxFunctorT() {
	/*DEBUG*/
}
//---------------------------------------------------------------------------
//TODO: - operator() (COMMENTS)
template <class ClassT, typename ReturnT, typename ParamT>
ReturnT
CxFunctorT<ClassT, ReturnT, ParamT>::operator()(ParamT Param) {
	return (_m_pObject->*_m_Method)(Param);
}
//---------------------------------------------------------------------------
//TODO: - Execute (COMMENTS)
template <class ClassT, typename ReturnT, typename ParamT>
ReturnT
CxFunctorT<ClassT, ReturnT, ParamT>::Execute(ParamT Param) {
	return operator()(Param);
}
//---------------------------------------------------------------------------

