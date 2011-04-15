/****************************************************************************
* Class name:  CxSingleton
* Description: ���������
* File name:   CxSingleton.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     29.06.2010 11:17:21
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Patterns_CxSingletonH
#define xLib_Patterns_CxSingletonH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
template <class ClassNameT>
class CxSingleton : public CxNonCopyable {
	public:
		static ClassNameT &GetInstance() {
			static ClassNameT m_Instance; 
			
			return m_Instance;
		}		

	private:
		CxSingleton();                                 
	   ~CxSingleton();                                 
};
//---------------------------------------------------------------------------
#endif //xLib_Patterns_CxSingletonH



/*
template <class T>
class CxSingleton {
	public:
		static CxSingleton &Instance();

	private:
		CxSingleton();
	   ////~CxSingleton();
	
};
template <class T>
CxSingleton<T> &CxSingleton<T>::Instance() {
	static CxSingleton theSingleInstance;

	return theSingleInstance;
}
template <class T>
T &Singleton<T>::Instance() {
	Create();
	T *p;
	if (!Locked() && (p = Obj().p))
		return *p;
	throw E_AccessViolation("Uutl::Singleton<T>::Instance");
}
//---------------------------------------------------------------------------

*/

/*
class OnlyOne {
	private:
		OnlyOne()
		{
		}
 
	public:
		static OnlyOne& Instance()
		{
			static OnlyOne theSingleInstance;
			return theSingleInstance;
		}
 
		// ...
};
*/
