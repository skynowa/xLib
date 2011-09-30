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
            ///< constructor
        virtual ~CxDll           ();
            ///< destructor

        BOOL     bIsLoaded       ();
            ///< is loaded
        BOOL     bLoad           (const std::tstring &csDllPath);
            ///< load
        VOID *   fpGetProcAddress(const std::tstring &csProcName);
            ///< get address of an exported function or variable
        BOOL     bFree           ();
            ///< free

    private:
        BOOL     _m_bRes;   ///< for private use

    #if defined(xOS_ENV_WIN)
        HMODULE  _m_hDLL;   ///< dll module handle
    #elif defined(xOS_ENV_UNIX)
        VOID    *_m_hDLL;   ///< dll module handle
    #endif
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxDllH



#if xTODO
    FARPROC is defined something like:
    typedef int(*FARPROC)(void)
    or
    typedef int (CALLBACK *FARPROC)()
    or
    typedef int (FAR WINAPI *FARPROC)()

    basically its just a func pointer.
#endif

#if xTODO
    http://www.codeproject.com/script/Articles/ViewDownloads.aspx?aid=13817
    http://www.yolinux.com/TUTORIALS/LibraryArchives-StaticAndDynamic.html
#endif

#if xTODO
    Static libraries (.a)
    Dynamically linked shared object libraries (.so)
#endif

#if xTODO
    dlopen() - gain access to an executable object file
    dclose() - close a dlopen object
    dlsym() - obtain the address of a symbol from a dlopen object
    dlvsym() - Programming interface to dynamic linking loader.
    dlerror() - get diagnostic information

    void *dlopen(const char
    void *dlsym(void *handle, char *symbol);
    const char *dlerror();
    int dlclose(void *handle);
#endif
