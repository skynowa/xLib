/****************************************************************************
* Class name:  CxFunctorT
* Description: function object
* File name:   CxFunctorT.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     30.09.2010 15:28:35
*
*****************************************************************************/


#ifndef xLib_Common_CxFunctorH
#define xLib_Common_CxFunctorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
template <class ClassT, typename ReturnT, typename ParamT>
class CxFunctorT {
	public:
		typedef  ReturnT   (ClassT::*Method)(ParamT);

		         CxFunctorT(ClassT *pObject, Method method);
		virtual ~CxFunctorT();

		ReturnT  operator()(ParamT Param);
		ReturnT  Execute   (ParamT Param);

	private:
		ClassT  *_m_pObject;
		Method   _m_Method;
};
//---------------------------------------------------------------------------
#include <Common/CxFunctorT.inl>
//---------------------------------------------------------------------------
#endif //xLib_Common_CxFunctorH

/*
class thread_adapter {
	public:
		thread_adapter(void (*func)(void *), void *param) : 
			_func (func), 
			_param(param)
		{
		}

		void operator()() const { 
			_func(_param); 
		}

	private:
		void (*_func)(void *);
		void *_param;
};
*/

/*
http://habrahabr.ru/blogs/cpp/111680/
*/
