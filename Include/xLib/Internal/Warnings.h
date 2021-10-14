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
	#pragma warning(disable: 4312) // 'type cast': conversion from 'xl::int_t' to 'T' of greater size
#elif xCOMPILER_CLANG
    // off
#elif xCOMPILER_GNUC
    // off
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#else
    #error Unknown complier
#endif
