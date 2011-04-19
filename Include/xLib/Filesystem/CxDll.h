/****************************************************************************
* Class name:  CxDll
* Description: dynamic linking loader
* File name:   CxDll.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.11.2009 23:39:28
*
*****************************************************************************/


#ifndef xLib_Fso_CxDllH 
#define xLib_Fso_CxDllH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxDll : public CxNonCopyable {
    private:
        BOOL     _m_bRes;

    #if defined(xOS_WIN)
        HMODULE  _m_hDLL;
    #elif defined(xOS_LINUX)
        VOID    *_m_hDLL;
    #endif

	public:
		         CxDll           ();
		virtual ~CxDll           ();

		BOOL     bIsLoaded       ();
		BOOL     bLoad           (const tString &csDllPath);
		VOID *   fpGetProcAddress(const tString &csProcName);
		BOOL     bFree           ();
};
//---------------------------------------------------------------------------
#endif //xLib_Fso_CxDllH

/*
FARPROC is defined something like:
typedef int(*FARPROC)(void)
or
typedef int (CALLBACK *FARPROC)()
or
typedef int (FAR WINAPI *FARPROC)()

basically its just a func pointer.
*/

//http://www.codeproject.com/script/Articles/ViewDownloads.aspx?aid=13817
//http://www.yolinux.com/TUTORIALS/LibraryArchives-StaticAndDynamic.html


/*
Static libraries (.a)
Dynamically linked shared object libraries (.so)
*/

/*
dlopen() - gain access to an executable object file
dclose() - close a dlopen object
dlsym() - obtain the address of a symbol from a dlopen object
dlvsym() - Programming interface to dynamic linking loader.
dlerror() - get diagnostic information

void *dlopen(const char
void *dlsym(void *handle, char *symbol);
const char *dlerror();
int dlclose(void *handle);
*/
