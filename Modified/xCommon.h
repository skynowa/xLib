#ifndef xLib_xCommonH
#define xLib_xCommonH
//---------------------------------------------------------------------------
#ifndef __cplusplus
	#error xLib requires C++ compilation (use a .cpp suffix)
#endif
//---------------------------------------------------------------------------
//win version
////#define _WIN32_WINNT_NT4       0x0400	//Windows NT 4.0
////#define _WIN32_WINNT_WIN2K     0x0500	//Windows 2000
////#define _WIN32_WINNT_WINXP     0x0501	//Windows Server 2003, Windows XP
////#define _WIN32_WINNT_WS03      0x0502	//Windows Server 2003 with SP1, Windows XP with SP2
////#define _WIN32_WINNT_WIN6      0x0600	//
////#define _WIN32_WINNT_VISTA     0x0600	//Windows Vista
////#define _WIN32_WINNT_WS08      0x0600	//Windows Server 2008
////#define _WIN32_WINNT_LONGHORN  0x0600	//
////#define _WIN32_WINNT_WIN7      0x0601	//Windows 7

#define xWINVER       	       WINVER	//текущяя версия Windows

#define xWIN32_31       /*FIX*/0x0100	//Windows NT 3.1
#define xWIN32_95       /*FIX*/0x0200	//Windows 95
#define xWIN32_98ME            0x0300	//Windows 98, Windows Me
#define xWIN32_NT4       	   0x0400	//Windows NT 4.0
#define xWIN32_2K     		   0x0500	//Windows 2000
#define xWIN32_XP    	       0x0501	//Windows Server 2003, Windows XP
#define xWIN32_S03      	   0x0502	//Windows Server 2003 with SP1, Windows XP with SP2
#define xWIN32_VISTA     	   0x0600	//Windows Vista, Windows Server 2008
#define xWIN32_7      	       0x0601	//Windows 7
//---------------------------------------------------------------------------
//Remove pointless warning messages
#ifdef _MSC_VER
	////#pragma warning (disable : 4511)	//copy operator could not be generated
	////#pragma warning (disable : 4512)	//assignment operator could not be generated
	////#pragma warning (disable : 4702)	//unreachable code (bugs in Microsoft's STL)
	////#pragma warning (disable : 4786)	//identifier was truncated
	#pragma warning (disable : 4996)	//function or variable may be unsafe (deprecated)

	#ifndef _CRT_SECURE_NO_WARNINGS
		#define _CRT_SECURE_NO_WARNINGS //eliminate deprecation warnings for VS2005
	#endif
	////#define _SECURE_SCL 0
	
	//Required for VS 2008 (fails on XP and Win2000 without this fix)
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0600
	#endif

	#ifdef WINVER
		#undef  WINVER
		#define WINVER 0x0600
	#else
		#define WINVER 0x0600
	#endif

	#ifdef _WIN32_WINNT
		#undef  _WIN32_WINNT
		#define _WIN32_WINNT 0x0600
	#else
		#define _WIN32_WINNT 0x0600
	#endif

#endif // _MSC_VER

#ifdef __BORLANDC__
	#pragma option -w-8027				//function not expanded inline
	#pragma option -w-8057				//parameter is never used
	#pragma option -w-8058				//cannot create pre-compiled header: initialized data in header
	#pragma option -w-8004 				//is assigned a value that is never used
	#pragma option -w-8022 				//hides virtual function 'Image::Clone()'
	#pragma option -w-8008 				//Condition is always true

	#define xD2S(s) 	tString((s).c_str())
	#define xD2AS(s) 	tString((s).t_str())
	#define xS2D(s) 	String((s).c_str()) 
	#define xD2WD(s)	WideString((s))


	//xTRY_BOOL
	#define xTRY_BOOL	\
				BOOL bRes = FALSE;  \
				try	{				\
					{			

	#define xCATCH_BOOL_RET	\
					}	\
					bRes = TRUE;	\
				} \
				catch (Exception &e) {	\
					xASSERT_MSG(FALSE, xD2AS(e.Message).c_str());	\
				}                             \
				catch (std::exception e) {   \
					std::string asWhat = e.what();	\
					xASSERT_MSG(FALSE, xS2TS(asWhat).c_str());	\
				}	\
				catch (...) {	\
					xASSERT_MSG(FALSE, xT("Неизвестная ошибка"));	\
				}	\
				return bRes; 

	//xTRY_LONG
	#define xTRY_LONG(ret_error_value)	LONG liRes = ret_error_value;  \
				try	{				\
					{				\
						liRes = 		\

	#define xCATCH_LONG_RET	\
					}	\
				}	\
				catch (Exception &e) {	\
					xASSERT_MSG(FALSE, xD2AS(e.Message).c_str());	\
				}	\
				catch (std::exception e) {	\
					std::string asWhat = e.what();	\
					xASSERT_MSG(FALSE, xS2TS(asWhat).c_str());	\
				}	\
				catch (...) {	\
					xASSERT_MSG(FALSE, xT("Неизвестная ошибка"));	\
				}	\
				return liRes; 

	//xTRY_VARIANT
	#define xTRY_VARIANT(ret_error_value)	Variant vRes = ret_error_value;  \
				try	{				\
					{				\
						vRes = 		\

	#define xCATCH_VARIANT_RET	\
					}	\
				}	\
				catch (Exception &e) {	\
					xASSERT_MSG(FALSE, xD2AS(e.Message).c_str());	\
				}	\
				catch (std::exception e) {	\
					std::string asWhat = e.what();	\
					xASSERT_MSG(FALSE, xS2TS(asWhat).c_str());	\
				}	\
				catch (...) {	\
					xASSERT_MSG(FALSE, xT("Неизвестная ошибка"));	\
				}	\
				return vRes; 

#endif //__BORLANDC__
//---------------------------------------------------------------------------
//OBM_ (#include <winuser.h>)
#define OEMRESOURCE
///#define WIN32_LEAN_AND_MEAN	//Prevent winsock.h #include's

#include <windows.h>
#include <tchar.h>
#include <windowsx.h>
#include <winuser.h>
#include <string>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <utility>
#include <ctime>
#include <conio.h>
////#include <shellapi.h>
//---------------------------------------------------------------------------
//For compilers lacking Win64 support
////#ifndef  GetWindowLongPtr
////	#define GetWindowLongPtr   GetWindowLong
////	#define SetWindowLongPtr   SetWindowLong
////	#define GWLP_WNDPROC       GWL_WNDPROC
////	#define GWLP_HINSTANCE     GWL_HINSTANCE
////	#define GWLP_ID            GWL_ID
////	#define GWLP_USERDATA      GWL_USERDATA
////	#define DWLP_DLGPROC       DWL_DLGPROC
////	#define DWLP_MSGRESULT     DWL_MSGRESULT
////	#define DWLP_USER          DWL_USER
////	#define DWORD_PTR          DWORD
////	#define LONG_PTR           LONG
////	#define ULONG_PTR          LONG
////#endif
////	#ifndef GetClassLongPtr
////	#define GetClassLongPtr    GetClassLong
////	#define SetClassLongPtr    SetClassLong
////	#define GCLP_HBRBACKGROUND GCL_HBRBACKGROUND
////	#define GCLP_HCURSOR       GCL_HCURSOR
////	#define GCLP_HICON         GCL_HICON
////	#define GCLP_HICONSM       GCL_HICONSM
////	#define GCLP_HMODULE       GCL_HMODULE
////	#define GCLP_MENUNAME      GCL_MENUNAME
////	#define GCLP_WNDPROC       GCL_WNDPROC
////#endif

//Strict
#ifndef STRICT
	#define STRICT 1
#endif

//Prevent winsock.h #include's
#define _WINSOCKAPI_   

//For Visual Studio 6 (without an updated platform SDK) and Dev-C++
#ifndef OPENFILENAME_SIZE_VERSION_400
	#define OPENFILENAME_SIZE_VERSION_400 sizeof(OPENFILENAME)
#endif
//---------------------------------------------------------------------------
#if defined(UNICODE) || defined(_UNICODE)
	#define xT(x)					 L ## x
	
	typedef std::wstring             tString;     
	typedef std::basic_string<unsigned char> uString;
	typedef std::wostringstream		 tostringstream; 
	typedef std::wistringstream		 tistringstream;
	typedef std::wifstream			 tifstream;      
	typedef std::wofstream			 tofstream;  

	#define tcin					 std::wcin
	#define tcout					 std::wcout  
	#define tendl                    std::endl   
#else   
	#define xT(x)					 x
	
	typedef std::string              tString;       
	typedef std::basic_string<unsigned char> uString;
	typedef std::ostringstream       tostringstream; 
	typedef std::istringstream       tistringstream;  
	typedef std::ifstream            tifstream;      
	typedef std::ofstream            tofstream;     
	typedef std::ostream             tcout; 

	#define tcin                     std::cin  
	#define tcout                    std::cout   
	#define tendl                    std::endl   
#endif  /*_UNICODE*/
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
//Automatically include the xLib namespace define xNO_USING_NAMESPACE to skip this step
namespace NxLib {}
#ifndef xNO_USING_NAMESPACE
    using namespace NxLib;
#endif
//---------------------------------------------------------------------------
#include <xLib/xLinking.h>
#include <xLib/CxConst.h>
#include <xLib/CxNonCopyable.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/CxString.h>
#include <xLib/Gui/Dialogs/CxMsgBoxT.h>
//---------------------------------------------------------------------------
#endif  //xLib_xCommonH