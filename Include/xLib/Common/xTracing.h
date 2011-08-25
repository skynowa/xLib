/**
 * \file  xTracing.h
 * \brief compile time tracing
 */


#ifndef xLib_Common_xTracingH
#define xLib_Common_xTracingH
//---------------------------------------------------------------------------
#if xIS_COMPILE_TIME_TRACING
    //--------------------------------------------------
    //OS family
    #if defined(xOS_WIN)
        #pragma message("xLib: xOS_WIN")
    #elif defined(xOS_LINUX)
        #pragma message("xLib: xOS_LINUX")
    #elif defined(xOS_FREEBSD)
        #pragma message("xLib: xOS_FREEBSD")
    #else
        #pragma message("xLib: unsupported OS")
    #endif

    //--------------------------------------------------
    //OS architecture
    #if defined(xARCHITECTURE_32BIT)
        #pragma message("xLib: xARCHITECTURE_32BIT")
    #elif defined(xARCHITECTURE_64BIT)
        #pragma message("xLib: xARCHITECTURE_64BIT")
    #else
        #pragma message("xLib: unsupported architectures")
    #endif

    //--------------------------------------------------
    //Compilers
    #if defined(xCOMPILER_MINGW32)
        #pragma message("xLib: xCOMPILER_MINGW32")
    #elif defined(xCOMPILER_MS)
        #pragma message("xLib: xCOMPILER_MS")
    #elif defined(xCOMPILER_CODEGEAR)
        #pragma message("xLib: xCOMPILER_CODEGEAR")
    #elif defined(xCOMPILER_INTEL)
        #pragma message("xLib: xCOMPILER_INTEL")
    #elif defined(xCOMPILER_GNUC)
        #pragma message("xLib: xCOMPILER_GNUC")
    #else
        #pragma message("xLib: unsupported compiler")
    #endif

    //--------------------------------------------------
    //unicode, ansi
    #if defined(xUNICODE)
        #pragma message("xLib: xUNICODE")
    #else
        #pragma message("xLib: xANSI")
    #endif
#endif
//---------------------------------------------------------------------------
#endif //xLib_Common_xTracingH
