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
            // n/a
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

namespace xl
{
//-------------------------------------------------------------------------------------------------
#if   xCOMPILER_MS
    #ifdef xUNICODE
        #define DBGHELP_TRANSLATE_TCHAR 1
    #endif

    #include <Dbghelp.h>
    #pragma comment(lib, "dbghelp.lib")
#elif xCOMPILER_GNUC || xCOMPILER_MINGW
    #include <cxxabi.h>
#else
	#error xLib: unsupported compiler
#endif

std::string
demangleName(
	const char *a_nameRaw
)
{
	if (a_nameRaw == nullptr) {
		return {};
	}

    std::string sRv;

#if   xCOMPILER_MS
    constexpr DWORD buffSize {1024};
    char            buff[buffSize + 1] {};
    const     DWORD flags {UNDNAME_COMPLETE}; // Enable full undecoration

    DWORD dwRv = ::UnDecorateSymbolName(a_nameRaw, buff, buffSize, flags);
    sRv = (dwRv != 0UL) ? a_nameRaw : buff;
#elif xCOMPILER_MINGW || xCOMPILER_GNUC
    int status {- 1};

    char *buff = abi::__cxa_demangle(a_nameRaw, nullptr, nullptr, &status);
    sRv = (buff == nullptr || status != 0) ? a_nameRaw : buff;

    if (buff != nullptr) {
        std::free(buff); buff = nullptr;
    }
#else
    sRv = a_nameRaw;
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
} // ns xl
