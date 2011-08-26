/**
 * \file  CxDll.h
 * \brief dynamic linking loader
 */


#ifndef xLib_Filesystem_CxDllH
#define xLib_Filesystem_CxDllH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxDll :
    public CxNonCopyable
    /// dynamic linking loader
{
    public:
                 CxDll           ();
        virtual ~CxDll           ();

        BOOL     bIsLoaded       ();
        BOOL     bLoad           (const std::tstring &csDllPath);
        VOID *   fpGetProcAddress(const std::tstring &csProcName);
        BOOL     bFree           ();

    private:
        BOOL     _m_bRes;

    #if defined(xOS_WIN)
        HMODULE  _m_hDLL;
    #elif defined(xOS_LINUX)
        VOID    *_m_hDLL;
    #endif
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxDllH

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
