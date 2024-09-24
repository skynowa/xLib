/**
 * \file   Functions.cpp
 * \brief  function macroses
 */


#include "Functions.h"

#include <xLib/Core/Core.h>

#if   xENV_WIN
    #include "Platform/Win/Functions_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Functions_unix.inl"

    #if   xENV_LINUX
        #if   xOS_ANDROID
            #include "Platform/Linux/Functions_android.inl"
        #elif xOS_LINUX
            // #include "Platform/Linux/Functions_linux.inl"
        #endif
    #elif xENV_BSD
        #include "Platform/Bsd/Functions_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/Functions_apple.inl"
    #endif
#endif
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*   Custom
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
#if   xCOMPILER_MS
    #include <dbghelp.h>
    #pragma comment(lib, "dbghelp.lib")
#elif xCOMPILER_GNUC || xCOMPILER_MINGW
    #include <cxxabi.h>
#else
	#error xLib: unsupported compiler
#endif
//-------------------------------------------------------------------------------------------------
std::tstring_t
demangleName(
	const char *a_nameOrig
)
{
    std::tstring_t sRv;
    std::string    className;

#if   xCOMPILER_MS
    constexpr DWORD buffSize {1024};
    char            buff[buffSize + 1] {};
    const     DWORD flags = {UNDNAME_COMPLETE}; // Enable full undecoration

    DWORD dwRv = ::UnDecorateSymbolName(a_nameOrig, buff, buffSize, flags);
    className = (dwRv != 0UL) ? a_nameOrig : buff;
#elif xCOMPILER_MINGW || xCOMPILER_GNUC
    int_t status {- 1};

    char *buff = abi::__cxa_demangle(a_nameOrig, nullptr, nullptr, &status);
    className = (buff == nullptr || status != 0) ? a_nameOrig : buff;

    Utils::bufferFreeT(buff);
#else
    className = a_nameOrig;
#endif

    sRv = xA2T(className);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
