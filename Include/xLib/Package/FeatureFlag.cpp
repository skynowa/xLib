/**
 * \file  FeatureFlag.cpp
 * \brief Feature flag / toggle
 */


#include "FeatureFlag.h"

#if   xENV_WIN
    #include "Platform/Win/FeatureFlag_win.inl"
#elif xENV_UNIX
    // #include "Platform/Unix/FeatureFlag_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/FeatureFlag_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/FeatureFlag_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Apple/FeatureFlag_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xl, package)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
FeatureFlag::FeatureFlag()
{
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
FeatureFlag::~FeatureFlag()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
