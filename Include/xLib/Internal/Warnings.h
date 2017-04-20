/**
 * \file   Warnings.h
 * \brief  warnings on/off
 */


#pragma once

#if   xCOMPILER_MINGW
    // off
#elif xCOMPILER_MS
    // off
    #pragma warning(disable: 4996) // function or variable may be unsafe (deprecated)
    #pragma warning(disable: 4355) // 'this' : used in base member initializer list
    #pragma warning(disable: 4101) // 'e' : unreferenced local variable
#elif xCOMPILER_CODEGEAR
    // off
    #pragma option -w-8027  // function not expanded inline
    #pragma option -w-8057  // parameter is never used
    #pragma option -w-8058  // cannot create pre-compiled header: initialized data in header
    #pragma option -w-8004  // is assigned a value that is never used
    #pragma option -w-8008  // Condition is always true
#elif xCOMPILER_CLANG
    // off
#elif xCOMPILER_GNUC
    // off
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#else
    #error Unknown complier
#endif
