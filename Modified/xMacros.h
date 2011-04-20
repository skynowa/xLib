/****************************************************************************
* Class name:  CxMacros
* Description: functions like macroses
* File name:   CxMacros.h
* Compilers:   Visual C++ 2010, C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     10.12.2010 19:13:57
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_CxMacrosH
#define xLib_CxMacrosH
//---------------------------------------------------------------------------
#define xDELETE_PTR(p)   	  { if (NULL != (p)) {delete p;     p = NULL;} }
#define xDELETE_ARRAY(a)	  { if (NULL != (a)) {delete [] a;  a = NULL;} } 
#define xARRAY_ZERO_DELETE(a) { if (NULL != (a)) {xZERO_BUFF(a); delete [] a;  a = NULL;} } 

#define xZERO_BUFF(b)         { memset(&b, 0, sizeof(b)); }
#define xARRAY_SIZE(a)        ( sizeof(a) / sizeof((a)[0]) )				

#define xMAX(a, b)            { (((a) > (b)) ? (a) : (b)) }
#define xMIN(a, b)            { (((a) < (b)) ? (a) : (b)) }
#define xUNUSED_ARG(arg)	  (arg) = (arg)

#define xS2US(s)			 uString( (s).begin(),  (s).begin()  + (s).size()  )
#define xUS2S(us)			 tString( (us).begin(), (us).begin() + (us).size() )

#define xS2TS(s)			 tString( (s).begin(),  (s).begin()  + (s).size()  )
#define xTS2S(ts)			 std::string( (ts).begin(), (ts).begin() + (ts).size() )

#define xRANDOMIZE() 		 ( srand( (UINT)::GetTickCount() ) ) 
#define xRANDOM(x)           ( rand() % x )
//---------------------------------------------------------------------------
//for Windows
#define xIS_9xME              ( (::GetVersion () & 0x80000000) != 0 )

#define xMALLOC(s)           ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, (s))
#define xFREE(p)             ::HeapFree (::GetProcessHeap(), 0,                (p))

#define xKEYDOWN(vk_code)    ( (::GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0 )
#define xKEYUP(vk_code)      ( (::GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1 ) 

#define xGET_X_LPARAM(lp)    ( (INT)(SHORT)LOWORD(lp) )
#define xGET_Y_LPARAM(lp)    ( (INT)(SHORT)HIWORD(lp) )
//---------------------------------------------------------------------------
class CxMacros {
	public:
		//#define xDELETE_PTR(p)   	  { if (NULL != (p)) {delete p;     p = NULL;} }
		template<class T>
		static inline void xDELETE_PTR(T *&a_ptr) {
			if (NULL != a_ptr)  {
				delete a_ptr;
				a_ptr = NULL;
			}
		}

		////#define xDELETE_ARRAY(a)	  { if (NULL != (a)) {delete [] a;  a = NULL;} }
		template<class T>
		static inline void xDELETE_ARRAY(T *&a_ptr) {
			if (NULL != a_ptr)  {
				delete [] a_ptr;
				a_ptr = NULL;
			}
		}

		////#define xARRAY_ZERO_DELETE(a) { if (NULL != (a)) {xZERO_BUFF(a); delete [] a;  a = NULL;} } 
		template<class T>
		static inline void xARRAY_ZERO_DELETE(T *&a_ptr) {
			if (NULL != a_ptr)  {
				xZERO_BUFF(a_ptr);

				delete [] a_ptr;
				a_ptr = NULL;
			}
		}

		////#define xZERO_BUFF(b)         { ; }
		template<class T>
		static inline void xZERO_BUFF(T *&a_ptr) {
			if (NULL != a_ptr)  {
				memset(&a_ptr, 0, sizeof(b));
			}
		}


		////#define xARRAY_SIZE       (a);

	private:
				 CxMacros();
		        ~CxMacros();
};
//---------------------------------------------------------------------------
////#include <CxMacros.inl>
//---------------------------------------------------------------------------
#endif //CxMacrosH
